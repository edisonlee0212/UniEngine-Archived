#include "pch.h"
#include "EntityEditorSystem.h"
#include "TransformSystem.h"
inline void UniEngine::EntityEditorSystem::DrawEntityMenu(bool enabled, Entity& entity)
{
	if (ImGui::BeginPopupContextItem())
	{
		if (ImGui::Button("Delete"))
			EntityManager::DeleteEntity(entity);

		if (ImGui::Button(enabled ? "Disable" : "Enable")) {
			if (enabled) {
				entity.SetEnabled(false);
			}
			else {
				entity.SetEnabled(true);
			}
		}
		ImGui::EndPopup();
	}
}

void UniEngine::EntityEditorSystem::DrawEntityNode(Entity& entity)
{
	std::string title = "Entity ";
	bool enabled = entity.Enabled();
	if (enabled) {
		ImGui::PushStyleColor(ImGuiCol_Text, ImVec4({ 1, 1, 1, 1 }));
	}
	title += std::to_string(entity.Index);

	bool opened = ImGui::TreeNodeEx(title.c_str(), ImGuiTreeNodeFlags_NoTreePushOnOpen | ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_NoAutoOpenOnLog | (_SelectedEntity == entity ? ImGuiTreeNodeFlags_Framed : ImGuiTreeNodeFlags_FramePadding));
	if (enabled) {
		ImGui::PopStyleColor();
	}
	if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(0)) {
		_SelectedEntity = entity;
	}
	DrawEntityMenu(enabled, entity);
	if (opened) {
		ImGui::TreePush();
		EntityManager::ForEachChild(entity, [this](Entity child) {
			DrawEntityNode(child);
			});
		ImGui::TreePop();
	}
}

void UniEngine::EntityEditorSystem::InspectComponent(ComponentBase* data, ComponentType type)
{
	if (_ComponentGUIMap.find(type.TypeID) != _ComponentGUIMap.end()) {
		_ComponentGUIMap.at(type.TypeID)(data);
	}
}

void UniEngine::EntityEditorSystem::AddComponentInspector(ComponentType type,
	const std::function<void(ComponentBase* data)>& func)
{
	_ComponentGUIMap.insert_or_assign(type.TypeID, func);
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
						bool enabled = entity.Enabled();
						if (enabled) {
							ImGui::PushStyleColor(ImGuiCol_Text, ImVec4({ 1, 1, 1, 1 }));
						}
						title += std::to_string(entity.Index);
						bool opened = ImGui::TreeNodeEx(title.c_str(), ImGuiTreeNodeFlags_NoTreePushOnOpen | ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_NoAutoOpenOnLog | (_SelectedEntity == entity ? ImGuiTreeNodeFlags_Framed : ImGuiTreeNodeFlags_FramePadding));
						if (enabled) {
							ImGui::PopStyleColor();
						}
						DrawEntityMenu(enabled, entity);
						if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(0)) {
							_SelectedEntity = entity;
						}
					}
					ImGui::PopStyleColor();
					ImGui::PopStyleColor();
					ImGui::PopStyleColor();
				}
				});
		}
		else if (_SelectedHierarchyDisplayMode == 1) {
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
				//TempComponentInspector(type, data);
				InspectComponent(static_cast<ComponentBase*>(data), type);
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

UniEngine::Entity UniEngine::EntityEditorSystem::GetSelectedEntity() const
{
	return _SelectedEntity;
}
