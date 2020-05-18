#include "UniEngine.h"

UniEngine::Engine::Engine()
{
	_Looping = false;
}

void UniEngine::Engine::GLInit()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif

	/*auto window = WindowManager::CreateWindow(1280, 720);

	glfwSetFramebufferSizeCallback(window, WindowManager::ResizeCallback);
	glfwSetCursorPosCallback(window, Input::CursorPositionCallback);
	glfwSetScrollCallback(window, Input::MouseScrollCallback);
	glfwSetKeyCallback(window, Input::KeyCallback);
	glfwSetMouseButtonCallback(window, Input::MouseButtonCallback);*/
	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		//Debug::Error("Failed to initialize GLAD");
		exit(-1);
	}

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_CULL_FACE);

}

void UniEngine::Engine::Start()
{
	GLInit();
	world = new World();

}

void UniEngine::Engine::Loop()
{
	if (_Looping) return;
	_Looping = true;
	while (_Looping)
	{
		world->Update();
	}
}

void UniEngine::Engine::End()
{
	delete world;
	glfwTerminate();
}
