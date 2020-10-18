#include "pch.h"
#include "Camera.h"

#include "TransformSystem.h"
#include "WindowManager.h"

using namespace UniEngine;

GLUBO* Camera::_CameraData;
CameraInfoBlock Camera::_MainCameraInfoBlock;

void Camera::OnGui()
{
	ImGui::DragFloat("Near", &NearDistance, NearDistance / 10.0f, 0, FarDistance);
	ImGui::DragFloat("Far", &FarDistance, FarDistance / 10.0f, NearDistance);
	ImGui::DragFloat("FieldOfView", &FieldOfView, 1.0f, 1, 359);
	if(ImGui::TreeNode("Content"))
	{
		ImGui::Image((ImTextureID)_ColorTexture->ID(), ImVec2(_ResolutionX / 5.0f, _ResolutionY / 5.0f), ImVec2(0, 1), ImVec2(1, 0));
		ImGui::TreePop();
	}
}

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

	float e = tanf(glm::radians(FieldOfView * 0.5f));
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
	FieldOfView(DEFAULTFOV)
{
	YawAngle = YAW;
	PitchAngle = PITCH;
	NearDistance = nearPlane;
	FarDistance = farPlane;
	_LayerMask = layerMask;
	_ResolutionX = resolutionX;
	_ResolutionY = resolutionY;
	_ColorTexture = new GLTexture2D(0, GL_RGB32F, resolutionX, resolutionY, false);
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

	YawAngle += xoffset;
	PitchAngle += yoffset;

	// Make sure that when pitch is out of bounds, screen doesn't get flipped
	if (constrainPitch)
	{
		if (PitchAngle > 89.0f)
			PitchAngle = 89.0f;
		if (PitchAngle < -89.0f)
			PitchAngle = -89.0f;
	}

	glm::vec3 front;
	front.x = cos(glm::radians(YawAngle)) * cos(glm::radians(PitchAngle));
	front.y = sin(glm::radians(PitchAngle));
	front.z = sin(glm::radians(YawAngle)) * cos(glm::radians(PitchAngle));
	front = glm::normalize(front);
	glm::vec3 right = glm::normalize(glm::cross(front, glm::vec3(0.0f, 1.0f, 0.0f)));  // Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
	glm::vec3 up = glm::normalize(glm::cross(right, front));
	return glm::quatLookAt(front, up);
}

void UniEngine::Camera::ProcessMouseScroll(float yoffset)
{
	if (FieldOfView >= 1.0f && FieldOfView <= 180.0f)
		FieldOfView -= yoffset;
	if (FieldOfView <= 1.0f)
		FieldOfView = 1.0f;
	if (FieldOfView >= 180.0f)
		FieldOfView = 180.0f;
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

glm::vec3 Camera::Project(LocalToWorld& ltw, glm::vec3 position)
{
	return _MainCameraInfoBlock.Projection * _MainCameraInfoBlock.View * glm::vec4(position, 1.0f);
}

glm::vec3 Camera::UnProject(LocalToWorld& ltw, glm::vec3 position)
{
	glm::mat4 inversed = glm::inverse(_MainCameraInfoBlock.Projection * _MainCameraInfoBlock.View);
	glm::vec4 start = glm::vec4(
		position, 1.0f);
	start = inversed * start;
	return start / start.w;
}

glm::vec3 Camera::GetMouseWorldPoint(LocalToWorld& ltw, glm::vec2 mousePosition)
{
	glm::mat4 inversed = glm::inverse(_MainCameraInfoBlock.Projection * _MainCameraInfoBlock.View);
	const float halfX = static_cast<float>(_ResolutionX) / 2.0f;
	const float halfY = static_cast<float>(_ResolutionY) / 2.0f;
	const glm::vec4 start = glm::vec4(
		(mousePosition.x - halfX) / halfX,
		-1 * (mousePosition.y - halfY) / halfY,
		0.0f, 1.0f);
	const auto position = inversed * start;
	return start / start.w;
}

Ray Camera::ScreenPointToRay(LocalToWorld& ltw, glm::vec2 mousePosition) const
{
	
	const glm::mat4 inv = glm::inverse(_MainCameraInfoBlock.Projection * _MainCameraInfoBlock.View);
	const float halfX = static_cast<float>(_ResolutionX) / 2.0f;
	const float halfY = static_cast<float>(_ResolutionY) / 2.0f;
	const auto realX = (mousePosition.x + halfX) / halfX;
	const auto realY = (mousePosition.y - halfY) / halfY;
	if (glm::abs(realX) > 1.0f || glm::abs(realY) > 1.0f) return { glm::vec3(FLT_MAX), glm::vec3(FLT_MAX) };
	glm::vec4 start = glm::vec4(
		realX,
		-1 * realY,
		-1, 1.0);
	glm::vec4 end = glm::vec4(realX,
	                                -1 * realY,
	                                1, 1.0);
	
	
	start = inv * start;
	end = inv * end;
	start /= start.w;
	end /= end.w;
	const glm::vec3 dir = glm::normalize(glm::vec3(end - start));
	
	return {glm::vec3(ltw.Value[3]) + NearDistance * dir, glm::vec3(ltw.Value[3]) + FarDistance * dir};
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
	Projection = glm::perspective(glm::radians(camera->FieldOfView * 0.5f), ratio, camera->NearDistance, camera->FarDistance);
	Position = glm::vec4(position, 0);
	View = glm::lookAt(position, position + front, up);
	ReservedParameters = glm::vec4(camera->NearDistance, camera->FarDistance, camera->FieldOfView, 0);
}

void UniEngine::CameraInfoBlock::UploadMatrices(GLUBO* target)
{
	target->SubData(0, sizeof(CameraInfoBlock), this);
}
