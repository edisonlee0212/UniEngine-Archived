#include "pch.h"
#include "EntityEditorSystem.h"
#include "TransformSystem.h"

std::map<size_t, std::function<void(UniEngine::ComponentBase* data)>> UniEngine::EntityEditorSystem::_ComponentGUIMap;
UniEngine::Entity UniEngine::EntityEditorSystem::_SelectedEntity;
inline bool UniEngine::EntityEditorSystem::DrawEntityMenu(bool enabled, Entity& entity)
{
	bool deleted = false;
	if (ImGui::BeginPopupContextItem(std::to_string(entity.Index).c_str()))
	{
		if (ImGui::Button("Delete")) {
			EntityManager::DeleteEntity(entity);
			deleted = true;
		}
		if (ImGui::Button(enabled ? "Disable" : "Enable")) {
			if (enabled) {
				entity.SetEnabled(false);
			}
			else {
				entity.SetEnabled(true);
			}
		}
		if (ImGui::BeginMenu("Rename"))
		{

			static char newName[256];
			ImGui::InputText("New name", newName, 256);
			if (ImGui::Button("Confirm"))EntityManager::SetEntityName(entity, std::string(newName));

			ImGui::EndMenu();
		}
		ImGui::EndPopup();
	}
	return deleted;
}

void UniEngine::EntityEditorSystem::DrawEntityNode(Entity& entity)
{
	std::string title = std::to_string(entity.Index) + ": ";
	title += entity.GetName();
	bool enabled = entity.Enabled();
	if (enabled) {
		ImGui::PushStyleColor(ImGuiCol_Text, ImVec4({ 1, 1, 1, 1 }));
	}

	bool opened = ImGui::TreeNodeEx(title.c_str(), ImGuiTreeNodeFlags_NoTreePushOnOpen | ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_NoAutoOpenOnLog | (_SelectedEntity == entity ? ImGuiTreeNodeFlags_Framed : ImGuiTreeNodeFlags_FramePadding));
	if (enabled) {
		ImGui::PopStyleColor();
	}
	if (ImGui::IsItemHovered() && ImGui::IsMouseClicked(0)) {
		_SelectedEntity = entity;
	}
	const bool deleted = DrawEntityMenu(enabled, entity);
	if (opened && !deleted) {
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
						Entity entity = storage.ChunkArray->Entities.at(j);
						std::string title = std::to_string(entity.Index) + ": ";
						title += entity.GetName();
						bool enabled = entity.Enabled();
						if (enabled) {
							ImGui::PushStyleColor(ImGuiCol_Text, ImVec4({ 1, 1, 1, 1 }));
						}
						ImGui::TreeNodeEx(title.c_str(), ImGuiTreeNodeFlags_NoTreePushOnOpen | ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoAutoOpenOnLog | (_SelectedEntity == entity ? ImGuiTreeNodeFlags_Framed : ImGuiTreeNodeFlags_FramePadding));
						if (enabled) {
							ImGui::PopStyleColor();
						}
						DrawEntityMenu(enabled, entity);
						if (ImGui::IsItemHovered() && ImGui::IsMouseClicked(0)) {
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
				if (EntityManager::GetParent(entity).IsNull()) DrawEntityNode(entity);
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
			std::string title = std::to_string(_SelectedEntity.Index) + ": ";
			title += _SelectedEntity.GetName();
			ImGui::Text(title.c_str());
			bool deleted = DrawEntityMenu(_SelectedEntity.Enabled(), _SelectedEntity);
			ImGui::Separator();
			if (!deleted) {
				if (ImGui::CollapsingHeader("Local components", ImGuiTreeNodeFlags_DefaultOpen)) {
					EntityManager::ForEachComponentUnsafe(_SelectedEntity, [this](ComponentType type, void* data) {
						std::string info = std::string(type.Name + 7);
						info += " Size: " + std::to_string(type.Size);
						ImGui::Text(info.c_str());
						InspectComponent(static_cast<ComponentBase*>(data), type);
						ImGui::Separator();
						});
				}
				if (ImGui::CollapsingHeader("Shared components", ImGuiTreeNodeFlags_DefaultOpen)) {
					int i = 0;
					EntityManager::ForEachSharedComponent(_SelectedEntity, [&i](SharedComponentElement data)
						{
							ImGui::Checkbox((data.Name + 6), &data.SharedComponentData->_Enabled);
							if (ImGui::TreeNode(("Component Settings##" + std::to_string(i)).c_str())) {
								data.SharedComponentData->OnGui();
								ImGui::TreePop();
							}
							ImGui::Separator();
							i++;
						});
				}
			}
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

void UniEngine::EntityEditorSystem::SetSelectedEntity(Entity entity)
{
	if(entity.IsNull() || entity.IsDeleted()) return;
	_SelectedEntity = entity;
}
