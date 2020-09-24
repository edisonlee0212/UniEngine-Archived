#pragma once
#include "UniEngineAPI.h"
namespace UniEngine {
	enum EntityEditorSystemConfigFlags {
		EntityEditorSystem_None = 0,
		EntityEditorSystem_EnableEntityHierarchy = 1 << 0,
		EntityEditorSystem_EnableEntityInspector = 1 << 1
	};
	class UNIENGINE_API EntityEditorSystem :
		public SystemBase
	{
		static std::map<size_t, std::function<void(ComponentBase* data)>> _ComponentGUIMap;
		unsigned int _ConfigFlags = 0;
		int _SelectedHierarchyDisplayMode = 1;
		static Entity _SelectedEntity;
		bool DrawEntityMenu(bool enabled, Entity& entity);
		void DrawEntityNode(Entity& entity);
		void InspectComponent(ComponentBase* data, ComponentType type);
	public:
		template<typename T1 = ComponentBase>
		static void AddComponentInspector(const std::function<void(ComponentBase* data)>& func);
		void OnCreate() override;
		void OnDestroy() override;
		void Update() override;
		void FixedUpdate() override;
		static Entity GetSelectedEntity() { return _SelectedEntity; }
		static void SetSelectedEntity(Entity entity);
	};

	template <typename T1>
	void EntityEditorSystem::AddComponentInspector(const std::function<void(ComponentBase* data)>& func)
	{
		_ComponentGUIMap.insert_or_assign(typeid(T1).hash_code(), func);
	}
}
