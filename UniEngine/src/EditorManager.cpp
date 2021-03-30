#include "pch.h"
#include "EditorManager.h"

#include "ResourceManager.h"
#include "UniEngine.h"
#include "Default.h"
#include "DirectionalLight.h"
#include "InputManager.h"
#include "Model.h"
#include "PointLight.h"
#include "RenderManager.h"
#include "TransformManager.h"
#include "PostProcessing.h"
using namespace UniEngine;
inline bool UniEngine::EditorManager::DrawEntityMenu(bool enabled, Entity& entity)
{
	bool deleted = false;
	if (ImGui::BeginPopupContextItem(std::to_string(entity.m_index).c_str()))
	{
		if (ImGui::Button("Delete")) {
			EntityManager::DeleteEntity(entity);
			deleted = true;
		}
		if (!deleted && ImGui::Button(enabled ? "Disable" : "Enable")) {
			if (enabled) {
				entity.SetEnabled(false);
			}
			else {
				entity.SetEnabled(true);
			}
		}
		if (!deleted && ImGui::BeginMenu("Rename"))
		{
			static char newName[256];
			ImGui::InputText("New name", newName, 256);
			if (ImGui::Button("Confirm"))EntityManager::SetEntityName(entity, std::string(newName));

			ImGui::EndMenu();
		}
		ImGui::EndPopup();
	}
	return deleted;
}


void UniEngine::EditorManager::InspectComponentData(Entity entity, ComponentBase* data, ComponentType type, bool isRoot)
{
	if (GetInstance().m_componentDataInspectorMap.find(type.m_typeId) != GetInstance().m_componentDataInspectorMap.end()) {
		GetInstance().m_componentDataInspectorMap.at(type.m_typeId)(entity, data, isRoot);
	}
}

Entity EditorManager::MouseEntitySelection(const glm::vec2& mousePosition)
{
	Entity retVal;
	GetInstance().m_sceneCameraEntityRecorder->Bind();
	float entityIndex = 0;
	const glm::vec2 resolution = GetInstance().m_sceneCameraEntityRecorder->GetResolution();
	glm::vec2 point = resolution;
	point.x += mousePosition.x;
	point.y -= mousePosition.y;
	if (point.x >= 0 && point.x < resolution.x && point.y >= 0 && point.y < resolution.y) {
		glReadPixels(point.x, point.y, 1, 1, GL_RED, GL_FLOAT, &entityIndex);
		if (entityIndex > 0)
		{
			retVal.m_version = EntityManager::GetInstance().m_entityInfos->at(static_cast<unsigned>(entityIndex)).m_version;
			retVal.m_index = static_cast<unsigned>(entityIndex);
		}
	}
	return retVal;
}

void EditorManager::HighLightEntityPrePassHelper(const Entity& entity)
{
	if (!entity.IsValid() || entity.IsDeleted() || !entity.IsEnabled()) return;
	EntityManager::ForEachChild(entity, [](Entity child)
		{
			HighLightEntityPrePassHelper(child);
		}
	);
	if (entity.HasPrivateComponent<MeshRenderer>())
	{
		auto& mmc = entity.GetPrivateComponent<MeshRenderer>();
		if (mmc->IsEnabled() && mmc->m_material != nullptr && mmc->m_mesh != nullptr)
		{
			auto ltw = EntityManager::GetComponentData<GlobalTransform>(entity);
			auto* mesh = mmc->m_mesh.get();
			mesh->Enable();
			mesh->Vao()->DisableAttributeArray(12);
			mesh->Vao()->DisableAttributeArray(13);
			mesh->Vao()->DisableAttributeArray(14);
			mesh->Vao()->DisableAttributeArray(15);
			GetInstance().m_sceneHighlightPrePassProgram->SetFloat4x4("model", ltw.m_value);
			glDrawElements(GL_TRIANGLES, (GLsizei)mesh->GetTriangleAmount() * 3, GL_UNSIGNED_INT, 0);
		}
	}
	if (entity.HasPrivateComponent<Particles>())
	{
		auto& immc = entity.GetPrivateComponent<Particles>();
		if (immc->IsEnabled() && immc->m_material != nullptr && immc->m_mesh != nullptr)
		{
			auto count = immc->m_matrices.size();
			std::unique_ptr<GLVBO> matricesBuffer = std::make_unique<GLVBO>();
			matricesBuffer->SetData((GLsizei)count * sizeof(glm::mat4), immc->m_matrices.data(), GL_STATIC_DRAW);
			auto ltw = EntityManager::GetComponentData<GlobalTransform>(entity);
			auto* mesh = immc->m_mesh.get();
			mesh->Enable();
			mesh->Vao()->EnableAttributeArray(12);
			mesh->Vao()->SetAttributePointer(12, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)0);
			mesh->Vao()->EnableAttributeArray(13);
			mesh->Vao()->SetAttributePointer(13, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(sizeof(glm::vec4)));
			mesh->Vao()->EnableAttributeArray(14);
			mesh->Vao()->SetAttributePointer(14, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(2 * sizeof(glm::vec4)));
			mesh->Vao()->EnableAttributeArray(15);
			mesh->Vao()->SetAttributePointer(15, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(3 * sizeof(glm::vec4)));
			mesh->Vao()->SetAttributeDivisor(12, 1);
			mesh->Vao()->SetAttributeDivisor(13, 1);
			mesh->Vao()->SetAttributeDivisor(14, 1);
			mesh->Vao()->SetAttributeDivisor(15, 1);
			GetInstance().m_sceneHighlightPrePassInstancedProgram->SetFloat4x4("model", ltw.m_value);
			glDrawElementsInstanced(GL_TRIANGLES, (GLsizei)mesh->GetTriangleAmount() * 3, GL_UNSIGNED_INT, 0, (GLsizei)count);
		}
	}
}

