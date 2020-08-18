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

void UniEngine::EntityEditorSystem::Update()
{
	if (_ConfigFlags & EntityEditorSystem_EnableEntityHierarchy) {
		ImGui::Begin("Entity Hierarchy");
		EntityManager::ForAllEntities([this](int i, Entity entity) {
			if (EntityManager::GetParent(entity).IsNull())DrawEntityNode(entity);
			});

		ImGui::End();
	}
	if (_ConfigFlags & EntityEditorSystem_EnableEntityInspector) {
		ImGui::Begin("Entity Inspector");
		if (!_SelectedEntity.IsNull() && !_SelectedEntity.IsDeleted()) {
			std::string title = "Entity Index: ";
			title += std::to_string(_SelectedEntity.Index);
			EntityManager::ForEachComponentUnsafe(_SelectedEntity, [](ComponentType type, void* data) {
				std::string info = std::string(type.Name + 7);
				info += " Size: " + std::to_string(type.Size);
				ImGui::Text(info.c_str());
				
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
