#pragma once
#include "Core.h"
#include "UniEngineAPI.h"
namespace UniEngine {
	enum class FocusMode
	{
		None,
		MainCamera,
		SceneCamera
	};
    class UNIENGINE_API InputManager : public ManagerBase
    {
        friend class EditorManager;
        friend class Application;
    	
    public:
        static void Init();
        static void CursorPositionCallback(GLFWwindow* window, double xpos, double ypos);
        static void MouseScrollCallback(GLFWwindow* window, double xpos, double ypos);
        static bool GetKey(int key, FocusMode mode = FocusMode::MainCamera);
        static bool GetMouse(int button, FocusMode mode = FocusMode::MainCamera);
        static glm::vec2 GetMouseAbsolutePosition(FocusMode mode = FocusMode::MainCamera);
        static glm::vec2 GetMouseScreenPosition(FocusMode mode = FocusMode::MainCamera);
        static glm::vec2 GetMouseScroll(FocusMode mode = FocusMode::MainCamera);
        static bool GetMouseScrolled(FocusMode mode = FocusMode::MainCamera);
        static bool GetMouseMoved(FocusMode mode = FocusMode::MainCamera);
        static void Update();
        static void SetMouseScreenPosition(glm::vec2 value);
    private:
        static void PreUpdate();
        static void LateUpdate();
        static bool _EnableInputMenu;
        static GLFWwindow* _Window;
        friend class Application;
        friend class WindowManager;
        friend class RenderManager;
        static void SetWindow(GLFWwindow* window);
        static void SetFocused(FocusMode mode);
        static FocusMode _FocusMode;
        static double _CursorX; 
        static double _CursorY;
        static double _CursorScrollX;
        static double _CursorScrollY;
        friend class Application;
        static glm::vec2 _MouseScreenPosition;
        static bool _CursorMoved;
        static bool _CursorScrolled;
    };

}
