#pragma once
#include "CoreAPI.h"

//From https://github.com/vit-vit/CTPL/blob/master/ctpl_stl.h

// thread pool to run user's functors with signature
//      ret func(int id, other_params)
// where id is the index of the thread that runs the functor
// ret is some return type


namespace UniEngine {

    namespace detail {
        template <typename T>
        class ThreadQueue {
        public:
            bool push(T const& value) {
                std::unique_lock<std::mutex> lock(this->mutex);
                this->q.push(value);
                return true;
            }
            // deletes the retrieved element, do not use for non integral types
            bool pop(T& v) {
                std::unique_lock<std::mutex> lock(this->mutex);
                if (this->q.empty())
                    return false;
                v = this->q.front();
                this->q.pop();
                return true;
            }
            bool empty() {
                std::unique_lock<std::mutex> lock(this->mutex);
                return this->q.empty();
            }
        private:
            std::queue<T> q;
            std::mutex mutex;
        };
    }

    class ThreadPool {

    public:

        ThreadPool() { this->Init(); }
        ThreadPool(int nThreads) { this->Init(); this->Resize(nThreads); }

        // the destructor waits for all the functions in the queue to be finished
        ~ThreadPool() {
            this->FinishAll(true);
        }

        // get the number of running threads in the pool
        int Size() { return static_cast<int>(this->_Threads.size()); }

        // number of idle threads
        int IdleAmount() { return this->_WaitingThreadAmount; }
        std::thread& GetThread(int i) { return *this->_Threads[i]; }

        // change the number of threads in the pool
        // should be called from one thread, otherwise be careful to not interleave, also with this->stop()
        // nThreads must be >= 0
        void Resize(int nThreads) {
            if (!this->_IsStop && !this->_IsDone) {
                int oldNThreads = static_cast<int>(this->_Threads.size());
                if (oldNThreads <= nThreads) {  // if the number of threads is increased
                    this->_Threads.resize(nThreads);
                    this->_Flags.resize(nThreads);

                    for (int i = oldNThreads; i < nThreads; ++i) {
                        this->_Flags[i] = std::make_shared<std::atomic<bool>>(false);
                        this->SetThread(i);
                    }
                }
                else {  // the number of threads is decreased
                    for (int i = oldNThreads - 1; i >= nThreads; --i) {
                        *this->_Flags[i] = true;  // this thread will finish
                        this->_Threads[i]->detach();
                    }
                    {
                        // stop the detached threads that were waiting
                        std::unique_lock<std::mutex> lock(this->_Mutex);
                        this->_ThreadPoolCondition.notify_all();
                    }
                    this->_Threads.resize(nThreads);  // safe to delete because the threads are detached
                    this->_Flags.resize(nThreads);  // safe to delete because the threads have copies of shared_ptr of the flags, not originals
                }
            }
        }

        // empty the queue
        void ClearQueue() {
            std::function<void(int id)>* _f;
            while (this->_ThreadPool.pop(_f))
                delete _f; // empty the queue
        }

        // pops a functional wrapper to the original function
        std::function<void(int)> Pop() {
            std::function<void(int id)>* _f = nullptr;
            this->_ThreadPool.pop(_f);
            std::unique_ptr<std::function<void(int id)>> func(_f); // at return, delete the function even if an exception occurred
            std::function<void(int)> f;
            if (_f)
                f = *_f;
            return f;
        }

        // wait for all computing threads to finish and stop all threads
        // may be called asynchronously to not pause the calling thread while waiting
        // if isWait == true, all the functions in the queue are run, otherwise the queue is cleared without running the functions
        void FinishAll(bool isWait = false) {
            if (!isWait) {
                if (this->_IsStop)
                    return;
                this->_IsStop = true;
                for (int i = 0, n = this->Size(); i < n; ++i) {
                    *this->_Flags[i] = true;  // command the threads to stop
                }
                this->ClearQueue();  // empty the queue
            }
            else {
                if (this->_IsDone || this->_IsStop)
                    return;
                this->_IsDone = true;  // give the waiting threads a command to finish
            }
            {
                std::unique_lock<std::mutex> lock(this->_Mutex);
                this->_ThreadPoolCondition.notify_all();  // stop all waiting threads
            }
            for (int i = 0; i < static_cast<int>(this->_Threads.size()); ++i) {  // wait for the computing threads to finish
                if (this->_Threads[i]->joinable())
                    this->_Threads[i]->join();
            }
            // if there were no threads in the pool but some functors in the queue, the functors are not deleted by the threads
            // therefore delete them here
            this->ClearQueue();
            this->_Threads.clear();
            this->_Flags.clear();
        }

