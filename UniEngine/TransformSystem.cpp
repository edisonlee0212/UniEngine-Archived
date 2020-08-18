#include "pch.h"
#include "TransformSystem.h"
using namespace UniEngine;

void UniEngine::TransformSystem::OnCreate()
{
	_CachedParentHierarchies = std::vector<std::pair<Entity, ChildInfo>>();

	_LP = EntityManager::CreateEntityQuery();
	EntityManager::SetEntityQueryAllFilters(_LP, LocalToParent(), LocalTranslation());
	EntityManager::SetEntityQueryNoneFilters(_LP, LocalRotation(), LocalScale());
	_LPR = EntityManager::CreateEntityQuery();
	EntityManager::SetEntityQueryAllFilters(_LPR, LocalToParent(), LocalTranslation(), LocalRotation());
	EntityManager::SetEntityQueryNoneFilters(_LPR, LocalScale());
	_LPS = EntityManager::CreateEntityQuery();
	EntityManager::SetEntityQueryAllFilters(_LPS, LocalToParent(), LocalTranslation(), LocalScale());
	EntityManager::SetEntityQueryNoneFilters(_LPS, LocalRotation());
	_LPRS = EntityManager::CreateEntityQuery();
	EntityManager::SetEntityQueryAllFilters(_LPRS, LocalToParent(), LocalTranslation(), LocalRotation(), LocalScale());
	_LR = EntityManager::CreateEntityQuery();
	EntityManager::SetEntityQueryAllFilters(_LR, LocalToParent(), LocalRotation());
	EntityManager::SetEntityQueryNoneFilters(_LR, LocalTranslation(), LocalScale());
	_LRS = EntityManager::CreateEntityQuery();
	EntityManager::SetEntityQueryAllFilters(_LRS, LocalToParent(), LocalRotation(), LocalScale());
	EntityManager::SetEntityQueryNoneFilters(_LRS, LocalTranslation());
	_LS = EntityManager::CreateEntityQuery();
	EntityManager::SetEntityQueryAllFilters(_LS, LocalToParent(), LocalScale());
	EntityManager::SetEntityQueryNoneFilters(_LS, LocalTranslation(), LocalRotation());

	_P = EntityManager::CreateEntityQuery();
	EntityManager::SetEntityQueryAllFilters(_P, LocalToWorld(), Translation());
	EntityManager::SetEntityQueryNoneFilters(_P, Rotation(), Scale());
	_PR = EntityManager::CreateEntityQuery();
	EntityManager::SetEntityQueryAllFilters(_PR, LocalToWorld(), Translation(), Rotation());
	EntityManager::SetEntityQueryNoneFilters(_PR, Scale());
	_PS = EntityManager::CreateEntityQuery();
	EntityManager::SetEntityQueryAllFilters(_PS, LocalToWorld(), Translation(), Scale());
	EntityManager::SetEntityQueryNoneFilters(_PS, Rotation());
	_PRS = EntityManager::CreateEntityQuery();
	EntityManager::SetEntityQueryAllFilters(_PRS, LocalToWorld(), Translation(), Rotation(), Scale());
	_R = EntityManager::CreateEntityQuery();
	EntityManager::SetEntityQueryAllFilters(_R, LocalToWorld(), Rotation());
	EntityManager::SetEntityQueryNoneFilters(_R, Translation(), Scale());
	_RS = EntityManager::CreateEntityQuery();
	EntityManager::SetEntityQueryAllFilters(_RS, LocalToWorld(), Rotation(), Scale());
	EntityManager::SetEntityQueryNoneFilters(_RS, Translation());
	_S = EntityManager::CreateEntityQuery();
	EntityManager::SetEntityQueryAllFilters(_S, LocalToWorld(), Scale());
	EntityManager::SetEntityQueryNoneFilters(_S, Translation(), Rotation());

	Enable();
}

void UniEngine::TransformSystem::OnDestroy()
{
	Disable();
}

