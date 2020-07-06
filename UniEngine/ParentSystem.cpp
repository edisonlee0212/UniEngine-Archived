#include "pch.h"
#include "ParentSystem.h"

void UniEngine::ParentSystem::CalculateLTW(LocalToWorld pltw, Entity entity)
{
	for (auto i : EntityManager::GetChildren(entity)) {
		auto ltp = EntityManager::GetComponentData<LocalToParent>(i);
		LocalToWorld ltw;
		ltw.value = pltw.value * ltp.value;
		EntityManager::SetComponentData<LocalToWorld>(entity, ltw);
		CalculateLTW(ltw, i);
	}
}

void UniEngine::ParentSystem::Update()
{
	auto entities = EntityManager::GetAllEntitiesUnsafe();
	for (auto i : *entities) {
		if (!i.IsDeleted() && EntityManager::GetParent(i).IsNull()) {
			CalculateLTW(EntityManager::GetComponentData<LocalToWorld>(i), i);
		}
	}
}
