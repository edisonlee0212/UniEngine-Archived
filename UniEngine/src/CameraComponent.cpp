#include "pch.h"
#include "CameraComponent.h"
#include "SerializationManager.h"
#include "RenderManager.h"
#include "Ray.h"
#include "Transforms.h"
#include "PostProcessing.h"
UniEngine::CameraInfoBlock UniEngine::CameraComponent::_CameraInfoBlock;
std::unique_ptr<UniEngine::GLUBO> UniEngine::CameraComponent::_CameraUniformBufferBlock;
UniEngine::CameraLayerMask::CameraLayerMask()
{
	Value = 0;
}

UniEngine::Plane::Plane(): a(0), b(0), c(0), d(0)
{
}

void UniEngine::Plane::Normalize()
{
	const float mag = glm::sqrt(a * a + b * b + c * c);
	a /= mag;
	b /= mag;
	c /= mag;
	d /= mag;
}

void UniEngine::CameraComponent::StoreToJpg(const std::string& path, int resizeX, int resizeY) const
{
	_ColorTexture->StoreToPng(path, resizeX, resizeY);
}

void UniEngine::CameraComponent::StoreToPng(const std::string& path, int resizeX, int resizeY, bool alphaChannel) const
{
	_ColorTexture->StoreToPng(path, resizeX, resizeY, alphaChannel);
}

void UniEngine::CameraComponent::CalculatePlanes(std::vector<Plane>& planes, glm::mat4 projection, glm::mat4 view)
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

void UniEngine::CameraComponent::CalculateFrustumPoints(float nearPlane, float farPlane, glm::vec3 cameraPos,
	glm::quat cameraRot, glm::vec3* points) const
{
	const glm::vec3 front = cameraRot * glm::vec3(0, 0, -1);
	const glm::vec3 right = cameraRot * glm::vec3(1, 0, 0);
	const glm::vec3 up = cameraRot * glm::vec3(0, 1, 0);
	const glm::vec3 nearCenter = front * nearPlane;
	const glm::vec3 farCenter = front * farPlane;

	const float e = tanf(glm::radians(FOV * 0.5f));
	const float near_ext_y = e * nearPlane;
	const float near_ext_x = near_ext_y * GetResolutionRatio();
	const float far_ext_y = e * farPlane;
	const float far_ext_x = far_ext_y * GetResolutionRatio();

	points[0] = cameraPos + nearCenter - right * near_ext_x - up * near_ext_y;
	points[1] = cameraPos + nearCenter - right * near_ext_x + up * near_ext_y;
	points[2] = cameraPos + nearCenter + right * near_ext_x + up * near_ext_y;
	points[3] = cameraPos + nearCenter + right * near_ext_x - up * near_ext_y;
	points[4] = cameraPos + farCenter - right * far_ext_x - up * far_ext_y;
	points[5] = cameraPos + farCenter - right * far_ext_x + up * far_ext_y;
	points[6] = cameraPos + farCenter + right * far_ext_x + up * far_ext_y;
	points[7] = cameraPos + farCenter + right * far_ext_x - up * far_ext_y;
}

glm::quat UniEngine::CameraComponent::ProcessMouseMovement(float yawAngle, float pitchAngle,
	bool constrainPitch)
{
	// Make sure that when pitch is out of bounds, screen doesn't get flipped
	if (constrainPitch)
	{
		if (pitchAngle > 89.0f)
			pitchAngle = 89.0f;
		if (pitchAngle < -89.0f)
			pitchAngle = -89.0f;
	}

	glm::vec3 front;
	front.x = cos(glm::radians(yawAngle)) * cos(glm::radians(pitchAngle));
	front.y = sin(glm::radians(pitchAngle));
	front.z = sin(glm::radians(yawAngle)) * cos(glm::radians(pitchAngle));
	front = glm::normalize(front);
	const glm::vec3 right = glm::normalize(glm::cross(front, glm::vec3(0.0f, 1.0f, 0.0f)));  // Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
	const glm::vec3 up = glm::normalize(glm::cross(right, front));
	return glm::quatLookAt(front, up);
}

std::shared_ptr<UniEngine::Texture2D> UniEngine::CameraComponent::GetTexture() const
{
	return _ColorTexture;
}

glm::mat4 UniEngine::CameraComponent::GetProjection() const
{
	return glm::perspective(glm::radians(FOV * 0.5f), GetResolutionRatio(), NearDistance, FarDistance);
}

glm::vec3 UniEngine::CameraComponent::Project(GlobalTransform& ltw, glm::vec3 position)
{
	return _CameraInfoBlock.Projection * _CameraInfoBlock.View * glm::vec4(position, 1.0f);
}

