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

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glEnable(GL_DEPTH_TEST);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//glEnable(GL_CULL_FACE);
	

	
	_World = new World();
	Default::Load(_World);
}

void UniEngine::EngineDriver::Loop()
{
	if (_Looping) return;
	_Looping = true;
	while (_Looping)
	{
		glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		_World->Update();
		InputManager::Update();
		//WindowManager::Update();
		glfwSwapBuffers(WindowManager::CurrentWindow()->GLFWwindow());
		glfwPollEvents();
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

