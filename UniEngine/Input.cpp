#include "Input.h"
using namespace UniEngine;

double Input::_CursorX, Input::_CursorY, Input::_CursorScrollX, Input::_CursorScrollY;
bool Input::_CursorMoved, Input::_CursorScrolled;
bool Input::_KeyPressed[349];
bool Input::_KeyDown[349];
bool Input::_KeyUp[349];
bool Input::_MousePressed[8];
bool Input::_MouseDown[8];
bool Input::_MouseUp[8];

Input::Input() {
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
void Input::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
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
void Input::MouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
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
void Input::CursorPositionCallback(GLFWwindow* window, double xpos, double ypos) {
    _CursorMoved = true;
    _CursorX = xpos;
    _CursorY = ypos;
}
void Input::MouseScrollCallback(GLFWwindow* window, double xpos, double ypos) {
    _CursorScrolled = true;
    _CursorScrollX = xpos;
    _CursorScrollY = ypos;
}
bool Input::GetKeyDown(int key) {
    bool down = _KeyDown[key];
    _KeyDownChecked[key] = true;
    return down;
}
bool Input::GetKeyUp(int key) {
    bool up = _KeyUp[key];
    _KeyUpChecked[key] = true;
    return up;
}
bool Input::GetKey(int key) {
    return _KeyPressed[key];
}
bool Input::GetMouseDown(int button) {
    bool down = _MouseDown[button];
    _MouseDownChecked[button] = true;
    return down;
}
bool Input::GetMouseUp(int button) {
    bool up = _MouseUp[button];
    _MouseUpChecked[button] = true;
    return up;
}
bool Input::GetMouse(int button) {
    return _MousePressed[button];
}
float2 Input::GetMousePosition() {
    return float2(_CursorX, _CursorY);
}
float2 Input::GetMouseScroll() {
    return float2(_CursorScrollX, _CursorScrollY);
}
bool Input::GetMouseScrolled() {
    bool scrolled = _CursorScrolled;
    _CursorScrolledChecked = true;
    return scrolled;
}
bool Input::GetMouseMoved() {
    bool moved = _CursorMoved;
    _CursorMovedChecked = true;
    return moved;
}