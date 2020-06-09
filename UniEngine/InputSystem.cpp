#include "InputSystem.h"
#include "InputManager.h"
#include "World.h"
using namespace UniEngine;
UniEngine::InputSystem::InputSystem()
{
}

void UniEngine::InputSystem::OnCreate()
{
	Enable();
}

void UniEngine::InputSystem::OnDestroy()
{
	Disable();
}

void UniEngine::InputSystem::Update()
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

#pragma region Handle Movement
	if (InputManager::GetKey(GLFW_KEY_W))
		_World->MainCamera()->ProcessKeyboard(FORWARD, Time::DeltaTime());
	if (InputManager::GetKey(GLFW_KEY_S))
		_World->MainCamera()->ProcessKeyboard(BACKWARD, Time::DeltaTime());
	if (InputManager::GetKey(GLFW_KEY_A))
		_World->MainCamera()->ProcessKeyboard(LEFT, Time::DeltaTime());
	if (InputManager::GetKey(GLFW_KEY_D))
		_World->MainCamera()->ProcessKeyboard(RIGHT, Time::DeltaTime());
	if (InputManager::GetKey(GLFW_KEY_LEFT_SHIFT))
		_World->MainCamera()->ProcessKeyboard(UP, Time::DeltaTime());
	if (InputManager::GetKey(GLFW_KEY_LEFT_CONTROL))
		_World->MainCamera()->ProcessKeyboard(DOWN, Time::DeltaTime());
#pragma endregion
#pragma region HandleMouse
	auto position = InputManager::GetMousePosition();
	if (!startMouse) {
		_LastX = position.x;
		_LastY = position.y;
		startMouse = true;
	}
	float xoffset = position.x - _LastX;
	float yoffset = -position.y + _LastY;
	_LastX = position.x;
	_LastY = position.y;
	if (InputManager::GetMouse(GLFW_MOUSE_BUTTON_RIGHT)) {
		if (xoffset != 0 || yoffset != 0)_World->MainCamera()->ProcessMouseMovement(xoffset, yoffset);
		position = InputManager::GetMouseScroll();
		if (!startScroll) {
			_LastScrollY = position.y;
			startScroll = true;
		}
		float yscrolloffset = -position.y + _LastScrollY;
		_LastScrollY = position.y;
		if (yscrolloffset != 0)_World->MainCamera()->ProcessMouseScroll(yscrolloffset);


	}
#pragma endregion
}
