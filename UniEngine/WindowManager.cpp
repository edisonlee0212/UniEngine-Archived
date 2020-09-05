#include "pch.h"
#include "WindowManager.h"
#include "InputManager.h"
#include "RenderTarget.h"
#include "Default.h"
using namespace UniEngine;

std::vector<GLFWmonitor*> WindowManager::_Monitors;
GLFWmonitor* WindowManager::_PrimaryMonitor;
GLFWwindow* WindowManager::_Window;
unsigned WindowManager::_WindowWidth;
unsigned WindowManager::_WindowHeight;


void WindowManager::ResizeCallback(GLFWwindow* window, int width, int height) {
	_WindowWidth = width;
	_WindowHeight = height;
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

void UniEngine::WindowManager::Init(std::string name, bool fullScreen)
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

	
	// glfw window creation
	// --------------------
	const GLFWvidmode* mode = glfwGetVideoMode(_PrimaryMonitor);
	_WindowWidth = fullScreen ? mode->width : mode->width - 200;
	_WindowHeight = fullScreen ? mode->height : mode->height - 200;

	_Window = glfwCreateWindow(_WindowWidth, _WindowHeight, name.c_str(), fullScreen ? _PrimaryMonitor : nullptr, NULL);
	if(!fullScreen) glfwMaximizeWindow(_Window);
	glfwSetFramebufferSizeCallback(_Window, WindowManager::ResizeCallback);
	InputManager::SetWindow(_Window);
	if (_Window == NULL)
	{
		Debug::Error("Failed to create GLFW window");
	}
	glfwMakeContextCurrent(_Window);
}

GLFWwindow* UniEngine::WindowManager::GetWindow()
{
	return _Window;
}

GLFWmonitor* UniEngine::WindowManager::PrimaryMonitor()
{
	return _PrimaryMonitor;
}

void UniEngine::WindowManager::Start()
{
	RenderTarget::BindDefault();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}

void UniEngine::WindowManager::Update()
{
 	glfwSwapBuffers(_Window);
}

void UniEngine::WindowManager::DrawTexture(GLTexture2D* texture)
{
	RenderTarget::BindDefault();
	/* Make the window's context current */
	glViewport(0, 0, _WindowWidth, _WindowHeight);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	/* Render here */
	glDisable(GL_DEPTH_TEST);
	glDrawBuffer(GL_BACK);
	auto program = Default::GLPrograms::ScreenProgram;
	program->Bind();
	program->SetFloat("depth", 0);
	Default::GLPrograms::ScreenVAO->Bind();
	//Default::Textures::UV->Texture()->Bind(GL_TEXTURE_2D);
	texture->Bind(0);
	program->SetInt("screenTexture", 0);
	program->SetFloat2("center", glm::vec2(0));
	program->SetFloat2("size", glm::vec2(1.0));
	glDrawArrays(GL_TRIANGLES, 0, 6);
}