void EditorManager::HighLightEntityHelper(const Entity& entity)
{
	if (!entity.IsValid() || entity.IsDeleted() || !entity.IsEnabled()) return;
	EntityManager::ForEachChild(entity, [](Entity child)
		{
			HighLightEntityHelper(child);
		}
	);
	if (entity.HasPrivateComponent<MeshRenderer>())
	{
		auto& mmc = entity.GetPrivateComponent<MeshRenderer>();
		if (mmc->IsEnabled() && mmc->m_material != nullptr && mmc->m_mesh != nullptr)
		{
			auto ltw = EntityManager::GetComponentData<GlobalTransform>(entity);
			auto* mesh = mmc->m_mesh.get();
			mesh->Enable();
			mesh->Vao()->DisableAttributeArray(12);
			mesh->Vao()->DisableAttributeArray(13);
			mesh->Vao()->DisableAttributeArray(14);
			mesh->Vao()->DisableAttributeArray(15);
			GetInstance().m_sceneHighlightProgram->SetFloat4x4("model", ltw.m_value);
			GetInstance().m_sceneHighlightProgram->SetFloat3("scale", ltw.GetScale());
			glDrawElements(GL_TRIANGLES, (GLsizei)mesh->GetTriangleAmount() * 3, GL_UNSIGNED_INT, 0);
		}
	}
	if (entity.HasPrivateComponent<Particles>())
	{
		auto& immc = entity.GetPrivateComponent<Particles>();
		if (immc->IsEnabled() && immc->m_material != nullptr && immc->m_mesh != nullptr)
		{
			auto count = immc->m_matrices.size();
			std::unique_ptr<GLVBO> matricesBuffer = std::make_unique<GLVBO>();
			matricesBuffer->SetData((GLsizei)count * sizeof(glm::mat4), immc->m_matrices.data(), GL_STATIC_DRAW);
			auto ltw = EntityManager::GetComponentData<GlobalTransform>(entity);
			auto* mesh = immc->m_mesh.get();
			mesh->Enable();
			mesh->Vao()->EnableAttributeArray(12);
			mesh->Vao()->SetAttributePointer(12, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)0);
			mesh->Vao()->EnableAttributeArray(13);
			mesh->Vao()->SetAttributePointer(13, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(sizeof(glm::vec4)));
			mesh->Vao()->EnableAttributeArray(14);
			mesh->Vao()->SetAttributePointer(14, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(2 * sizeof(glm::vec4)));
			mesh->Vao()->EnableAttributeArray(15);
			mesh->Vao()->SetAttributePointer(15, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(3 * sizeof(glm::vec4)));
			mesh->Vao()->SetAttributeDivisor(12, 1);
			mesh->Vao()->SetAttributeDivisor(13, 1);
			mesh->Vao()->SetAttributeDivisor(14, 1);
			mesh->Vao()->SetAttributeDivisor(15, 1);
			GetInstance().m_sceneHighlightInstancedProgram->SetFloat4x4("model", ltw.m_value);
			glDrawElementsInstanced(GL_TRIANGLES, (GLsizei)mesh->GetTriangleAmount() * 3, GL_UNSIGNED_INT, 0, (GLsizei)count);
		}
	}
}

void EditorManager::MoveCamera(const glm::quat& targetRotation, const glm::vec3& targetPosition, const float& transitionTime)
{
	GetInstance().m_previousRotation = GetInstance().m_sceneCameraRotation;
	GetInstance().m_previousPosition = GetInstance().m_sceneCameraPosition;
	GetInstance().m_transitionTime = transitionTime;
	GetInstance().m_transitionTimer = 0;
	GetInstance().m_targetRotation = targetRotation;
	GetInstance().m_targetPosition = targetPosition;
	GetInstance().m_lockCamera = true;
	GetInstance().m_leftMouseButtonHold = false;
	GetInstance().m_rightMouseButtonHold = false;
	GetInstance().m_startMouse = false;
}

void EditorManager::HighLightEntity(const Entity& entity, const glm::vec4& color)
{
	if (!entity.IsValid() || entity.IsDeleted() || !entity.IsEnabled()) return;
	CameraComponent::m_cameraInfoBlock.UpdateMatrices(GetInstance().m_sceneCamera.get(),
		GetInstance().m_sceneCameraPosition,
		GetInstance().m_sceneCameraRotation
	);
	CameraComponent::m_cameraInfoBlock.UploadMatrices(GetInstance().m_sceneCamera.get());
	GetInstance().m_sceneCamera->Bind();
	glEnable(GL_STENCIL_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);
	glStencilFunc(GL_ALWAYS, 1, 0xFF);
	glStencilMask(0xFF);
	GetInstance().m_sceneHighlightPrePassProgram->Bind();
	GetInstance().m_sceneHighlightPrePassProgram->SetFloat4("color", glm::vec4(1.0f, 0.5f, 0.0f, 0.5f));
	HighLightEntityPrePassHelper(entity);
	glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
	glStencilMask(0x00);
	GetInstance().m_sceneHighlightProgram->Bind();
	GetInstance().m_sceneHighlightProgram->SetFloat4("color", color);
	HighLightEntityHelper(entity);
	glStencilMask(0xFF);
	glStencilFunc(GL_ALWAYS, 0, 0xFF);
	glEnable(GL_DEPTH_TEST);
}

