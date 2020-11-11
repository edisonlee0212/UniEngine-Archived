#include "pch.h"
#include "EditorManager.h"

#include "AssetManager.h"

#include "Default.h"
#include "DirectionalLightComponent.h"
#include "InputManager.h"
#include "Model.h"
#include "PointLightComponent.h"
#include "RenderManager.h"
#include "TransformSystem.h"
using namespace UniEngine;
std::map<size_t, std::function<void(ComponentBase* data)>> EditorManager::_ComponentGUIMap;
unsigned int EditorManager::_ConfigFlags = 0;
int EditorManager::_SelectedHierarchyDisplayMode = 1;
Entity EditorManager::_SelectedEntity;
bool EditorManager::_DisplayLog = true;
bool EditorManager::_DisplayError = true;

glm::quat EditorManager::_SceneCameraRotation;
glm::vec3 EditorManager::_SceneCameraPosition;
std::unique_ptr<CameraComponent> EditorManager::_SceneCamera;
int EditorManager::_SceneCameraResolutionX;
int EditorManager::_SceneCameraResolutionY;
inline bool UniEngine::EditorManager::DrawEntityMenu(bool enabled, Entity& entity)
{
	bool deleted = false;
	if (ImGui::BeginPopupContextItem(std::to_string(entity.Index).c_str()))
	{
		if (ImGui::Button("Delete")) {
			EntityManager::DeleteEntity(entity);
			deleted = true;
		}
		if (!deleted && ImGui::Button(enabled ? "Disable" : "Enable")) {
			if (enabled) {
				entity.SetEnabled(false);
			}
			else {
				entity.SetEnabled(true);
			}
		}
		if (!deleted && ImGui::BeginMenu("Rename"))
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

void UniEngine::EditorManager::DrawEntityNode(Entity& entity)
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
		EntityManager::ForEachChild(entity, [](Entity child) {
			DrawEntityNode(child);
			});
		ImGui::TreePop();
	}
}

void UniEngine::EditorManager::InspectComponent(ComponentBase* data, ComponentType type)
{
	if (_ComponentGUIMap.find(type.TypeID) != _ComponentGUIMap.end()) {
		_ComponentGUIMap.at(type.TypeID)(data);
	}
}

void UniEngine::EditorManager::Init()
{
	AddComponentInspector<DirectionalLightComponent>([](ComponentBase* data)
		{
			std::stringstream stream;
			stream << std::hex << "0x" << (size_t)data;
			auto* dl = static_cast<DirectionalLightComponent*>((void*)data);
			ImGui::ColorEdit3("Diffuse", &dl->diffuse[0]);
			ImGui::DragFloat("Diffuse Brightness", &dl->diffuseBrightness, 0.1f);
			ImGui::ColorEdit3("Specular", &dl->specular[0]);
			ImGui::DragFloat("Specular Brightness", &dl->specularBrightness, 0.1f);
			ImGui::DragFloat("Bias", &dl->depthBias, 0.001f);
			ImGui::InputFloat("Normal Offset", &dl->normalOffset, 0.01f);
			ImGui::DragFloat("Light Size", &dl->lightSize, 0.1f);
		});
	AddComponentInspector<PointLightComponent>([](ComponentBase* data)
		{
			std::stringstream stream;
			stream << std::hex << "0x" << (size_t)data;
			auto* dl = static_cast<PointLightComponent*>((void*)data);
			ImGui::ColorEdit3("Diffuse", &dl->diffuse[0]);
			ImGui::DragFloat("Diffuse Brightness", &dl->diffuseBrightness, 0.1f);
			ImGui::ColorEdit3("Specular", &dl->specular[0]);
			ImGui::DragFloat("Specular Brightness", &dl->specularBrightness, 0.1f);
			ImGui::DragFloat("Bias", &dl->bias, 0.001f);

			ImGui::DragFloat("Constant", &dl->constant, 0.1f);
			ImGui::DragFloat("Linear", &dl->quadratic, 0.1f);

			//ImGui::InputFloat("Normal Offset", &dl->normalOffset, 0.01f);
			//ImGui::DragFloat("Light Size", &dl->lightSize, 0.1f);
		});
	
	_SelectedEntity.Index = 0;
	_ConfigFlags += EntityEditorSystem_EnableEntityHierarchy;
	_ConfigFlags += EntityEditorSystem_EnableEntityInspector;

	_SceneCameraPosition = glm::vec3(0.0f);
	_SceneCameraRotation = glm::quat(glm::vec3(0.0f));
	_SceneCamera = std::make_unique<CameraComponent>();
	_SceneCamera->SkyBox = Default::Textures::DefaultSkybox;
}

void UniEngine::EditorManager::Destroy()
{

}

