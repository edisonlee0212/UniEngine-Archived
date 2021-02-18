#include "pch.h"
#include "Application.h"
#include "CameraComponent.h"
#include "Default.h"
#include "InputManager.h"
#include "PhysicsSimulationManager.h"
#include "WindowManager.h"
#include "TransformManager.h"
#include "RenderManager.h"
#include "EditorManager.h"
#include "ResourceManager.h"
#include "SerializationManager.h"

using namespace UniEngine;

bool Application::_Initialized = false;
bool Application::_InnerLooping = false;
bool Application::_Playing = false;
float Application::_TimeStep = 0.016f;

std::unique_ptr<World> UniEngine::Application::_World;
std::vector<std::function<void()>> Application::_ExternalPreUpdateFunctions;
std::vector<std::function<void()>> Application::_ExternalUpdateFunctions;
std::vector<std::function<void()>> Application::_ExternalLateUpdateFunctions;

#pragma region Utilities

void UniEngine::Application::SetTimeStep(float value) {
	_TimeStep = value;
	_World->SetTimeStep(value);
}

#pragma endregion
void APIENTRY glDebugOutput(GLenum source,
	GLenum type,
	unsigned int id,
	GLenum severity,
	GLsizei length,
	const char* message,
	const void* userParam);

void UniEngine::Application::Init(bool fullScreen)
{
	_Initialized = false;
	WindowManager::Init("UniEngine", fullScreen);
	InputManager::Init();
	JobManager::Resize(std::thread::hardware_concurrency());

#pragma region OpenGL
	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		Debug::Error("Failed to initialize GLAD");
		exit(-1);
	}

	GLCore::Init();

	// enable OpenGL debug context if context allows for debug context

	int flags; glGetIntegerv(GL_CONTEXT_FLAGS, &flags);
	if (flags & GL_CONTEXT_FLAG_DEBUG_BIT)
	{
		glEnable(GL_DEBUG_OUTPUT);
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS); // makes sure errors are displayed synchronously
		glDebugMessageCallback(glDebugOutput, nullptr);
		glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
	}
	SerializationManager::Init();
#pragma endregion
	_World = std::make_unique<World>(0);
	EntityManager::Attach(_World);
	_World->SetTimeStep(_TimeStep);

	PhysicsSimulationManager::Init();
#pragma region ImGUI
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
	//io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

	ImGui::StyleColorsDark();
	ImGuiStyle& style = ImGui::GetStyle();
	if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{
		style.WindowRounding = 0.0f;
		style.Colors[ImGuiCol_WindowBg].w = 1.0f;
	}
	ImGui_ImplGlfw_InitForOpenGL(WindowManager::GetWindow(), true);
	ImGui_ImplOpenGL3_Init("#version 460 core");
#pragma endregion
	Default::Load(_World.get());
	TransformManager::Init();
	RenderManager::Init();
	EditorManager::Init();
#pragma region Internal Systems
#pragma endregion
	_Initialized = true;
#pragma region Main Camera
	CameraComponent::GenerateMatrices();
	EntityArchetype archetype = EntityManager::CreateEntityArchetype("Camera", GlobalTransform(), Transform(), CameraLayerMask());
	const auto mainCameraEntity = EntityManager::CreateEntity(archetype, "Main Camera");	
	Transform cameraLtw;
	cameraLtw.SetPosition(glm::vec3(0.0f, 5.0f, 10.0f));
	cameraLtw.SetEulerRotation(glm::radians(glm::vec3(0, 0, 15)));
	EntityManager::SetComponentData(mainCameraEntity, cameraLtw);
	auto mainCameraComponent = std::make_unique<CameraComponent>();
	RenderManager::SetMainCamera(mainCameraComponent.get());
	mainCameraComponent->SkyBox = Default::Textures::DefaultSkybox;
	EntityManager::SetPrivateComponent<CameraComponent>(mainCameraEntity, std::move(mainCameraComponent));

	
#pragma endregion
	_World->ResetTime();

}

