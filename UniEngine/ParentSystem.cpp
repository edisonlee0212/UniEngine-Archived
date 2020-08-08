#include "pch.h"
#include "ParentSystem.h"
#include "UniEngine.h"
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
		auto ltp = EntityManager::GetComponentData<LocalToParent>(i);
		LocalToWorld ltw;
		ltw.value = pltw.value * ltp.value;
		EntityManager::SetComponentData<LocalToWorld>(i, ltw);
		CalculateLTW(ltw, i);
	}
}

void UniEngine::ParentSystem::Update()
{
	std::vector<std::shared_future<void>> futures;
	for (auto i : *EntityManager::GetParentRootsUnsafe()) {
		if (!i.IsDeleted() && EntityManager::GetParent(i).IsNull()) {
			LocalToWorld ltw = EntityManager::GetComponentData<LocalToWorld>(i);
			futures.push_back(_ThreadPool->Push([ltw, i, this](int id) {
				CalculateLTW(ltw, i);
				}).share());

		}
	}
	for (auto i : futures) i.wait();
}
