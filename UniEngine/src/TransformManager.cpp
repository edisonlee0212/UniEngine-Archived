#include "pch.h"
#include "TransformManager.h"
#include "UniEngine.h"
#include "EditorManager.h"
#include "SerializationManager.h"
using namespace UniEngine;
bool TransformManager::_AddCheck;
size_t TransformManager::_CurrentStoredHierarchyVersion = INT_MAX;
EntityQuery TransformManager::_TransformQuery;
std::vector<std::pair<Entity, ChildInfo>> TransformManager::_CachedParentHierarchies;
void UniEngine::TransformManager::Init()
{
	_TransformQuery = EntityManager::CreateEntityQuery();
	EntityManager::SetEntityQueryAllFilters(_TransformQuery, Transform(), GlobalTransform());
	_CachedParentHierarchies = std::vector<std::pair<Entity, ChildInfo>>();

	SerializationManager::RegisterComponentDataSerializerDeserializer<Transform>(
		{
		[](ComponentBase* data)
		{
			Transform* out = static_cast<Transform*>(data);
			glm::mat4 val = out->Value;
			std::stringstream stream;
			stream << val[0].x << ',' << val[0].y << ',' << val[0].z << ',' << val[0].w << '-';
			stream << val[1].x << ',' << val[1].y << ',' << val[1].z << ',' << val[1].w << '-';
			stream << val[2].x << ',' << val[2].y << ',' << val[2].z << ',' << val[2].w << '-';
			stream << val[3].x << ',' << val[3].y << ',' << val[3].z << ',' << val[3].w;
			return stream.str();
		},
		[](const std::string& data, ComponentBase* ptr)
		{
			std::stringstream stream;
			stream << data;
			Transform* out = static_cast<Transform*>(ptr);
			glm::mat4 val;
			char temp;
			for (int i = 0; i < 4; i++) {
				for(int j = 0; j < 4; j++)
				{
					stream >> val[i][j] >> temp;
				}
			}
			out->Value = val;
			Debug::Log("Finished");
		}
	});
}

void UniEngine::TransformManager::LateUpdate()
{
	EntityManager::ForEach<Transform, GlobalTransform>(_TransformQuery, [](int i, Entity entity, Transform* ltp, GlobalTransform* ltw)
		{
			if(EntityManager::GetParent(entity).IsNull())
			{
				ltw->Value = ltp->Value;
				CalculateLtwRecursive(ltw, entity);
			}
		}, false
	);
	if (!Application::IsPlaying())
	{
		PhysicsSimulationManager::UploadTransforms();
	}
}

void UniEngine::TransformManager::CalculateLtwRecursive(GlobalTransform* pltw, Entity entity)
{
	/*
	Here we have 2 ways to deal with children, you can use lambda function or you can get children
	and manipulate them directly. The method I'm using here, which is the second one,
	is faster and I don't know why...
	*/
	for (const auto& i : EntityManager::GetChildren(entity)) {
		if (!i.HasComponentData<Transform>()) continue;
		auto ltp = EntityManager::GetComponentData<Transform>(i);
		GlobalTransform ltw;
		ltw.Value = pltw->Value * ltp.Value;
		EntityManager::SetComponentData<GlobalTransform>(i, ltw);
		CalculateLtwRecursive(&ltw, i);
	}
}

void UniEngine::TransformManager::CollectHierarchy(std::vector<std::pair<Entity, ChildInfo>>* container, Entity entity)
{
	auto children = EntityManager::GetChildren(entity);
	const auto initialSize = container->size();
	for (const auto& i : children) {
		if (EntityManager::HasComponentData<GlobalTransform>(i) && EntityManager::HasComponentData<Transform>(i) && EntityManager::HasComponentData<GlobalTransform>(entity)) {
			ChildInfo info;
			info.Child = i;
			auto ltp = EntityManager::GetComponentData<Transform>(i);
			auto pltw = EntityManager::GetComponentData<GlobalTransform>(entity);
			container->push_back(std::make_pair(entity, info));
			GlobalTransform ltw;
			ltw.Value = pltw.Value * ltp.Value;
			EntityManager::SetComponentData<GlobalTransform>(i, ltw);
		}
	}
	for (int i = initialSize; i < container->size(); i++) {
		Entity target = container->at(i).second.Child;
		for (const auto& child : EntityManager::GetChildren(target)) {
			if (EntityManager::HasComponentData<GlobalTransform>(child) && EntityManager::HasComponentData<Transform>(child) && EntityManager::HasComponentData<GlobalTransform>(target)) {
				ChildInfo info;
				info.Child = child;
				auto ltp = EntityManager::GetComponentData<Transform>(child);
				auto pltw = EntityManager::GetComponentData<GlobalTransform>(target);
				container->push_back(std::make_pair(target, info));
				GlobalTransform ltw;
				ltw.Value = pltw.Value * ltp.Value;
				EntityManager::SetComponentData<GlobalTransform>(child, ltw);
			}
		}
	}
}