void UniEngine::EditorManager::Init()
{
	GetInstance().m_enabled = true;
	GetInstance().m_basicEntityArchetype = EntityManager::CreateEntityArchetype("General", GlobalTransform(), Transform());

	GetInstance().m_sceneCameraEntityRecorderTexture = std::make_unique<GLTexture2D>(1, GL_R32F, GetInstance().m_sceneCameraResolutionX, GetInstance().m_sceneCameraResolutionY, false);
	GetInstance().m_sceneCameraEntityRecorderTexture->SetInt(GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	GetInstance().m_sceneCameraEntityRecorderTexture->SetInt(GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	GetInstance().m_sceneCameraEntityRecorderTexture->ReSize(0, GL_R32F, GL_RED, GL_FLOAT, 0, GetInstance().m_sceneCameraResolutionX, GetInstance().m_sceneCameraResolutionY);
	GetInstance().m_sceneCameraEntityRecorderRenderBuffer = std::make_unique<GLRenderBuffer>();
	GetInstance().m_sceneCameraEntityRecorder = std::make_unique<RenderTarget>(GetInstance().m_sceneCameraResolutionX, GetInstance().m_sceneCameraResolutionY);
	GetInstance().m_sceneCameraEntityRecorderRenderBuffer->AllocateStorage(GL_DEPTH24_STENCIL8, GetInstance().m_sceneCameraResolutionX, GetInstance().m_sceneCameraResolutionY);
	GetInstance().m_sceneCameraEntityRecorder->SetResolution(GetInstance().m_sceneCameraResolutionX, GetInstance().m_sceneCameraResolutionY);
	GetInstance().m_sceneCameraEntityRecorder->AttachRenderBuffer(GetInstance().m_sceneCameraEntityRecorderRenderBuffer.get(), GL_DEPTH_STENCIL_ATTACHMENT);
	GetInstance().m_sceneCameraEntityRecorder->AttachTexture(GetInstance().m_sceneCameraEntityRecorderTexture.get(), GL_COLOR_ATTACHMENT0);


	std::string vertShaderCode = std::string("#version 460 core\n")
		+ *Default::ShaderIncludes::Uniform +
		"\n" +
		FileIO::LoadFileAsString(FileIO::GetResourcePath("Shaders/Vertex/Empty.vert"));
	std::string fragShaderCode = std::string("#version 460 core\n") +
		FileIO::LoadFileAsString(FileIO::GetResourcePath("Shaders/Fragment/EntityRecorder.frag"));

	auto vertShader = std::make_shared<GLShader>(ShaderType::Vertex);
	vertShader->Compile(vertShaderCode);
	auto fragShader = std::make_shared<GLShader>(ShaderType::Fragment);
	fragShader->Compile(fragShaderCode);


	GetInstance().m_sceneCameraEntityRecorderProgram = std::make_unique<GLProgram>(
		vertShader,
		fragShader
		);

	vertShaderCode = std::string("#version 460 core\n")
		+ *Default::ShaderIncludes::Uniform +
		"\n" +
		FileIO::LoadFileAsString(FileIO::GetResourcePath("Shaders/Vertex/EmptyInstanced.vert"));
	vertShader = std::make_shared<GLShader>(ShaderType::Vertex);
	vertShader->Compile(vertShaderCode);
	GetInstance().m_sceneCameraEntityInstancedRecorderProgram = std::make_unique<GLProgram>(
		vertShader,
		fragShader
		);

	vertShaderCode = std::string("#version 460 core\n")
		+ *Default::ShaderIncludes::Uniform +
		"\n" +
		FileIO::LoadFileAsString(FileIO::GetResourcePath("Shaders/Vertex/Empty.vert"));
	vertShader = std::make_shared<GLShader>(ShaderType::Vertex);
	vertShader->Compile(vertShaderCode);

	fragShaderCode = std::string("#version 460 core\n") +
		FileIO::LoadFileAsString(FileIO::GetResourcePath("Shaders/Fragment/Highlight.frag"));

	fragShader = std::make_shared<GLShader>(ShaderType::Fragment);
	fragShader->Compile(fragShaderCode);

	GetInstance().m_sceneHighlightPrePassProgram = std::make_unique<GLProgram>(
		vertShader,
		fragShader
		);

	vertShaderCode = std::string("#version 460 core\n")
		+ *Default::ShaderIncludes::Uniform +
		"\n" +
		FileIO::LoadFileAsString(FileIO::GetResourcePath("Shaders/Vertex/EmptyInstanced.vert"));
	vertShader = std::make_shared<GLShader>(ShaderType::Vertex);
	vertShader->Compile(vertShaderCode);
	GetInstance().m_sceneHighlightPrePassInstancedProgram = std::make_unique<GLProgram>(
		vertShader,
		fragShader
		);


	vertShaderCode = std::string("#version 460 core\n")
		+ *Default::ShaderIncludes::Uniform +
		"\n" +
		FileIO::LoadFileAsString(FileIO::GetResourcePath("Shaders/Vertex/Highlight.vert"));

	vertShader = std::make_shared<GLShader>(ShaderType::Vertex);
	vertShader->Compile(vertShaderCode);

	GetInstance().m_sceneHighlightProgram = std::make_unique<GLProgram>(
		vertShader,
		fragShader
		);

	vertShaderCode = std::string("#version 460 core\n")
		+ *Default::ShaderIncludes::Uniform +
		"\n" +
		FileIO::LoadFileAsString(FileIO::GetResourcePath("Shaders/Vertex/HighlightInstanced.vert"));

	vertShader = std::make_shared<GLShader>(ShaderType::Vertex);
	vertShader->Compile(vertShaderCode);

	GetInstance().m_sceneHighlightInstancedProgram = std::make_unique<GLProgram>(
		vertShader,
		fragShader
		);

	RegisterComponentDataInspector<GlobalTransform>([](Entity entity, ComponentBase* data, bool isRoot)
		{
			auto* ltw = reinterpret_cast<GlobalTransform*>(data);
			glm::vec3 er;
			glm::vec3 t;
			glm::vec3 s;
			ltw->Decompose(t, er, s);
			er = glm::degrees(er);
			ImGui::InputFloat3("Position##Global", &t.x, "%.3f", ImGuiInputTextFlags_ReadOnly);
			ImGui::InputFloat3("Rotation##Global", &er.x, "%.3f", ImGuiInputTextFlags_ReadOnly);
			ImGui::InputFloat3("Scale##Global", &s.x, "%.3f", ImGuiInputTextFlags_ReadOnly);
		}
	);


	RegisterComponentDataInspector<Transform>([](Entity entity, ComponentBase* data, bool isRoot)
		{
			static Entity previousEntity;
			if (entity.IsStatic())
			{
				previousEntity.m_index = previousEntity.m_version = 0;
				auto* ltp = static_cast<Transform*>(static_cast<void*>(data));
				glm::vec3 er;
				glm::vec3 t;
				glm::vec3 s;
				ltp->Decompose(t, er, s);
				er = glm::degrees(er);
				ImGui::InputFloat3("Position##Local", &t.x, "%.3f", ImGuiInputTextFlags_ReadOnly);
				ImGui::InputFloat3("Rotation##Local", &er.x, "%.3f", ImGuiInputTextFlags_ReadOnly);
				ImGui::InputFloat3("Scale##Local", &s.x, "%.3f", ImGuiInputTextFlags_ReadOnly);
				return;
			}
			auto* ltp = static_cast<Transform*>(static_cast<void*>(data));
			bool edited = false;

			if (previousEntity != entity) {
				previousEntity = entity;
				ltp->Decompose(GetInstance().m_previouslyStoredPosition, GetInstance().m_previouslyStoredRotation, GetInstance().m_previouslyStoredScale);
				GetInstance().m_previouslyStoredRotation = glm::degrees(GetInstance().m_previouslyStoredRotation);
				GetInstance().m_localPositionSelected = true;
				GetInstance().m_localRotationSelected = false;
				GetInstance().m_localScaleSelected = false;
			}
			if (ImGui::DragFloat3("##LocalPosition", &GetInstance().m_previouslyStoredPosition.x, 0.1f, 0, 0)) edited = true;
			ImGui::SameLine();
			if (ImGui::Selectable("Position##Local", &GetInstance().m_localPositionSelected) && GetInstance().m_localPositionSelected)
			{
				GetInstance().m_localRotationSelected = false;
				GetInstance().m_localScaleSelected = false;
			}
			if (ImGui::DragFloat3("##LocalRotation", &GetInstance().m_previouslyStoredRotation.x, 1.0f, 0, 0)) edited = true;
			ImGui::SameLine();
			if (ImGui::Selectable("Rotation##Local", &GetInstance().m_localRotationSelected) && GetInstance().m_localRotationSelected)
			{
				GetInstance().m_localPositionSelected = false;
				GetInstance().m_localScaleSelected = false;
			}
			if (ImGui::DragFloat3("##LocalScale", &GetInstance().m_previouslyStoredScale.x, 0.01f, 0, 0)) edited = true;
			ImGui::SameLine();
			if (ImGui::Selectable("Scale##Local", &GetInstance().m_localScaleSelected) && GetInstance().m_localScaleSelected)
			{
				GetInstance().m_localRotationSelected = false;
				GetInstance().m_localPositionSelected = false;
			}
			if (edited)
			{
				ltp->m_value = glm::translate(GetInstance().m_previouslyStoredPosition) * glm::mat4_cast(glm::quat(glm::radians(GetInstance().m_previouslyStoredRotation))) * glm::scale(GetInstance().m_previouslyStoredScale);
			}
		}
	);

	RegisterPrivateComponentMenu<DirectionalLight>([](Entity owner)
		{
			if (owner.HasPrivateComponent<DirectionalLight>()) return;
			if (ImGui::SmallButton("DirectionalLight"))
			{
				owner.SetPrivateComponent(std::make_unique<DirectionalLight>());
			}
		}
	);
	RegisterPrivateComponentMenu<PointLight>([](Entity owner)
		{
			if (owner.HasPrivateComponent<PointLight>()) return;
			if (ImGui::SmallButton("PointLight"))
			{
				owner.SetPrivateComponent(std::make_unique<PointLight>());
			}
		}
	);
	RegisterPrivateComponentMenu<SpotLight>([](Entity owner)
		{
			if (owner.HasPrivateComponent<SpotLight>()) return;
			if (ImGui::SmallButton("CameraComponent"))
			{
				owner.SetPrivateComponent(std::make_unique<SpotLight>());
			}
		}
	);

	RegisterPrivateComponentMenu<CameraComponent>([](Entity owner)
		{
			if (owner.HasPrivateComponent<CameraComponent>()) return;
			if (ImGui::SmallButton("CameraComponent"))
			{
				owner.SetPrivateComponent(std::make_unique<CameraComponent>());
			}
		}
	);
	RegisterPrivateComponentMenu<RigidBody>([](Entity owner)
		{
			if (owner.HasPrivateComponent<RigidBody>()) return;
			if (Application::IsPlaying()) return;
			if (ImGui::SmallButton("RigidBody"))
			{
				owner.SetPrivateComponent(std::make_unique<RigidBody>());
			}
		}
	);
	RegisterPrivateComponentMenu<MeshRenderer>([](Entity owner)
		{
			if (owner.HasPrivateComponent<MeshRenderer>()) return;
			if (ImGui::SmallButton("MeshRenderer"))
			{
				owner.SetPrivateComponent(std::make_unique<MeshRenderer>());
			}
		}
	);
	RegisterPrivateComponentMenu<PostProcessing>([](Entity owner)
		{
			if (owner.HasPrivateComponent<PostProcessing>()) return;
			if (ImGui::SmallButton("PostProcessing"))
			{
				owner.SetPrivateComponent(std::make_unique<PostProcessing>());
			}
		}
	);

	RegisterPrivateComponentMenu<Particles>([](Entity owner)
		{
			if (owner.HasPrivateComponent<Particles>()) return;
			if (ImGui::SmallButton("Particles"))
			{
				owner.SetPrivateComponent(std::make_unique<Particles>());
			}
		}
	);
	GetInstance().m_selectedEntity.m_index = 0;
	GetInstance().m_configFlags += EntityEditorSystem_EnableEntityHierarchy;
	GetInstance().m_configFlags += EntityEditorSystem_EnableEntityInspector;
	GetInstance().m_sceneCamera = std::make_unique<CameraComponent>();
	GetInstance().m_sceneCamera->m_drawSkyBox = false;
	GetInstance().m_sceneCamera->m_skyBox = Default::Textures::DefaultSkybox;
}

void UniEngine::EditorManager::Destroy()
{

}
static const char* HierarchyDisplayMode[]{ "Archetype", "Hierarchy" };

void EditorManager::PreUpdate()
{
	if (ImGui::BeginMainMenuBar()) {
		if (ImGui::Button(Application::m_playing ? "Pause" : "Play"))
		{
			Application::m_playing = !Application::m_playing;
		}
		ImGui::Separator();
		if (ImGui::BeginMenu("File"))
		{
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Edit"))
		{
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("View"))
		{
			ImGui::Checkbox("Console", &GetInstance().m_enableConsole);
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Window"))
		{
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Help"))
		{
			ImGui::EndMenu();
		}
		ImGui::EndMainMenuBar();
	}
	const auto resolution = GetInstance().m_sceneCamera->m_gBuffer->GetResolution();
	if (GetInstance().m_sceneCameraResolutionX != 0 && GetInstance().m_sceneCameraResolutionY != 0 && (resolution.x != GetInstance().m_sceneCameraResolutionX || resolution.y != GetInstance().m_sceneCameraResolutionY)) {
		GetInstance().m_sceneCamera->ResizeResolution(GetInstance().m_sceneCameraResolutionX, GetInstance().m_sceneCameraResolutionY);
		GetInstance().m_sceneCameraEntityRecorderTexture->ReSize(0, GL_R32F, GL_RED, GL_FLOAT, 0, GetInstance().m_sceneCameraResolutionX, GetInstance().m_sceneCameraResolutionY);
		GetInstance().m_sceneCameraEntityRecorderRenderBuffer->AllocateStorage(GL_DEPTH24_STENCIL8, GetInstance().m_sceneCameraResolutionX, GetInstance().m_sceneCameraResolutionY);
		GetInstance().m_sceneCameraEntityRecorder->SetResolution(GetInstance().m_sceneCameraResolutionX, GetInstance().m_sceneCameraResolutionY);
	}
	GetInstance().m_sceneCamera->Clear();
	GetInstance().m_sceneCameraEntityRecorder->Clear();
	if(GetInstance().m_lockCamera)
	{
		GetInstance().m_transitionTimer += Application::GetCurrentWorld()->Time()->DeltaTime();
		const float a = 1.0 - glm::pow(1.0 - GetInstance().m_transitionTimer / GetInstance().m_transitionTime, 4.0f);
		GetInstance().m_sceneCameraRotation = glm::mix(GetInstance().m_previousRotation, GetInstance().m_targetRotation, a);
		GetInstance().m_sceneCameraPosition = glm::mix(GetInstance().m_previousPosition, GetInstance().m_targetPosition, a);
		if (a >= 1.0f) {
			GetInstance().m_lockCamera = false;
			GetInstance().m_sceneCameraRotation = GetInstance().m_targetRotation;
			GetInstance().m_sceneCameraPosition = GetInstance().m_targetPosition;
			GetInstance().m_sceneCameraYawAngle = -90;
			GetInstance().m_sceneCameraPitchAngle = 0;
		}
	}
}


void UniEngine::EditorManager::Update()
{

}

Entity EditorManager::GetSelectedEntity()
{
	return GetInstance().m_selectedEntity;
}

void UniEngine::EditorManager::DrawEntityNode(Entity& entity)
{
	std::string title = std::to_string(entity.m_index) + ": ";
	title += entity.GetName();
	bool enabled = entity.IsEnabled();
	if (enabled) {
		ImGui::PushStyleColor(ImGuiCol_Text, ImVec4({ 1, 1, 1, 1 }));
	}
	bool opened = ImGui::TreeNodeEx(title.c_str(), ImGuiTreeNodeFlags_NoTreePushOnOpen | ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_NoAutoOpenOnLog | (GetInstance().m_selectedEntity == entity ? ImGuiTreeNodeFlags_Framed : ImGuiTreeNodeFlags_FramePadding));
	if (ImGui::BeginDragDropSource())
	{
		const std::string hash = std::to_string(std::hash<std::string>{}(typeid(Entity).name()));
		ImGui::SetDragDropPayload(hash.c_str(), &entity, sizeof(Entity));
		ImGui::TextColored(ImVec4(0, 0, 1, 1), title.c_str());
		ImGui::EndDragDropSource();
	}
	if (ImGui::BeginDragDropTarget())
	{
		const std::string hash = std::to_string(std::hash<std::string>{}(typeid(Entity).name()));
		if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload(hash.c_str()))
		{
			IM_ASSERT(payload->DataSize == sizeof(Entity));
			Entity payload_n = *static_cast<Entity*>(payload->Data);
			EntityManager::SetParent(payload_n, entity);
		}
		ImGui::EndDragDropTarget();
	}
	if (enabled) {
		ImGui::PopStyleColor();
	}
	if (ImGui::IsItemHovered() && ImGui::IsMouseClicked(0)) {
		GetInstance().m_selectedEntity = entity;
	}
	const bool deleted = DrawEntityMenu(enabled, entity);
	if (opened && !deleted) {
		ImGui::TreePush();
		EntityManager::ForEachChild(entity, [](Entity child) {
			DrawEntityNode(child);
			});
		ImGui::TreePop();
	}
}

void EditorManager::LateUpdate()
{
	if (GetInstance().m_leftMouseButtonHold && !InputManager::GetMouseInternal(GLFW_MOUSE_BUTTON_LEFT, WindowManager::GetWindow()))
	{
		GetInstance().m_leftMouseButtonHold = false;
	}
	if (GetInstance().m_rightMouseButtonHold && !InputManager::GetMouseInternal(GLFW_MOUSE_BUTTON_RIGHT, WindowManager::GetWindow()))
	{
		GetInstance().m_rightMouseButtonHold = false;
		GetInstance().m_startMouse = false;
	}
#pragma region Entity Explorer
	if (GetInstance().m_configFlags & EntityEditorSystem_EnableEntityHierarchy) {
		ImGui::Begin("Entity Explorer");
		if (ImGui::BeginDragDropTarget())
		{
			const std::string hash = std::to_string(std::hash<std::string>{}(typeid(Entity).name()));
			if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload(hash.c_str()))
			{
				IM_ASSERT(payload->DataSize == sizeof(Entity));
				Entity payload_n = *static_cast<Entity*>(payload->Data);
				auto parent = EntityManager::GetParent(payload_n);
				if (!parent.IsNull()) EntityManager::RemoveChild(payload_n, parent);
			}
			ImGui::EndDragDropTarget();
		}
		if (ImGui::BeginPopupContextWindow("DataComponentInspectorPopup"))
		{
			if (ImGui::Button("Create new entity"))
			{
				auto newEntity = EntityManager::CreateEntity(GetInstance().m_basicEntityArchetype);
				newEntity.SetComponentData(Transform());
				newEntity.SetComponentData(GlobalTransform());
			}
			ImGui::EndPopup();
		}
		ImGui::Combo("Display mode", &GetInstance().m_selectedHierarchyDisplayMode, HierarchyDisplayMode, IM_ARRAYSIZE(HierarchyDisplayMode));
		if (GetInstance().m_selectedHierarchyDisplayMode == 0) {
			EntityManager::UnsafeForEachEntityStorage([](int i, EntityComponentStorage storage) {
				ImGui::Separator();
				std::string title = std::to_string(i) + ". " + storage.m_archetypeInfo->m_name;
				if (ImGui::CollapsingHeader(title.c_str())) {
					ImGui::PushStyleColor(ImGuiCol_HeaderActive, ImVec4(0.2, 0.3, 0.2, 1.0));
					ImGui::PushStyleColor(ImGuiCol_HeaderHovered, ImVec4(0.2, 0.2, 0.2, 1.0));
					ImGui::PushStyleColor(ImGuiCol_Header, ImVec4(0.2, 0.2, 0.3, 1.0));
					for (int j = 0; j < storage.m_archetypeInfo->m_entityAliveCount; j++) {
						Entity entity = storage.m_chunkArray->Entities.at(j);
						std::string title = std::to_string(entity.m_index) + ": ";
						title += entity.GetName();
						bool enabled = entity.IsEnabled();
						if (enabled) {
							ImGui::PushStyleColor(ImGuiCol_Text, ImVec4({ 1, 1, 1, 1 }));
						}
						ImGui::TreeNodeEx(title.c_str(), ImGuiTreeNodeFlags_NoTreePushOnOpen | ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoAutoOpenOnLog | (GetInstance().m_selectedEntity == entity ? ImGuiTreeNodeFlags_Framed : ImGuiTreeNodeFlags_FramePadding));
						if (enabled) {
							ImGui::PopStyleColor();
						}
						DrawEntityMenu(enabled, entity);
						if (ImGui::IsItemHovered() && ImGui::IsMouseClicked(0)) {
							GetInstance().m_selectedEntity = entity;
						}
					}
					ImGui::PopStyleColor();
					ImGui::PopStyleColor();
					ImGui::PopStyleColor();
				}
				});
		}
		else if (GetInstance().m_selectedHierarchyDisplayMode == 1) {
			ImGui::PushStyleColor(ImGuiCol_HeaderActive, ImVec4(0.2, 0.3, 0.2, 1.0));
			ImGui::PushStyleColor(ImGuiCol_HeaderHovered, ImVec4(0.2, 0.2, 0.2, 1.0));
			ImGui::PushStyleColor(ImGuiCol_Header, ImVec4(0.2, 0.2, 0.3, 1.0));
			EntityManager::ForAllEntities([](int i, Entity entity) {
				if (EntityManager::GetParent(entity).IsNull()) DrawEntityNode(entity);
				});
			ImGui::PopStyleColor();
			ImGui::PopStyleColor();
			ImGui::PopStyleColor();
		}

		ImGui::End();
	}
#pragma endregion
#pragma region Entity Inspector
	if (GetInstance().m_configFlags & EntityEditorSystem_EnableEntityInspector) {
		ImGui::Begin("Entity Inspector");
		if (!GetInstance().m_selectedEntity.IsNull() && !GetInstance().m_selectedEntity.IsDeleted()) {
			std::string title = std::to_string(GetInstance().m_selectedEntity.m_index) + ": ";
			title += GetInstance().m_selectedEntity.GetName();
			bool enabled = GetInstance().m_selectedEntity.IsEnabled();
			if (ImGui::Checkbox((title + "##EnabledCheckbox").c_str(), &enabled)) {
				if (GetInstance().m_selectedEntity.IsEnabled() != enabled)
				{
					GetInstance().m_selectedEntity.SetEnabled(enabled);
				}
			}
			ImGui::SameLine();
			bool isStatic = GetInstance().m_selectedEntity.IsStatic();
			if (ImGui::Checkbox("Static", &isStatic))
			{
				if (GetInstance().m_selectedEntity.IsStatic() != isStatic)
				{
					GetInstance().m_selectedEntity.SetStatic(isStatic);
				}
			}
			bool deleted = DrawEntityMenu(GetInstance().m_selectedEntity.IsEnabled(), GetInstance().m_selectedEntity);
			ImGui::Separator();
			if (!deleted) {
				if (ImGui::CollapsingHeader("Data components", ImGuiTreeNodeFlags_DefaultOpen)) {
					if (ImGui::BeginPopupContextItem("DataComponentInspectorPopup"))
					{
						ImGui::Text("Add data component: ");
						ImGui::Separator();
						for (auto& i : GetInstance().m_componentDataMenuList)
						{
							i.second(GetInstance().m_selectedEntity);
						}
						ImGui::Separator();
						ImGui::EndPopup();
					}
					bool skip = false;
					int i = 0;
					EntityManager::UnsafeForEachComponent(GetInstance().m_selectedEntity, [&skip, &i](ComponentType type, void* data)
						{
							if (skip) return;
							std::string info = type.m_name.substr(7);
							info += " Size: " + std::to_string(type.m_size);
							ImGui::Text(info.c_str());
							ImGui::PushID(i);
							if (ImGui::BeginPopupContextItem(("DataComponentDeletePopup" + std::to_string(i)).c_str()))
							{
								if (ImGui::Button("Remove"))
								{
									skip = true;
									EntityManager::RemoveComponentData(GetInstance().m_selectedEntity, type.m_typeId);
								}
								ImGui::EndPopup();
							}
							ImGui::PopID();
							InspectComponentData(GetInstance().m_selectedEntity, static_cast<ComponentBase*>(data), type, EntityManager::GetParent(GetInstance().m_selectedEntity).IsNull());
							ImGui::Separator();
							i++;
						}
					);
				}

				if (ImGui::CollapsingHeader("Private components", ImGuiTreeNodeFlags_DefaultOpen)) {
					if (ImGui::BeginPopupContextItem("PrivateComponentInspectorPopup"))
					{
						ImGui::Text("Add private component: ");
						ImGui::Separator();
						for (auto& i : GetInstance().m_privateComponentMenuList)
						{
							i.second(GetInstance().m_selectedEntity);
						}
						ImGui::Separator();
						ImGui::EndPopup();
					}

					int i = 0;
					bool skip = false;
					EntityManager::ForEachPrivateComponent(GetInstance().m_selectedEntity, [&i, &skip](PrivateComponentElement& data)
						{
							if (skip) return;
							ImGui::Checkbox(data.m_name.substr(6).c_str(), &data.m_privateComponentData->m_enabled);
							ImGui::PushID(i);
							if (ImGui::BeginPopupContextItem(("PrivateComponentDeletePopup" + std::to_string(i)).c_str()))
							{
								if (ImGui::Button("Remove"))
								{
									skip = true;
									EntityManager::RemovePrivateComponent(GetInstance().m_selectedEntity, data.m_typeId);
								}
								ImGui::EndPopup();
							}
							ImGui::PopID();
							if (!skip) {
								if (ImGui::TreeNodeEx(("Component Settings##" + std::to_string(i)).c_str(), ImGuiTreeNodeFlags_DefaultOpen)) {
									data.m_privateComponentData->OnGui();
									ImGui::TreePop();
								}
								ImGui::Separator();
								i++;
							}
						}
					);
				}
			}
		}
		else {
			GetInstance().m_selectedEntity.m_index = 0;
		}
		ImGui::End();
	}
#pragma endregion
#pragma region Scene Window	
	ImVec2 viewPortSize;
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0, 0 });
	ImGui::Begin("Scene");
	{
		// Using a Child allow to fill all the space of the window.
		// It also allows customization
		if (ImGui::BeginChild("CameraRenderer")) {
			viewPortSize = ImGui::GetWindowSize();
			// Because I use the texture from OpenGL, I need to invert the V from the UV.
			ImGui::Image((ImTextureID)GetInstance().m_sceneCamera->GetTexture()->Texture()->Id(), viewPortSize, ImVec2(0, 1), ImVec2(1, 0));
			if (ImGui::BeginDragDropTarget())
			{
				const std::string modelTypeHash = std::to_string(std::hash<std::string>{}(typeid(Model).name()));
				if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload(modelTypeHash.c_str()))
				{
					IM_ASSERT(payload->DataSize == sizeof(std::shared_ptr<Model>));
					std::shared_ptr<Model> payload_n = *(std::shared_ptr<Model>*)payload->Data;
					EntityArchetype archetype = EntityManager::CreateEntityArchetype("Default", Transform(), GlobalTransform());
					Transform ltw;
					ResourceManager::ToEntity(archetype, payload_n).SetComponentData(ltw);
				}
				const std::string meshTypeHash = std::to_string(std::hash<std::string>{}(typeid(Mesh).name()));
				if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload(meshTypeHash.c_str()))
				{
					IM_ASSERT(payload->DataSize == sizeof(std::shared_ptr<Mesh>));
					std::shared_ptr<Mesh> payload_n = *(std::shared_ptr<Mesh>*)payload->Data;
					Transform ltw;
					auto meshRenderer = std::make_unique<MeshRenderer>();
					meshRenderer->m_mesh = payload_n;
					meshRenderer->m_material = std::make_shared<Material>();
					meshRenderer->m_material->SetTexture(Default::Textures::StandardTexture);
					meshRenderer->m_material->SetProgram(Default::GLPrograms::StandardProgram);
					Entity entity = EntityManager::CreateEntity("Mesh");
					entity.SetComponentData(ltw);
					entity.SetPrivateComponent(std::move(meshRenderer));
				}
				ImGui::EndDragDropTarget();
			}
			static int corner = 1;
			ImVec2 overlayPos = ImGui::GetWindowPos();
			ImVec2 window_pos = ImVec2((corner & 1) ? (overlayPos.x + viewPortSize.x) : (overlayPos.x), (corner & 2) ? (overlayPos.y + viewPortSize.y) : (overlayPos.y));
			if (GetInstance().m_enableInfoWindow)
			{
				ImVec2 window_pos_pivot = ImVec2((corner & 1) ? 1.0f : 0.0f, (corner & 2) ? 1.0f : 0.0f);
				ImGui::SetNextWindowPos(window_pos, ImGuiCond_Always, window_pos_pivot);
				ImGui::SetNextWindowBgAlpha(0.35f);
				ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoNav;

				ImGui::BeginChild("Render Info", ImVec2(200, 100), false, window_flags);
				ImGui::Text("%.1f FPS", ImGui::GetIO().Framerate);
				ImGui::Checkbox("Skybox", &GetInstance().m_sceneCamera->m_drawSkyBox);
				if (ImGui::Button("Reset camera"))
				{
					MoveCamera(GetInstance().m_defaultSceneCameraRotation, GetInstance().m_defaultSceneCameraPosition);
				}
				ImGui::Separator();
				if (ImGui::IsMousePosValid()) {
					glm::vec2 pos;
					InputManager::GetMousePositionInternal(ImGui::GetCurrentWindowRead(), pos);
					ImGui::Text("Mouse Position: (%.1f,%.1f)", pos.x, pos.y);
				}
				else {
					ImGui::Text("Mouse Position: <invalid>");
				}
				ImGui::EndChild();
			}

			glm::vec2 mousePosition = glm::vec2(FLT_MAX, FLT_MIN);
			if (GetInstance().m_sceneWindowFocused)
			{
				bool valid = InputManager::GetMousePositionInternal(ImGui::GetCurrentWindowRead(), mousePosition);
				float xOffset = 0;
				float yOffset = 0;
				if (valid) {
					if (!GetInstance().m_startMouse) {
						GetInstance().m_lastX = mousePosition.x;
						GetInstance().m_lastY = mousePosition.y;
						GetInstance().m_startMouse = true;
					}
					xOffset = mousePosition.x - GetInstance().m_lastX;
					yOffset = -mousePosition.y + GetInstance().m_lastY;
					GetInstance().m_lastX = mousePosition.x;
					GetInstance().m_lastY = mousePosition.y;
#pragma region Scene Camera Controller
					if (!GetInstance().m_rightMouseButtonHold && !(mousePosition.x > 0 || mousePosition.y < 0 || mousePosition.x < -viewPortSize.x || mousePosition.y > viewPortSize.y) &&
						InputManager::GetMouseInternal(GLFW_MOUSE_BUTTON_RIGHT, WindowManager::GetWindow())) {
						GetInstance().m_rightMouseButtonHold = true;
					}
					if (GetInstance().m_rightMouseButtonHold && !GetInstance().m_lockCamera)
					{
						glm::vec3 front = GetInstance().m_sceneCameraRotation * glm::vec3(0, 0, -1);
						glm::vec3 right = GetInstance().m_sceneCameraRotation * glm::vec3(1, 0, 0);
						if (InputManager::GetKeyInternal(GLFW_KEY_W, WindowManager::GetWindow())) {
							GetInstance().m_sceneCameraPosition += front * static_cast<float>(Application::GetCurrentWorld()->Time()->DeltaTime()) * GetInstance().m_velocity;
						}
						if (InputManager::GetKeyInternal(GLFW_KEY_S, WindowManager::GetWindow())) {
							GetInstance().m_sceneCameraPosition -= front * static_cast<float>(Application::GetCurrentWorld()->Time()->DeltaTime()) * GetInstance().m_velocity;
						}
						if (InputManager::GetKeyInternal(GLFW_KEY_A, WindowManager::GetWindow())) {
							GetInstance().m_sceneCameraPosition -= right * static_cast<float>(Application::GetCurrentWorld()->Time()->DeltaTime()) * GetInstance().m_velocity;
						}
						if (InputManager::GetKeyInternal(GLFW_KEY_D, WindowManager::GetWindow())) {
							GetInstance().m_sceneCameraPosition += right * static_cast<float>(Application::GetCurrentWorld()->Time()->DeltaTime()) * GetInstance().m_velocity;
						}
						if (InputManager::GetKeyInternal(GLFW_KEY_LEFT_SHIFT, WindowManager::GetWindow())) {
							GetInstance().m_sceneCameraPosition.y += GetInstance().m_velocity * static_cast<float>(Application::GetCurrentWorld()->Time()->DeltaTime());
						}
						if (InputManager::GetKeyInternal(GLFW_KEY_LEFT_CONTROL, WindowManager::GetWindow())) {
							GetInstance().m_sceneCameraPosition.y -= GetInstance().m_velocity * static_cast<float>(Application::GetCurrentWorld()->Time()->DeltaTime());
						}
						if (xOffset != 0.0f || yOffset != 0.0f) {
							GetInstance().m_sceneCameraYawAngle += xOffset * GetInstance().m_sensitivity;
							GetInstance().m_sceneCameraPitchAngle += yOffset * GetInstance().m_sensitivity;
							if (GetInstance().m_sceneCameraPitchAngle > 89.0f)
								GetInstance().m_sceneCameraPitchAngle = 89.0f;
							if (GetInstance().m_sceneCameraPitchAngle < -89.0f)
								GetInstance().m_sceneCameraPitchAngle = -89.0f;

							GetInstance().m_sceneCameraRotation = CameraComponent::ProcessMouseMovement(GetInstance().m_sceneCameraYawAngle, GetInstance().m_sceneCameraPitchAngle, false);
						}
					}
#pragma endregion
				}
			}
#pragma region Gizmos and Entity Selection
			bool mouseSelectEntity = true;
			if (!GetInstance().m_selectedEntity.IsNull() && !GetInstance().m_selectedEntity.IsDeleted() && !GetInstance().m_selectedEntity.IsStatic())
			{
				ImGuizmo::SetOrthographic(false);
				ImGuizmo::SetDrawlist();
				ImGuizmo::SetRect(ImGui::GetWindowPos().x, ImGui::GetWindowPos().y, viewPortSize.x, viewPortSize.y);
				glm::mat4 cameraView = glm::inverse(glm::translate(GetInstance().m_sceneCameraPosition) * glm::mat4_cast(GetInstance().m_sceneCameraRotation));
				glm::mat4 cameraProjection = GetInstance().m_sceneCamera->GetProjection();
				const auto op = GetInstance().m_localPositionSelected ? ImGuizmo::OPERATION::TRANSLATE : GetInstance().m_localRotationSelected ? ImGuizmo::OPERATION::ROTATE : ImGuizmo::OPERATION::SCALE;

				auto transform = GetInstance().m_selectedEntity.GetComponentData<Transform>();
				GlobalTransform parentGlobalTransform;
				Entity parentEntity = EntityManager::GetParent(GetInstance().m_selectedEntity);
				if (!parentEntity.IsNull())
				{
					parentGlobalTransform = EntityManager::GetParent(GetInstance().m_selectedEntity).GetComponentData<GlobalTransform>();
				}
				auto globalTransform = GetInstance().m_selectedEntity.GetComponentData<GlobalTransform>();
				ImGuizmo::Manipulate(glm::value_ptr(cameraView), glm::value_ptr(cameraProjection), op, ImGuizmo::LOCAL, glm::value_ptr(globalTransform.m_value));
				if (ImGuizmo::IsUsing()) {
					transform.m_value = glm::inverse(parentGlobalTransform.m_value) * globalTransform.m_value;
					GetInstance().m_selectedEntity.SetComponentData(transform);
					transform.Decompose(GetInstance().m_previouslyStoredPosition, GetInstance().m_previouslyStoredRotation, GetInstance().m_previouslyStoredScale);
					mouseSelectEntity = false;
				}
			}
			if (GetInstance().m_sceneWindowFocused && mouseSelectEntity)
			{
				if (!GetInstance().m_leftMouseButtonHold && !(mousePosition.x > 0 || mousePosition.y < 0 || mousePosition.x < -viewPortSize.x || mousePosition.y > viewPortSize.y) && InputManager::GetMouseInternal(GLFW_MOUSE_BUTTON_LEFT, WindowManager::GetWindow()))
				{
					Entity focusedEntity = MouseEntitySelection(mousePosition);
					Entity rootEntity = EntityManager::GetRoot(focusedEntity);
					if (focusedEntity.m_index == 0)
					{
						GetInstance().m_selectedEntity.m_index = 0;
					}
					else
					{
						Entity walker = focusedEntity;
						bool found = false;
						while(!walker.IsNull())
						{
							if(walker == GetInstance().m_selectedEntity)
							{
								found = true;
								break;
							}
							walker = EntityManager::GetParent(walker);
						}
						if(found)
						{
							walker = EntityManager::GetParent(walker);
							if(walker.IsNull())
							{
								GetInstance().m_selectedEntity = focusedEntity;
							}else
							{
								GetInstance().m_selectedEntity = walker;
							}
						}else
						{
							GetInstance().m_selectedEntity = focusedEntity;
						}
					}
					/*
					else if (GetInstance().m_selectedEntity == rootEntity)
					{
						GetInstance().m_selectedEntity = focusedEntity;
					}
					else
					{
						GetInstance().m_selectedEntity = rootEntity;
					}
					*/
					GetInstance().m_leftMouseButtonHold = true;
				}
			}
			HighLightEntity(GetInstance().m_selectedEntity, glm::vec4(1.0, 0.5, 0.0, 0.8));
#pragma endregion
			if (ImGui::IsWindowFocused())
			{
				if (!GetInstance().m_sceneWindowFocused) {
					GetInstance().m_sceneWindowFocused = true;
					GetInstance().m_rightMouseButtonHold = true;
					GetInstance().m_leftMouseButtonHold = true;
				}
			}
			else
			{
				GetInstance().m_sceneWindowFocused = false;
			}
		}
		ImGui::EndChild();
		GetInstance().m_sceneCamera->SetEnabled(!(ImGui::GetCurrentWindowRead()->Hidden && !ImGui::GetCurrentWindowRead()->Collapsed));
	}
	ImGui::End();
	ImGui::PopStyleVar();
	GetInstance().m_sceneCameraResolutionX = viewPortSize.x;
	GetInstance().m_sceneCameraResolutionY = viewPortSize.y;
	if (InputManager::GetKeyInternal(GLFW_KEY_DELETE, WindowManager::GetWindow())) {
		if (!GetInstance().m_selectedEntity.IsNull() && !GetInstance().m_selectedEntity.IsDeleted())
		{
			EntityManager::DeleteEntity(GetInstance().m_selectedEntity);
		}
	}