glm::vec3 UniEngine::CameraComponent::UnProject(GlobalTransform& ltw, glm::vec3 position) const
{
	glm::mat4 inversed = glm::inverse(_CameraInfoBlock.Projection * _CameraInfoBlock.View);
	glm::vec4 start = glm::vec4(
		position, 1.0f);
	start = inversed * start;
	return start / start.w;
}

glm::vec3 UniEngine::CameraComponent::GetMouseWorldPoint(GlobalTransform& ltw, glm::vec2 mousePosition) const
{
	const float halfX = static_cast<float>(_ResolutionX) / 2.0f;
	const float halfY = static_cast<float>(_ResolutionY) / 2.0f;
	const glm::vec4 start = glm::vec4(
		(mousePosition.x - halfX) / halfX,
		-1 * (mousePosition.y - halfY) / halfY,
		0.0f, 1.0f);
	return start / start.w;
}

void UniEngine::CameraComponent::SetClearColor(glm::vec3 color) const
{
	_FrameBuffer->ClearColor(glm::vec4(color.x, color.y, color.z, 0.0f));
	_FrameBuffer->Clear();
	_FrameBuffer->ClearColor(glm::vec4(0.0f));
}

UniEngine::Ray UniEngine::CameraComponent::ScreenPointToRay(GlobalTransform& ltw, glm::vec2 mousePosition) const
{
	const auto position = ltw.GetPosition();
	const auto rotation = ltw.GetRotation();
	const glm::vec3 front = rotation * glm::vec3(0, 0, -1);
	const glm::vec3 up = rotation * glm::vec3(0, 1, 0);
	const auto projection = glm::perspective(glm::radians(FOV * 0.5f), GetResolutionRatio(), NearDistance, FarDistance);
	const auto view = glm::lookAt(position, position + front, up);
	const glm::mat4 inv = glm::inverse(projection * view);
	const float halfX = static_cast<float>(_ResolutionX) / 2.0f;
	const float halfY = static_cast<float>(_ResolutionY) / 2.0f;
	const auto realX = (mousePosition.x + halfX) / halfX;
	const auto realY = (mousePosition.y - halfY) / halfY;
	if (glm::abs(realX) > 1.0f || glm::abs(realY) > 1.0f)
		return { glm::vec3(FLT_MAX), glm::vec3(FLT_MAX) };
	glm::vec4 start = glm::vec4(
		realX,
		-1 * realY,
		-1, 1.0);
	glm::vec4 end = glm::vec4(realX, -1.0f * realY, 1.0f, 1.0f);
	start = inv * start;
	end = inv * end;
	start /= start.w;
	end /= end.w;
	const glm::vec3 dir = glm::normalize(glm::vec3(end - start));
	return { glm::vec3(ltw.Value[3]) + NearDistance * dir, glm::vec3(ltw.Value[3]) + FarDistance * dir };
}

void UniEngine::CameraComponent::GenerateMatrices()
{
	_CameraUniformBufferBlock = std::make_unique<GLUBO>();
	_CameraUniformBufferBlock->SetData(sizeof(_CameraInfoBlock), nullptr, GL_STREAM_DRAW);
	_CameraUniformBufferBlock->SetBase(0);
}

void UniEngine::CameraComponent::Serialize(YAML::Emitter& out)
{
	out << YAML::Key << "_ResolutionX" << YAML::Value << _ResolutionX;
	out << YAML::Key << "_ResolutionY" << YAML::Value << _ResolutionY;
	out << YAML::Key << "_IsMainCamera" << YAML::Value << _IsMainCamera;
	out << YAML::Key << "DrawSkyBox" << YAML::Value << DrawSkyBox;
	out << YAML::Key << "ClearColor" << YAML::Value << ClearColor;

	out << YAML::Key << "NearDistance" << YAML::Value << NearDistance;
	out << YAML::Key << "FarDistance" << YAML::Value << FarDistance;
	out << YAML::Key << "FOV" << YAML::Value << FOV;
}

void UniEngine::CameraComponent::Deserialize(const YAML::Node& in)
{
	_ResolutionX = in["_ResolutionX"].as<int>();
	_ResolutionY = in["_ResolutionY"].as<int>();
	_IsMainCamera = in["_IsMainCamera"].as<bool>();
	if (_IsMainCamera) RenderManager::SetMainCamera(this);
	DrawSkyBox = in["DrawSkyBox"].as<bool>();
	ClearColor.x = in["ClearColor"][0].as<float>();
	ClearColor.y = in["ClearColor"][1].as<float>();
	ClearColor.z = in["ClearColor"][2].as<float>();
	
	NearDistance = in["NearDistance"].as<float>();
	FarDistance = in["FarDistance"].as<float>();
	FOV = in["FOV"].as<float>();
}

