#include "pch.h"
#include "JobManager.h"
using namespace UniEngine;

ThreadPool JobManager::_ThreadPool;

inline ThreadPool& JobManager::GetThreadPool()
{
	return GetInstance()._ThreadPool;
}

inline void JobManager::Resize(int value)
{
	return GetInstance()._ThreadPool.Resize(value);
}