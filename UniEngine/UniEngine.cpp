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

World* Application::_World = nullptr;
Entity Application::_MainCameraEntity;
CameraComponent* Application::_MainCameraComponent = nullptr;
bool Application::_Loopable = false;
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

inline void UniEngine::Application::SceneWindowHelper()
{
	ImGuiViewport* viewport = ImGui::GetMainViewport();
	ImVec2 overlayPos;
	ImVec2 work_area_size;
	bool p_open = true;
	const float DISTANCE = 10.0f;
	static int corner = 1;
	ImGuiIO& io = ImGui::GetIO();

	ImGui::Begin("Scene");
	{
		InputManager::SetFocused(ImGui::IsWindowFocused(ImGuiFocusedFlags_RootAndChildWindows));
		// Using a Child allow to fill all the space of the window.
		// It also alows customization
		ImGui::BeginChild("CameraRenderer");
		viewport = ImGui::GetWindowViewport();
		// Get the size of the child (i.e. the whole draw size of the windows).
		work_area_size = ImGui::GetWindowSize();
		overlayPos = ImGui::GetWindowPos();
		// Because I use the texture from OpenGL, I need to invert the V from the UV.
		ImGui::Image((ImTextureID)_MainCameraComponent->Value->GetTexture()->ID(), work_area_size, ImVec2(0, 1), ImVec2(1, 0));
		ImGui::EndChild();

		ImVec2 window_pos = ImVec2((corner & 1) ? (overlayPos.x + work_area_size.x - DISTANCE) : (overlayPos.x + DISTANCE), (corner & 2) ? (overlayPos.y + work_area_size.y - DISTANCE) : (overlayPos.y + DISTANCE));
		ImVec2 window_pos_pivot = ImVec2((corner & 1) ? 1.0f : 0.0f, (corner & 2) ? 1.0f : 0.0f);
		ImGui::SetNextWindowPos(window_pos, ImGuiCond_Always, window_pos_pivot);
		ImGui::SetNextWindowBgAlpha(0.35f);
		ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoNav;

		ImGui::BeginChild("Render Info", ImVec2(200, 100), false, window_flags);
		ImGui::Text("%.1f FPS", ImGui::GetIO().Framerate);
		size_t tris = RenderManager::Triangles();
		std::string trisstr = "";
		if (tris < 999) trisstr += std::to_string(tris);
		else if (tris < 999999) trisstr += std::to_string((int)(tris / 1000)) + "K";
		else trisstr += std::to_string((int)(tris / 1000000)) + "M";
		trisstr += " tris";
		ImGui::Text(trisstr.c_str());
		ImGui::Text("%d drawcall", RenderManager::DrawCall());
		ImGui::Separator();
		if (ImGui::IsMousePosValid())
			ImGui::Text("Mouse Position: (%.1f,%.1f)", io.MousePos.x, io.MousePos.y);
		else
			ImGui::Text("Mouse Position: <invalid>");

		ImGui::EndChild();
	}
	ImGui::End();

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
	_Loopable = false;
	WindowManager::Init("UniEngine", fullScreen);
	InputManager::Init();
	_ThreadPool.Resize(std::thread::hardware_concurrency());
	EntityManager::Init(&_ThreadPool);
	ManagerBase::_ThreadPool = &_ThreadPool;

	GLInit();
	_World = new World(0, &_ThreadPool);
	EntityManager::SetWorld(_World);
	_World->Init();
	_World->SetTimeStep(_TimeStep);
#pragma region Main Camera
	Camera::GenerateMatrices();
	EntityArchetype archetype = EntityManager::CreateEntityArchetype("Camera", Translation(), Rotation(), Scale(), LocalToWorld(), CameraLayerMask());
	_MainCameraEntity = EntityManager::CreateEntity(archetype);
	Translation pos;
	pos.Value = glm::vec3(0.0f, 5.0f, 10.0f);
	EntityManager::SetComponentData<Translation>(_MainCameraEntity, pos);
	_MainCameraComponent = new CameraComponent();
	_MainCameraComponent->Value = new Camera(1600, 900, 0.1f, 500.0f);;
	EntityManager::SetSharedComponent<CameraComponent>(_MainCameraEntity, _MainCameraComponent);
#pragma endregion
#pragma region Internal Systems
	//Initialization System Group
	_World->CreateSystem<TransformSystem>(SystemGroup::PreparationSystemGroup);

	//Simulation System Group
	_World->CreateSystem<PhysicsSystem>(SystemGroup::SimulationSystemGroup);


	//Presentation System Group
	_World->CreateSystem<RenderSystem>(SystemGroup::PresentationSystemGroup);

#pragma endregion
#pragma region ImGUI
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
	io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

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
	Default::Load(_World);
	LightingManager::Init();
	_Loopable = true;

}