void UniEngine::CameraComponent::ResizeResolution(int x, int y)
{
	if (_ResolutionX == x && _ResolutionY == y) return;
	_ResolutionX = x > 0 ? x : 1;
	_ResolutionY = y > 0 ? y : 1;
	_GBuffer->SetResolution(_ResolutionX, _ResolutionY);
	_GPositionBuffer->ReSize(0, GL_RGBA32F, GL_RGBA, GL_FLOAT, 0, _ResolutionX, _ResolutionY);
	_GNormalBuffer->ReSize(0, GL_RGBA32F, GL_RGBA, GL_FLOAT, 0, _ResolutionX, _ResolutionY);
	_GColorSpecularBuffer->ReSize(0, GL_RGBA32F, GL_RGBA, GL_FLOAT, 0, _ResolutionX, _ResolutionY);
	_GMetallicRoughnessAO->ReSize(0, GL_RGBA32F, GL_RGBA, GL_FLOAT, 0, _ResolutionX, _ResolutionY);
	_GDepthBuffer->AllocateStorage(GL_DEPTH32F_STENCIL8, _ResolutionX, _ResolutionY);

	

	_ColorTexture->_Texture->ReSize(0, GL_RGBA32F, GL_RGBA, GL_FLOAT, 0, _ResolutionX, _ResolutionY);
	_DepthStencilBuffer->ReSize(0, GL_DEPTH32F_STENCIL8, GL_DEPTH_STENCIL, GL_FLOAT_32_UNSIGNED_INT_24_8_REV, 0, _ResolutionX, _ResolutionY);

	if(GetOwner().HasPrivateComponent<PostProcessing>())
	{
		GetOwner().GetPrivateComponent<PostProcessing>()->ResizeResolution(_ResolutionX, _ResolutionY);
	}
}