#pragma endregion
#pragma region Logs and errors
	if (GetInstance().m_enableConsole) {
		ImGui::Begin("Console");
		ImGui::Checkbox("Log", &GetInstance().m_enableConsoleLogs);
		ImGui::SameLine();
		ImGui::Checkbox("Warning", &GetInstance().m_enableConsoleWarnings);
		ImGui::SameLine();
		ImGui::Checkbox("Error", &GetInstance().m_enableConsoleErrors);
		int i = 0;
		for (auto msg = Debug::GetConsoleMessages().rbegin(); msg != Debug::GetConsoleMessages().rend(); ++msg)
		{
			if (i > 999) break;
			i++;
			switch (msg->m_type)
			{
			case ConsoleMessageType::Log:
				if (GetInstance().m_enableConsoleLogs)
				{
					ImGui::TextColored(ImVec4(0, 0, 1, 1), "%.2f: ", msg->m_time);
					ImGui::SameLine();
					ImGui::TextColored(ImVec4(1, 1, 1, 1), msg->m_value.c_str());
					ImGui::Separator();
				}
				break;
			case ConsoleMessageType::Warning:
				if (GetInstance().m_enableConsoleWarnings)
				{
					ImGui::TextColored(ImVec4(0, 0, 1, 1), "%.2f: ", msg->m_time);
					ImGui::SameLine();
					ImGui::TextColored(ImVec4(1, 1, 0, 1), msg->m_value.c_str());
					ImGui::Separator();
				}
				break;
			case ConsoleMessageType::Error:
				if (GetInstance().m_enableConsoleErrors)
				{
					ImGui::TextColored(ImVec4(0, 0, 1, 1), "%.2f: ", msg->m_time);
					ImGui::SameLine();
					ImGui::TextColored(ImVec4(1, 0, 0, 1), msg->m_value.c_str());
					ImGui::Separator();
				}
				break;
			}

		}
		ImGui::End();
	}
