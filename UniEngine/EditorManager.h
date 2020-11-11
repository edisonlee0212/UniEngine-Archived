#pragma once
#include "CameraComponent.h"
#include "Core.h"
#include "UniEngineAPI.h"
namespace UniEngine {
	enum EntityEditorSystemConfigFlags {
		EntityEditorSystem_None = 0,
		EntityEditorSystem_EnableEntityHierarchy = 1 << 0,
		EntityEditorSystem_EnableEntityInspector = 1 << 1
	};
	class UNIENGINE_API EditorManager :
		public ManagerBase
	{
		static bool _Enabled;
		static std::map<size_t, std::function<void(ComponentBase* data)>> _ComponentGUIMap;
		static unsigned int _ConfigFlags;
		static int _SelectedHierarchyDisplayMode;
		static Entity _SelectedEntity;
		static bool _DisplayLog;
		static bool _DisplayError;

#pragma region Scene Camera
		friend class RenderManager;
		static glm::quat _SceneCameraRotation;
		static glm::vec3 _SceneCameraPosition;
		static std::unique_ptr<CameraComponent> _SceneCamera;
		static int _SceneCameraResolutionX;
		static int _SceneCameraResolutionY;
		static float _Velocity;
		static float _Sensitivity;
		static float _LastX;
		static float _LastY;
		static float _LastScrollY;
		static bool _StartMouse;
		static bool _StartScroll;
#pragma endregion


		
		static bool DrawEntityMenu(bool enabled, Entity& entity);
		static void DrawEntityNode(Entity& entity);
		static void InspectComponent(ComponentBase* data, ComponentType type);
	public:
		static void OnGui();
		template<typename T1 = ComponentBase>
		static void AddComponentInspector(const std::function<void(ComponentBase* data)>& func);
		static void Init();
		static void Destroy();
		static void Start();
		static void Update();
		static Entity GetSelectedEntity() { return _SelectedEntity; }
		static void SetSelectedEntity(Entity entity);
	};

	template <typename T1>
	void EditorManager::AddComponentInspector(const std::function<void(ComponentBase* data)>& func)
	{
		_ComponentGUIMap.insert_or_assign(typeid(T1).hash_code(), func);
	}
}
