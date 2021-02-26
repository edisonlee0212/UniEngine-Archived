#include "pch.h"
#include "TransformManager.h"
#include "UniEngine.h"
#include "EditorManager.h"
#include "SerializationManager.h"
using namespace UniEngine;
EntityQuery TransformManager::_TransformQuery;
void UniEngine::TransformManager::Init()
{
	_TransformQuery = EntityManager::CreateEntityQuery();
	EntityManager::SetEntityQueryAllFilters(_TransformQuery, Transform(), GlobalTransform());
}


void UniEngine::TransformManager::LateUpdate()
{
	EntityManager::ForEach<Transform, GlobalTransform>(JobManager::PrimaryWorkers(), _TransformQuery, [](int i, Entity entity, Transform& ltp, GlobalTransform& ltw)
		{
			if (EntityManager::IsEntityStatic(entity) || !EntityManager::GetParent(entity).IsNull()) return;
			ltw.Value = ltp.Value;
			CalculateLtwRecursive(ltw, entity);
		}, false
		);

	if (!Application::IsPlaying())
	{
		PhysicsSimulationManager::UploadTransforms();
	}
}

void UniEngine::TransformManager::CalculateLtwRecursive(const GlobalTransform& pltw, Entity entity)
{
	if(EntityManager::IsEntityStatic(entity)) return;
	for (const auto& i : EntityManager::GetChildren(entity)) {
		auto ltp = EntityManager::GetComponentData<Transform>(i);
		GlobalTransform ltw;
		ltw.Value = pltw.Value * ltp.Value;
		EntityManager::SetComponentData<GlobalTransform>(i, ltw);
		//auto* ltp = static_cast<Transform*>(static_cast<void*>(EntityManager::GetComponentDataPointer(entity, typeid(Transform).hash_code())));
		//auto* ltw = static_cast<GlobalTransform*>(static_cast<void*>(EntityManager::GetComponentDataPointer(entity, typeid(GlobalTransform).hash_code())));
		//ltw->Value = pltw->Value * ltp->Value;
		CalculateLtwRecursive(ltw, i);
	}
}
