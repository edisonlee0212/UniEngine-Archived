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
			unsigned mask = 0;
			mask += EntityManager::HasComponentData<Position>(i) ? 1 : 0;
			mask += EntityManager::HasComponentData<Rotation>(i) ? 2 : 0;
			mask += EntityManager::HasComponentData<Scale>(i) ? 4 : 0;
			glm::vec3 p;
			glm::quat r;
			glm::vec3 s;
			switch (mask)
			{
			case 1:
				p = EntityManager::GetComponentData<Position>(i).value;
				ltw.value = glm::translate(p);
				EntityManager::SetComponentData<LocalToWorld>(i, ltw);
				break;
			case 2:
				r = EntityManager::GetComponentData<Rotation>(i).value;
				ltw.value = glm::mat4_cast(r);
				EntityManager::SetComponentData<LocalToWorld>(i, ltw);
				break;
			case 3:
				p = EntityManager::GetComponentData<Position>(i).value;
				r = EntityManager::GetComponentData<Rotation>(i).value;
				ltw.value = glm::translate(glm::mat4_cast(r), p);
				EntityManager::SetComponentData<LocalToWorld>(i, ltw);
				break;
			case 4:
				s = EntityManager::GetComponentData<Scale>(i).value;
				ltw.value = glm::scale(glm::mat4(1.0f), s);
				EntityManager::SetComponentData<LocalToWorld>(i, ltw);
				break;
			case 5:
				p = EntityManager::GetComponentData<Position>(i).value;
				s = EntityManager::GetComponentData<Scale>(i).value;
				ltw.value = glm::scale(glm::translate(glm::mat4(1.0f), p), s);
				EntityManager::SetComponentData<LocalToWorld>(i, ltw);
				break;
			case 6:
				r = EntityManager::GetComponentData<Rotation>(i).value;
				s = EntityManager::GetComponentData<Scale>(i).value;
				ltw.value = glm::scale(glm::mat4_cast(r), s);
				EntityManager::SetComponentData<LocalToWorld>(i, ltw);
				break;
			case 7:
				p = EntityManager::GetComponentData<Position>(i).value;
				r = EntityManager::GetComponentData<Rotation>(i).value;
				s = EntityManager::GetComponentData<Scale>(i).value;
				ltw.value = glm::scale(glm::translate(glm::mat4_cast(r), p), s);
				EntityManager::SetComponentData<LocalToWorld>(i, ltw);
				break;
			default:
				break;
			}
		}
		else if(!EntityManager::GetParent(i).IsNull() && EntityManager::HasComponentData<LocalToParent>(i)) {
			LocalToParent ltp = LocalToParent();
			unsigned mask = 0;
			mask += EntityManager::HasComponentData<LocalPosition>(i) ? 1 : 0;
			mask += EntityManager::HasComponentData<LocalRotation>(i) ? 2 : 0;
			mask += EntityManager::HasComponentData<LocalScale>(i) ? 4 : 0;

			glm::vec3 lp;
			glm::quat lr;
			glm::vec3 ls;
			switch (mask)
			{
			case 1:
				lp = EntityManager::GetComponentData<LocalPosition>(i).value;
				ltp.value = glm::translate(lp);
				EntityManager::SetComponentData<LocalToParent>(i, ltp);
				break;
			case 2:
				lr = EntityManager::GetComponentData<LocalRotation>(i).value;
				ltp.value = glm::mat4_cast(lr);
				EntityManager::SetComponentData<LocalToParent>(i, ltp);
				break;
			case 3:
				lp = EntityManager::GetComponentData<LocalPosition>(i).value;
				lr = EntityManager::GetComponentData<LocalRotation>(i).value;
				ltp.value = glm::translate(glm::mat4_cast(lr), lp);
				EntityManager::SetComponentData<LocalToParent>(i, ltp);
				break;
			case 4:
				ls = EntityManager::GetComponentData<LocalScale>(i).value;
				ltp.value = glm::scale(glm::mat4(1.0f), ls);
				EntityManager::SetComponentData<LocalToParent>(i, ltp);
				break;
			case 5:
				lp = EntityManager::GetComponentData<LocalPosition>(i).value;
				ls = EntityManager::GetComponentData<LocalScale>(i).value;
				ltp.value = glm::scale(glm::translate(glm::mat4(1.0f), lp), ls);
				EntityManager::SetComponentData<LocalToParent>(i, ltp);
				break;
			case 6:
				lr = EntityManager::GetComponentData<LocalRotation>(i).value;
				ls = EntityManager::GetComponentData<LocalScale>(i).value;
				ltp.value = glm::scale(glm::mat4_cast(lr), ls);
				EntityManager::SetComponentData<LocalToParent>(i, ltp);
				break;
			case 7:
				lp = EntityManager::GetComponentData<LocalPosition>(i).value;
				lr = EntityManager::GetComponentData<LocalRotation>(i).value;
				ls = EntityManager::GetComponentData<LocalScale>(i).value;
				ltp.value = glm::scale(glm::translate(glm::mat4_cast(lr), lp), ls);
				EntityManager::SetComponentData<LocalToParent>(i, ltp);
				break;
			default:
				break;
			}
		}
	}
}
