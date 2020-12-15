#include "pch.h"
#include "JobManager.h"
using namespace UniEngine;

ThreadPool JobManager::_ThreadPool;

inline ThreadPool& JobManager::GetThreadPool()
{
	return Get()._ThreadPool;
}

inline void JobManager::Resize(int value)
{
	return Get()._ThreadPool.Resize(value);
}