#pragma once
#include "UniEngineAPI.h"
#include "Singleton.h"
#include "ThreadPool.h"
namespace UniEngine
{
	class UNIENGINE_API JobManager final : public Singleton<JobManager>
	{
		ThreadPool m_primaryWorkers;
		ThreadPool m_secondaryWorkers;
	public:
		static void ResizePrimaryWorkers(int size);
		static void ResizeSecondaryWorkers(int size);
		static ThreadPool& PrimaryWorkers();
		static ThreadPool& SecondaryWorkers();
	};
}
