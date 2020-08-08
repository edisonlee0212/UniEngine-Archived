#include "pch.h"
#include "InputManager.h"
#include "WindowManager.h"
using namespace UniEngine;

double InputManager::_CursorX;
double InputManager::_CursorY;
double InputManager::_CursorScrollX;
double InputManager::_CursorScrollY;
bool InputManager::_CursorMoved;
bool InputManager::_CursorScrolled;

bool InputManager::_Focused;

inline void InputManager::Init() {
    _CursorX = _CursorY = _CursorScrollX = _CursorScrollY = 0;
    _CursorMoved = _CursorScrolled = false;
}

inline void InputManager::CursorPositionCallback(GLFWwindow* window, double xpos, double ypos) {
    if (window != WindowManager::GetWindow()) return;
    _CursorMoved = true;
    _CursorX = xpos;
    _CursorY = ypos;
}
inline void InputManager::MouseScrollCallback(GLFWwindow* window, double xpos, double ypos) {
    if (window != WindowManager::GetWindow()) return;
    _CursorScrolled = true;
    _CursorScrollX = xpos;
    _CursorScrollY = ypos;
}

inline bool InputManager::GetKey(int key) {
    return _Focused && glfwGetKey(WindowManager::GetWindow(), key) == GLFW_PRESS;
}

inline bool InputManager::GetMouse(int button) {
    return _Focused && glfwGetMouseButton(WindowManager::GetWindow(), button) == GLFW_PRESS;
}
inline glm::vec2 InputManager::GetMousePosition() {
    if(!_Focused) return glm::vec2(_CursorX, _CursorY);
    else {
        double x = 0;
        double y = 0;
        glfwGetCursorPos(WindowManager::GetWindow(), &x, &y);
        return glm::vec2(x, y);
    }
}
inline glm::vec2 InputManager::GetMouseScroll() {
    return glm::vec2(_CursorScrollX, _CursorScrollY);
}
inline bool InputManager::GetMouseScrolled() {
    return _CursorScrolled;
}
inline bool InputManager::GetMouseMoved() {
    return _CursorMoved;
}

inline void UniEngine::InputManager::Update()
{
    InputManager::_CursorMoved = false;
    InputManager::_CursorScrolled = false;
}

inline void UniEngine::InputManager::SetFocused(bool value)
{
    _Focused = value;
}