void UniEngine::TransformSystem::Update()
{
	EntityManager::ForEach<LocalToParent, LocalTranslation>(_LP, [](int i, Entity entity, LocalToParent* ltp, LocalTranslation* lp) {
		ltp->Value = glm::translate(glm::mat4(1.0f), lp->Value);
		});
	EntityManager::ForEach<LocalToParent, LocalTranslation, LocalRotation>(_LPR, [](int i, Entity entity, LocalToParent* ltp, LocalTranslation* lp, LocalRotation* lr) {
		ltp->Value = glm::translate(glm::mat4(1.0f), lp->Value) * glm::mat4_cast(lr->Value);
		});
	EntityManager::ForEach<LocalToParent, LocalTranslation, LocalScale>(_LPS, [](int i, Entity entity, LocalToParent* ltp, LocalTranslation* lp, LocalScale* ls) {
		ltp->Value = glm::translate(glm::mat4(1.0f), lp->Value) * glm::scale(ls->Value);
		});
	EntityManager::ForEach<LocalToParent, LocalTranslation, LocalRotation, LocalScale>(_LPRS, [](int i, Entity entity, LocalToParent* ltp, LocalTranslation* lp, LocalRotation* lr, LocalScale* ls) {
		ltp->Value = glm::translate(glm::mat4(1.0f), lp->Value) * glm::mat4_cast(lr->Value) * glm::scale(ls->Value);
		});
	EntityManager::ForEach<LocalToParent, LocalRotation>(_LR, [](int i, Entity entity, LocalToParent* ltp, LocalRotation* lr) {
		ltp->Value = glm::mat4_cast(lr->Value);
		});
	EntityManager::ForEach<LocalToParent, LocalRotation, LocalScale>(_LRS, [](int i, Entity entity, LocalToParent* ltp, LocalRotation* lr, LocalScale* ls) {
		ltp->Value = glm::mat4_cast(lr->Value) * glm::scale(ls->Value);
		});
	EntityManager::ForEach<LocalToParent, LocalScale>(_LS, [](int i, Entity entity, LocalToParent* ltp, LocalScale* ls) {
		ltp->Value = glm::scale(ls->Value);
		});

	EntityManager::ForEach<LocalToWorld, Translation>(_P, [](int i, Entity entity, LocalToWorld* ltw, Translation* lp) {
		ltw->Value = glm::translate(glm::mat4(1.0f), lp->Value);
		});
	EntityManager::ForEach<LocalToWorld, Translation, Rotation>(_PR, [](int i, Entity entity, LocalToWorld* ltw, Translation* lp, Rotation* lr) {
		ltw->Value = glm::translate(glm::mat4(1.0f), lp->Value) * glm::mat4_cast(lr->Value);
		});
	EntityManager::ForEach<LocalToWorld, Translation, Scale>(_PS, [](int i, Entity entity, LocalToWorld* ltw, Translation* lp, Scale* ls) {
		ltw->Value = glm::translate(glm::mat4(1.0f), lp->Value) * glm::scale(ls->Value);
		});
	EntityManager::ForEach<LocalToWorld, Translation, Rotation, Scale>(_PRS, [](int i, Entity entity, LocalToWorld* ltw, Translation* lp, Rotation* lr, Scale* ls) {
		ltw->Value = glm::translate(glm::mat4(1.0f), lp->Value) * glm::mat4_cast(lr->Value) * glm::scale(ls->Value);
		});
	EntityManager::ForEach<LocalToWorld, Rotation>(_R, [](int i, Entity entity, LocalToWorld* ltw, Rotation* lr) {
		ltw->Value = glm::mat4_cast(lr->Value);
		});
	EntityManager::ForEach<LocalToWorld, Rotation, Scale>(_RS, [](int i, Entity entity, LocalToWorld* ltw, Rotation* lr, Scale* ls) {
		ltw->Value = glm::mat4_cast(lr->Value) * glm::scale(ls->Value);
		});
	EntityManager::ForEach<LocalToWorld, Scale>(_S, [](int i, Entity entity, LocalToWorld* ltw, Scale* ls) {
		ltw->Value = glm::scale(ls->Value);
		});

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
						const auto& info = list->at(index);
						auto pltw = EntityManager::GetComponentData<LocalToWorld>(info.first);
						auto ltp = EntityManager::GetComponentData<LocalToParent>(info.second.Child);
						//if (info.second.LastPLTW == pltw && info.second.LastLTP == ltp) continue;
						//info.second.LastPLTW = pltw;
						//info.second.LastLTP = ltp;
						//list->at(index) = info;
						LocalToWorld ltw;
						ltw.Value = pltw.Value * ltp.Value;
						EntityManager::SetComponentData<LocalToWorld>(info.second.Child, ltw);
					}
				}
			).share());
		}
		for (size_t i = 0; i < reminder; i++) {
			size_t index = capacity * threadSize + i;
			const auto& info = list->at(index);
			auto pltw = EntityManager::GetComponentData<LocalToWorld>(info.first);
			auto ltp = EntityManager::GetComponentData<LocalToParent>(info.second.Child);
			//if (info.second.LastPLTW == pltw && info.second.LastLTP == ltp) continue;
			//info.second.LastPLTW = pltw;
			//info.second.LastLTP = ltp;
			//list->at(index) = info;
			LocalToWorld ltw;
			ltw.Value = pltw.Value * ltp.Value;
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

void UniEngine::TransformSystem::CalculateLTWRecursive(LocalToWorld pltw, Entity entity)
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
		ltw.Value = pltw.Value * ltp.Value;
		EntityManager::SetComponentData<LocalToWorld>(i, ltw);
		CalculateLTWRecursive(ltw, i);
	}
}

void UniEngine::TransformSystem::CollectHierarchy(std::vector<std::pair<Entity, ChildInfo>>* container, Entity entity)
{
	auto children = EntityManager::GetChildren(entity);
	auto initialSize = container->size();
	for (const auto& i : children) {
		if (EntityManager::HasComponentData<LocalToWorld>(i) && EntityManager::HasComponentData<LocalToParent>(i) && EntityManager::HasComponentData<LocalToWorld>(entity)) {
			ChildInfo info;
			info.Child = i;
			auto ltp = EntityManager::GetComponentData<LocalToParent>(i);
			auto pltw = EntityManager::GetComponentData<LocalToWorld>(entity);
			container->push_back(std::make_pair(entity, info));
			LocalToWorld ltw;
			ltw.Value = pltw.Value * ltp.Value;
			EntityManager::SetComponentData<LocalToWorld>(i, ltw);
		}
	}
	for (int i = initialSize; i < container->size(); i++) {
		Entity target = container->at(i).second.Child;
		for (const auto& child : EntityManager::GetChildren(target)) {
			if (EntityManager::HasComponentData<LocalToWorld>(child) && EntityManager::HasComponentData<LocalToParent>(child) && EntityManager::HasComponentData<LocalToWorld>(target)) {
				ChildInfo info;
				info.Child = child;
				auto ltp = EntityManager::GetComponentData<LocalToParent>(child);
				auto pltw = EntityManager::GetComponentData<LocalToWorld>(target);
				container->push_back(std::make_pair(target, info));
				LocalToWorld ltw;
				ltw.Value = pltw.Value * ltp.Value;
				EntityManager::SetComponentData<LocalToWorld>(child, ltw);
			}
		}
	}
}