#pragma once
#include "UniEngineAPI.h"
#include "Singleton.h"
#include "ThreadPool.h"
namespace UniEngine
{
	class UNIENGINE_API JobManager final : public Singleton<JobManager>
	{
		ThreadPool _PrimaryWorkers;
		ThreadPool _SecondaryWorkers;
	public:
		static void ResizePrimaryWorkers(int size);
		static void ResizeSecondaryWorkers(int size);
		static ThreadPool& PrimaryWorkers();
		static ThreadPool& SecondaryWorkers();
	};
}
