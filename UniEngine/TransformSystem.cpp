#include "pch.h"
#include "TransformSystem.h"
using namespace UniEngine;
glm::mat4 UniEngine::TransformSystem::TRS(glm::vec3 translation, glm::quat rotation, glm::vec3 scale) {
	return glm::scale(glm::translate(glm::mat4_cast(rotation), translation), scale);
}

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
	for (auto i : *EntityManager::GetAllEntities()) {
		LocalToWorld ltw = LocalToWorld();
		auto p = EntityManager::GetComponentData<Position>(i.Entity).value;
		auto r = EntityManager::GetComponentData<Rotation>(i.Entity).value;
		auto s = EntityManager::GetComponentData<Scale>(i.Entity).value;
		ltw.value = TRS(p, r, s);
		EntityManager::SetComponentData<LocalToWorld>(i.Entity, ltw);
	}

	
}
