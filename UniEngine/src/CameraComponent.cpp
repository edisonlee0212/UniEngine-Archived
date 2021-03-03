#include "pch.h"
#include "CameraComponent.h"
#include "SerializationManager.h"
#include "RenderManager.h"
#include "Ray.h"
#include "Transforms.h"
#include "PostProcessing.h"
UniEngine::CameraInfoBlock UniEngine::CameraComponent::m_cameraInfoBlock;
std::unique_ptr<UniEngine::GLUBO> UniEngine::CameraComponent::m_cameraUniformBufferBlock;
UniEngine::CameraLayerMask::CameraLayerMask()
{
	m_value = 0;
}

UniEngine::Plane::Plane(): m_a(0), m_b(0), m_c(0), m_d(0)
{
}

void UniEngine::Plane::Normalize()
{
	const float mag = glm::sqrt(m_a * m_a + m_b * m_b + m_c * m_c);
	m_a /= mag;
	m_b /= mag;
	m_c /= mag;
	m_d /= mag;
}

void UniEngine::CameraComponent::StoreToJpg(const std::string& path, int resizeX, int resizeY) const
{
	m_colorTexture->StoreToPng(path, resizeX, resizeY);
}

void UniEngine::CameraComponent::StoreToPng(const std::string& path, int resizeX, int resizeY, bool alphaChannel) const
{
	m_colorTexture->StoreToPng(path, resizeX, resizeY, alphaChannel);
}

void UniEngine::CameraComponent::CalculatePlanes(std::vector<Plane>& planes, glm::mat4 projection, glm::mat4 view)
{
	glm::mat4 comboMatrix = projection * glm::transpose(view);
	planes[0].m_a = comboMatrix[3][0] + comboMatrix[0][0];
	planes[0].m_b = comboMatrix[3][1] + comboMatrix[0][1];
	planes[0].m_c = comboMatrix[3][2] + comboMatrix[0][2];
	planes[0].m_d = comboMatrix[3][3] + comboMatrix[0][3];

	planes[1].m_a = comboMatrix[3][0] - comboMatrix[0][0];
	planes[1].m_b = comboMatrix[3][1] - comboMatrix[0][1];
	planes[1].m_c = comboMatrix[3][2] - comboMatrix[0][2];
	planes[1].m_d = comboMatrix[3][3] - comboMatrix[0][3];

	planes[2].m_a = comboMatrix[3][0] - comboMatrix[1][0];
	planes[2].m_b = comboMatrix[3][1] - comboMatrix[1][1];
	planes[2].m_c = comboMatrix[3][2] - comboMatrix[1][2];
	planes[2].m_d = comboMatrix[3][3] - comboMatrix[1][3];

	planes[3].m_a = comboMatrix[3][0] + comboMatrix[1][0];
	planes[3].m_b = comboMatrix[3][1] + comboMatrix[1][1];
	planes[3].m_c = comboMatrix[3][2] + comboMatrix[1][2];
	planes[3].m_d = comboMatrix[3][3] + comboMatrix[1][3];

	planes[4].m_a = comboMatrix[3][0] + comboMatrix[2][0];
	planes[4].m_b = comboMatrix[3][1] + comboMatrix[2][1];
	planes[4].m_c = comboMatrix[3][2] + comboMatrix[2][2];
	planes[4].m_d = comboMatrix[3][3] + comboMatrix[2][3];

	planes[5].m_a = comboMatrix[3][0] - comboMatrix[2][0];
	planes[5].m_b = comboMatrix[3][1] - comboMatrix[2][1];
	planes[5].m_c = comboMatrix[3][2] - comboMatrix[2][2];
	planes[5].m_d = comboMatrix[3][3] - comboMatrix[2][3];

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

	const float e = tanf(glm::radians(m_fov * 0.5f));
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
	return m_colorTexture;
}