#pragma endregion

}



void UniEngine::EditorManager::SetSelectedEntity(Entity entity)
{
	if (entity.IsNull() || entity.IsDeleted()) return;
	GetInstance().m_selectedEntity = entity;
}

std::unique_ptr<CameraComponent>& EditorManager::GetSceneCamera()
{
	return GetInstance().m_sceneCamera;
}

bool EditorManager::Draggable(const std::string& name, std::shared_ptr<ResourceBehaviour>& target)
{
	const std::string tag = "##" + (target ? std::to_string(target->GetHashCode()) : "");
	ImGui::Button(target ? (target->m_name + tag).c_str() : "none");
	if (ImGui::BeginDragDropSource(ImGuiDragDropFlags_SourceAllowNullID))
	{
		const std::string hash = std::to_string(std::hash<std::string>{}(name));
		ImGui::SetDragDropPayload(hash.c_str(), &target, sizeof(std::shared_ptr<ResourceBehaviour>));
		if (target && target->m_icon)ImGui::Image(reinterpret_cast<ImTextureID>(target->m_icon->Texture()->Id()), ImVec2(30, 30), ImVec2(0, 1), ImVec2(1, 0));
		else ImGui::TextColored(ImVec4(0, 0, 1, 1), (name + tag).substr(6).c_str());
		ImGui::EndDragDropSource();
	}
	bool removed = false;
	if (target && ImGui::BeginPopupContextItem(tag.c_str()))
	{
		if (ImGui::BeginMenu(("Rename" + tag).c_str()))
		{
			static char newName[256];
			ImGui::InputText(("New name" + tag).c_str(), newName, 256);
			if (ImGui::Button(("Confirm" + tag).c_str())) target->m_name = std::string(newName);
			ImGui::EndMenu();
		}
		if (ImGui::Button(("Remove" + tag).c_str())) {
			target.reset();
			removed = true;
		}
		ImGui::EndPopup();
	}
	return removed;
}
