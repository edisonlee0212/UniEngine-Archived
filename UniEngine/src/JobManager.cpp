#include "pch.h"
#include "JobManager.h"
using namespace UniEngine;


void JobManager::ResizePrimaryWorkers(int size)
{
	GetInstance()._PrimaryWorkers.FinishAll(true);
	GetInstance()._PrimaryWorkers.Resize(size);
}

void JobManager::ResizeSecondaryWorkers(int size)
{
	GetInstance()._SecondaryWorkers.FinishAll(true);
	GetInstance()._SecondaryWorkers.Resize(size);
}

ThreadPool& JobManager::PrimaryWorkers()
{
	return GetInstance()._PrimaryWorkers;
}

ThreadPool& JobManager::SecondaryWorkers()
{
	return GetInstance()._SecondaryWorkers;
}