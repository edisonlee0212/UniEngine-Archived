#pragma once
#include "UniEngineAPI.h"
#include "Singleton.h"
#include "ThreadPool.h"
namespace UniEngine
{
	class UNIENGINE_API JobManager final : public Singleton<JobManager>
	{
		static ThreadPool _ThreadPool;
	public:
		static ThreadPool& GetThreadPool();
		static void Resize(int value);
	};
}
