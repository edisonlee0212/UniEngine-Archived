#include "CameraControlSystem.h"

void CameraControlSystem::Update()
{
	Position cameraPosition = EntityManager::GetComponentData<Position>(_TargetCameraEntity);
	glm::vec3 position = cameraPosition.value;
	glm::vec3 front = _TargetCamera->_Front;
	glm::vec3 right = _TargetCamera->_Right;
	if (InputManager::GetKey(GLFW_KEY_W)) {
		position += glm::vec3(front.x, 0.0f, front.z) * (float)_Time->DeltaTime() * _Velocity;
	}
	if (InputManager::GetKey(GLFW_KEY_S)) {
		position -= glm::vec3(front.x, 0.0f, front.z) * (float)_Time->DeltaTime() * _Velocity;
	}
	if (InputManager::GetKey(GLFW_KEY_A)) {
		position -= glm::vec3(right.x, 0.0f, right.z) * (float)_Time->DeltaTime() * _Velocity;
	}
	if (InputManager::GetKey(GLFW_KEY_D)) {
		position += glm::vec3(right.x, 0.0f, right.z) * (float)_Time->DeltaTime() * _Velocity;
	}
	if (InputManager::GetKey(GLFW_KEY_LEFT_SHIFT)) {
		position.y += _Velocity * (float)_Time->DeltaTime();
	}
	if (InputManager::GetKey(GLFW_KEY_LEFT_CONTROL)) {
		position.y -= _Velocity * (float)_Time->DeltaTime();
	}
	cameraPosition.value = position;
	EntityManager::SetComponentData<Position>(_TargetCameraEntity, cameraPosition);

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
		if (xoffset != 0 || yoffset != 0) _TargetCamera->ProcessMouseMovement(xoffset, yoffset, _Sensitivity);
		mousePosition = InputManager::GetMouseScroll();
		if (!startScroll) {
			_LastScrollY = mousePosition.y;
			startScroll = true;
		}
		float yscrolloffset = -mousePosition.y + _LastScrollY;
		_LastScrollY = mousePosition.y;
		if (yscrolloffset != 0) _TargetCamera->ProcessMouseScroll(yscrolloffset);
	}
}

void CameraControlSystem::SetTargetCamera(Entity targetCameraEntity)
{
	_TargetCameraEntity = targetCameraEntity;
	_TargetCameraComponent = EntityManager::GetSharedComponent<CameraComponent>(_TargetCameraEntity);
	_TargetCamera = _TargetCameraComponent->Value;
}

void CameraControlSystem::SetVelocity(float velocity)
{
	_Velocity = velocity;
}

void CameraControlSystem::SetSensitivity(float sensitivity)
{
	_Sensitivity = sensitivity;
}
