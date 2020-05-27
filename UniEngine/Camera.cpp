#include "Camera.h"
#include "WindowManager.h"

using namespace UniEngine;

unsigned Camera::_CameraInfoBufferID;

void UniEngine::Camera::UpdateMatrices()
{
	glBindBuffer(GL_UNIFORM_BUFFER, _CameraInfoBufferID);
	glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glm::mat4), glm::value_ptr(Projection));
	glBufferSubData(GL_UNIFORM_BUFFER, sizeof(glm::mat4), sizeof(glm::mat4), glm::value_ptr(View));
	glBufferSubData(GL_UNIFORM_BUFFER, 2 * sizeof(glm::mat4), sizeof(glm::vec3), glm::value_ptr(_Position));
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

void UniEngine::Camera::GenerateMatrices()
{
	glGenBuffers(1, &_CameraInfoBufferID);
	glBindBuffer(GL_UNIFORM_BUFFER, _CameraInfoBufferID);
	glBufferData(GL_UNIFORM_BUFFER, 2 * sizeof(glm::mat4) + sizeof(glm::vec4), NULL, GL_STATIC_DRAW);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
	glBindBufferRange(GL_UNIFORM_BUFFER, 0, _CameraInfoBufferID, 0, 2 * sizeof(glm::mat4));
	
}

RenderTarget* UniEngine::Camera::GetRenderTarget()
{
	return _RenderTarget;
}

Camera::Camera(RenderTarget* renderTarget, glm::vec3 position, glm::vec3 up, float yaw, float pitch) : _Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
{
	_RenderTarget = renderTarget;
	_Position = position;
	_WorldUp = up;
	Yaw = yaw;
	Pitch = pitch;
	UpdateCameraVectors();
}
// Constructor with scalar values
Camera::Camera(RenderTarget* renderTarget, float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch) : _Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
{
	_RenderTarget = renderTarget;
	_Position = glm::vec3(posX, posY, posZ);
	_WorldUp = glm::vec3(upX, upY, upZ);
	Yaw = yaw;
	Pitch = pitch;
	UpdateCameraVectors();
}

glm::vec3 UniEngine::Camera::ProcessKeyboard(Camera_Movement direction, float deltaTime)
{
	float velocity = MovementSpeed * deltaTime;
	if (direction == FORWARD)
		_Position += glm::vec3(_Front.x, 0.0f, _Front.z) * velocity;
	if (direction == BACKWARD)
		_Position -= glm::vec3(_Front.x, 0.0f, _Front.z) * velocity;
	if (direction == LEFT)
		_Position -= glm::vec3(_Right.x, 0.0f, _Right.z) * velocity;
	if (direction == RIGHT)
		_Position += glm::vec3(_Right.x, 0.0f, _Right.z) * velocity;
	if (direction == UP)
		_Position.y += velocity;
	if (direction == DOWN)
		_Position.y -= velocity;
	return _Position;
}

void UniEngine::Camera::ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch)
{
	xoffset *= MouseSensitivity;
	yoffset *= MouseSensitivity;

	Yaw += xoffset;
	Pitch += yoffset;

	// Make sure that when pitch is out of bounds, screen doesn't get flipped
	if (constrainPitch)
	{
		if (Pitch > 89.0f)
			Pitch = 89.0f;
		if (Pitch < -89.0f)
			Pitch = -89.0f;
	}

	// Update Front, Right and Up Vectors using the updated Euler angles
	UpdateCameraVectors();
}

void UniEngine::Camera::ProcessMouseScroll(float yoffset)
{
	if (Zoom >= 1.0f && Zoom <= 45.0f)
		Zoom -= yoffset;
	if (Zoom <= 1.0f)
		Zoom = 1.0f;
	if (Zoom >= 45.0f)
		Zoom = 45.0f;
}

void UniEngine::Camera::UpdateCameraVectors()
{
	// Calculate the new Front vector
	glm::vec3 front;
	front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
	front.y = sin(glm::radians(Pitch));
	front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
	_Front = glm::normalize(front);
	// Also re-calculate the Right and Up vector
	_Right = glm::normalize(glm::cross(_Front, _WorldUp));  // Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
	_Up = glm::normalize(glm::cross(_Right, _Front));
	UpdateViewProj();
}

void Camera::UpdateViewProj() {
	View = glm::lookAt(_Position, _Position + _Front, _Up);
	auto size = _RenderTarget->GetResolution();
	if (size.x == 0 || size.y == 0) return;
	Projection = glm::perspective(glm::radians(Zoom), size.x / size.y, 0.1f, 100.0f);
}