void UniEngine::Application::PreUpdateInternal()
{
	if (!_Initialized) return;
	glfwPollEvents();
	_Initialized = !glfwWindowShouldClose(WindowManager::GetWindow());
	_World->_Time->_DeltaTime = _World->_Time->_LastFrameTime - _World->_Time->_FrameStartTime;
	_World->SetFrameStartTime(glfwGetTime());
#pragma region ImGui
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
	ImGuizmo::BeginFrame();
#pragma endregion
#pragma region Dock
	static bool opt_fullscreen_persistant = true;
	bool opt_fullscreen = opt_fullscreen_persistant;
	static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

	// We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
	// because it would be confusing to have two docking targets within each others.
	ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoDocking;
	if (opt_fullscreen)
	{
		ImGuiViewport* viewport = ImGui::GetMainViewport();
		ImGui::SetNextWindowPos(viewport->WorkPos);
		ImGui::SetNextWindowSize(viewport->WorkSize);
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
#pragma endregion
	EditorManager::PreUpdate();
	WindowManager::PreUpdate();
	InputManager::PreUpdate();
	RenderManager::PreUpdate();
	
	for (const auto& i : _ExternalPreUpdateFunctions) i();
	if (_Playing) {
		_World->_Time->_FixedDeltaTime += _World->_Time->_DeltaTime;
		_World->PreUpdate();
	}
}

void UniEngine::Application::UpdateInternal()
{
	if (!_Initialized) return;
	
	EditorManager::Update();
	InputManager::Update();
	
	for (const auto& i : _ExternalUpdateFunctions) i();
	if (_Playing) {
		_World->Update();
	}
}

bool UniEngine::Application::LateUpdateInternal()
{
	if (!_Initialized) return false;
	
	InputManager::LateUpdate();
	ResourceManager::LateUpdate();
	WindowManager::LateUpdate();
	RenderManager::LateUpdate();
	TransformManager::LateUpdate();
	EditorManager::LateUpdate();
	for (const auto& i : _ExternalLateUpdateFunctions) i();

	if (_Playing) {
		_World->LateUpdate();
	}
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
	//Swap Window's framebuffer
	WindowManager::Swap();
	_World->_Time->_LastFrameTime = glfwGetTime();
	return _Initialized;
}

double Application::EngineTime()
{
	return glfwGetTime();
}

void Application::SetPlaying(bool value)
{
	_Playing = value;
}

bool Application::IsPlaying()
{
	return _Playing;
}

bool Application::IsInitialized()
{
	return _Initialized;
}

void UniEngine::Application::End()
{
	_World->Purge();
	PhysicsSimulationManager::Destroy();
	EditorManager::Destroy();
	glfwTerminate();
}

void UniEngine::Application::Run()
{
	_InnerLooping = true;
	while (_Initialized) {
		PreUpdateInternal();
		UpdateInternal();
		_Initialized = LateUpdateInternal();
	}
	_InnerLooping = false;
}

std::unique_ptr<World>& UniEngine::Application::GetCurrentWorld()
{
	return _World;
}

void Application::RegisterPreUpdateFunction(const std::function<void()>& func)
{
	_ExternalPreUpdateFunctions.push_back(func);
}

void Application::RegisterUpdateFunction(const std::function<void()>& func)
{
	_ExternalUpdateFunctions.push_back(func);
}

void Application::RegisterLateUpdateFunction(const std::function<void()>& func)
{
	_ExternalLateUpdateFunctions.push_back(func);
}



#pragma region OpenGL Debugging

void APIENTRY glDebugOutput(GLenum source,
	GLenum type,
	unsigned int id,
	GLenum severity,
	GLsizei length,
	const char* message,
	const void* userParam)
{
	if (id == 131154 || id == 131169 || id == 131185 || id == 131218 || id == 131204 || id == 131184) return; // ignore these non-significant error codes

	std::cout << "---------------" << std::endl;
	std::cout << "Debug message (" << id << "): " << message << std::endl;

	switch (source)
	{
	case GL_DEBUG_SOURCE_API:             std::cout << "Source: API"; break;
	case GL_DEBUG_SOURCE_WINDOW_SYSTEM:   std::cout << "Source: Window System"; break;
	case GL_DEBUG_SOURCE_SHADER_COMPILER: std::cout << "Source: Shader Compiler"; break;
	case GL_DEBUG_SOURCE_THIRD_PARTY:     std::cout << "Source: Third Party"; break;
	case GL_DEBUG_SOURCE_APPLICATION:     std::cout << "Source: Application"; break;
	case GL_DEBUG_SOURCE_OTHER:           std::cout << "Source: Other"; break;
	} std::cout << std::endl;

	switch (type)
	{
	case GL_DEBUG_TYPE_ERROR:               std::cout << "Type: Error"; break;
	case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: std::cout << "Type: Deprecated Behaviour"; break;
	case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:  std::cout << "Type: Undefined Behaviour"; break;
	case GL_DEBUG_TYPE_PORTABILITY:         std::cout << "Type: Portability"; break;
	case GL_DEBUG_TYPE_PERFORMANCE:         std::cout << "Type: Performance"; break;
	case GL_DEBUG_TYPE_MARKER:              std::cout << "Type: Marker"; break;
	case GL_DEBUG_TYPE_PUSH_GROUP:          std::cout << "Type: Push Group"; break;
	case GL_DEBUG_TYPE_POP_GROUP:           std::cout << "Type: Pop Group"; break;
	case GL_DEBUG_TYPE_OTHER:               std::cout << "Type: Other"; break;
	} std::cout << std::endl;

	switch (severity)
	{
	case GL_DEBUG_SEVERITY_HIGH:         std::cout << "Severity: high"; break;
	case GL_DEBUG_SEVERITY_MEDIUM:       std::cout << "Severity: medium"; break;
	case GL_DEBUG_SEVERITY_LOW:          std::cout << "Severity: low"; break;
	case GL_DEBUG_SEVERITY_NOTIFICATION: std::cout << "Severity: notification"; break;
	} std::cout << std::endl;
	std::cout << std::endl;
}

#pragma endregion