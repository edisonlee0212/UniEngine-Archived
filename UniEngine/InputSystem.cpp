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
	glBufferData(GL_UNIFORM_BUFFER, 2 * sizeof(glm::mat4) + sizeof(glm::vec4), NULL, GL_STATIC_DRAW);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
	glBindBufferRange(GL_UNIFORM_BUFFER, 0, _CameraMatricesBufferID, 0, 2 * sizeof(glm::mat4));
	
	
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
	_World->MainCamera()->UpdateViewProj();

	glBindBuffer(GL_UNIFORM_BUFFER, _CameraMatricesBufferID);
	glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glm::mat4), glm::value_ptr(_World->MainCamera()->Projection));
	glBufferSubData(GL_UNIFORM_BUFFER, sizeof(glm::mat4), sizeof(glm::mat4), glm::value_ptr(_World->MainCamera()->View));
	glBufferSubData(GL_UNIFORM_BUFFER, 2 * sizeof(glm::mat4), sizeof(glm::vec3), glm::value_ptr(_World->MainCamera()->Position));
	glBindBuffer(GL_UNIFORM_BUFFER, 0);

}
