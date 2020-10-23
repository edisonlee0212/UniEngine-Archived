#include "pch.h"
#include "CameraControlSystem.h"
#include "InputManager.h"
#include "UniEngine.h"
using namespace UniEngine;
void CameraControlSystem::Update()
{
	auto rc = EntityManager::GetComponentData<Rotation>(Application::GetMainCameraEntity());
	auto pc = EntityManager::GetComponentData<Translation>(Application::GetMainCameraEntity());
	glm::vec3 position = pc.Value;
	glm::vec3 front = rc.Value * glm::vec3(0, 0, -1);
	glm::vec3 right = rc.Value * glm::vec3(1, 0, 0);
	bool moved = false;
	if (InputManager::GetKey(GLFW_KEY_W)) {
		position += glm::vec3(front.x, 0.0f, front.z) * (float)_Time->DeltaTime() * _Velocity;
		moved = true;
	}
	if (InputManager::GetKey(GLFW_KEY_S)) {
		position -= glm::vec3(front.x, 0.0f, front.z) * (float)_Time->DeltaTime() * _Velocity;
		moved = true;
	}
	if (InputManager::GetKey(GLFW_KEY_A)) {
		position -= glm::vec3(right.x, 0.0f, right.z) * (float)_Time->DeltaTime() * _Velocity;
		moved = true;
	}
	if (InputManager::GetKey(GLFW_KEY_D)) {
		position += glm::vec3(right.x, 0.0f, right.z) * (float)_Time->DeltaTime() * _Velocity;
		moved = true;
	}
	if (InputManager::GetKey(GLFW_KEY_LEFT_SHIFT)) {
		position.y += _Velocity * (float)_Time->DeltaTime();
		moved = true;
	}
	if (InputManager::GetKey(GLFW_KEY_LEFT_CONTROL)) {
		position.y -= _Velocity * (float)_Time->DeltaTime();
		moved = true;
	}
	if (moved) {
		pc.Value = position;
		EntityManager::SetComponentData<Translation>(Application::GetMainCameraEntity(), pc);
	}
	auto mousePosition = InputManager::GetMouseAbsolutePosition();
	if (!startMouse) {
		_LastX = mousePosition.x;
		_LastY = mousePosition.y;
		startMouse = true;
	}
	float xoffset = mousePosition.x - _LastX;
	float yoffset = -mousePosition.y + _LastY;
	_LastX = mousePosition.x;
	_LastY = mousePosition.y;
	if (InputManager::GetMouse(GLFW_MOUSE_BUTTON_RIGHT)) {
		if (xoffset != 0 || yoffset != 0) {
			rc.Value = Application::GetMainCameraComponent()->get()->Value->ProcessMouseMovement(xoffset, yoffset, _Sensitivity);
			EntityManager::SetComponentData<Rotation>(Application::GetMainCameraEntity(), rc);
		}
		mousePosition = InputManager::GetMouseScroll();
		if (!startScroll) {
			_LastScrollY = mousePosition.y;
			startScroll = true;
		}
		float yscrolloffset = -mousePosition.y + _LastScrollY;
		_LastScrollY = mousePosition.y;
		if (yscrolloffset != 0) Application::GetMainCameraComponent()->get()->Value->ProcessMouseScroll(yscrolloffset);
	}
}



void CameraControlSystem::SetVelocity(float velocity)
{
	_Velocity = velocity;
}

void CameraControlSystem::SetSensitivity(float sensitivity)
{
	_Sensitivity = sensitivity;
}
