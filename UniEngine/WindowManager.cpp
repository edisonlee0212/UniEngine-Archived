#include "Misc.h"
#include "WindowManager.h"
#include "InputManager.h"
using namespace UniEngine;

GLFWmonitor* WindowManager::_PrimaryMonitor;
std::vector<GLFWmonitor*> WindowManager::_Monitors;
std::vector<Window*> WindowManager::_Windows;
Window* WindowManager::_CurrentWindow;

void WindowManager::ResizeCallback(GLFWwindow* window, int width, int height) {
	for (auto i : _Windows) {
		if (i->GetGLFWWinwow() == window) i->SetSizeCallback(width, height);
	}
}

void UniEngine::WindowManager::SetMonitorCallback(GLFWmonitor* monitor, int event)
{
	if (event == GLFW_CONNECTED)
	{
		// The monitor was connected
		for (auto i : _Monitors) if (i == monitor) return;
		_Monitors.push_back(monitor);
	}
	else if (event == GLFW_DISCONNECTED)
	{
		// The monitor was disconnected
		for (auto i = 0; i < _Monitors.size(); i++) {
			if (monitor == _Monitors[i]) {
				_Monitors.erase(_Monitors.begin() + i);
			}
		}
	}
	_PrimaryMonitor = glfwGetPrimaryMonitor();
}

Window* UniEngine::WindowManager::CreateWindow(GLFWwindow* window, unsigned resolutionX, unsigned resolutionY)
{
	auto w = new Window(window, resolutionX, resolutionY);
	_CurrentWindow = w;
	_Windows.push_back(w);
	return w;
}

void UniEngine::WindowManager::Init()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif
	int size;
	auto monitors = glfwGetMonitors(&size);
	for (auto i = 0; i < size; i++) {
		_Monitors.push_back(monitors[i]);
	}
	_PrimaryMonitor = glfwGetPrimaryMonitor();
	glfwSetMonitorCallback(SetMonitorCallback);
	
}

GLFWwindow* WindowManager::CreateGLFWwindow(unsigned width, unsigned height, std::string name, GLFWmonitor* monitor) {
	// glfw window creation
	// --------------------
	auto window = glfwCreateWindow(width, height, name.c_str(), monitor, NULL);
	glfwSetFramebufferSizeCallback(window, WindowManager::ResizeCallback);
	glfwSetCursorPosCallback(window, InputManager::CursorPositionCallback);
	glfwSetScrollCallback(window, InputManager::MouseScrollCallback);
	glfwSetKeyCallback(window, InputManager::KeyCallback);
	glfwSetMouseButtonCallback(window, InputManager::MouseButtonCallback);
	if (window == NULL)
	{
		Debug::Error("Failed to create GLFW window");
		return nullptr;
	}
	glfwMakeContextCurrent(window);
	
	return window;
}



std::vector<Window*>* UniEngine::WindowManager::Windows()
{
	return &_Windows;
}

Window* UniEngine::WindowManager::CurrentWindow()
{
	return _CurrentWindow;
}

GLFWmonitor* UniEngine::WindowManager::PrimaryMonitor()
{
	return _PrimaryMonitor;
}

void UniEngine::WindowManager::Update()
{
	for (auto i : _Windows) {
		i->Update();
	}
}

void UniEngine::WindowManager::Update(Window* window, Texture2D* texture)
{
	window->Update(texture);
}


