#include "UniEngine.h"
#include "World.h"
#include "WindowManager.h"
#include "InputManager.h"
#include "Default.h"
UniEngine::EngineDriver::EngineDriver()
{
	_Looping = false;
}

void UniEngine::EngineDriver::GLInit()
{
	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		Debug::Error("Failed to initialize GLAD");
		exit(-1);
	}
}

void UniEngine::EngineDriver::Start()
{
	WindowManager::Init();
	WindowManager::CreateWindow(1280, 720, "Main", NULL);
	GLInit();

	

	Default::Load();
	world = new World();
	Loop();
}

void UniEngine::EngineDriver::Loop()
{
	if (_Looping) return;
	_Looping = true;
	while (_Looping)
	{

		WindowManager::Update(WindowManager::CurrentWindow(), Default::Textures::MissingTexture);
		world->Update();
		InputManager::Update();
		WindowManager::Update();
	}
}

void UniEngine::EngineDriver::End()
{
	delete world;
	glfwTerminate();
}
