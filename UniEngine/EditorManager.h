#pragma once
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
		static std::map<size_t, std::function<void(ComponentBase* data)>> _ComponentGUIMap;
		static unsigned int _ConfigFlags;
		static int _SelectedHierarchyDisplayMode;
		static Entity _SelectedEntity;
		static bool _DisplayLog;
		static bool _DisplayError;
		static bool DrawEntityMenu(bool enabled, Entity& entity);
		static void DrawEntityNode(Entity& entity);
		static void InspectComponent(ComponentBase* data, ComponentType type);
	public:
		template<typename T1 = ComponentBase>
		static void AddComponentInspector(const std::function<void(ComponentBase* data)>& func);
		static void Init();
		static void Destroy();
		static void Start();
		static void Update();
		static void LateUpdate();
		static Entity GetSelectedEntity() { return _SelectedEntity; }
		static void SetSelectedEntity(Entity entity);
	};

	template <typename T1>
	void EditorManager::AddComponentInspector(const std::function<void(ComponentBase* data)>& func)
	{
		_ComponentGUIMap.insert_or_assign(typeid(T1).hash_code(), func);
	}
}
