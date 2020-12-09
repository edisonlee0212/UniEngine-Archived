#include "pch.h"
#include "InputManager.h"
#include "UniEngine.h"
#include "EditorManager.h"
#include "imgui_internal.h"
#include "WindowManager.h"
using namespace UniEngine;
bool InputManager::_EnableInputMenu = false;

inline void InputManager::Init() {
}

inline bool InputManager::GetKey(int key) {
	auto state = glfwGetKey(WindowManager::GetWindow(), key);
	return state == GLFW_PRESS || state == GLFW_REPEAT;
}

inline bool InputManager::GetMouse(int button) {
	return glfwGetMouseButton(WindowManager::GetWindow(), button) == GLFW_PRESS;
}
inline glm::vec2 InputManager::GetMouseAbsolutePosition() {
	double x = 0;
	double y = 0;
	glfwGetCursorPos(WindowManager::GetWindow(), &x, &y);
	return glm::vec2(x, y);
}

inline glm::vec2 InputManager::GetMouseScreenPosition(ImGuiWindow* window, int corner)
{
	ImGuiIO& io = ImGui::GetIO();
	auto viewPortSize = window->Size;
	auto overlayPos = window->Pos;
	ImVec2 window_pos = ImVec2((corner & 1) ? (overlayPos.x + viewPortSize.x) : (overlayPos.x), (corner & 2) ? (overlayPos.y + viewPortSize.y) : (overlayPos.y));
	if (ImGui::IsMousePosValid()) {
		float x = io.MousePos.x - window_pos.x;
		float y = io.MousePos.y - window_pos.y;
		return glm::vec2(x, y);
	}
	return glm::vec2(FLT_MIN, FLT_MIN);
}

inline void InputManager::Update()
{
}

void InputManager::PreUpdate()
{
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

