#include "InputSystem.h"
#include "InputManager.h"
#include "World.h"
using namespace UniEngine;
UniEngine::InputSystem::InputSystem()
{

}

void UniEngine::InputSystem::OnCreate()
{
	glGenBuffers(1, &_CameraMatricesBufferID);
	glBindBuffer(GL_UNIFORM_BUFFER, _CameraMatricesBufferID);
	glBufferData(GL_UNIFORM_BUFFER, 2 * sizeof(float4x4) + sizeof(float4x4), NULL, GL_STATIC_DRAW);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
	glBindBufferRange(GL_UNIFORM_BUFFER, 0, _CameraMatricesBufferID, 0, 2 * sizeof(float4x4));
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
		World::MainCamera()->ProcessKeyboard(FORWARD, Time::DeltaTime());
	if (InputManager::GetKey(GLFW_KEY_S))
		World::MainCamera()->ProcessKeyboard(BACKWARD, Time::DeltaTime());
	if (InputManager::GetKey(GLFW_KEY_A))
		World::MainCamera()->ProcessKeyboard(LEFT, Time::DeltaTime());
	if (InputManager::GetKey(GLFW_KEY_D))
		World::MainCamera()->ProcessKeyboard(RIGHT, Time::DeltaTime());
	if (InputManager::GetKey(GLFW_KEY_LEFT_SHIFT))
		World::MainCamera()->ProcessKeyboard(UP, Time::DeltaTime());
	if (InputManager::GetKey(GLFW_KEY_LEFT_CONTROL))
		World::MainCamera()->ProcessKeyboard(DOWN, Time::DeltaTime());
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
		if (xoffset != 0 || yoffset != 0)World::MainCamera()->ProcessMouseMovement(xoffset, yoffset);
		position = InputManager::GetMouseScroll();
		if (!startScroll) {
			_LastScrollY = position.y;
			startScroll = true;
		}
		float yscrolloffset = -position.y + _LastScrollY;
		_LastScrollY = position.y;
		if (yscrolloffset != 0)World::MainCamera()->ProcessMouseScroll(yscrolloffset);


	}
#pragma endregion
	World::MainCamera()->UpdateViewProj();

	glBindBuffer(GL_UNIFORM_BUFFER, _CameraMatricesBufferID);
	glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(float4x4), &World::MainCamera()->Projection);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
	glBindBuffer(GL_UNIFORM_BUFFER, _CameraMatricesBufferID);
	glBufferSubData(GL_UNIFORM_BUFFER, sizeof(float4x4), sizeof(float4x4), &World::MainCamera()->View);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
	glBindBuffer(GL_UNIFORM_BUFFER, _CameraMatricesBufferID);
	glBufferSubData(GL_UNIFORM_BUFFER, 2 * sizeof(float4x4), sizeof(float3), &World::MainCamera()->Position);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);

}
