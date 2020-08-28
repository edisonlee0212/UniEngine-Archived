#pragma once
#include <WS2tcpip.h>
#pragma comment (lib, "ws2_32.lib")
#include <string.h>
#include "UniEngine.h"

namespace UniEngine {
	class NetworkSystem :
		public SystemBase
	{
		SOCKET _Socket;//might change to pool of socket in the future
		std::queue<std::string> _LocalSendingQueue;
		std::queue<std::string> _ServerSendingQueue;
		std::queue<std::string> _ServerReadingQueue;
		std::queue<std::string> _LocalReadingQueue;
		std::mutex _ReceivingQueueMutex;
		std::mutex _SendingQueueMutex;

		std::thread* _SendingThread;
		std::thread* _ReceivingThread;

		std::atomic_bool _StopSendingThread;
		std::atomic_bool _StopReceivingThread;

		std::condition_variable _SendingThreadCV;
		std::condition_variable _ReceivingThreadCV;

		void TransferDataToServer();
		void TransferDataToLocal();
	public:
		void OnCreate();
		void OnDestroy() {};
		void Update() {};
		void FixedUpdate();


		/*
		std::queue<std::string> data_queue_local_s;
		std::queue<std::string> data_queue_server_s;
		std::queue<std::string> data_queue_server_r;
		std::queue<std::string> data_queue_local_r;*/
	};
}