glm::mat4 UniEngine::CameraComponent::GetProjection() const
{
	return glm::perspective(glm::radians(m_fov * 0.5f), GetResolutionRatio(), m_nearDistance, m_farDistance);
}

glm::vec3 UniEngine::CameraComponent::Project(GlobalTransform& ltw, glm::vec3 position)
{
	return m_cameraInfoBlock.m_projection * m_cameraInfoBlock.m_view * glm::vec4(position, 1.0f);
}

glm::vec3 UniEngine::CameraComponent::UnProject(GlobalTransform& ltw, glm::vec3 position) const
{
	glm::mat4 inversed = glm::inverse(m_cameraInfoBlock.m_projection * m_cameraInfoBlock.m_view);
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
	const auto projection = glm::perspective(glm::radians(m_fov * 0.5f), GetResolutionRatio(), m_nearDistance, m_farDistance);
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
	return { glm::vec3(ltw.Value[3]) + m_nearDistance * dir, glm::vec3(ltw.Value[3]) + m_farDistance * dir };
}

void UniEngine::CameraComponent::GenerateMatrices()
{
	m_cameraUniformBufferBlock = std::make_unique<GLUBO>();
	m_cameraUniformBufferBlock->SetData(sizeof(m_cameraInfoBlock), nullptr, GL_STREAM_DRAW);
	m_cameraUniformBufferBlock->SetBase(0);
}

void UniEngine::CameraComponent::Serialize(YAML::Emitter& out)
{
	out << YAML::Key << "_ResolutionX" << YAML::Value << _ResolutionX;
	out << YAML::Key << "_ResolutionY" << YAML::Value << _ResolutionY;
	out << YAML::Key << "_IsMainCamera" << YAML::Value << m_isMainCamera;
	out << YAML::Key << "DrawSkyBox" << YAML::Value << m_drawSkyBox;
	out << YAML::Key << "ClearColor" << YAML::Value << m_clearColor;

	out << YAML::Key << "NearDistance" << YAML::Value << m_nearDistance;
	out << YAML::Key << "FarDistance" << YAML::Value << m_farDistance;
	out << YAML::Key << "FOV" << YAML::Value << m_fov;
}

void UniEngine::CameraComponent::Deserialize(const YAML::Node& in)
{
	_ResolutionX = in["_ResolutionX"].as<int>();
	_ResolutionY = in["_ResolutionY"].as<int>();
	m_isMainCamera = in["_IsMainCamera"].as<bool>();
	if (m_isMainCamera) RenderManager::SetMainCamera(this);
	m_drawSkyBox = in["DrawSkyBox"].as<bool>();
	m_clearColor.x = in["ClearColor"][0].as<float>();
	m_clearColor.y = in["ClearColor"][1].as<float>();
	m_clearColor.z = in["ClearColor"][2].as<float>();
	
	m_nearDistance = in["NearDistance"].as<float>();
	m_farDistance = in["FarDistance"].as<float>();
	m_fov = in["FOV"].as<float>();
}

void UniEngine::CameraComponent::ResizeResolution(int x, int y)
{
	if (_ResolutionX == x && _ResolutionY == y) return;
	_ResolutionX = x > 0 ? x : 1;
	_ResolutionY = y > 0 ? y : 1;
	m_gBuffer->SetResolution(_ResolutionX, _ResolutionY);
	m_gPositionBuffer->ReSize(0, GL_RGBA32F, GL_RGBA, GL_FLOAT, 0, _ResolutionX, _ResolutionY);
	m_gNormalBuffer->ReSize(0, GL_RGBA32F, GL_RGBA, GL_FLOAT, 0, _ResolutionX, _ResolutionY);
	m_gColorSpecularBuffer->ReSize(0, GL_RGBA32F, GL_RGBA, GL_FLOAT, 0, _ResolutionX, _ResolutionY);
	m_gMetallicRoughnessAo->ReSize(0, GL_RGBA32F, GL_RGBA, GL_FLOAT, 0, _ResolutionX, _ResolutionY);
	m_gDepthBuffer->AllocateStorage(GL_DEPTH32F_STENCIL8, _ResolutionX, _ResolutionY);

	

	m_colorTexture->_Texture->ReSize(0, GL_RGBA32F, GL_RGBA, GL_FLOAT, 0, _ResolutionX, _ResolutionY);
	m_depthStencilBuffer->ReSize(0, GL_DEPTH32F_STENCIL8, GL_DEPTH_STENCIL, GL_FLOAT_32_UNSIGNED_INT_24_8_REV, 0, _ResolutionX, _ResolutionY);

	if(GetOwner().HasPrivateComponent<PostProcessing>())
	{
		GetOwner().GetPrivateComponent<PostProcessing>()->ResizeResolution(_ResolutionX, _ResolutionY);
	}
}

