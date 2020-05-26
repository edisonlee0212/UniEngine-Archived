#include "Misc.h"
#include "Window.h"
#include "RenderTarget.h"
#include "Default.h"
using namespace UniEngine;

void UniEngine::Window::SetSize(unsigned width, unsigned height)
{
	_Width = width;
	_Height = height;
}

glm::vec2 UniEngine::Window::GetSize()
{
	return glm::vec2(_Width, _Height);
}

GLFWwindow* UniEngine::Window::GLFWwindow()
{
	return _Window;
}

void UniEngine::Window::Update(Texture2D* texture)
{
	RenderTarget::BindDefault();
	/* Make the window's context current */
	glfwMakeContextCurrent(_Window);
	glViewport(0, 0, _Width, _Height);
	/* Render here */
	
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glDisable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT);
	auto program = Default::Screen::ScreenProgram;
	program->Use();
	
	Default::Screen::ScreenVAO->Bind();
	texture->Texture()->Bind(GL_TEXTURE_2D);
	glDrawArrays(GL_TRIANGLES, 0, 6);
}
