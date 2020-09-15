#pragma once
#include "UniEngineAPI.h"
namespace UniEngine {
    class UNIENGINE_API InputManager : public ManagerBase
    {
    public:
        static void Init();
        static void CursorPositionCallback(GLFWwindow* window, double xpos, double ypos);
        static void MouseScrollCallback(GLFWwindow* window, double xpos, double ypos);
        static bool GetKey(int key);
        static bool GetMouse(int button);
        static glm::vec2 GetMousePosition();
        static glm::vec2 GetMouseScroll();
        static bool GetMouseScrolled();
        static bool GetMouseMoved();
        static void Update();
        
    private:
        static GLFWwindow* _Window;
        friend class Application;
        friend class WindowManager;
        static void SetWindow(GLFWwindow* window);
        static void SetFocused(bool value);
        static bool _Focused;
        static double _CursorX; 
        static double _CursorY;
        static double _CursorScrollX;
        static double _CursorScrollY;
        static bool _CursorMoved;
        static bool _CursorScrolled;
    };

}