        template<typename F, typename... Rest>
        auto Push(F&& f, Rest&&... rest) ->std::future<decltype(f(0, rest...))> {
            auto pck = std::make_shared<std::packaged_task<decltype(f(0, rest...))(int)>>(
                std::bind(std::forward<F>(f), std::placeholders::_1, std::forward<Rest>(rest)...)
                );
            auto _f = new std::function<void(int id)>([pck](int id) {
                (*pck)(id);
                });
            this->_ThreadPool.push(_f);
            std::unique_lock<std::mutex> lock(this->_Mutex);
            this->_ThreadPoolCondition.notify_one();
            return pck->get_future();
        }

        // run the user's function that excepts argument int - id of the running thread. returned value is templatized
        // operator returns std::future, where the user can get the result and rethrow the catched exceptins
        template<typename F>
        auto Push(F&& f) ->std::future<decltype(f(0))> {
            auto pck = std::make_shared<std::packaged_task<decltype(f(0))(int)>>(std::forward<F>(f));
            auto _f = new std::function<void(int id)>([pck](int id) {
                (*pck)(id);
                });
            this->_ThreadPool.push(_f);
            std::unique_lock<std::mutex> lock(this->_Mutex);
            this->_ThreadPoolCondition.notify_one();
            return pck->get_future();
        }


    private:

        // deleted
        ThreadPool(const ThreadPool&);// = delete;
        ThreadPool(ThreadPool&&);// = delete;
        ThreadPool& operator=(const ThreadPool&);// = delete;
        ThreadPool& operator=(ThreadPool&&);// = delete;

        void SetThread(int i) {
            std::shared_ptr<std::atomic<bool>> flag(this->_Flags[i]); // a copy of the shared ptr to the flag
            auto f = [this, i, flag/* a copy of the shared ptr to the flag */]() {
                std::atomic<bool>& _flag = *flag;
                std::function<void(int id)>* _f;
                bool isPop = this->_ThreadPool.pop(_f);
                while (true) {
                    while (isPop) {  // if there is anything in the queue
                        std::unique_ptr<std::function<void(int id)>> func(_f); // at return, delete the function even if an exception occurred
                        (*_f)(i);
                        if (_flag)
                            return;  // the thread is wanted to stop, return even if the queue is not empty yet
                        else
                            isPop = this->_ThreadPool.pop(_f);
                    }
                    // the queue is empty here, wait for the next command
                    std::unique_lock<std::mutex> lock(this->_Mutex);
                    ++this->_WaitingThreadAmount;
                    this->_ThreadPoolCondition.wait(lock, [this, &_f, &isPop, &_flag]() { isPop = this->_ThreadPool.pop(_f); return isPop || this->_IsDone || _flag; });
                    --this->_WaitingThreadAmount;
                    if (!isPop)
                        return;  // if the queue is empty and this->isDone == true or *flag then return
                }
            };
            this->_Threads[i].reset(new std::thread(f)); // compiler may not support std::make_unique()
        }

        void Init() { this->_WaitingThreadAmount = 0; this->_IsStop = false; this->_IsDone = false; }

        std::vector<std::unique_ptr<std::thread>> _Threads;
        std::vector<std::shared_ptr<std::atomic<bool>>> _Flags;
        detail::ThreadQueue<std::function<void(int id)>*> _ThreadPool;
        std::atomic<bool> _IsDone;
        std::atomic<bool> _IsStop;
        std::atomic<int> _WaitingThreadAmount;  // how many threads are waiting

        std::mutex _Mutex;
        std::condition_variable _ThreadPoolCondition;
    };

}