UniEngine::CameraComponent::CameraComponent()
{
	_ResolutionX = 1;
	_ResolutionY = 1;
	
	_ColorTexture = std::make_shared<Texture2D>();
	_ColorTexture->Name = "CameraTexture";
	_ColorTexture->_Texture = std::make_shared<GLTexture2D>(0, GL_RGBA32F, _ResolutionX, _ResolutionY, false);
	_ColorTexture->_Texture->SetData(0, GL_RGBA32F, GL_RGBA, GL_FLOAT, 0);
	_ColorTexture->_Texture->SetInt(GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	_ColorTexture->_Texture->SetInt(GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	_ColorTexture->_Texture->SetInt(GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	_ColorTexture->_Texture->SetInt(GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	AttachTexture(_ColorTexture->_Texture.get(), GL_COLOR_ATTACHMENT0);

	_DepthStencilBuffer = std::make_unique<GLTexture2D>(0, GL_DEPTH32F_STENCIL8, _ResolutionX, _ResolutionY, false);
	_DepthStencilBuffer->SetData(0, GL_DEPTH32F_STENCIL8, GL_DEPTH_STENCIL, GL_FLOAT_32_UNSIGNED_INT_24_8_REV, 0);
	_DepthStencilBuffer->SetInt(GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	_DepthStencilBuffer->SetInt(GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	_DepthStencilBuffer->SetInt(GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	_DepthStencilBuffer->SetInt(GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	AttachTexture(_DepthStencilBuffer.get(), GL_DEPTH_STENCIL_ATTACHMENT);

	_GBuffer = std::make_unique<RenderTarget>(_ResolutionX, _ResolutionY);

	_GDepthBuffer = std::make_unique<GLRenderBuffer>();
	_GDepthBuffer->AllocateStorage(GL_DEPTH32F_STENCIL8, _ResolutionX, _ResolutionY);
	_GBuffer->AttachRenderBuffer(_GDepthBuffer.get(), GL_DEPTH_STENCIL_ATTACHMENT);
	
	_GPositionBuffer = std::make_unique<GLTexture2D>(0, GL_RGBA32F, _ResolutionX, _ResolutionY, false);
	_GPositionBuffer->SetData(0, GL_RGBA32F, GL_RGBA, GL_FLOAT, 0);
	_GPositionBuffer->SetInt(GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	_GPositionBuffer->SetInt(GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	_GPositionBuffer->SetInt(GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	_GPositionBuffer->SetInt(GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	_GBuffer->AttachTexture(_GPositionBuffer.get(), GL_COLOR_ATTACHMENT0);
	
	_GNormalBuffer = std::make_unique <GLTexture2D>(0, GL_RGBA32F, _ResolutionX, _ResolutionY, false);
	_GNormalBuffer->SetData(0, GL_RGBA32F, GL_RGBA, GL_FLOAT, 0);
	_GNormalBuffer->SetInt(GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	_GNormalBuffer->SetInt(GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	_GNormalBuffer->SetInt(GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	_GNormalBuffer->SetInt(GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	_GBuffer->AttachTexture(_GNormalBuffer.get(), GL_COLOR_ATTACHMENT1);
	
	_GColorSpecularBuffer = std::make_unique<GLTexture2D>(0, GL_RGBA32F, _ResolutionX, _ResolutionY, false);
	_GColorSpecularBuffer->SetData(0, GL_RGBA32F, GL_RGBA, GL_FLOAT, 0);
	_GColorSpecularBuffer->SetInt(GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	_GColorSpecularBuffer->SetInt(GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	_GColorSpecularBuffer->SetInt(GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	_GColorSpecularBuffer->SetInt(GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	_GBuffer->AttachTexture(_GColorSpecularBuffer.get(), GL_COLOR_ATTACHMENT2);

	_GMetallicRoughnessAO = std::make_unique<GLTexture2D>(0, GL_RGBA32F, _ResolutionX, _ResolutionY, false);
	_GMetallicRoughnessAO->SetData(0, GL_RGBA32F, GL_RGBA, GL_FLOAT, 0);
	_GMetallicRoughnessAO->SetInt(GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	_GMetallicRoughnessAO->SetInt(GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	_GMetallicRoughnessAO->SetInt(GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	_GMetallicRoughnessAO->SetInt(GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	_GBuffer->AttachTexture(_GMetallicRoughnessAO.get(), GL_COLOR_ATTACHMENT3);
	
	SetEnabled(true);
}

UniEngine::CameraComponent::~CameraComponent()
{
	if (RenderManager::GetMainCamera() == this) {
		RenderManager::SetMainCamera(nullptr);
	}
}

void UniEngine::CameraComponent::OnGui()
{
	ImGui::Checkbox("Allow auto resize", &AllowAutoResize);
	if(!AllowAutoResize)
	{
		glm::ivec2 resolution = { _ResolutionX, _ResolutionY };
		if(ImGui::DragInt2("Resolution", &resolution.x))
		{
			ResizeResolution(resolution.x, resolution.y);
		}
	}
	ImGui::Checkbox("Skybox", &DrawSkyBox);
	const bool savedState = _IsMainCamera;
	ImGui::Checkbox("Main Camera", &_IsMainCamera);
	if(savedState != _IsMainCamera)
	{
		if(_IsMainCamera)
		{
			RenderManager::SetMainCamera(this);
		}else
		{
			RenderManager::SetMainCamera(nullptr);
		}
	}
	if(!DrawSkyBox)
	{
		ImGui::ColorEdit3("Clear Color", (float*)(void*)&ClearColor);
	}
	ImGui::DragFloat("Near", &NearDistance, NearDistance / 10.0f, 0, FarDistance);
	ImGui::DragFloat("Far", &FarDistance, FarDistance / 10.0f, NearDistance);
	ImGui::DragFloat("FOV", &FOV, 1.0f, 1, 359);
	if (ImGui::TreeNode("Content"))
	{
		ImGui::Image((ImTextureID)_ColorTexture->Texture()->ID(), ImVec2(_ResolutionX / 5.0f, _ResolutionY / 5.0f), ImVec2(0, 1), ImVec2(1, 0));
		if (ImGui::Button("Take Screenshot"))
		{
			StoreToJpg("screenshot.jpg");
		}
		if (ImGui::Button("Take Screenshot (with alpha)"))
		{
			StoreToPng("greyscale.png", -1, -1, true);
		}
		ImGui::TreePop();
	}
}

void UniEngine::CameraInfoBlock::UpdateMatrices(CameraComponent* camera, glm::vec3 position, glm::quat rotation)
{
	glm::vec3 front = rotation * glm::vec3(0, 0, -1);
	glm::vec3 up = rotation * glm::vec3(0, 1, 0);
	auto ratio = camera->GetResolutionRatio();
	Projection = glm::perspective(glm::radians(camera->FOV * 0.5f), ratio, camera->NearDistance, camera->FarDistance);
	Position = glm::vec4(position, 0);
	View = glm::lookAt(position, position + front, up);
	ReservedParameters = glm::vec4(camera->NearDistance, camera->FarDistance, glm::tan(camera->FOV * 0.5f), camera->_ResolutionX / camera->_ResolutionY);
	BackGroundColor = glm::vec4(camera->ClearColor, 1.0f);
	if (camera->SkyBox) {
		Skybox = camera->SkyBox->Texture()->GetHandle();
		SkyboxEnabled = true;
	}
	else {
		Skybox = 0;
		SkyboxEnabled = false;
	}
}

void UniEngine::CameraInfoBlock::UploadMatrices(CameraComponent* camera)
{
	CameraComponent::_CameraUniformBufferBlock->SubData(0, sizeof(CameraInfoBlock), this);
}
