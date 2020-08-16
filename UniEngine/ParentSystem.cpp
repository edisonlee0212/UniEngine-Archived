#include "pch.h"
#include "ParentSystem.h"
#include "UniEngine.h"
void UniEngine::ParentSystem::OnCreate()
{
	_CachedParentHierarchies = std::vector<std::pair<Entity, ChildInfo>>();
	Enable();
}

void UniEngine::ParentSystem::OnDestroy()
{
	Disable();
}

void UniEngine::ParentSystem::CalculateLTWRecursive(LocalToWorld pltw, Entity entity)
{
	/*
	Here we have 2 ways to deal with children, you can use lambda function or you can get children
	and maniputale them directly. The method I'm using here, which is the second one,
	is faster and I don't know why...
	*/

	/*
	EntityManager::ForEachChild(entity, [pltw, this](Entity i) {
		auto ltp = EntityManager::GetComponentData<LocalToParent>(i);
		LocalToWorld ltw;
		ltw.value = pltw.value * ltp.value;
		EntityManager::SetComponentData<LocalToWorld>(i, ltw);
		CalculateLTW(ltw, i);
		});
	*/
	for (const auto& i : EntityManager::GetChildren(entity)) {
		auto ltp = EntityManager::GetComponentData<LocalToParent>(i);
		LocalToWorld ltw;
		ltw.value = pltw.value * ltp.value;
		EntityManager::SetComponentData<LocalToWorld>(i, ltw);
		CalculateLTWRecursive(ltw, i);
	}
}

void UniEngine::ParentSystem::CollectHierarchy(std::vector<std::pair<Entity, ChildInfo>>* container, Entity entity)
{
	auto children = EntityManager::GetChildren(entity);
	auto initialSize = container->size();
	for (const auto& i : children) {
		if (EntityManager::HasComponentData<LocalToWorld>(i) && EntityManager::HasComponentData<LocalToParent>(i) && EntityManager::HasComponentData<LocalToWorld>(entity)) {
			ChildInfo info;
			info.Child = i;
			info.LastLTP = EntityManager::GetComponentData<LocalToParent>(i);
			info.LastPLTW = EntityManager::GetComponentData<LocalToWorld>(entity);
			container->push_back(std::make_pair(entity, info));
			LocalToWorld ltw;
			ltw.value = info.LastPLTW.value * info.LastLTP.value;
			EntityManager::SetComponentData<LocalToWorld>(i, ltw);
		}
	}
	for (int i = initialSize; i < container->size(); i++) {
		Entity target = container->at(i).second.Child;
		for (const auto& child : EntityManager::GetChildren(target)) {
			if (EntityManager::HasComponentData<LocalToWorld>(child) && EntityManager::HasComponentData<LocalToParent>(child) && EntityManager::HasComponentData<LocalToWorld>(target)) {
				ChildInfo info;
				info.Child = child;
				info.LastLTP = EntityManager::GetComponentData<LocalToParent>(child);
				info.LastPLTW = EntityManager::GetComponentData<LocalToWorld>(target);
				container->push_back(std::make_pair(target, info));
				LocalToWorld ltw;
				ltw.value = info.LastPLTW.value * info.LastLTP.value;
				EntityManager::SetComponentData<LocalToWorld>(child, ltw);
			}
		}
	}
}

void UniEngine::ParentSystem::Update()
{
	/*
	std::vector<std::shared_future<void>> futures;
	auto threadPool = _ThreadPool;
	EntityManager::ForAllRootParent([&futures, &threadPool, this](int i, Entity rootParent) {
		LocalToWorld ltw = EntityManager::GetComponentData<LocalToWorld>(rootParent);
		futures.push_back(threadPool->Push([ltw, rootParent, this](int id) {
			CalculateLTWRecursive(ltw, rootParent);
			}).share());
		});
	for (auto i : futures) i.wait();
	*/

	if (EntityManager::GetParentHierarchyVersion() == _CurrentStoredHierarchyVersion) {
		std::vector<std::shared_future<void>> futures;
		auto list = &_CachedParentHierarchies;
		auto threadSize = _ThreadPool->Size();
		size_t capacity = _CachedParentHierarchies.size() / threadSize;
		size_t reminder = _CachedParentHierarchies.size() % threadSize;
		for (size_t i = 0; i < threadSize; i++) {
			futures.push_back(_ThreadPool->Push([&list, i, capacity](int id)
				{
					for (size_t j = 0; j < capacity; j++) {
						size_t index = capacity * i + j;
						auto info = list->at(index);
						auto pltw = EntityManager::GetComponentData<LocalToWorld>(info.first);
						auto ltp = EntityManager::GetComponentData<LocalToParent>(info.second.Child);
						if (info.second.LastPLTW == pltw && info.second.LastLTP == ltp) continue;
						info.second.LastPLTW = pltw;
						info.second.LastLTP = ltp;
						list->at(index) = info;
						LocalToWorld ltw;
						ltw.value = pltw.value * ltp.value;
						EntityManager::SetComponentData<LocalToWorld>(info.second.Child, ltw);
					}
				}
			).share());
		}
		for (size_t i = 0; i < reminder; i++) {
			size_t index = capacity * threadSize + i;
			auto info = list->at(index);
			auto pltw = EntityManager::GetComponentData<LocalToWorld>(info.first);
			auto ltp = EntityManager::GetComponentData<LocalToParent>(info.second.Child);
			if (info.second.LastPLTW == pltw && info.second.LastLTP == ltp) continue;
			info.second.LastPLTW = pltw;
			info.second.LastLTP = ltp;
			list->at(index) = info;
			LocalToWorld ltw;
			ltw.value = pltw.value * ltp.value;
			EntityManager::SetComponentData<LocalToWorld>(info.second.Child, ltw);
		}
		for (auto i : futures) i.wait();
	}
	else {
		_CachedParentHierarchies.clear();
		EntityManager::ForAllRootParent([this](int i, Entity rootParent) {
			CollectHierarchy(&_CachedParentHierarchies, rootParent);
			});
		_CurrentStoredHierarchyVersion = EntityManager::GetParentHierarchyVersion();
	}
}
