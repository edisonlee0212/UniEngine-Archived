#include "pch.h"
#include "InputManager.h"
#include "UniEngine.h"
#include "EditorManager.h"
#include "imgui_internal.h"
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
FocusMode InputManager::_FocusMode;
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

inline bool InputManager::GetKey(int key, FocusMode mode) {
	return _FocusMode == mode && glfwGetKey(_Window, key) == GLFW_PRESS;
}

inline bool InputManager::GetMouse(int button, FocusMode mode) {
	return _FocusMode == mode && glfwGetMouseButton(_Window, button) == GLFW_PRESS;
}
inline glm::vec2 InputManager::GetMouseAbsolutePosition(FocusMode mode) {
	if (_FocusMode != mode) return glm::vec2(_CursorX, _CursorY);

	double x = 0;
	double y = 0;
	glfwGetCursorPos(_Window, &x, &y);
	return glm::vec2(x, y);

}

inline glm::vec2 InputManager::GetMouseScreenPosition(FocusMode mode)
{
	return _FocusMode == mode ? _MouseScreenPosition : glm::vec2(FLT_MAX, FLT_MAX);
}

inline glm::vec2 InputManager::GetMouseScroll(FocusMode mode) {
	return glm::vec2(_CursorScrollX, _CursorScrollY);
}
inline bool InputManager::GetMouseScrolled(FocusMode mode) {
	return _CursorScrolled;
}
inline bool InputManager::GetMouseMoved(FocusMode mode) {
	return _CursorMoved;
}

inline void InputManager::Update()
{
	_CursorMoved = false;
	_CursorScrolled = false;
}

void InputManager::SetMouseScreenPosition(glm::vec2 value)
{
	_MouseScreenPosition = value;
}

void InputManager::PreUpdate()
{
	_FocusMode = FocusMode::None;
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0, 0 });
	_MouseScreenPosition = glm::vec2(FLT_MAX, FLT_MAX);
	ImGui::Begin("Scene");
	{

		EditorManager::_SceneCamera->SetEnabled(!(ImGui::GetCurrentWindowRead()->Hidden && !ImGui::GetCurrentWindowRead()->Collapsed));

		if (ImGui::IsWindowFocused(ImGuiFocusedFlags_RootAndChildWindows)) {
			ImGuiViewport* viewPort = ImGui::GetWindowViewport();
			SetWindow((GLFWwindow*)viewPort->PlatformHandle);
			SetFocused(FocusMode::SceneCamera);

			static int corner = 1;
			ImGuiIO& io = ImGui::GetIO();
			auto viewPortSize = ImGui::GetWindowSize();
			auto overlayPos = ImGui::GetWindowPos();
			ImVec2 window_pos = ImVec2((corner & 1) ? (overlayPos.x + viewPortSize.x) : (overlayPos.x), (corner & 2) ? (overlayPos.y + viewPortSize.y) : (overlayPos.y));
			if (ImGui::IsMousePosValid()) {
				float x = io.MousePos.x - window_pos.x;
				float y = io.MousePos.y - window_pos.y;
				_MouseScreenPosition = glm::vec2(x, y);
			}
		}

	}
	ImGui::End();
	ImGui::Begin("Camera");
	{
		if (ImGui::IsWindowFocused(ImGuiFocusedFlags_RootAndChildWindows)) {
			ImGuiViewport* viewPort = ImGui::GetWindowViewport();
			SetWindow((GLFWwindow*)viewPort->PlatformHandle);
			SetFocused(FocusMode::MainCamera);

			static int corner = 1;
			ImGuiIO& io = ImGui::GetIO();
			auto viewPortSize = ImGui::GetWindowSize();
			auto overlayPos = ImGui::GetWindowPos();
			ImVec2 window_pos = ImVec2((corner & 1) ? (overlayPos.x + viewPortSize.x) : (overlayPos.x), (corner & 2) ? (overlayPos.y + viewPortSize.y) : (overlayPos.y));
			if (ImGui::IsMousePosValid()) {
				float x = io.MousePos.x - window_pos.x;
				float y = io.MousePos.y - window_pos.y;
				_MouseScreenPosition = glm::vec2(x, y);
			}
		}
	}
	ImGui::End();
	ImGui::PopStyleVar();

}

void InputManager::LateUpdate()
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

inline void UniEngine::InputManager::SetFocused(FocusMode mode)
{
	_FocusMode = mode;
}
