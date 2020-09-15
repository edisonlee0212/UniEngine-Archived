#include "pch.h"
#include "Camera.h"
#include "WindowManager.h"

using namespace UniEngine;

GLUBO* Camera::_CameraData;
CameraInfoBlock Camera::_MainCameraInfoBlock;

size_t UniEngine::Camera::GetLayerMask()
{
	return _LayerMask;
}

void UniEngine::Camera::CalculatePlanes(Plane* planes, glm::mat4 projection, glm::mat4 view)
{
	glm::mat4 comboMatrix = projection * glm::transpose(view);

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

void UniEngine::Camera::CalculateFrustumPoints(float nearPlane, float farPlane, glm::vec3 cameraPos, glm::quat cameraRot, glm::vec3* points)
{
	glm::vec3 front = cameraRot * glm::vec3(0, 0, -1);
	glm::vec3 right = cameraRot * glm::vec3(1, 0, 0);
	glm::vec3 up = cameraRot * glm::vec3(0, 1, 0);
	glm::vec3 nearCenter = front * nearPlane;
	glm::vec3 farCenter = front * farPlane;

	float e = tanf(glm::radians(_FOV * 0.5f));
	float near_ext_y = e * nearPlane;
	float near_ext_x = near_ext_y * GetResolutionRatio();
	float far_ext_y = e * farPlane;
	float far_ext_x = far_ext_y * GetResolutionRatio();

	points[0] = cameraPos + nearCenter - right * near_ext_x - up * near_ext_y;
	points[1] = cameraPos + nearCenter - right * near_ext_x + up * near_ext_y;
	points[2] = cameraPos + nearCenter + right * near_ext_x + up * near_ext_y;
	points[3] = cameraPos + nearCenter + right * near_ext_x - up * near_ext_y;
	points[4] = cameraPos + farCenter - right * far_ext_x - up * far_ext_y;
	points[5] = cameraPos + farCenter - right * far_ext_x + up * far_ext_y;
	points[6] = cameraPos + farCenter + right * far_ext_x + up * far_ext_y;
	points[7] = cameraPos + farCenter + right * far_ext_x - up * far_ext_y;
}

void UniEngine::Camera::GenerateMatrices()
{
	_CameraData = new GLUBO();
	_CameraData->SetData(sizeof(CameraInfoBlock), NULL, GL_STATIC_DRAW);
	_CameraData->SetBase(0);
}


Camera::Camera(int resolutionX, int resolutionY, float nearPlane, float farPlane, size_t layerMask)
	: RenderTarget(),
	_FOV(DEFAULTFOV)
{
	_Yaw = YAW;
	_Pitch = PITCH;
	_Near = nearPlane;
	_Far = farPlane;
	_LayerMask = layerMask;
	_ResolutionX = resolutionX;
	_ResolutionY = resolutionY;
	_ColorTexture = new GLTexture2D(1, GL_RGB32F, resolutionX, resolutionY, false);
	_ColorTexture->SetData(0, GL_RGB32F, GL_RGB, GL_FLOAT, 0);
	_ColorTexture->SetInt(GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	_ColorTexture->SetInt(GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	AttachTexture(_ColorTexture, GL_COLOR_ATTACHMENT0);
	_RenderBuffer = new GLRenderBuffer();
	_RenderBuffer->AllocateStorage(GL_DEPTH24_STENCIL8, resolutionX, resolutionY);
	AttachRenderBuffer(_RenderBuffer, GL_DEPTH_STENCIL_ATTACHMENT);
}

glm::quat UniEngine::Camera::ProcessMouseMovement(float xoffset, float yoffset, float sensitivity, GLboolean constrainPitch)
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

	glm::vec3 front;
	front.x = cos(glm::radians(_Yaw)) * cos(glm::radians(_Pitch));
	front.y = sin(glm::radians(_Pitch));
	front.z = sin(glm::radians(_Yaw)) * cos(glm::radians(_Pitch));
	front = glm::normalize(front);
	glm::vec3 right = glm::normalize(glm::cross(front, glm::vec3(0.0f, 1.0f, 0.0f)));  // Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
	glm::vec3 up = glm::normalize(glm::cross(right, front));
	return glm::quatLookAt(front, up);
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

void UniEngine::Camera::SetResolution(int x, int y)
{
	if (_ResolutionX == x && _ResolutionY == y) return;
	_ResolutionX = x;
	_ResolutionY = y;
	_ColorTexture->ReSize(0, GL_RGB32F, GL_RGB, GL_FLOAT, 0, x, y);
	_RenderBuffer->AllocateStorage(GL_DEPTH24_STENCIL8, x, y);
	AttachTexture(_ColorTexture, GL_COLOR_ATTACHMENT0);
	AttachRenderBuffer(_RenderBuffer, GL_DEPTH_STENCIL_ATTACHMENT);
}

GLTexture2D* UniEngine::Camera::GetTexture()
{
	return _ColorTexture;
}

void UniEngine::Plane::Normalize()
{
	float mag = glm::sqrt(a * a + b * b + c * c);
	a /= mag;
	b /= mag;
	c /= mag;
	d /= mag;
}

void UniEngine::CameraInfoBlock::UpdateMatrices(Camera* camera, glm::vec3 position, glm::quat rotation)
{
	glm::vec3 front = rotation * glm::vec3(0, 0, -1);
	glm::vec3 up = rotation * glm::vec3(0, 1, 0);
	auto ratio = camera->GetResolutionRatio();
	if (ratio == 0) return;
	Projection = glm::perspective(glm::radians(camera->_FOV * 0.5f), ratio, camera->_Near, camera->_Far);
	Position = glm::vec4(position, 0);
	View = glm::lookAt(position, position + front, up);
	ReservedParameters = glm::vec4(camera->_Near, camera->_Far, camera->_FOV, 0);
}

void UniEngine::CameraInfoBlock::UploadMatrices(GLUBO* target)
{
	target->SubData(0, sizeof(CameraInfoBlock), this);
}
