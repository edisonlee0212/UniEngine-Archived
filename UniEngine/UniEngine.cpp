#include "UniEngine.h"
#include "World.h"
#include "WindowManager.h"
#include "InputManager.h"
#include "Default.h"

using namespace UniEngine;

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

	

	
	_World = new World();
	Default::Load(_World);
}

void UniEngine::EngineDriver::Loop()
{
	if (_Looping) return;
	_Looping = true;
	while (_Looping)
	{
		_World->Update();
		InputManager::Update();
		WindowManager::Update();
	}
}

void UniEngine::EngineDriver::End()
{
	delete _World;
	glfwTerminate();
}

World* UniEngine::EngineDriver::GetWorld()
{
	return _World;
}

