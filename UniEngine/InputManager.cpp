#include "pch.h"
#include "InputManager.h"
#include "WindowManager.h"
using namespace UniEngine;

double InputManager::_CursorX;
double InputManager::_CursorY;
double InputManager::_CursorScrollX;
double InputManager::_CursorScrollY;
bool InputManager::_CursorMoved;
bool InputManager::_EnableInputMenu;
bool InputManager::_CursorScrolled;
GLFWwindow* InputManager::_Window;
bool InputManager::_Focused;
glm::vec2 InputManager::_MouseScreenPosition;

inline void InputManager::Init() {
	_CursorX = _CursorY = _CursorScrollX = _CursorScrollY = 0;
	_CursorMoved = _CursorScrolled = false;
}

inline void InputManager::CursorPositionCallback(GLFWwindow* window, double xpos, double ypos) {
	if (window != _Window) return;
	_CursorMoved = true;
	_CursorX = xpos;
	_CursorY = ypos;
}
inline void InputManager::MouseScrollCallback(GLFWwindow* window, double xpos, double ypos) {
	if (window != _Window) return;
	_CursorScrolled = true;
	_CursorScrollX = xpos;
	_CursorScrollY = ypos;
}

inline bool InputManager::GetKey(int key) {
	return _Focused && glfwGetKey(_Window, key) == GLFW_PRESS;
}

inline bool InputManager::GetMouse(int button) {
	return _Focused && glfwGetMouseButton(_Window, button) == GLFW_PRESS;
}
inline glm::vec2 InputManager::GetMouseAbsolutePosition() {
	if (!_Focused) return glm::vec2(_CursorX, _CursorY);

	double x = 0;
	double y = 0;
	glfwGetCursorPos(_Window, &x, &y);
	return glm::vec2(x, y);

}

inline glm::vec2 InputManager::GetMouseScreenPosition()
{
	return _MouseScreenPosition;
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

void InputManager::SetMouseScreenPosition(glm::vec2 value)
{
	_MouseScreenPosition = value;
}

void InputManager::OnGui()
{
	if (ImGui::BeginMainMenuBar()) {
		if (ImGui::BeginMenu("View"))
		{
			ImGui::Checkbox("Input Manager", &_EnableInputMenu);
			ImGui::EndMenu();
		}
		ImGui::EndMainMenuBar();
	}
	if (_EnableInputMenu)
	{
		ImGui::Begin("Input Manager");
		ImGui::End();
	}
}

void UniEngine::InputManager::SetWindow(GLFWwindow* window)
{
	if (window == nullptr || window == _Window) return;
	_Window = window;
	glfwSetCursorPosCallback(window, CursorPositionCallback);
	glfwSetScrollCallback(window, MouseScrollCallback);
}

inline void UniEngine::InputManager::SetFocused(bool value)
{
	_Focused = value;
}
