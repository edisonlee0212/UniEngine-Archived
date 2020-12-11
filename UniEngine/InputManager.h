#pragma once
#include "Core.h"
#include "UniEngineAPI.h"
struct ImGuiWindow;

namespace UniEngine {
    class UNIENGINE_API InputManager : public ManagerBase
    {
        friend class EditorManager;
        friend class Application;
        static bool GetMousePositionInternal(ImGuiWindow* window, glm::vec2& pos);
        static void PreUpdate();
        static void LateUpdate();
        static bool _EnableInputMenu;
        friend class Application;
        friend class WindowManager;
        friend class RenderManager;
        friend class Application;
        static bool GetKeyInternal(int key, GLFWwindow* window);
        static bool GetMouseInternal(int button, GLFWwindow* window);
        static glm::vec2 GetMouseAbsolutePositionInternal(GLFWwindow* window);
    public:
        static void Init();
        static bool GetKey(int key);
        static bool GetMouse(int button);
        static glm::vec2 GetMouseAbsolutePosition();
        static bool GetMousePosition(glm::vec2& pos);
        static void Update();
    };

}
