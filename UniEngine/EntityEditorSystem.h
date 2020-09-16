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
        std::map<size_t, std::function<void(ComponentBase* data)>> _ComponentGUIMap;
        unsigned int _ConfigFlags = 0;
        int _SelectedHierarchyDisplayMode = 1;
        Entity _SelectedEntity;
        void DrawEntityMenu(bool enabled, Entity& entity);
        void DrawEntityNode(Entity& entity);
        void InspectComponent(ComponentBase* data, ComponentType type);
    public:
        void AddComponentInspector(ComponentType type, const std::function<void(ComponentBase* data)>& func);
        void OnCreate() override;
        void OnDestroy() override;
        void Update() override;
        void FixedUpdate() override;
        Entity GetSelectedEntity() const;
    };
}