void UniEngine::Application::LoopStart_Internal()
{
	if (!_Loopable) {
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
#pragma region Dock & Main Menu
	static bool opt_fullscreen_persistant = true;
	bool opt_fullscreen = opt_fullscreen_persistant;
	static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

	// We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
	// because it would be confusing to have two docking targets within each others.
	ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
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
	ImGui::Begin("DockSpace Demo", &openDock, window_flags);
	ImGui::PopStyleVar();

	if (opt_fullscreen)
		ImGui::PopStyleVar(2);

	// DockSpace
	ImGuiIO& io = ImGui::GetIO();
	if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
	{
		ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
		ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
	}


	if (ImGui::BeginMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			// Disabling fullscreen would allow the window to be moved to the front of other windows,
			// which we can't undo at the moment without finer window depth/z control.
			//ImGui::MenuItem("Fullscreen", NULL, &opt_fullscreen_persistant);

			if (ImGui::MenuItem("Flag: NoSplit", "", (dockspace_flags & ImGuiDockNodeFlags_NoSplit) != 0))                 dockspace_flags ^= ImGuiDockNodeFlags_NoSplit;
			if (ImGui::MenuItem("Flag: NoResize", "", (dockspace_flags & ImGuiDockNodeFlags_NoResize) != 0))                dockspace_flags ^= ImGuiDockNodeFlags_NoResize;
			if (ImGui::MenuItem("Flag: NoDockingInCentralNode", "", (dockspace_flags & ImGuiDockNodeFlags_NoDockingInCentralNode) != 0))  dockspace_flags ^= ImGuiDockNodeFlags_NoDockingInCentralNode;
			if (ImGui::MenuItem("Flag: PassthruCentralNode", "", (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode) != 0))     dockspace_flags ^= ImGuiDockNodeFlags_PassthruCentralNode;
			if (ImGui::MenuItem("Flag: AutoHideTabBar", "", (dockspace_flags & ImGuiDockNodeFlags_AutoHideTabBar) != 0))          dockspace_flags ^= ImGuiDockNodeFlags_AutoHideTabBar;
			ImGui::Separator();
			if (ImGui::MenuItem("Close DockSpace", NULL, false, &openDock != NULL))
				openDock = false;
			ImGui::EndMenu();
		}
		ImGui::EndMenuBar();
	}

	ImGui::End();
	ImVec2 viewPortSize;
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0, 0 });
	ImGui::Begin("Scene");
	{
		//viewPortSize = ImGui::GetContentRegionAvail();
		ImGui::BeginChild("CameraRenderer");
		// Get the size of the child (i.e. the whole draw size of the windows).
		viewPortSize = ImGui::GetWindowSize();
		ImGuiViewport* viewPort = ImGui::GetWindowViewport();
		InputManager::SetWindow((GLFWwindow*)viewPort->PlatformHandle);
		ImGui::EndChild();
	}
	ImGui::End();
	ImGui::PopStyleVar();
	_MainCameraComponent->Value->SetResolution(viewPortSize.x, viewPortSize.y);
#pragma endregion
	WindowManager::Start();
	RenderManager::Start();
	LightingManager::Start();
	return;
}

void UniEngine::Application::LoopMain_Internal()
{
	if (!_Loopable) {
		return;
	}
	_World->Update();

	return;
}

bool UniEngine::Application::LoopEnd_Internal()
{
	_Loopable = !glfwWindowShouldClose(WindowManager::GetWindow());
	if (!_Loopable) {
		return false;
	}
	InputManager::Update();
	SceneWindowHelper();
#pragma region Logs
	ImGui::Begin("Logs");
	size_t size = Debug::GetLogs()->size();
	std::string logs = "";
	for (int i = (int)size - 1; i >= 0; i--) {
		logs += Debug::GetLogs()->at(i)->c_str();
	}
	ImGui::Text(logs.c_str());
	ImGui::End();
#pragma endregion
#pragma region ImGui
	RenderTarget::BindDefault();
	ImGui::Render();
	int display_w, display_h;
	glfwGetFramebufferSize(WindowManager::GetWindow(), &display_w, &display_h);
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

	return _Loopable;
}

void UniEngine::Application::End()
{
	delete _World;
	glfwTerminate();
}

void UniEngine::Application::Run()
{
	_Running = true;
	while (_Loopable) {
		LoopStart_Internal();
		LoopMain_Internal();
		_Loopable = LoopEnd_Internal();
	}
	_Running = false;
}

World* UniEngine::Application::GetWorld()
{
	return _World;
}

Entity UniEngine::Application::GetMainCameraEntity()
{
	return _MainCameraEntity;
}

CameraComponent* UniEngine::Application::GetMainCameraComponent()
{
	return _MainCameraComponent;
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