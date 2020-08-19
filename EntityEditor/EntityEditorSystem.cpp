#include "pch.h"
#include "EntityEditorSystem.h"

void UniEngine::EntityEditorSystem::DrawEntityNode(Entity entity)
{
	std::string title = "Entity ";
	title += std::to_string(entity.Index);
	bool opened = ImGui::TreeNodeEx(title.c_str(), ImGuiTreeNodeFlags_NoTreePushOnOpen | ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_NoAutoOpenOnLog | (_SelectedEntity == entity ? ImGuiTreeNodeFlags_Framed : ImGuiTreeNodeFlags_FramePadding));
	if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(0)) {
		_SelectedEntity = entity;
	}
	if (opened) {
		ImGui::TreePush();
		EntityManager::ForEachChild(entity, [this](Entity child) {
			DrawEntityNode(child);
			});
		ImGui::TreePop();
	}
}

void UniEngine::EntityEditorSystem::DisplayComponent(ComponentBase* data, ComponentType type)
{

}

void UniEngine::EntityEditorSystem::TempComponentInspector(ComponentType type, void* data)
{
	if (type.TypeID == typeid(LocalToWorld).hash_code()) {
		ImGui::InputFloat4("x", (float*)data, 2, ImGuiInputTextFlags_ReadOnly);
		ImGui::InputFloat4("y", (float*)((char*)data + 16), 2, ImGuiInputTextFlags_ReadOnly);
		ImGui::InputFloat4("z", (float*)((char*)data + 32), 2, ImGuiInputTextFlags_ReadOnly);
		ImGui::InputFloat4("w", (float*)((char*)data + 48), 2, ImGuiInputTextFlags_ReadOnly);
	}
	else if (type.TypeID == typeid(LocalToParent).hash_code()) {
		ImGui::InputFloat4("x", (float*)data, 2, ImGuiInputTextFlags_ReadOnly);
		ImGui::InputFloat4("y", (float*)((char*)data + 16), 2, ImGuiInputTextFlags_ReadOnly);
		ImGui::InputFloat4("z", (float*)((char*)data + 32), 2, ImGuiInputTextFlags_ReadOnly);
		ImGui::InputFloat4("w", (float*)((char*)data + 48), 2, ImGuiInputTextFlags_ReadOnly);
	}
	else if (type.TypeID == typeid(Translation).hash_code()) {
		ImGui::InputFloat3("value", (float*)data, 2, ImGuiInputTextFlags_ReadOnly);
	}
	else if (type.TypeID == typeid(Rotation).hash_code()) {
		ImGui::InputFloat4("value", (float*)data, 2, ImGuiInputTextFlags_ReadOnly);
	}
	else if (type.TypeID == typeid(Scale).hash_code()) {
		ImGui::InputFloat3("value", (float*)data, 2, ImGuiInputTextFlags_ReadOnly);
	}
	else if (type.TypeID == typeid(LocalTranslation).hash_code()) {
		ImGui::InputFloat3("value", (float*)data, 2, ImGuiInputTextFlags_ReadOnly);
	}
	else if (type.TypeID == typeid(LocalRotation).hash_code()) {
		ImGui::InputFloat4("value", (float*)data, 2, ImGuiInputTextFlags_ReadOnly);
	}
	else if (type.TypeID == typeid(LocalScale).hash_code()) {
		ImGui::InputFloat3("value", (float*)data, 2, ImGuiInputTextFlags_ReadOnly);
	}

}

void UniEngine::EntityEditorSystem::OnCreate()
{
	_SelectedEntity.Index = 0;
	Enable();
	_ConfigFlags += EntityEditorSystem_EnableEntityHierarchy;
	_ConfigFlags += EntityEditorSystem_EnableEntityInspector;
}

void UniEngine::EntityEditorSystem::OnDestroy()
{
}
static const char* HierarchyDisplayMode[]{ "Archetype", "Hierarchy" };

void UniEngine::EntityEditorSystem::Update()
{
	if (_ConfigFlags & EntityEditorSystem_EnableEntityHierarchy) {
		ImGui::Begin("Entity Explorer");
		ImGui::Combo("Display mode", &_SelectedHierarchyDisplayMode, HierarchyDisplayMode, IM_ARRAYSIZE(HierarchyDisplayMode));
		
		if (_SelectedHierarchyDisplayMode == 0) {
			EntityManager::ForEachEntityStorageUnsafe([this](int i, EntityComponentStorage storage) {
				ImGui::Separator();
				
				std::string title = std::to_string(i) + ". " + storage.ArchetypeInfo->Name;
				if (ImGui::CollapsingHeader(title.c_str())) {
					ImGui::PushStyleColor(ImGuiCol_HeaderActive, ImVec4(0.2, 0.3, 0.2, 1.0));
					ImGui::PushStyleColor(ImGuiCol_HeaderHovered, ImVec4(0.2, 0.2, 0.2, 1.0));
					ImGui::PushStyleColor(ImGuiCol_Header, ImVec4(0.2, 0.2, 0.3, 1.0));
					for (int j = 0; j < storage.ArchetypeInfo->EntityAliveCount; j++) {
						std::string title = "Entity ";
						Entity entity = storage.ChunkArray->Entities.at(j);
						title += std::to_string(entity.Index);
						bool opened = ImGui::TreeNodeEx(title.c_str(), ImGuiTreeNodeFlags_NoTreePushOnOpen | ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_NoAutoOpenOnLog | (_SelectedEntity == entity ? ImGuiTreeNodeFlags_Framed : ImGuiTreeNodeFlags_FramePadding));
						if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(0)) {
							_SelectedEntity = entity;
						}
					}
					ImGui::PopStyleColor();
					ImGui::PopStyleColor();
					ImGui::PopStyleColor();
				}
				});
		} else if(_SelectedHierarchyDisplayMode == 1) {
			ImGui::PushStyleColor(ImGuiCol_HeaderActive, ImVec4(0.2, 0.3, 0.2, 1.0));
			ImGui::PushStyleColor(ImGuiCol_HeaderHovered, ImVec4(0.2, 0.2, 0.2, 1.0));
			ImGui::PushStyleColor(ImGuiCol_Header, ImVec4(0.2, 0.2, 0.3, 1.0));
			EntityManager::ForAllEntities([this](int i, Entity entity) {
				if (EntityManager::GetParent(entity).IsNull())DrawEntityNode(entity);
				});
			ImGui::PopStyleColor();
			ImGui::PopStyleColor();
			ImGui::PopStyleColor();
		}
		
		ImGui::End();
	}
	if (_ConfigFlags & EntityEditorSystem_EnableEntityInspector) {
		ImGui::Begin("Entity Inspector");
		if (!_SelectedEntity.IsNull() && !_SelectedEntity.IsDeleted()) {
			std::string title = "Entity Index: ";
			title += std::to_string(_SelectedEntity.Index);
			ImGui::Text(title.c_str());
			ImGui::Separator();
			EntityManager::ForEachComponentUnsafe(_SelectedEntity, [this](ComponentType type, void* data) {
				std::string info = std::string(type.Name + 7);
				info += " Size: " + std::to_string(type.Size);
				ImGui::Text(info.c_str());
				TempComponentInspector(type, data);
				ImGui::Separator();
				});
		}
		else {
			_SelectedEntity.Index = 0;
		}
		ImGui::End();
	}
}

void UniEngine::EntityEditorSystem::FixedUpdate()
{
}
