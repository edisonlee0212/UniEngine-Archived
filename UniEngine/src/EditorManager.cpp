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
float EditorManager::_SceneCameraYawAngle = -90;
float EditorManager::_SceneCameraPitchAngle = 0;
bool EditorManager::_Enabled = false;
EntityArchetype EditorManager::_BasicEntityArchetype;
std::map<size_t, std::function<void(ComponentBase* data, bool isRoot)>> EditorManager::_ComponentDataInspectorMap;
std::vector<std::pair<size_t, std::function<void(Entity owner)>>> EditorManager::_PrivateComponentMenuList;
std::vector<std::pair<size_t, std::function<void(Entity owner)>>> EditorManager::_ComponentDataMenuList;
unsigned int EditorManager::_ConfigFlags = 0;
int EditorManager::_SelectedHierarchyDisplayMode = 1;
Entity EditorManager::_SelectedEntity;
bool EditorManager::_EnableConsole = true;
Transform* EditorManager::_PreviouslyStoredTransform;
GlobalTransform* EditorManager::_PreviouslyStoredGlobalTransform;
glm::vec3 EditorManager::_PreviouslyStoredPosition;
glm::vec3 EditorManager::_PreviouslyStoredRotation;
glm::vec3 EditorManager::_PreviouslyStoredScale;
glm::quat EditorManager::_SceneCameraRotation = glm::quat(glm::radians(glm::vec3(-14.0f, 0.0f, 0.0f)));
glm::vec3 EditorManager::_SceneCameraPosition = glm::vec3(0, 5, 10);
std::unique_ptr<CameraComponent> EditorManager::_SceneCamera;
std::unique_ptr<GLProgram> EditorManager::_SceneCameraEntityRecorderProgram;
std::unique_ptr<GLProgram> EditorManager::_SceneCameraEntityInstancedRecorderProgram;
std::unique_ptr<RenderTarget> EditorManager::_SceneCameraEntityRecorder;
std::unique_ptr<GLTexture2D> EditorManager::_SceneCameraEntityRecorderTexture;
std::unique_ptr<GLRenderBuffer> EditorManager::_SceneCameraEntityRecorderRenderBuffer;
int EditorManager::_SceneCameraResolutionX = 1;
int EditorManager::_SceneCameraResolutionY = 1;
float EditorManager::_Velocity = 20.0f;
float EditorManager::_Sensitivity = 0.1f;
float EditorManager::_LastX = 0;
float EditorManager::_LastY = 0;
float EditorManager::_LastScrollY = 0;
bool EditorManager::_StartMouse = false;
bool EditorManager::_StartScroll = false;
bool EditorManager::_LocalPositionSelected = false;
bool EditorManager::_LocalRotationSelected = false;
bool EditorManager::_LocalScaleSelected = false;
bool EditorManager::_EnableConsoleLogs = true;
bool EditorManager::_EnableConsoleErrors = true;
bool EditorManager::_EnableConsoleWarnings = false;
bool EditorManager::_LeftMouseButtonHold = false;
bool EditorManager::_RightMouseButtonHold = false;
bool EditorManager::_SceneWindowFocused = false;
std::unique_ptr<GLProgram> EditorManager::_SceneHighlightPrePassProgram;
std::unique_ptr<GLProgram> EditorManager::_SceneHighlightProgram;
std::unique_ptr<GLProgram> EditorManager::_SceneHighlightPrePassInstancedProgram;
std::unique_ptr<GLProgram> EditorManager::_SceneHighlightInstancedProgram;
inline bool UniEngine::EditorManager::DrawEntityMenu(bool enabled, Entity& entity)
{
	bool deleted = false;
	if (ImGui::BeginPopupContextItem(std::to_string(entity.Index).c_str()))
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

void UniEngine::EditorManager::DrawEntityNode(Entity& entity)
{
	std::string title = std::to_string(entity.Index) + ": ";
	title += entity.GetName();
	bool enabled = entity.Enabled();
	if (enabled) {
		ImGui::PushStyleColor(ImGuiCol_Text, ImVec4({ 1, 1, 1, 1 }));
	}

	bool opened = ImGui::TreeNodeEx(title.c_str(), ImGuiTreeNodeFlags_NoTreePushOnOpen | ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_NoAutoOpenOnLog | (_SelectedEntity == entity ? ImGuiTreeNodeFlags_Framed : ImGuiTreeNodeFlags_FramePadding));
	if (enabled) {
		ImGui::PopStyleColor();
	}
	if (ImGui::IsItemHovered() && ImGui::IsMouseClicked(0)) {
		_SelectedEntity = entity;
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

void UniEngine::EditorManager::InspectComponentData(ComponentBase* data, ComponentType type, bool isRoot)
{
	if (_ComponentDataInspectorMap.find(type.TypeID) != _ComponentDataInspectorMap.end()) {
		_ComponentDataInspectorMap.at(type.TypeID)(data, isRoot);
	}
}

Entity EditorManager::MouseEntitySelection(const glm::vec2& mousePosition)
{
	Entity retVal;
	_SceneCameraEntityRecorder->Bind();
	float entityIndex = 0;
	const glm::vec2 resolution = _SceneCameraEntityRecorder->GetResolution();
	glm::vec2 point = resolution;
	point.x += mousePosition.x;
	point.y -= mousePosition.y;
	if (point.x >= 0 && point.x < resolution.x && point.y >= 0 && point.y < resolution.y) {
		glReadPixels(point.x, point.y, 1, 1, GL_RED, GL_FLOAT, &entityIndex);
		if (entityIndex > 0)
		{
			retVal.Version = EntityManager::_EntityInfos->at(static_cast<unsigned>(entityIndex)).Version;
			retVal.Index = static_cast<unsigned>(entityIndex);
		}
	}
	return retVal;
}

void EditorManager::HighLightEntityPrePassHelper(const Entity& entity)
{
	if (!entity.IsValid() || entity.IsDeleted() || !entity.Enabled()) return;
	EntityManager::ForEachChild(entity, [](Entity child)
		{
			HighLightEntityPrePassHelper(child);
		}
	);
	if (entity.HasPrivateComponent<MeshRenderer>())
	{
		auto& mmc = entity.GetPrivateComponent<MeshRenderer>();
		if (mmc->IsEnabled() && mmc->Material != nullptr && mmc->Mesh != nullptr)
		{
			auto ltw = EntityManager::GetComponentData<GlobalTransform>(entity);
			auto* mesh = mmc->Mesh.get();
			mesh->Enable();
			mesh->VAO()->DisableAttributeArray(12);
			mesh->VAO()->DisableAttributeArray(13);
			mesh->VAO()->DisableAttributeArray(14);
			mesh->VAO()->DisableAttributeArray(15);
			_SceneHighlightPrePassProgram->SetFloat4x4("model", ltw.Value);
			glDrawElements(GL_TRIANGLES, (GLsizei)mesh->Size(), GL_UNSIGNED_INT, 0);
		}
	}
	if(entity.HasPrivateComponent<Particles>())
	{
		auto& immc = entity.GetPrivateComponent<Particles>();
		if (immc->IsEnabled() && immc->Material != nullptr && immc->Mesh != nullptr)
		{
			auto count = immc->Matrices.size();
			std::unique_ptr<GLVBO> matricesBuffer = std::make_unique<GLVBO>();
			matricesBuffer->SetData((GLsizei)count * sizeof(glm::mat4), immc->Matrices.data(), GL_STATIC_DRAW);
			auto ltw = EntityManager::GetComponentData<GlobalTransform>(entity);
			auto* mesh = immc->Mesh.get();
			mesh->Enable();
			mesh->VAO()->EnableAttributeArray(12);
			mesh->VAO()->SetAttributePointer(12, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)0);
			mesh->VAO()->EnableAttributeArray(13);
			mesh->VAO()->SetAttributePointer(13, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(sizeof(glm::vec4)));
			mesh->VAO()->EnableAttributeArray(14);
			mesh->VAO()->SetAttributePointer(14, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(2 * sizeof(glm::vec4)));
			mesh->VAO()->EnableAttributeArray(15);
			mesh->VAO()->SetAttributePointer(15, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(3 * sizeof(glm::vec4)));
			mesh->VAO()->SetAttributeDivisor(12, 1);
			mesh->VAO()->SetAttributeDivisor(13, 1);
			mesh->VAO()->SetAttributeDivisor(14, 1);
			mesh->VAO()->SetAttributeDivisor(15, 1);
			_SceneHighlightPrePassInstancedProgram->SetFloat4x4("model", ltw.Value);
			glDrawElementsInstanced(GL_TRIANGLES, (GLsizei)mesh->Size(), GL_UNSIGNED_INT, 0, (GLsizei)count);
		}
	}
}

void EditorManager::HighLightEntityHelper(const Entity& entity)
{
	if (!entity.IsValid() || entity.IsDeleted() || !entity.Enabled()) return;
	EntityManager::ForEachChild(entity, [](Entity child)
		{
			HighLightEntityHelper(child);
		}
	);
	if (entity.HasPrivateComponent<MeshRenderer>())
	{
		auto& mmc = entity.GetPrivateComponent<MeshRenderer>();
		if (mmc->IsEnabled() && mmc->Material != nullptr && mmc->Mesh != nullptr)
		{
			auto ltw = EntityManager::GetComponentData<GlobalTransform>(entity);
			auto* mesh = mmc->Mesh.get();
			mesh->Enable();
			mesh->VAO()->DisableAttributeArray(12);
			mesh->VAO()->DisableAttributeArray(13);
			mesh->VAO()->DisableAttributeArray(14);
			mesh->VAO()->DisableAttributeArray(15);
			_SceneHighlightProgram->SetFloat4x4("model", ltw.Value);
			_SceneHighlightProgram->SetFloat3("scale", ltw.GetScale());
			glDrawElements(GL_TRIANGLES, (GLsizei)mesh->Size(), GL_UNSIGNED_INT, 0);
		}
	}
	if (entity.HasPrivateComponent<Particles>())
	{
		auto& immc = entity.GetPrivateComponent<Particles>();
		if (immc->IsEnabled() && immc->Material != nullptr && immc->Mesh != nullptr)
		{
			auto count = immc->Matrices.size();
			std::unique_ptr<GLVBO> matricesBuffer = std::make_unique<GLVBO>();
			matricesBuffer->SetData((GLsizei)count * sizeof(glm::mat4), immc->Matrices.data(), GL_STATIC_DRAW);
			auto ltw = EntityManager::GetComponentData<GlobalTransform>(entity);
			auto* mesh = immc->Mesh.get();
			mesh->Enable();
			mesh->VAO()->EnableAttributeArray(12);
			mesh->VAO()->SetAttributePointer(12, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)0);
			mesh->VAO()->EnableAttributeArray(13);
			mesh->VAO()->SetAttributePointer(13, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(sizeof(glm::vec4)));
			mesh->VAO()->EnableAttributeArray(14);
			mesh->VAO()->SetAttributePointer(14, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(2 * sizeof(glm::vec4)));
			mesh->VAO()->EnableAttributeArray(15);
			mesh->VAO()->SetAttributePointer(15, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(3 * sizeof(glm::vec4)));
			mesh->VAO()->SetAttributeDivisor(12, 1);
			mesh->VAO()->SetAttributeDivisor(13, 1);
			mesh->VAO()->SetAttributeDivisor(14, 1);
			mesh->VAO()->SetAttributeDivisor(15, 1);
			_SceneHighlightInstancedProgram->SetFloat4x4("model", ltw.Value);
			glDrawElementsInstanced(GL_TRIANGLES, (GLsizei)mesh->Size(), GL_UNSIGNED_INT, 0, (GLsizei)count);
		}
	}
}

void EditorManager::HighLightEntity(const Entity& entity, const glm::vec4& color)
{
	if (!entity.IsValid() || entity.IsDeleted() || !entity.Enabled()) return;
	CameraComponent::_CameraInfoBlock.UpdateMatrices(_SceneCamera.get(),
		_SceneCameraPosition,
		_SceneCameraRotation
	);
	CameraComponent::_CameraInfoBlock.UploadMatrices(_SceneCamera.get());
	_SceneCamera->Bind();
	glEnable(GL_STENCIL_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);
	glStencilFunc(GL_ALWAYS, 1, 0xFF);
	glStencilMask(0xFF);
	_SceneHighlightPrePassProgram->Bind();
	_SceneHighlightPrePassProgram->SetFloat4("color", glm::vec4(1.0f, 0.5f, 0.0f, 0.5f));
	HighLightEntityPrePassHelper(entity);
	glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
	glStencilMask(0x00);
	_SceneHighlightProgram->Bind();
	_SceneHighlightProgram->SetFloat4("color", color);
	HighLightEntityHelper(entity);
	glStencilMask(0xFF);
	glStencilFunc(GL_ALWAYS, 0, 0xFF);
	glEnable(GL_DEPTH_TEST);
}

void UniEngine::EditorManager::Init()
{
	_Enabled = true;
	_BasicEntityArchetype = EntityManager::CreateEntityArchetype("General", GlobalTransform(), Transform());

	_SceneCameraEntityRecorderTexture = std::make_unique<GLTexture2D>(1, GL_R32F, _SceneCameraResolutionX, _SceneCameraResolutionY, false);
	_SceneCameraEntityRecorderTexture->SetInt(GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	_SceneCameraEntityRecorderTexture->SetInt(GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	_SceneCameraEntityRecorderTexture->ReSize(0, GL_R32F, GL_RED, GL_FLOAT, 0, _SceneCameraResolutionX, _SceneCameraResolutionY);
	_SceneCameraEntityRecorderRenderBuffer = std::make_unique<GLRenderBuffer>();
	_SceneCameraEntityRecorder = std::make_unique<RenderTarget>(_SceneCameraResolutionX, _SceneCameraResolutionY);
	_SceneCameraEntityRecorderRenderBuffer->AllocateStorage(GL_DEPTH24_STENCIL8, _SceneCameraResolutionX, _SceneCameraResolutionY);
	_SceneCameraEntityRecorder->SetResolution(_SceneCameraResolutionX, _SceneCameraResolutionY);
	_SceneCameraEntityRecorder->AttachRenderBuffer(_SceneCameraEntityRecorderRenderBuffer.get(), GL_DEPTH_STENCIL_ATTACHMENT);
	_SceneCameraEntityRecorder->AttachTexture(_SceneCameraEntityRecorderTexture.get(), GL_COLOR_ATTACHMENT0);


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


	_SceneCameraEntityRecorderProgram = std::make_unique<GLProgram>(
		vertShader,
		fragShader
	);
	
	vertShaderCode = std::string("#version 460 core\n")
		+ *Default::ShaderIncludes::Uniform +
		"\n" +
		FileIO::LoadFileAsString(FileIO::GetResourcePath("Shaders/Vertex/EmptyInstanced.vert"));
	vertShader = std::make_shared<GLShader>(ShaderType::Vertex);
	vertShader->Compile(vertShaderCode);
	_SceneCameraEntityInstancedRecorderProgram = std::make_unique<GLProgram>(
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

	_SceneHighlightPrePassProgram = std::make_unique<GLProgram>(
		vertShader,
		fragShader
		);

	vertShaderCode = std::string("#version 460 core\n")
		+ *Default::ShaderIncludes::Uniform +
		"\n" +
		FileIO::LoadFileAsString(FileIO::GetResourcePath("Shaders/Vertex/EmptyInstanced.vert"));
	vertShader = std::make_shared<GLShader>(ShaderType::Vertex);
	vertShader->Compile(vertShaderCode);
	_SceneHighlightPrePassInstancedProgram = std::make_unique<GLProgram>(
		vertShader,
		fragShader
		);

	
	vertShaderCode = std::string("#version 460 core\n")
		+ *Default::ShaderIncludes::Uniform +
		"\n" +
		FileIO::LoadFileAsString(FileIO::GetResourcePath("Shaders/Vertex/Highlight.vert"));

	vertShader = std::make_shared<GLShader>(ShaderType::Vertex);
	vertShader->Compile(vertShaderCode);

	_SceneHighlightProgram = std::make_unique<GLProgram>(
		vertShader,
		fragShader
		);

	vertShaderCode = std::string("#version 460 core\n")
		+ *Default::ShaderIncludes::Uniform +
		"\n" +
		FileIO::LoadFileAsString(FileIO::GetResourcePath("Shaders/Vertex/HighlightInstanced.vert"));

	vertShader = std::make_shared<GLShader>(ShaderType::Vertex);
	vertShader->Compile(vertShaderCode);

	_SceneHighlightInstancedProgram = std::make_unique<GLProgram>(
		vertShader,
		fragShader
		);
	
	RegisterComponentDataInspector<GlobalTransform>([](ComponentBase* data, bool isRoot)
		{
			std::stringstream stream;
			GlobalTransform* ltw = reinterpret_cast<GlobalTransform*>(data);
			if (ltw != _PreviouslyStoredGlobalTransform) {
				_PreviouslyStoredGlobalTransform = ltw;
				_LocalPositionSelected = true;
				_LocalRotationSelected = false;
				_LocalScaleSelected = false;
			}
			glm::vec3 er;
			glm::vec3 t;
			glm::vec3 s;
			ltw->Decompose(t, er, s);
			er = glm::degrees(er);
			ImGui::DragFloat3("##Global Position", &t.x, 1, 0, 0, "%.3f", ImGuiInputTextFlags_ReadOnly);
			ImGui::SameLine();
			if (ImGui::Selectable("Position##Global", &_LocalPositionSelected) && _LocalPositionSelected)
			{
				_LocalRotationSelected = false;
				_LocalScaleSelected = false;
			}
			ImGui::DragFloat3("##Global Rotation", &er.x, 1, 0, 0, "%.3f", ImGuiInputTextFlags_ReadOnly);
			ImGui::SameLine();
			if (ImGui::Selectable("Rotation##Global", &_LocalRotationSelected) && _LocalRotationSelected)
			{
				_LocalPositionSelected = false;
				_LocalScaleSelected = false;
			}
			ImGui::DragFloat3("##Global Scale", &s.x, 1, 0, 0, "%.3f", ImGuiInputTextFlags_ReadOnly);
			ImGui::SameLine();
			if (ImGui::Selectable("Scale##Global", &_LocalScaleSelected) && _LocalScaleSelected)
			{
				_LocalRotationSelected = false;
				_LocalPositionSelected = false;
			}
		}
	);


	RegisterComponentDataInspector<Transform>([](ComponentBase* data, bool isRoot)
		{
			std::stringstream stream;
			auto ltp = static_cast<Transform*>(static_cast<void*>(data));
			bool edited = false;
			if (ltp != _PreviouslyStoredTransform) {
				_PreviouslyStoredTransform = ltp;
				ltp->Decompose(_PreviouslyStoredPosition, _PreviouslyStoredRotation, _PreviouslyStoredScale);
				_PreviouslyStoredRotation = glm::degrees(_PreviouslyStoredRotation);
				_LocalPositionSelected = true;
				_LocalRotationSelected = false;
				_LocalScaleSelected = false;
			}
			if (ImGui::DragFloat3("##Local Position", &_PreviouslyStoredPosition.x, 0.1f)) edited = true;
			ImGui::SameLine();
			if (ImGui::Selectable("Position##Local", &_LocalPositionSelected) && _LocalPositionSelected)
			{
				_LocalRotationSelected = false;
				_LocalScaleSelected = false;
			}
			if (ImGui::DragFloat3("##Local Rotation", &_PreviouslyStoredRotation.x, 1.0f)) edited = true;
			ImGui::SameLine();
			if (ImGui::Selectable("Rotation##Local", &_LocalRotationSelected) && _LocalRotationSelected)
			{
				_LocalPositionSelected = false;
				_LocalScaleSelected = false;
			}
			if (ImGui::DragFloat3("##Local Scale", &_PreviouslyStoredScale.x, 0.01f)) edited = true;
			ImGui::SameLine();
			if (ImGui::Selectable("Scale##Local", &_LocalScaleSelected) && _LocalScaleSelected)
			{
				_LocalRotationSelected = false;
				_LocalPositionSelected = false;
			}
			if (edited)
			{
				ltp->Value = glm::translate(_PreviouslyStoredPosition) * glm::mat4_cast(glm::quat(glm::radians(_PreviouslyStoredRotation))) * glm::scale(_PreviouslyStoredScale);
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

	RegisterComponentDataMenu<GlobalTransform>([](Entity owner)
		{
			if (owner.HasComponentData<GlobalTransform>()) return;
			if (ImGui::SmallButton("GlobalTransform"))
			{
				EntityManager::AddComponentData(owner, GlobalTransform());
			}
		}
	);

	RegisterComponentDataMenu<Transform>([](Entity owner)
		{
			if (owner.HasComponentData<Transform>()) return;
			if (ImGui::SmallButton("Transform"))
			{
				EntityManager::AddComponentData(owner, Transform());
			}
		}
	);

	RegisterComponentDataMenu<PointLight>([](Entity owner)
		{
			if (owner.HasComponentData<PointLight>()) return;
			if (ImGui::SmallButton("PointLight"))
			{
				EntityManager::AddComponentData(owner, PointLight());
			}
		}
	);

	RegisterComponentDataMenu<SpotLight>([](Entity owner)
		{
			if (owner.HasComponentData<SpotLight>()) return;
			if (ImGui::SmallButton("SpotLight"))
			{
				EntityManager::AddComponentData(owner, SpotLight());
			}
		}
	);

	RegisterComponentDataMenu<DirectionalLight>([](Entity owner)
		{
			if (owner.HasComponentData<DirectionalLight>()) return;
			if (ImGui::SmallButton("DirectionalLight"))
			{
				EntityManager::AddComponentData(owner, DirectionalLight());
			}
		}
	);
	_SelectedEntity.Index = 0;
	_ConfigFlags += EntityEditorSystem_EnableEntityHierarchy;
	_ConfigFlags += EntityEditorSystem_EnableEntityInspector;
	_SceneCamera = std::make_unique<CameraComponent>();
	_SceneCamera->DrawSkyBox = false;
}

void UniEngine::EditorManager::Destroy()
{

}
static const char* HierarchyDisplayMode[]{ "Archetype", "Hierarchy" };

void EditorManager::PreUpdate()
{
#pragma region ImGui
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
	ImGuizmo::BeginFrame();
#pragma endregion
#pragma region Dock & Main Menu
	static bool opt_fullscreen_persistant = true;
	bool opt_fullscreen = opt_fullscreen_persistant;
	static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

	// We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
	// because it would be confusing to have two docking targets within each others.
	ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoDocking;
	if (opt_fullscreen)
	{
		ImGuiViewport* viewport = ImGui::GetMainViewport();
		ImGui::SetNextWindowPos(viewport->GetWorkPos());
		ImGui::SetNextWindowSize(viewport->GetWorkSize());
		ImGui::SetNextWindowViewport(viewport->ID);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
		window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
		window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
	}

	// When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background
	// and handle the pass-thru hole, so we ask Begin() to not render a background.
	if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
		window_flags |= ImGuiWindowFlags_NoBackground;

	// Important: note that we proceed even if Begin() returns false (aka window is collapsed).
	// This is because we want to keep our DockSpace() active. If a DockSpace() is inactive,
	// all active windows docked into it will lose their parent and become undocked.
	// We cannot preserve the docking relationship between an active window and an inactive docking, otherwise
	// any change of dockspace/settings would lead to windows being stuck in limbo and never being visible.

	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
	static bool openDock = true;
	ImGui::Begin("Root DockSpace", &openDock, window_flags);
	ImGui::PopStyleVar();
	if (opt_fullscreen)
		ImGui::PopStyleVar(2);
	ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
	ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
	ImGui::End();

	if (ImGui::BeginMainMenuBar()) {
		if (ImGui::Button(Application::_Playing ? "Pause" : "Play"))
		{
			Application::_Playing = !Application::_Playing;
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
			ImGui::Checkbox("Console", &_EnableConsole);
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

#pragma endregion
	const auto resolution = _SceneCamera->_GBuffer->GetResolution();
	if (_SceneCameraResolutionX != 0 && _SceneCameraResolutionY != 0 && (resolution.x != _SceneCameraResolutionX || resolution.y != _SceneCameraResolutionY)) {
		_SceneCamera->ResizeResolution(_SceneCameraResolutionX, _SceneCameraResolutionY);
		_SceneCameraEntityRecorderTexture->ReSize(0, GL_R32F, GL_RED, GL_FLOAT, 0, _SceneCameraResolutionX, _SceneCameraResolutionY);
		_SceneCameraEntityRecorderRenderBuffer->AllocateStorage(GL_DEPTH24_STENCIL8, _SceneCameraResolutionX, _SceneCameraResolutionY);
		_SceneCameraEntityRecorder->SetResolution(_SceneCameraResolutionX, _SceneCameraResolutionY);
	}
	_SceneCamera->Clear();
	_SceneCameraEntityRecorder->Clear();
}


void UniEngine::EditorManager::Update()
{

}

Entity EditorManager::GetSelectedEntity()
{
	return _SelectedEntity;
}

void EditorManager:: LateUpdate()
{
	if (_LeftMouseButtonHold && !InputManager::GetMouseInternal(GLFW_MOUSE_BUTTON_LEFT, WindowManager::GetWindow()))
	{
		_LeftMouseButtonHold = false;
	}
	if (_RightMouseButtonHold && !InputManager::GetMouseInternal(GLFW_MOUSE_BUTTON_RIGHT, WindowManager::GetWindow()))
	{
		_RightMouseButtonHold = false;
		_StartMouse = false;
	}
#pragma region Entity Explorer
	if (_ConfigFlags & EntityEditorSystem_EnableEntityHierarchy) {
		ImGui::Begin("Entity Explorer");
		if (ImGui::BeginPopupContextWindow("DataComponentInspectorPopup"))
		{
			if (ImGui::Button("Create new entity"))
			{
				auto newEntity = EntityManager::CreateEntity(_BasicEntityArchetype);
				newEntity.SetComponentData(Transform());
				newEntity.SetComponentData(GlobalTransform());
			}
			ImGui::EndPopup();
		}
		ImGui::Combo("Display mode", &_SelectedHierarchyDisplayMode, HierarchyDisplayMode, IM_ARRAYSIZE(HierarchyDisplayMode));
		if (_SelectedHierarchyDisplayMode == 0) {
			EntityManager::UnsafeForEachEntityStorage([](int i, EntityComponentStorage storage) {
				ImGui::Separator();

				std::string title = std::to_string(i) + ". " + storage.ArchetypeInfo->Name;
				if (ImGui::CollapsingHeader(title.c_str())) {
					ImGui::PushStyleColor(ImGuiCol_HeaderActive, ImVec4(0.2, 0.3, 0.2, 1.0));
					ImGui::PushStyleColor(ImGuiCol_HeaderHovered, ImVec4(0.2, 0.2, 0.2, 1.0));
					ImGui::PushStyleColor(ImGuiCol_Header, ImVec4(0.2, 0.2, 0.3, 1.0));
					for (int j = 0; j < storage.ArchetypeInfo->EntityAliveCount; j++) {
						Entity entity = storage.ChunkArray->Entities.at(j);
						std::string title = std::to_string(entity.Index) + ": ";
						title += entity.GetName();
						bool enabled = entity.Enabled();
						if (enabled) {
							ImGui::PushStyleColor(ImGuiCol_Text, ImVec4({ 1, 1, 1, 1 }));
						}
						ImGui::TreeNodeEx(title.c_str(), ImGuiTreeNodeFlags_NoTreePushOnOpen | ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoAutoOpenOnLog | (_SelectedEntity == entity ? ImGuiTreeNodeFlags_Framed : ImGuiTreeNodeFlags_FramePadding));
						if (enabled) {
							ImGui::PopStyleColor();
						}
						DrawEntityMenu(enabled, entity);
						if (ImGui::IsItemHovered() && ImGui::IsMouseClicked(0)) {
							_SelectedEntity = entity;
						}
					}
					ImGui::PopStyleColor();
					ImGui::PopStyleColor();
					ImGui::PopStyleColor();
				}
				});
		}
		else if (_SelectedHierarchyDisplayMode == 1) {
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
	if (_ConfigFlags & EntityEditorSystem_EnableEntityInspector) {
		ImGui::Begin("Entity Inspector");
		if (!_SelectedEntity.IsNull() && !_SelectedEntity.IsDeleted()) {
			std::string title = std::to_string(_SelectedEntity.Index) + ": ";
			title += _SelectedEntity.GetName();
			bool enabled = _SelectedEntity.Enabled();
			ImGui::Checkbox(title.c_str(), &enabled);
			if (_SelectedEntity.Enabled() != enabled)
			{
				_SelectedEntity.SetEnabled(enabled);
			}
			bool deleted = DrawEntityMenu(_SelectedEntity.Enabled(), _SelectedEntity);
			ImGui::Separator();
			if (!deleted) {
				if (ImGui::CollapsingHeader("Data components", ImGuiTreeNodeFlags_DefaultOpen)) {
					if (ImGui::BeginPopupContextItem("DataComponentInspectorPopup"))
					{
						ImGui::Text("Add data component: ");
						ImGui::Separator();
						for (auto& i : _ComponentDataMenuList)
						{
							i.second(_SelectedEntity);
						}
						ImGui::Separator();
						ImGui::EndPopup();
					}
					bool skip = false;
					int i = 0;
					EntityManager::UnsafeForEachComponent(_SelectedEntity, [&skip, &i](ComponentType type, void* data)
						{
							if (skip) return;
							std::string info = type.Name.substr(7);
							info += " Size: " + std::to_string(type.Size);
							ImGui::Text(info.c_str());
							ImGui::PushID(i);
							if (ImGui::BeginPopupContextItem(("DataComponentDeletePopup" + std::to_string(i)).c_str()))
							{
								if (ImGui::Button("Remove"))
								{
									skip = true;
									EntityManager::RemoveComponentData(_SelectedEntity, type.TypeID);
								}
								ImGui::EndPopup();
							}
							ImGui::PopID();
							InspectComponentData(static_cast<ComponentBase*>(data), type, EntityManager::GetParent(_SelectedEntity).IsNull());
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
						for (auto& i : _PrivateComponentMenuList)
						{
							i.second(_SelectedEntity);
						}
						ImGui::Separator();
						ImGui::EndPopup();
					}

					int i = 0;
					bool skip = false;
					EntityManager::ForEachPrivateComponent(_SelectedEntity, [&i, &skip](PrivateComponentElement& data)
						{
							if (skip) return;
							ImGui::Checkbox(data.Name.substr(6).c_str(), &data.PrivateComponentData->_Enabled);
							ImGui::PushID(i);
							if (ImGui::BeginPopupContextItem(("PrivateComponentDeletePopup" + std::to_string(i)).c_str()))
							{
								if (ImGui::Button("Remove"))
								{
									skip = true;
									EntityManager::RemovePrivateComponent(_SelectedEntity, data.TypeID);
								}
								ImGui::EndPopup();
							}
							ImGui::PopID();
							if (!skip) {
								if (ImGui::TreeNodeEx(("Component Settings##" + std::to_string(i)).c_str(), ImGuiTreeNodeFlags_DefaultOpen)) {
									data.PrivateComponentData->OnGui();
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
			_SelectedEntity.Index = 0;
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
			ImGui::Image((ImTextureID)_SceneCamera->GetTexture()->Texture()->ID(), viewPortSize, ImVec2(0, 1), ImVec2(1, 0));
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
					meshRenderer->Mesh = payload_n;
					meshRenderer->Material = std::make_shared<Material>();
					meshRenderer->Material->SetTexture(Default::Textures::StandardTexture);
					meshRenderer->Material->SetProgram(Default::GLPrograms::StandardProgram);
					Entity entity = EntityManager::CreateEntity("Mesh");
					entity.SetComponentData(ltw);
					entity.SetPrivateComponent(std::move(meshRenderer));
				}
				ImGui::EndDragDropTarget();
			}
			glm::vec2 mousePosition = glm::vec2(FLT_MAX, FLT_MIN);
			if (_SceneWindowFocused)
			{
				bool valid = InputManager::GetMousePositionInternal(ImGui::GetCurrentWindowRead(), mousePosition);
				float xOffset = 0;
				float yOffset = 0;
				if (valid) {
					if (!_StartMouse) {
						_LastX = mousePosition.x;
						_LastY = mousePosition.y;
						_StartMouse = true;
					}
					xOffset = mousePosition.x - _LastX;
					yOffset = -mousePosition.y + _LastY;
					_LastX = mousePosition.x;
					_LastY = mousePosition.y;
#pragma region Scene Camera Controller
					if (!_RightMouseButtonHold && !(mousePosition.x > 0 || mousePosition.y < 0 || mousePosition.x < -viewPortSize.x || mousePosition.y > viewPortSize.y) &&
						InputManager::GetMouseInternal(GLFW_MOUSE_BUTTON_RIGHT, WindowManager::GetWindow())) {
						_RightMouseButtonHold = true;
					}
					if(_RightMouseButtonHold)
					{
						glm::vec3 front = _SceneCameraRotation * glm::vec3(0, 0, -1);
						glm::vec3 right = _SceneCameraRotation * glm::vec3(1, 0, 0);
						if (InputManager::GetKeyInternal(GLFW_KEY_W, WindowManager::GetWindow())) {
							_SceneCameraPosition += glm::vec3(front.x, 0.0f, front.z) * (float)Application::GetCurrentWorld()->Time()->DeltaTime() * _Velocity;
						}
						if (InputManager::GetKeyInternal(GLFW_KEY_S, WindowManager::GetWindow())) {
							_SceneCameraPosition -= glm::vec3(front.x, 0.0f, front.z) * (float)Application::GetCurrentWorld()->Time()->DeltaTime() * _Velocity;
						}
						if (InputManager::GetKeyInternal(GLFW_KEY_A, WindowManager::GetWindow())) {
							_SceneCameraPosition -= glm::vec3(right.x, 0.0f, right.z) * (float)Application::GetCurrentWorld()->Time()->DeltaTime() * _Velocity;
						}
						if (InputManager::GetKeyInternal(GLFW_KEY_D, WindowManager::GetWindow())) {
							_SceneCameraPosition += glm::vec3(right.x, 0.0f, right.z) * (float)Application::GetCurrentWorld()->Time()->DeltaTime() * _Velocity;
						}
						if (InputManager::GetKeyInternal(GLFW_KEY_LEFT_SHIFT, WindowManager::GetWindow())) {
							_SceneCameraPosition.y += _Velocity * (float)Application::GetCurrentWorld()->Time()->DeltaTime();
						}
						if (InputManager::GetKeyInternal(GLFW_KEY_LEFT_CONTROL, WindowManager::GetWindow())) {
							_SceneCameraPosition.y -= _Velocity * (float)Application::GetCurrentWorld()->Time()->DeltaTime();
						}
						if (xOffset != 0 || yOffset != 0) {
							_SceneCameraYawAngle += xOffset * _Sensitivity;
							_SceneCameraPitchAngle += yOffset * _Sensitivity;
							if (_SceneCameraPitchAngle > 89.0f)
								_SceneCameraPitchAngle = 89.0f;
							if (_SceneCameraPitchAngle < -89.0f)
								_SceneCameraPitchAngle = -89.0f;

							_SceneCameraRotation = CameraComponent::ProcessMouseMovement(_SceneCameraYawAngle, _SceneCameraPitchAngle, false);
						}
					}
#pragma endregion
				}
			}
#pragma region Gizmos and Entity Selection
			bool mouseSelectEntity = true;
			if (!_SelectedEntity.IsNull() && !_SelectedEntity.IsDeleted())
			{
				ImGuizmo::SetOrthographic(false);
				ImGuizmo::SetDrawlist();
				ImGuizmo::SetRect(ImGui::GetWindowPos().x, ImGui::GetWindowPos().y, viewPortSize.x, viewPortSize.y);
				glm::mat4 cameraView = glm::inverse(glm::translate(_SceneCameraPosition) * glm::mat4_cast(_SceneCameraRotation));
				glm::mat4 cameraProjection = _SceneCamera->GetProjection();
				const auto op = _LocalPositionSelected ? ImGuizmo::OPERATION::TRANSLATE : _LocalRotationSelected ? ImGuizmo::OPERATION::ROTATE : ImGuizmo::OPERATION::SCALE;
				if (_SelectedEntity.HasComponentData<Transform>()) {
					auto transform = _SelectedEntity.GetComponentData<Transform>();
					GlobalTransform parentGlobalTransform;
					Entity parentEntity = EntityManager::GetParent(_SelectedEntity);
					if (!parentEntity.IsNull())
					{
						parentGlobalTransform = EntityManager::GetParent(_SelectedEntity).GetComponentData<GlobalTransform>();
					}
					auto globalTransform = _SelectedEntity.GetComponentData<GlobalTransform>();
					ImGuizmo::Manipulate(glm::value_ptr(cameraView), glm::value_ptr(cameraProjection), op, ImGuizmo::LOCAL, glm::value_ptr(globalTransform.Value));
					if (ImGuizmo::IsUsing()) {
						transform.Value = glm::inverse(parentGlobalTransform.Value) * globalTransform.Value;
						_SelectedEntity.SetComponentData(transform);
						transform.Decompose(_PreviouslyStoredPosition, _PreviouslyStoredRotation, _PreviouslyStoredScale);
						mouseSelectEntity = false;
					}
				}
				else if (_SelectedEntity.HasComponentData<GlobalTransform>())
				{
					auto globalTransform = _SelectedEntity.GetComponentData<GlobalTransform>();
					ImGuizmo::Manipulate(glm::value_ptr(cameraView), glm::value_ptr(cameraProjection), op, ImGuizmo::LOCAL, glm::value_ptr(globalTransform.Value));
					if (ImGuizmo::IsUsing()) {
						_SelectedEntity.SetComponentData(globalTransform);
						mouseSelectEntity = false;
					}
				}
			}
			if (_SceneWindowFocused && mouseSelectEntity)
			{
				if (!_LeftMouseButtonHold && !(mousePosition.x > 0 || mousePosition.y < 0 || mousePosition.x < -viewPortSize.x || mousePosition.y > viewPortSize.y) && InputManager::GetMouseInternal(GLFW_MOUSE_BUTTON_LEFT, WindowManager::GetWindow()))
				{
					Entity focusedEntity = MouseEntitySelection(mousePosition);
					Entity rootEntity = EntityManager::GetRoot(focusedEntity);
					if (focusedEntity.Index == 0)
					{
						_SelectedEntity.Index = 0;
					}
					else if (_SelectedEntity == rootEntity)
					{
						_SelectedEntity = focusedEntity;
					}
					else
					{
						_SelectedEntity = rootEntity;
					}
					_LeftMouseButtonHold = true;
				}
			}
			HighLightEntity(_SelectedEntity, glm::vec4(1.0, 0.5, 0.0, 0.8));
#pragma endregion
			if(ImGui::IsWindowFocused())
			{
				if (!_SceneWindowFocused) {
					_SceneWindowFocused = true;
					_RightMouseButtonHold = true;
					_LeftMouseButtonHold = true;
				}
			}else
			{
				_SceneWindowFocused = false;
			}
		}
		ImGui::EndChild();
		_SceneCamera->SetEnabled(!(ImGui::GetCurrentWindowRead()->Hidden && !ImGui::GetCurrentWindowRead()->Collapsed));
	}
	ImGui::End();
	ImGui::PopStyleVar();
	_SceneCameraResolutionX = viewPortSize.x;
	_SceneCameraResolutionY = viewPortSize.y;
	if (InputManager::GetKeyInternal(GLFW_KEY_DELETE, WindowManager::GetWindow())) {
		if (!_SelectedEntity.IsNull() && !_SelectedEntity.IsDeleted())
		{
			EntityManager::DeleteEntity(_SelectedEntity);
		}
	}
#pragma endregion
#pragma region Logs and errors
	if (_EnableConsole) {
		ImGui::Begin("Console");
		ImGui::Checkbox("Log", &_EnableConsoleLogs);
		ImGui::SameLine();
		ImGui::Checkbox("Warning", &_EnableConsoleWarnings);
		ImGui::SameLine();
		ImGui::Checkbox("Error", &_EnableConsoleErrors);
		int i = 0;
		for (auto msg = Debug::GetConsoleMessages().rbegin(); msg != Debug::GetConsoleMessages().rend(); ++msg)
		{
			if (i > 999) break;
			i++;
			switch (msg->Type)
			{
			case ConsoleMessageType::Log:
				if (_EnableConsoleLogs)
				{
					ImGui::TextColored(ImVec4(0, 0, 1, 1), "%.2f: ", msg->Time);
					ImGui::SameLine();
					ImGui::TextColored(ImVec4(1, 1, 1, 1), msg->Value.c_str());
					ImGui::Separator();
				}
				break;
			case ConsoleMessageType::Warning:
				if (_EnableConsoleWarnings)
				{
					ImGui::TextColored(ImVec4(0, 0, 1, 1), "%.2f: ", msg->Time);
					ImGui::SameLine();
					ImGui::TextColored(ImVec4(1, 1, 0, 1), msg->Value.c_str());
					ImGui::Separator();
				}
				break;
			case ConsoleMessageType::Error:
				if (_EnableConsoleErrors)
				{
					ImGui::TextColored(ImVec4(0, 0, 1, 1), "%.2f: ", msg->Time);
					ImGui::SameLine();
					ImGui::TextColored(ImVec4(1, 0, 0, 1), msg->Value.c_str());
					ImGui::Separator();
				}
				break;
			}

		}
		ImGui::End();
	}
#pragma endregion
#pragma region ImGui
	RenderTarget::BindDefault();
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	// Update and Render additional Platform Windows
	// (Platform functions may change the current OpenGL context, so we save/restore it to make it easier to paste this code elsewhere.
	//  For this specific demo app we could also call glfwMakeContextCurrent(window) directly)
	if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{
		GLFWwindow* backup_current_context = glfwGetCurrentContext();
		ImGui::UpdatePlatformWindows();
		ImGui::RenderPlatformWindowsDefault();
		glfwMakeContextCurrent(backup_current_context);
	}
#pragma endregion
}



void UniEngine::EditorManager::SetSelectedEntity(Entity entity)
{
	if (entity.IsNull() || entity.IsDeleted()) return;
	_SelectedEntity = entity;
}

bool EditorManager::Draggable(const std::string& name, std::shared_ptr<ResourceBehaviour>& target)
{
	const std::string tag = "##" + (target ? std::to_string(target->GetHashCode()) : "");
	ImGui::Button(target ? (target->Name + tag).c_str() : "none");
	if (ImGui::BeginDragDropSource(ImGuiDragDropFlags_SourceAllowNullID))
	{
		const std::string hash = std::to_string(std::hash<std::string>{}(name));
		ImGui::SetDragDropPayload(hash.c_str(), &target, sizeof(std::shared_ptr<ResourceBehaviour>));
		if (target && target->_Icon)ImGui::Image(reinterpret_cast<ImTextureID>(target->_Icon->Texture()->ID()), ImVec2(30, 30), ImVec2(0, 1), ImVec2(1, 0));
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
			if (ImGui::Button(("Confirm" + tag).c_str())) target->Name = std::string(newName);
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
