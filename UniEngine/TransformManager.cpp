#include "pch.h"
#include "TransformManager.h"
#include "UniEngine.h"
#include "EditorManager.h"
using namespace UniEngine;
bool TransformManager::_AddCheck;
size_t TransformManager::_CurrentStoredHierarchyVersion = INT_MAX;
EntityQuery TransformManager::_TransformQuery;
std::vector<std::pair<Entity, ChildInfo>> TransformManager::_CachedParentHierarchies;
void UniEngine::TransformManager::Init()
{
	_TransformQuery = EntityManager::CreateEntityQuery();
	EntityManager::SetEntityQueryAllFilters(_TransformQuery, LocalToParent(), LocalToWorld());
	_CachedParentHierarchies = std::vector<std::pair<Entity, ChildInfo>>();
	EditorManager::RegisterComponentDataInspector<LocalToWorld>( [](ComponentBase* data, bool isRoot)
		{
			std::stringstream stream;
			LocalToWorld* ltw = reinterpret_cast<LocalToWorld*>(data);
			glm::vec3 er;
			glm::vec3 t;
			glm::vec3 s;
			ltw->GetTERS(t, er, s);
			er = glm::degrees(er);
			ImGui::InputFloat3("Global Position", &t.x, "%.3f", ImGuiInputTextFlags_ReadOnly);
			ImGui::InputFloat3("Global Rotation", &er.x, "%.3f", ImGuiInputTextFlags_ReadOnly);
			ImGui::InputFloat3("Global Scale", &s.x, "%.3f", ImGuiInputTextFlags_ReadOnly);
		}
	);


	EditorManager::RegisterComponentDataInspector<LocalToParent>( [](ComponentBase* data, bool isRoot)
		{
			std::stringstream stream;
			auto ltp = reinterpret_cast<LocalToParent*>(data);
			bool edited = false;
			glm::vec3 er;
			glm::vec3 t;
			glm::vec3 s;
			ltp->GetTERS(t, er, s);
			er = glm::degrees(er);
			if (ImGui::DragFloat3("Local Position", &t.x, 0.1f)) edited = true;
			if (ImGui::DragFloat3("Local Rotation", &er.x, 1.0f)) edited = true;
			if (ImGui::DragFloat3("Local Scale", &s.x, 0.01f)) edited = true;
			if (edited)
			{
				er.y = glm::clamp(er.y, -89.0f, 89.0f);
				auto nltp = glm::translate(t) * glm::mat4_cast(glm::quat(glm::radians(er))) * glm::scale(s);
				ltp->Value = nltp;
			}
		}
	);
}

void UniEngine::TransformManager::LateUpdate()
{
	EntityManager::ForEach<LocalToParent, LocalToWorld>(_TransformQuery, [](int i, Entity entity, LocalToParent* ltp, LocalToWorld* ltw)
		{
			if(EntityManager::GetParent(entity).IsNull())
			{
				ltw->Value = ltp->Value;
			}
		}
	);
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
			LocalToWorld ltw;
			ltw.Value = pltw.Value * ltp.Value;
			EntityManager::SetComponentData<LocalToWorld>(info.second.Child, ltw);
		}
		for (const auto& i : futures) i.wait();
	}
	else {
		_CachedParentHierarchies.clear();
		EntityManager::ForAllRootParent([](int i, Entity rootParent) {
			CollectHierarchy(&_CachedParentHierarchies, rootParent);
			}
		);
		_CurrentStoredHierarchyVersion = EntityManager::GetParentHierarchyVersion();
	}

	if(!Application::IsPlaying())
	{
		PhysicsSimulationManager::UploadTransforms();
	}
}

void UniEngine::TransformManager::CalculateLtwRecursive(LocalToWorld pltw, Entity entity)
{
	/*
	Here we have 2 ways to deal with children, you can use lambda function or you can get children
	and maniputale them directly. The method I'm using here, which is the second one,
	is faster and I don't know why...
	*/
	for (const auto& i : EntityManager::GetChildren(entity)) {
		auto ltp = EntityManager::GetComponentData<LocalToParent>(i);
		LocalToWorld ltw;
		ltw.Value = pltw.Value * ltp.Value;
		EntityManager::SetComponentData<LocalToWorld>(i, ltw);
		CalculateLtwRecursive(ltw, i);
	}
}

void UniEngine::TransformManager::CollectHierarchy(std::vector<std::pair<Entity, ChildInfo>>* container, Entity entity)
{
	auto children = EntityManager::GetChildren(entity);
	const auto initialSize = container->size();
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