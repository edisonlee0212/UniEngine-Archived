#pragma once
#include "CameraComponent.h"
#include "Core.h"
#include "UniEngineAPI.h"
#include "Texture2D.h"
namespace UniEngine {
	struct Transform;
	enum EntityEditorSystemConfigFlags {
		EntityEditorSystem_None = 0,
		EntityEditorSystem_EnableEntityHierarchy = 1 << 0,
		EntityEditorSystem_EnableEntityInspector = 1 << 1
	};
	class UNIENGINE_API EditorManager :
		public Singleton<EditorManager>
	{
		static EntityArchetype _BasicEntityArchetype;
		static bool _Enabled;
		static std::map<size_t, std::function<void(ComponentBase* data, bool isRoot)>> _ComponentDataInspectorMap;
		static std::vector<std::pair<size_t, std::function<void(Entity owner)>>> _PrivateComponentMenuList;
		static std::vector<std::pair<size_t, std::function<void(Entity owner)>>> _ComponentDataMenuList;
		static unsigned int _ConfigFlags;
		static int _SelectedHierarchyDisplayMode;
		static Entity _SelectedEntity;
		static bool _EnableConsole;
		static Transform* _PreviouslyStoredTransform;
		static GlobalTransform* _PreviouslyStoredGlobalTransform;
		static glm::vec3 _PreviouslyStoredPosition;
		static glm::vec3 _PreviouslyStoredRotation;
		static glm::vec3 _PreviouslyStoredScale;
		static bool _LocalPositionSelected;
		static bool _LocalRotationSelected;
		static bool _LocalScaleSelected;

		static bool _EnableConsoleLogs;
		static bool _EnableConsoleErrors;
		static bool _EnableConsoleWarnings;
		
#pragma region Scene Camera
		friend class RenderManager;
		friend class InputManager;
		static glm::quat _SceneCameraRotation;
		static glm::vec3 _SceneCameraPosition;
		static std::unique_ptr<GLProgram> _SceneHighlightPrePassProgram;
		static std::unique_ptr<GLProgram> _SceneHighlightProgram;

		static std::unique_ptr<GLProgram> _SceneCameraEntityRecorderProgram;
		static std::unique_ptr<RenderTarget> _SceneCameraEntityRecorder;
		static std::unique_ptr<GLTexture2D> _SceneCameraEntityRecorderTexture;
		static std::unique_ptr<GLRenderBuffer> _SceneCameraEntityRecorderRenderBuffer;
		static Entity _FocusedEntity;
		static std::unique_ptr<CameraComponent> _SceneCamera;
		static float _SceneCameraYawAngle;
		static float _SceneCameraPitchAngle;
		static int _SceneCameraResolutionX;
		static int _SceneCameraResolutionY;
		static float _Velocity;
		static float _Sensitivity;
		static float _LastX;
		static float _LastY;
		static float _LastScrollY;
		static bool _StartMouse;
		static bool _StartScroll;
		static bool _EscapeHold;
#pragma endregion
		static bool DrawEntityMenu(bool enabled, Entity& entity);
		static void DrawEntityNode(Entity& entity);
		static void InspectComponentData(ComponentBase* data, ComponentType type, bool isRoot);
	public:
		static void LateUpdate();
		template<typename T1 = ComponentBase>
		static void RegisterComponentDataInspector(const std::function<void(ComponentBase* data, bool isRoot)>& func);
		template<typename T1 = PrivateComponentBase>
		static void RegisterPrivateComponentMenu(const std::function<void(Entity owner)>& func);
		template<typename T1 = ComponentBase>
		static void RegisterComponentDataMenu(const std::function<void(Entity owner)>& func);
		static void Init();
		static void Destroy();
		static void PreUpdate();
		static void Update();
		static Entity GetSelectedEntity() { return _SelectedEntity; }
		static void SetSelectedEntity(Entity entity);

		template<typename T = ResourceBehaviour>
		static bool DragAndDrop(std::shared_ptr<T>& target);
		template<typename T = ResourceBehaviour>
		static bool Draggable(std::shared_ptr<T>& target);

		static bool Draggable(const std::string& name, std::shared_ptr<ResourceBehaviour>& target);
	};

	template <typename T1>
	void EditorManager::RegisterComponentDataInspector(const std::function<void(ComponentBase* data, bool isRoot)>& func)
	{
		_ComponentDataInspectorMap.insert_or_assign(typeid(T1).hash_code(), func);
	}

	template <typename T1>
	void EditorManager::RegisterPrivateComponentMenu(const std::function<void(Entity owner)>& func)
	{
		for(int i = 0; i < _PrivateComponentMenuList.size(); i++)
		{
			if(_PrivateComponentMenuList[i].first == typeid(T1).hash_code())
			{
				_PrivateComponentMenuList[i].second = func;
				return;
			}
		}
		_PrivateComponentMenuList.emplace_back(typeid(T1).hash_code(), func);
	}

