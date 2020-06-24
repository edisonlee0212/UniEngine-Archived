#include "pch.h"
#include "Camera.h"
#include "WindowManager.h"

using namespace UniEngine;

GLUBO* Camera::_CameraData;

void UniEngine::Camera::CalculatePlanes(Plane* planes)
{
	glm::mat4 comboMatrix = _Projection * glm::transpose(_View);

	planes[0].a = comboMatrix[3][0] + comboMatrix[0][0];
	planes[0].b = comboMatrix[3][1] + comboMatrix[0][1];
	planes[0].c = comboMatrix[3][2] + comboMatrix[0][2];
	planes[0].d = comboMatrix[3][3] + comboMatrix[0][3];

	planes[1].a = comboMatrix[3][0] - comboMatrix[0][0];
	planes[1].b = comboMatrix[3][1] - comboMatrix[0][1];
	planes[1].c = comboMatrix[3][2] - comboMatrix[0][2];
	planes[1].d = comboMatrix[3][3] - comboMatrix[0][3];

	planes[2].a = comboMatrix[3][0] - comboMatrix[1][0];
	planes[2].b = comboMatrix[3][1] - comboMatrix[1][1];
	planes[2].c = comboMatrix[3][2] - comboMatrix[1][2];
	planes[2].d = comboMatrix[3][3] - comboMatrix[1][3];

	planes[3].a = comboMatrix[3][0] + comboMatrix[1][0];
	planes[3].b = comboMatrix[3][1] + comboMatrix[1][1];
	planes[3].c = comboMatrix[3][2] + comboMatrix[1][2];
	planes[3].d = comboMatrix[3][3] + comboMatrix[1][3];

	planes[4].a = comboMatrix[3][0] + comboMatrix[2][0];
	planes[4].b = comboMatrix[3][1] + comboMatrix[2][1];
	planes[4].c = comboMatrix[3][2] + comboMatrix[2][2];
	planes[4].d = comboMatrix[3][3] + comboMatrix[2][3];

	planes[5].a = comboMatrix[3][0] - comboMatrix[2][0];
	planes[5].b = comboMatrix[3][1] - comboMatrix[2][1];
	planes[5].c = comboMatrix[3][2] - comboMatrix[2][2];
	planes[5].d = comboMatrix[3][3] - comboMatrix[2][3];

	planes[0].Normalize();
	planes[1].Normalize();
	planes[2].Normalize();
	planes[3].Normalize();
	planes[4].Normalize();
	planes[5].Normalize();

}

void UniEngine::Camera::CalculateFrustumPoints(glm::vec3 cameraPos, glm::vec3* points, float nearPlane, float farPlane)
{
	glm::vec3 nearCenter = _Front * nearPlane;
	glm::vec3 farCenter = _Front * farPlane;

	float e = tanf(glm::radians(_FOV * 0.5f));
	float near_ext_y = e * nearPlane;
	float near_ext_x = near_ext_y * _RenderTarget->GetResolutionRatio();
	float far_ext_y = e * farPlane;
	float far_ext_x = far_ext_y * _RenderTarget->GetResolutionRatio();

	points[0] = cameraPos + nearCenter - _Right * near_ext_x - _Up * near_ext_y;
	points[1] = cameraPos + nearCenter - _Right * near_ext_x + _Up * near_ext_y;
	points[2] = cameraPos + nearCenter + _Right * near_ext_x + _Up * near_ext_y;
	points[3] = cameraPos + nearCenter + _Right * near_ext_x - _Up * near_ext_y;
	points[4] = cameraPos + farCenter - _Right * far_ext_x - _Up * far_ext_y;
	points[5] = cameraPos + farCenter - _Right * far_ext_x + _Up * far_ext_y;
	points[6] = cameraPos + farCenter + _Right * far_ext_x + _Up * far_ext_y;
	points[7] = cameraPos + farCenter + _Right * far_ext_x - _Up * far_ext_y;
}

void UniEngine::Camera::UpdateMatrices(glm::vec3 position)
{
	// Calculate the new Front vector
	glm::vec3 front;
	front.x = cos(glm::radians(_Yaw)) * cos(glm::radians(_Pitch));
	front.y = sin(glm::radians(_Pitch));
	front.z = sin(glm::radians(_Yaw)) * cos(glm::radians(_Pitch));
	_Front = glm::normalize(front);
	// Also re-calculate the Right and Up vector
	_Right = glm::normalize(glm::cross(_Front, glm::vec3(0.0f, 1.0f, 0.0f)));  // Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
	_Up = glm::normalize(glm::cross(_Right, _Front));

	_View = glm::lookAt(position, position + _Front, _Up);
	auto ratio = _RenderTarget->GetResolutionRatio();
	if (ratio == 0) return;
	_Projection = glm::perspective(glm::radians(_FOV * 0.5f), ratio, _Near, _Far);

	_CameraData->SubData(0, sizeof(glm::mat4), glm::value_ptr(_Projection));
	_CameraData->SubData(sizeof(glm::mat4), sizeof(glm::mat4), glm::value_ptr(_View));
	_CameraData->SubData(2 * sizeof(glm::mat4), sizeof(glm::vec3), glm::value_ptr(position));
}

void UniEngine::Camera::GenerateMatrices()
{
	_CameraData = new GLUBO();
	_CameraData->SetData(2 * sizeof(glm::mat4) + sizeof(glm::vec4), NULL, GL_STATIC_DRAW);
	_CameraData->SetRange(0, 0, 2 * sizeof(glm::mat4));
}

RenderTarget* UniEngine::Camera::GetRenderTarget()
{
	return _RenderTarget;
}

Camera::Camera(RenderTarget* renderTarget, float yaw, float pitch, float nearPlane, float farPlane) : _Front(glm::vec3(0.0f, 0.0f, -1.0f)), _FOV(DEFAULTFOV)
{
	_RenderTarget = renderTarget;
	_Yaw = yaw;
	_Pitch = pitch;
	_Near = nearPlane;
	_Far = farPlane;
}

void UniEngine::Camera::ProcessMouseMovement(float xoffset, float yoffset, float sensitivity, GLboolean constrainPitch)
{
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	_Yaw += xoffset;
	_Pitch += yoffset;

	// Make sure that when pitch is out of bounds, screen doesn't get flipped
	if (constrainPitch)
	{
		if (_Pitch > 89.0f)
			_Pitch = 89.0f;
		if (_Pitch < -89.0f)
			_Pitch = -89.0f;
	}
}

void UniEngine::Camera::ProcessMouseScroll(float yoffset)
{
	if (_FOV >= 1.0f && _FOV <= 180.0f)
		_FOV -= yoffset;
	if (_FOV <= 1.0f)
		_FOV = 1.0f;
	if (_FOV >= 180.0f)
		_FOV = 180.0f;
}

void UniEngine::Plane::Normalize()
{
	float mag = glm::sqrt(a * a + b * b + c * c);
	a /= mag;
	b /= mag;
	c /= mag;
	d /= mag;
}
