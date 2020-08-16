#include "pch.h"
#include "ParentSystem.h"
#include "UniEngine.h"
void UniEngine::ParentSystem::OnCreate()
{
	_CachedParentHierarchies = std::vector<std::vector<std::pair<Entity, Entity>>>();
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

void UniEngine::ParentSystem::CollectHierarchy(std::vector<std::pair<Entity, Entity>>* container, Entity entity)
{
	auto children = EntityManager::GetChildren(entity);
	for (const auto& i : children) container->push_back(std::pair<Entity, Entity>(entity, i));
	for (int i = 0; i < container->size(); i++) {
		Entity target = container->at(i).second;
		for (const auto& child : EntityManager::GetChildren(target))
			container->push_back(std::make_pair(target, child));
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

	if (EntityManager::GetParentHierarchyVersion() != _CurrentStoredHierarchyVersion) {
		for (int i = 0; i < _CachedParentHierarchies.size(); i++) {
			_CachedParentHierarchies[i].clear();
		}
		_CachedParentHierarchies.clear();
		EntityManager::ForAllRootParent([this](int i, Entity rootParent) {
			_CachedParentHierarchies.push_back(std::vector<std::pair<Entity, Entity>>());
			CollectHierarchy(&_CachedParentHierarchies.at(i), rootParent);
			});
		_CurrentStoredHierarchyVersion = EntityManager::GetParentHierarchyVersion();
	}

	std::vector<std::shared_future<void>> futures;
	auto lists = &_CachedParentHierarchies;
	for (const auto& list : _CachedParentHierarchies) {
		futures.push_back(_ThreadPool->Push([&list](int id) {
			for (int j = 0; j < list.size(); j++) {
				auto pltw = EntityManager::GetComponentData<LocalToWorld>(list[j].first);
				auto ltp = EntityManager::GetComponentData<LocalToParent>(list[j].second);
				LocalToWorld ltw;
				ltw.value = pltw.value * ltp.value;
				EntityManager::SetComponentData<LocalToWorld>(list[j].second, ltw);
			}
			}).share());
	}
	for (auto i : futures) i.wait();

}