	template <typename T1>
	void EditorManager::RegisterComponentDataMenu(const std::function<void(Entity owner)>& func)
	{
		for (int i = 0; i < _ComponentDataMenuList.size(); i++)
		{
			if (_ComponentDataMenuList[i].first == typeid(T1).hash_code())
			{
				_ComponentDataMenuList[i].second = func;
				return;
			}
		}
		_ComponentDataMenuList.emplace_back(typeid(T1).hash_code(), func);
	}

	template <typename T>
	bool EditorManager::DragAndDrop(std::shared_ptr<T>& target)
	{
		const std::shared_ptr<ResourceBehaviour> ptr = std::dynamic_pointer_cast<ResourceBehaviour>(target);
		const std::string tag = "##" + (ptr ? std::to_string(ptr->GetHashCode()) : "");
		ImGui::Button(ptr ? (ptr->Name + tag).c_str() : "none");
		if (ImGui::BeginDragDropSource(ImGuiDragDropFlags_SourceAllowNullID))
		{
			const std::string hash = std::to_string(std::hash<std::string>{}(typeid(T).name()));
			ImGui::SetDragDropPayload(hash.c_str(), &target, sizeof(std::shared_ptr<T>));
			if(ptr && ptr->_Icon)ImGui::Image(reinterpret_cast<ImTextureID>(ptr->_Icon->Texture()->ID()), ImVec2(30, 30), ImVec2(0, 1), ImVec2(1, 0));
			else ImGui::TextColored(ImVec4(0, 0, 1, 1), (std::string(typeid(T).name()) + tag).substr(6).c_str());
			ImGui::EndDragDropSource();
		}
		bool removed = false;
		if (ptr && ImGui::BeginPopupContextItem(tag.c_str()))
		{
			if (ImGui::BeginMenu(("Rename" + tag).c_str()))
			{
				static char newName[256];
				ImGui::InputText(("New name" + tag).c_str(), newName, 256);
				if (ImGui::Button(("Confirm" + tag).c_str())) ptr->Name = std::string(newName);
				ImGui::EndMenu();
			}
			if (ImGui::Button(("Remove" + tag).c_str())) {
				target.reset();
				removed = true;
			}
			ImGui::EndPopup();
		}
		if (ImGui::BeginDragDropTarget())
		{
			const std::string hash = std::to_string(std::hash<std::string>{}(typeid(T).name()));
			if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload(hash.c_str()))
			{
				IM_ASSERT(payload->DataSize == sizeof(std::shared_ptr<T>));
				std::shared_ptr<T> payload_n = *static_cast<std::shared_ptr<T>*>(payload->Data);
				target = payload_n;
			}
			ImGui::EndDragDropTarget();
		}
		return removed;
	}

	template <typename T>
	bool EditorManager::Draggable(std::shared_ptr<T>& target)
	{
		const std::shared_ptr<ResourceBehaviour> ptr = std::dynamic_pointer_cast<ResourceBehaviour>(target);
		const std::string tag = "##" + (ptr ? std::to_string(ptr->GetHashCode()) : "");
		ImGui::Button(ptr ? (ptr->Name + tag).c_str() : "none");
		if (ImGui::BeginDragDropSource(ImGuiDragDropFlags_SourceAllowNullID))
		{
			const std::string hash = std::to_string(std::hash<std::string>{}(typeid(T).name()));
			ImGui::SetDragDropPayload(hash.c_str(), &target, sizeof(std::shared_ptr<ResourceBehaviour>));
			if (ptr && ptr->_Icon)ImGui::Image(reinterpret_cast<ImTextureID>(ptr->_Icon->Texture()->ID()), ImVec2(30, 30), ImVec2(0, 1), ImVec2(1, 0));
			else ImGui::TextColored(ImVec4(0, 0, 1, 1), (std::string(typeid(T).name()) + tag).substr(6).c_str());
			ImGui::EndDragDropSource();
		}
		bool removed = false;
		if (ptr && ImGui::BeginPopupContextItem(tag.c_str()))
		{
			if (ImGui::BeginMenu(("Rename" + tag).c_str()))
			{
				static char newName[256];
				ImGui::InputText(("New name" + tag).c_str(), newName, 256);
				if (ImGui::Button(("Confirm" + tag).c_str())) ptr->Name = std::string(newName);
				ImGui::EndMenu();
			}
			if (ImGui::Button(("Remove" + tag).c_str())) {
				target.reset();
				removed = true;
			}
			ImGui::EndPopup();
		}
		return removed;
	}
}
