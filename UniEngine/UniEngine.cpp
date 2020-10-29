#include "pch.h"
#include "UniEngine.h"

GLenum glCheckError_(const char* file, int line);
#define glCheckError() glCheckError_(__FILE__, __LINE__)

void APIENTRY glDebugOutput(GLenum source,
	GLenum type,
	unsigned int id,
	GLenum severity,
	GLsizei length,
	const char* message,
	const void* userParam);

using namespace UniEngine;
std::shared_ptr<World> Application::_World;
Entity Application::_MainCameraEntity;
bool Application::_Initialized = false;
bool Application::_Running = false;
double Application::_RealWorldTime;
float Application::_TimeStep = 0.016f;
ThreadPool Application::_ThreadPool;
#pragma region Utilities

void UniEngine::Application::SetTimeStep(float value) {
	_TimeStep = value;
	_World->SetTimeStep(value);
}
void UniEngine::Application::PreUpdate()
{
	if (_Running) {
		Debug::Error("Application already running!");
		return;
	}
	LoopStart_Internal();
}

void UniEngine::Application::Update()
{
	if (_Running) {
		Debug::Error("Application already running!");
		return;
	}
	LoopMain_Internal();
}

bool UniEngine::Application::LateUpdate()
{
	if (_Running) {
		Debug::Error("Application already running!");
		return false;
	}
	return LoopEnd_Internal();
}


void UniEngine::Application::GLInit()
{
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


}

#pragma endregion

void UniEngine::Application::Init(bool fullScreen)
{
	_Initialized = false;
	WindowManager::Init("UniEngine", fullScreen);
	InputManager::Init();
	_ThreadPool.Resize(std::thread::hardware_concurrency());
	ManagerBase::_ThreadPool = &_ThreadPool;
	GLInit();
	_World = std::make_shared<World>(0, &_ThreadPool);
	EntityManager::SetWorld(_World.get());
	ManagerBase::SetWorld(_World.get());
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
	RenderManager::Init();
	EditorManager::Init();
#pragma region Internal Systems
	//Initialization System Group
	_World->CreateSystem<TransformSystem>(SystemGroup::PreparationSystemGroup);
#pragma endregion
	_Initialized = true;
#pragma region Main Camera
	Camera::GenerateMatrices();
	EntityArchetype archetype = EntityManager::CreateEntityArchetype("Camera", Translation(), Rotation(), Scale(), LocalToWorld(), CameraLayerMask());
	_MainCameraEntity = EntityManager::CreateEntity(archetype, "Main Camera");
	Translation pos;
	pos.Value = glm::vec3(0.0f, 5.0f, 10.0f);
	EntityManager::SetComponentData<Translation>(_MainCameraEntity, pos);
	auto mainCameraComponent = std::make_unique<CameraComponent>();
	mainCameraComponent->SkyBox = Default::Textures::DefaultSkybox;
	mainCameraComponent->Value = std::make_shared<Camera>(1600, 900, 0.1f, 500.0f);
	EntityManager::SetPrivateComponent<CameraComponent>(_MainCameraEntity, std::move(mainCameraComponent));
#pragma endregion

	glfwPollEvents();
	_RealWorldTime = glfwGetTime();
	_World->SetWorldTime(_RealWorldTime);
	_World->ResetTime();
}

void UniEngine::Application::LoopStart_Internal()
{
	if (!_Initialized) {
		return;
	}
	glfwPollEvents();
	_RealWorldTime = glfwGetTime();
	_World->SetWorldTime(_RealWorldTime);
#pragma region ImGui
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
#pragma endregion	
	EditorManager::Start();
	WindowManager::Start();
	RenderManager::Start();
}

void UniEngine::Application::LoopMain_Internal()
{
	if (!_Initialized) {
		return;
	}
	_World->Update();
	EditorManager::Update();
	InputManager::Update();
}

bool UniEngine::Application::LoopEnd_Internal()
{
	
	_Initialized = !glfwWindowShouldClose(WindowManager::GetWindow());
	if (!_Initialized) {
		return false;
	}
	RenderManager::LateUpdate();
	EditorManager::LateUpdate();
	InputManager::OnGui();
	AssetManager::OnGui();
	WindowManager::OnGui();
	RenderManager::OnGui();

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
	WindowManager::Update();

	return _Initialized;
}

bool Application::IsInitialized()
{
	return _Initialized;
}

void UniEngine::Application::End()
{
	PhysicsSimulationManager::Destroy();
	EditorManager::Destroy();
	glfwTerminate();
}

void UniEngine::Application::Run()
{
	_Running = true;
	while (_Initialized) {
		LoopStart_Internal();
		LoopMain_Internal();
		_Initialized = LoopEnd_Internal();
	}
	_Running = false;
}

std::shared_ptr<World>& UniEngine::Application::GetWorld()
{
	return _World;
}

Entity UniEngine::Application::GetMainCameraEntity()
{
	return _MainCameraEntity;
}

std::unique_ptr<CameraComponent>* UniEngine::Application::GetMainCameraComponent()
{
	return _MainCameraEntity.GetPrivateComponent<CameraComponent>();
}

#pragma region OpenGL Debugging
GLenum glCheckError_(const char* file, int line)
{
	GLenum errorCode;
	while ((errorCode = glGetError()) != GL_NO_ERROR)
	{
		std::string error;
		switch (errorCode)
		{
		case GL_INVALID_ENUM:                  error = "INVALID_ENUM"; break;
		case GL_INVALID_VALUE:                 error = "INVALID_VALUE"; break;
		case GL_INVALID_OPERATION:             error = "INVALID_OPERATION"; break;
		case GL_STACK_OVERFLOW:                error = "STACK_OVERFLOW"; break;
		case GL_STACK_UNDERFLOW:               error = "STACK_UNDERFLOW"; break;
		case GL_OUT_OF_MEMORY:                 error = "OUT_OF_MEMORY"; break;
		case GL_INVALID_FRAMEBUFFER_OPERATION: error = "INVALID_FRAMEBUFFER_OPERATION"; break;
		}
		std::cout << error << " | " << file << " (" << line << ")" << std::endl;
	}
	return errorCode;
}
#define glCheckError() glCheckError_(__FILE__, __LINE__)

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