void EditorManager::Start()
{
	_SceneCamera->ResizeResolution(_SceneCameraResolutionX, _SceneCameraResolutionY);
#pragma region Dock & Main Menu
	static bool opt_fullscreen_persistant = true;
	bool opt_fullscreen = opt_fullscreen_persistant;
	static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

	// We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
	// because it would be confusing to have two docking targets within each others.
	ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoDocking;
	if (opt_fullscreen)
	{
		ImGuiViewport* viewport = ImGui::GetMainViewport();
		ImGui::SetNextWindowPos(viewport->GetWorkPos());
		ImGui::SetNextWindowSize(viewport->GetWorkSize());
		ImGui::SetNextWindowViewport(viewport->ID);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
		window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
		window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
	}

	// When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background
	// and handle the pass-thru hole, so we ask Begin() to not render a background.
	if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
		window_flags |= ImGuiWindowFlags_NoBackground;

	// Important: note that we proceed even if Begin() returns false (aka window is collapsed).
	// This is because we want to keep our DockSpace() active. If a DockSpace() is inactive,
	// all active windows docked into it will lose their parent and become undocked.
	// We cannot preserve the docking relationship between an active window and an inactive docking, otherwise
	// any change of dockspace/settings would lead to windows being stuck in limbo and never being visible.

	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
	static bool openDock = true;
	ImGui::Begin("Root DockSpace", &openDock, window_flags);
	ImGui::PopStyleVar();
	if (opt_fullscreen)
		ImGui::PopStyleVar(2);
	ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
	ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
	ImGui::End();

	if (ImGui::BeginMainMenuBar()) {
		if (ImGui::BeginMenu("File"))
		{
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Edit"))
		{
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("View"))
		{
			ImGui::Checkbox("Log", &_DisplayLog);
			ImGui::Checkbox("Error", &_DisplayError);
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Window"))
		{
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Help"))
		{
			ImGui::EndMenu();
		}
		ImGui::EndMainMenuBar();
	}

#pragma endregion


#pragma region Select entity here

#pragma endregion

}

static const char* HierarchyDisplayMode[]{ "Archetype", "Hierarchy" };

void UniEngine::EditorManager::Update()
{
	if (_ConfigFlags & EntityEditorSystem_EnableEntityHierarchy) {
		ImGui::Begin("Entity Explorer");
		ImGui::Combo("Display mode", &_SelectedHierarchyDisplayMode, HierarchyDisplayMode, IM_ARRAYSIZE(HierarchyDisplayMode));

		if (_SelectedHierarchyDisplayMode == 0) {
			EntityManager::ForEachEntityStorageUnsafe([](int i, EntityComponentStorage storage) {
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
			EntityManager::ForAllEntities([](int i, Entity entity) {
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
					EntityManager::ForEachComponentUnsafe(_SelectedEntity, [](ComponentType type, void* data) {
						std::string info = std::string(type.Name + 7);
						info += " Size: " + std::to_string(type.Size);
						ImGui::Text(info.c_str());
						InspectComponent(static_cast<ComponentBase*>(data), type);
						ImGui::Separator();
						});
				}
				if (ImGui::CollapsingHeader("Private components", ImGuiTreeNodeFlags_DefaultOpen)) {
					int i = 0;
					EntityManager::ForEachPrivateComponent(_SelectedEntity, [&i](PrivateComponentElement& data)
						{
							ImGui::Checkbox((data.Name + 6), &data.PrivateComponentData->_Enabled);
							if (ImGui::TreeNode(("Component Settings##" + std::to_string(i)).c_str())) {
								data.PrivateComponentData->OnGui();
								ImGui::TreePop();
							}
							ImGui::Separator();
							i++;
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
void EditorManager::OnGui()
{
#pragma region Scene Camera Window
	ImVec2 viewPortSize;
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0, 0 });

	ImGui::Begin("Scene");
	{
		viewPortSize = ImGui::GetWindowSize();
		ImVec2 overlayPos;
		static int corner = 1;
		ImGuiIO& io = ImGui::GetIO();
		// Using a Child allow to fill all the space of the window.
		// It also allows customization
		if (ImGui::BeginChild("CameraRenderer")) {
			viewPortSize = ImGui::GetWindowSize();
			
			// Get the size of the child (i.e. the whole draw size of the windows).
			overlayPos = ImGui::GetWindowPos();
			// Because I use the texture from OpenGL, I need to invert the V from the UV.
			ImGui::Image((ImTextureID)_SceneCamera.get()->GetCamera()->GetTexture()->ID(), viewPortSize, ImVec2(0, 1), ImVec2(1, 0));
			if (ImGui::BeginDragDropTarget())
			{
				if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("ASSET_MODEL"))
				{
					IM_ASSERT(payload->DataSize == sizeof(std::shared_ptr<Model>));
					std::shared_ptr<Model> payload_n = *(std::shared_ptr<Model>*)payload->Data;
					EntityArchetype archetype = EntityManager::CreateEntityArchetype("Model",
						EulerRotation(),
						LocalToParent(),
						Translation(),
						Rotation(),
						Scale(),
						LocalToWorld());
					Scale t;
					t.Value = glm::vec3(1.0f);
					AssetManager::ToEntity(archetype, payload_n).SetComponentData(t);
				}
				ImGui::EndDragDropTarget();
			}
		}
		ImGui::EndChild();

	}
	ImGui::End();
	ImGui::PopStyleVar();
	_SceneCameraResolutionX = viewPortSize.x;
	_SceneCameraResolutionY = viewPortSize.y;

#pragma endregion
#pragma region Logs and errors
	if (_DisplayLog) {
		ImGui::Begin("Log");
		size_t size = Debug::GetLogs()->size();
		std::string logs = "";
		for (int i = (int)size - 1; i >= 0; i--) {
			logs += Debug::GetLogs()->at(i)->c_str();
		}
		ImGui::Text(logs.c_str());
		ImGui::End();
	}
	if (_DisplayError)
	{
		ImGui::Begin("Error");
		size_t size = Debug::GetErrors()->size();
		std::string logs = "";
		for (int i = (int)size - 1; i >= 0; i--) {
			logs += Debug::GetErrors()->at(i)->c_str();
		}
		ImGui::Text(logs.c_str());
		ImGui::End();
	}
#pragma endregion

}



void UniEngine::EditorManager::SetSelectedEntity(Entity entity)
{
	if(entity.IsNull() || entity.IsDeleted()) return;
	_SelectedEntity = entity;
}
