#pragma once
#include "Core.h"
#include "UniEngineAPI.h"
struct ImGuiWindow;

namespace UniEngine {
    class UNIENGINE_API InputManager : public ManagerBase
    {
        friend class EditorManager;
        friend class Application;
    	
    public:
        static void Init();
        static bool GetKey(int key);
        static bool GetMouse(int button);
        static glm::vec2 GetMouseAbsolutePosition();
        static glm::vec2 GetMouseScreenPosition(ImGuiWindow* window, int corner = 1);
        static void Update();
    private:
        static void PreUpdate();
        static void LateUpdate();
        static bool _EnableInputMenu;
        friend class Application;
        friend class WindowManager;
        friend class RenderManager;
        friend class Application;
    };

}
