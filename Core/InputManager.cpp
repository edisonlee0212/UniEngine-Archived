#include "pch.h"
#include "InputManager.h"
using namespace UniEngine;

void InputManager::Init() {
    for (int i = 0; i < 349; i++) {
        _KeyPressed[i] = false;
        _KeyDown[i] = false;
        _KeyUp[i] = false;
        _KeyDownChecked[i] = false;
        _KeyUpChecked[i] = false;
    }
    for (int i = 0; i < 8; i++) {
        _MousePressed[i] = false;
        _MouseDown[i] = false;
        _MouseUp[i] = false;
        _MouseDownChecked[i] = false;
        _MouseUpChecked[i] = false;
    }
    _CursorX = _CursorY = _CursorScrollX = _CursorScrollY = 0;
    _CursorMoved = _CursorScrolled = false;
    _CursorMovedChecked = _CursorScrolledChecked = false;
}
void InputManager::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_UNKNOWN) return;
    if (action == GLFW_PRESS) {
        _KeyPressed[key] = true;
        _KeyDown[key] = true;
        _KeyDownChecked[key] = false;
    }
    else if (action == GLFW_RELEASE) {
        _KeyPressed[key] = false;
        _KeyUp[key] = true;
        _KeyUpChecked[key] = false;
    }
}
void InputManager::MouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
    if (button == GLFW_KEY_UNKNOWN) return;
    if (action == GLFW_PRESS) {
        _MousePressed[button] = true;
        _MouseDown[button] = true;
        _MouseDownChecked[button] = true;
    }
    else if (action == GLFW_RELEASE) {
        _MousePressed[button] = false;
        _MouseUp[button] = true;
        _MouseUpChecked[button] = true;
    }
}
void InputManager::CursorPositionCallback(GLFWwindow* window, double xpos, double ypos) {
    _CursorMoved = true;
    _CursorX = xpos;
    _CursorY = ypos;
}
void InputManager::MouseScrollCallback(GLFWwindow* window, double xpos, double ypos) {
    _CursorScrolled = true;
    _CursorScrollX = xpos;
    _CursorScrollY = ypos;
}
bool InputManager::GetKeyDown(int key) {
    bool down = _KeyDown[key];
    _KeyDownChecked[key] = true;
    return down;
}
bool InputManager::GetKeyUp(int key) {
    bool up = _KeyUp[key];
    _KeyUpChecked[key] = true;
    return up;
}
bool InputManager::GetKey(int key) {
    return _KeyPressed[key];
}
bool InputManager::GetMouseDown(int button) {
    bool down = _MouseDown[button];
    _MouseDownChecked[button] = true;
    return down;
}
bool InputManager::GetMouseUp(int button) {
    bool up = _MouseUp[button];
    _MouseUpChecked[button] = true;
    return up;
}
bool InputManager::GetMouse(int button) {
    return _MousePressed[button];
}
glm::vec2 InputManager::GetMousePosition() {
    return glm::vec2(_CursorX, _CursorY);
}
glm::vec2 InputManager::GetMouseScroll() {
    return glm::vec2(_CursorScrollX, _CursorScrollY);
}
bool InputManager::GetMouseScrolled() {
    bool scrolled = _CursorScrolled;
    _CursorScrolledChecked = true;
    return scrolled;
}
bool InputManager::GetMouseMoved() {
    bool moved = _CursorMoved;
    _CursorMovedChecked = true;
    return moved;
}

void UniEngine::InputManager::Update()
{
    for (auto i = 0; i < 349; i++) {
        if (InputManager::_KeyDownChecked[i]) InputManager::_KeyDown[i] = false;
        if (InputManager::_KeyUpChecked[i]) InputManager::_KeyUp[i] = false;
    }

    for (auto i = 0; i < 8; i++) {
        if (InputManager::_MouseDownChecked[i]) InputManager::_MouseDown[i] = false;
        if (InputManager::_MouseUpChecked[i]) InputManager::_MouseUp[i] = false;
    }

    if (InputManager::_CursorMovedChecked) InputManager::_CursorMoved = false;
    if (InputManager::_CursorScrolledChecked) InputManager::_CursorScrolled = false;
}
