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
		if (EntityManager::GetParent(i).IsNull() && EntityManager::HasComponentData<LocalToWorld>(i)) {
			LocalToWorld ltw = LocalToWorld();
			glm::vec3 p;
			glm::quat r;
			glm::vec3 s;
			glm::mat4 translation = glm::identity<glm::mat4>();
			glm::mat4 rotation = glm::identity<glm::mat4>();
			glm::mat4 scale = glm::identity<glm::mat4>();
			if (EntityManager::HasComponentData<Position>(i)) {
				translation = glm::translate(glm::mat4(1.0f), EntityManager::GetComponentData<Position>(i).value);
			}
			if (EntityManager::HasComponentData<Rotation>(i)) {
				rotation = glm::mat4_cast(EntityManager::GetComponentData<Rotation>(i).value);
			}
			if (EntityManager::HasComponentData<Scale>(i)) {
				scale = glm::scale(EntityManager::GetComponentData<Scale>(i).value);
			}
			ltw.value = translation * rotation * scale;
			EntityManager::SetComponentData<LocalToWorld>(i, ltw);
		}
		else if(!EntityManager::GetParent(i).IsNull() && EntityManager::HasComponentData<LocalToParent>(i)) {
			LocalToParent ltp = LocalToParent();
			glm::vec3 lp;
			glm::quat lr;
			glm::vec3 ls;

			glm::mat4 translation = glm::identity<glm::mat4>();
			glm::mat4 rotation = glm::identity<glm::mat4>();
			glm::mat4 scale = glm::identity<glm::mat4>();
			if (EntityManager::HasComponentData<LocalPosition>(i)) {
				translation = glm::translate(glm::mat4(1.0f), EntityManager::GetComponentData<LocalPosition>(i).value);
			}
			if (EntityManager::HasComponentData<LocalRotation>(i)) {
				rotation = glm::mat4_cast(EntityManager::GetComponentData<LocalRotation>(i).value);
			}
			if (EntityManager::HasComponentData<LocalScale>(i)) {
				scale = glm::scale(EntityManager::GetComponentData<LocalScale>(i).value);
			}
			ltp.value = translation * rotation * scale;
			EntityManager::SetComponentData<LocalToParent>(i, ltp);
		}
	}
}
