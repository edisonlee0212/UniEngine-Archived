#include "pch.h"
#include "TransformSystem.h"
using namespace UniEngine;

UniEngine::TransformSystem::TransformSystem()
{

}

void UniEngine::TransformSystem::OnCreate()
{
	Enable();
}

void UniEngine::TransformSystem::OnDestroy()
{
	Disable();
}



void UniEngine::TransformSystem::Update()
{
	auto entities = EntityManager::GetAllEntitiesUnsafe();
	for (auto i : *entities) {
		if (i.IsDeleted()) continue;
		if (EntityManager::GetParent(i).IsNull()) {
			LocalToWorld ltw = LocalToWorld();
			auto p = EntityManager::GetComponentData<Position>(i).value;
			auto r = EntityManager::GetComponentData<Rotation>(i).value;
			auto s = EntityManager::GetComponentData<Scale>(i).value;
			ltw.value = glm::scale(glm::translate(glm::mat4_cast(r), p), s);
			EntityManager::SetComponentData<LocalToWorld>(i, ltw);
		}
		else {
			LocalToParent ltp = LocalToParent();
			auto lp = EntityManager::GetComponentData<LocalPosition>(i).value;
			auto lr = EntityManager::GetComponentData<LocalRotation>(i).value;
			auto ls = EntityManager::GetComponentData<LocalScale>(i).value;
			ltp.value = glm::scale(glm::translate(glm::mat4_cast(lr), lp), ls);
			EntityManager::SetComponentData<LocalToParent>(i, ltp);

		}
	}
}
