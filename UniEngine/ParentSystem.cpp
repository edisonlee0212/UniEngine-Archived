#include "pch.h"
#include "ParentSystem.h"

void UniEngine::ParentSystem::OnCreate()
{
	Enable();
}

void UniEngine::ParentSystem::OnDestroy()
{
	Disable();
}

void UniEngine::ParentSystem::CalculateLTW(LocalToWorld pltw, Entity entity)
{
	for (auto i : EntityManager::GetChildren(entity)) {
		if (EntityManager::HasComponentData<LocalToParent>(i)
			&& EntityManager::HasComponentData<LocalToWorld>(i)) {
			auto ltp = EntityManager::GetComponentData<LocalToParent>(i);
			LocalToWorld ltw;
			ltw.value = pltw.value * ltp.value;
			EntityManager::SetComponentData<LocalToWorld>(i, ltw);
			CalculateLTW(ltw, i);
		}
	}
}

void UniEngine::ParentSystem::Update()
{
	for (auto i : *EntityManager::GetParentRootsUnsafe()) {
		if (!i.IsDeleted() && EntityManager::GetParent(i).IsNull() 
			&& EntityManager::HasComponentData<LocalToWorld>(i)) {
			LocalToWorld ltw = EntityManager::GetComponentData<LocalToWorld>(i);
			CalculateLTW(ltw, i);
		}
	}
}
