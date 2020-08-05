#include "pch.h"
#include "CameraControlSystem.h"
#include "InputManager.h"
#include "UniEngine.h"
using namespace UniEngine;
void CameraControlSystem::Update()
{
	_CameraRotation = EntityManager::GetComponentData<Rotation>(Engine::GetMainCameraEntity());
	_CameraPosition = EntityManager::GetComponentData<Translation>(Engine::GetMainCameraEntity());
	glm::vec3 position = _CameraPosition.Value;
	glm::vec3 front = _CameraRotation.Value * glm::vec3(0, 0, -1);
	glm::vec3 right = _CameraRotation.Value * glm::vec3(1, 0, 0);
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
		_CameraPosition.Value = position;
		if(!_EnableWindowControl) EntityManager::SetComponentData<Translation>(Engine::GetMainCameraEntity(), _CameraPosition);
		_P[0] = position.x;
		_P[1] = position.y;
		_P[2] = position.z;
	}
	auto mousePosition = InputManager::GetMousePosition();
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
			_CameraRotation.Value = Engine::GetMainCameraComponent()->Value->ProcessMouseMovement(xoffset, yoffset, _Sensitivity);
			EntityManager::SetComponentData<Rotation>(Engine::GetMainCameraEntity(), _CameraRotation);
		}
		mousePosition = InputManager::GetMouseScroll();
		if (!startScroll) {
			_LastScrollY = mousePosition.y;
			startScroll = true;
		}
		float yscrolloffset = -mousePosition.y + _LastScrollY;
		_LastScrollY = mousePosition.y;
		if (yscrolloffset != 0) Engine::GetMainCameraComponent()->Value->ProcessMouseScroll(yscrolloffset);
	}
	if (_EnableWindowControl) {
		ImGui::Begin("Camera Controller");
		ImGui::InputFloat3("Position", &_P[0], 1);
		//ImGui::InputFloat4("Rotation", &_R[0], 1);
		ImGui::End();
		_CameraPosition.Value = glm::vec3(_P[0], _P[1], _P[2]);
		EntityManager::SetComponentData<Translation>(Engine::GetMainCameraEntity(), _CameraPosition);
	}
}

void UniEngine::CameraControlSystem::EnableWindowControl(bool value)
{
	_EnableWindowControl = true;
}


void UniEngine::CameraControlSystem::SetPosition(glm::vec3 position)
{
	_P[0] = position.x;
	_P[1] = position.y;
	_P[2] = position.z;
	_CameraPosition.Value = position;
	EntityManager::SetComponentData<Translation>(Engine::GetMainCameraEntity(), _CameraPosition);
}

void CameraControlSystem::SetVelocity(float velocity)
{
	_Velocity = velocity;
}

void CameraControlSystem::SetSensitivity(float sensitivity)
{
	_Sensitivity = sensitivity;
}