UniEngine::CameraComponent::CameraComponent()
{
	_ResolutionX = 1;
	_ResolutionY = 1;
	
	m_colorTexture = std::make_shared<Texture2D>();
	m_colorTexture->m_name = "CameraTexture";
	m_colorTexture->_Texture = std::make_shared<GLTexture2D>(0, GL_RGBA32F, _ResolutionX, _ResolutionY, false);
	m_colorTexture->_Texture->SetData(0, GL_RGBA32F, GL_RGBA, GL_FLOAT, 0);
	m_colorTexture->_Texture->SetInt(GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	m_colorTexture->_Texture->SetInt(GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	m_colorTexture->_Texture->SetInt(GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	m_colorTexture->_Texture->SetInt(GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	AttachTexture(m_colorTexture->_Texture.get(), GL_COLOR_ATTACHMENT0);

	m_depthStencilBuffer = std::make_unique<GLTexture2D>(0, GL_DEPTH32F_STENCIL8, _ResolutionX, _ResolutionY, false);
	m_depthStencilBuffer->SetData(0, GL_DEPTH32F_STENCIL8, GL_DEPTH_STENCIL, GL_FLOAT_32_UNSIGNED_INT_24_8_REV, 0);
	m_depthStencilBuffer->SetInt(GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	m_depthStencilBuffer->SetInt(GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	m_depthStencilBuffer->SetInt(GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	m_depthStencilBuffer->SetInt(GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	AttachTexture(m_depthStencilBuffer.get(), GL_DEPTH_STENCIL_ATTACHMENT);

	m_gBuffer = std::make_unique<RenderTarget>(_ResolutionX, _ResolutionY);

	m_gDepthBuffer = std::make_unique<GLRenderBuffer>();
	m_gDepthBuffer->AllocateStorage(GL_DEPTH32F_STENCIL8, _ResolutionX, _ResolutionY);
	m_gBuffer->AttachRenderBuffer(m_gDepthBuffer.get(), GL_DEPTH_STENCIL_ATTACHMENT);
	
	m_gPositionBuffer = std::make_unique<GLTexture2D>(0, GL_RGBA32F, _ResolutionX, _ResolutionY, false);
	m_gPositionBuffer->SetData(0, GL_RGBA32F, GL_RGBA, GL_FLOAT, 0);
	m_gPositionBuffer->SetInt(GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	m_gPositionBuffer->SetInt(GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	m_gPositionBuffer->SetInt(GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	m_gPositionBuffer->SetInt(GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	m_gBuffer->AttachTexture(m_gPositionBuffer.get(), GL_COLOR_ATTACHMENT0);
	
	m_gNormalBuffer = std::make_unique <GLTexture2D>(0, GL_RGBA32F, _ResolutionX, _ResolutionY, false);
	m_gNormalBuffer->SetData(0, GL_RGBA32F, GL_RGBA, GL_FLOAT, 0);
	m_gNormalBuffer->SetInt(GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	m_gNormalBuffer->SetInt(GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	m_gNormalBuffer->SetInt(GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	m_gNormalBuffer->SetInt(GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	m_gBuffer->AttachTexture(m_gNormalBuffer.get(), GL_COLOR_ATTACHMENT1);
	
	m_gColorSpecularBuffer = std::make_unique<GLTexture2D>(0, GL_RGBA32F, _ResolutionX, _ResolutionY, false);
	m_gColorSpecularBuffer->SetData(0, GL_RGBA32F, GL_RGBA, GL_FLOAT, 0);
	m_gColorSpecularBuffer->SetInt(GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	m_gColorSpecularBuffer->SetInt(GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	m_gColorSpecularBuffer->SetInt(GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	m_gColorSpecularBuffer->SetInt(GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	m_gBuffer->AttachTexture(m_gColorSpecularBuffer.get(), GL_COLOR_ATTACHMENT2);

	m_gMetallicRoughnessAo = std::make_unique<GLTexture2D>(0, GL_RGBA32F, _ResolutionX, _ResolutionY, false);
	m_gMetallicRoughnessAo->SetData(0, GL_RGBA32F, GL_RGBA, GL_FLOAT, 0);
	m_gMetallicRoughnessAo->SetInt(GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	m_gMetallicRoughnessAo->SetInt(GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	m_gMetallicRoughnessAo->SetInt(GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	m_gMetallicRoughnessAo->SetInt(GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	m_gBuffer->AttachTexture(m_gMetallicRoughnessAo.get(), GL_COLOR_ATTACHMENT3);
	
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
	ImGui::Checkbox("Allow auto resize", &m_allowAutoResize);
	if(!m_allowAutoResize)
	{
		glm::ivec2 resolution = { _ResolutionX, _ResolutionY };
		if(ImGui::DragInt2("Resolution", &resolution.x))
		{
			ResizeResolution(resolution.x, resolution.y);
		}
	}
	ImGui::Checkbox("Skybox", &m_drawSkyBox);
	const bool savedState = m_isMainCamera;
	ImGui::Checkbox("Main Camera", &m_isMainCamera);
	if(savedState != m_isMainCamera)
	{
		if(m_isMainCamera)
		{
			RenderManager::SetMainCamera(this);
		}else
		{
			RenderManager::SetMainCamera(nullptr);
		}
	}
	if(!m_drawSkyBox)
	{
		ImGui::ColorEdit3("Clear Color", (float*)(void*)&m_clearColor);
	}
	ImGui::DragFloat("Near", &m_nearDistance, m_nearDistance / 10.0f, 0, m_farDistance);
	ImGui::DragFloat("Far", &m_farDistance, m_farDistance / 10.0f, m_nearDistance);
	ImGui::DragFloat("FOV", &m_fov, 1.0f, 1, 359);
	if (ImGui::TreeNode("Content"))
	{
		ImGui::Image((ImTextureID)m_colorTexture->Texture()->Id(), ImVec2(_ResolutionX / 5.0f, _ResolutionY / 5.0f), ImVec2(0, 1), ImVec2(1, 0));
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
	m_projection = glm::perspective(glm::radians(camera->m_fov * 0.5f), ratio, camera->m_nearDistance, camera->m_farDistance);
	m_position = glm::vec4(position, 0);
	m_view = glm::lookAt(position, position + front, up);
	m_reservedParameters = glm::vec4(camera->m_nearDistance, camera->m_farDistance, glm::tan(camera->m_fov * 0.5f), camera->_ResolutionX / camera->_ResolutionY);
	m_backGroundColor = glm::vec4(camera->m_clearColor, 1.0f);
	if (camera->m_skyBox) {
		m_skybox = camera->m_skyBox->Texture()->GetHandle();
		m_skyboxEnabled = true;
	}
	else {
		m_skybox = 0;
		m_skyboxEnabled = false;
	}
}

void UniEngine::CameraInfoBlock::UploadMatrices(CameraComponent* camera)
{
	CameraComponent::m_cameraUniformBufferBlock->SubData(0, sizeof(CameraInfoBlock), this);
}
