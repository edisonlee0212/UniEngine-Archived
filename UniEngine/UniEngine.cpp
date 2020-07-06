#include "pch.h"
#include "UniEngine.h"
#include "RenderSystem.h"
#include "TransformSystem.h"
#include "PhysicsSystem.h"
#include "ParentSystem.h"
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

UniEngine::Engine::Engine()
{
	_Loopable = false;
	WindowManager::Init();
	InputManager::Init();
}

void UniEngine::Engine::GLInit()
{
	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		Debug::Error("Failed to initialize GLAD");
		exit(-1);
	}
	// enable OpenGL debug context if context allows for debug context
	/*
	int flags; glGetIntegerv(GL_CONTEXT_FLAGS, &flags);
	if (flags & GL_CONTEXT_FLAG_DEBUG_BIT)
	{
		glEnable(GL_DEBUG_OUTPUT);
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS); // makes sure errors are displayed synchronously
		glDebugMessageCallback(glDebugOutput, nullptr);
		glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
	}*/
}

void UniEngine::Engine::Start(GLFWwindow* targetWindow, unsigned width, unsigned height)
{
	_TimeStep = 0.1f;
	GLInit();
	WindowManager::NewWindow(targetWindow, width, height);
	Camera::GenerateMatrices();

	
	_World = new World(0);
	EntityManager::SetWorld(_World);

	_World->Init();
	
	//Initialization System Group
	_World->CreateSystem<ParentSystem>();

	//Simulation System Group
	_World->CreateSystem<PhysicsSystem>();
	_World->CreateSystem<TransformSystem>();

	//Presentation System Group
	_World->CreateSystem<RenderSystem>();
	
	Default::Load(_World);
	LightingManager::Init();
	_Loopable = true;

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();

	ImGui_ImplGlfw_InitForOpenGL(targetWindow, true);
	ImGui_ImplOpenGL3_Init("#version 460 core");
	ImGui::StyleColorsDark();
}

bool UniEngine::Engine::LoopStart()
{
	if (!_Loopable) {
		return false;
	}
	glfwPollEvents();
	_RealWorldTime = glfwGetTime();
	_World->SetWorldTime(_RealWorldTime);
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
	ImGui::Begin("Time Info");
	float previousTimeStep = _TimeStep;
	ImGui::SliderFloat("sec/step", &_TimeStep, 0.05f, 1.0f);
	ImGui::End();

	if (previousTimeStep != _TimeStep)_World->SetTimeStep(_TimeStep);

	RenderManager::Start();
	LightingManager::Start();
	return true;
}

bool UniEngine::Engine::Loop()
{
	if (!_Loopable) {
		return false;
	}

	_World->Update();
	
	return true;
}

bool UniEngine::Engine::LoopEnd()
{
	if (!_Loopable) {
		return false;
	}
	
	InputManager::Update();
	DrawInfoWindow();
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	WindowManager::Update();
	return true;
}

void UniEngine::Engine::End()
{
	delete _World;
	glfwTerminate();
}

World* UniEngine::Engine::GetWorld()
{
	return _World;
}

void UniEngine::Engine::SetMainCamera(Entity entity)
{
	_MainCamera = entity;
	LightingManager::SetMainCamera(entity);
}

void UniEngine::Engine::DrawInfoWindow() {
	ImGui::Begin("World Info");
	ImGui::Text("%.1f FPS", ImGui::GetIO().Framerate);
	int tris = RenderManager::Triangles();
	std::string trisstr = "";
	if (tris < 999) {
		trisstr += std::to_string(tris);
	}
	else if (tris < 999999) {
		trisstr += std::to_string((int)(tris / 1000)) + "K";
	}
	else {
		trisstr += std::to_string((int)(tris / 1000000)) + "M";
	}
	trisstr += " tris";
	ImGui::Text(trisstr.c_str());

	ImGui::Text("%d drawcall", RenderManager::DrawCall());

	ImGui::End();

	ImGui::Begin("Logs");
	int size = Debug::mLogMessages.size();
	std::string logs = "";
	for (int i = size - 1; i > 0; i--) {
		if (i < size - 50) break;
		logs += *Debug::mLogMessages[i];
	}
	ImGui::Text(logs.c_str());
	ImGui::End();
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
	if (id == 131169 || id == 131185 || id == 131218 || id == 131204) return; // ignore these non-significant error codes

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