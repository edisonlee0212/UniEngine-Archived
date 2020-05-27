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
