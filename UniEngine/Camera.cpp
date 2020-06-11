#include "pch.h"
#include "Camera.h"
#include "WindowManager.h"

using namespace UniEngine;

void UniEngine::Camera::UpdateMatrices(glm::vec3 position)
{
	// Calculate the new Front vector
	glm::vec3 front;
	front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
	front.y = sin(glm::radians(Pitch));
	front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
	_Front = glm::normalize(front);
	// Also re-calculate the Right and Up vector
	_Right = glm::normalize(glm::cross(_Front, glm::vec3(0.0f, 1.0f, 0.0f)));  // Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
	_Up = glm::normalize(glm::cross(_Right, _Front));

	View = glm::lookAt(position, position + _Front, _Up);
	auto ratio = _RenderTarget->GetResolutionRatio();
	if (ratio == 0) return;
	Projection = glm::perspective(glm::radians(Zoom), ratio, 0.1f, 100.0f);

	glBindBuffer(GL_UNIFORM_BUFFER, _CameraInfoBufferID);
	glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glm::mat4), glm::value_ptr(Projection));
	glBufferSubData(GL_UNIFORM_BUFFER, sizeof(glm::mat4), sizeof(glm::mat4), glm::value_ptr(View));
	glBufferSubData(GL_UNIFORM_BUFFER, 2 * sizeof(glm::mat4), sizeof(glm::vec3), glm::value_ptr(position));
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

Camera::Camera(RenderTarget* renderTarget, float yaw, float pitch) : _Front(glm::vec3(0.0f, 0.0f, -1.0f)), Zoom(ZOOM)
{
	_RenderTarget = renderTarget;
	Yaw = yaw;
	Pitch = pitch;
}

void UniEngine::Camera::ProcessMouseMovement(float xoffset, float yoffset, float sensitivity, GLboolean constrainPitch)
{
	xoffset *= sensitivity;
	yoffset *= sensitivity;

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