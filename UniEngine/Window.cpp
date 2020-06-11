#include "pch.h"
#include "Misc.h"
#include "Window.h"
#include "RenderTarget.h"
#include "Default.h"
using namespace UniEngine;

void UniEngine::Window::SetSizeCallback(unsigned width, unsigned height)
{
	_Width = width;
	_Height = height;
}

UniEngine::Window::Window(GLFWwindow* window, unsigned width, unsigned height)
{
	_Window = window;
	_Width = width;
	_Height = height;
	_ResolutionY = height;
	_ResolutionX = width;
	_ColorTexture = SetTexture2D(GL_COLOR_ATTACHMENT0, 0, GL_RGB, 0, GL_RGB, GL_UNSIGNED_BYTE);
	_ColorTexture->SetIntParameter(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	_ColorTexture->SetIntParameter(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	_RenderBuffer = SetRenderBuffer(GL_DEPTH_STENCIL_ATTACHMENT, GL_DEPTH24_STENCIL8);
}

glm::vec2 UniEngine::Window::GetWindowSize()
{
	return glm::vec2(_Width, _Height);
}

GLFWwindow* UniEngine::Window::GetGLFWWinwow()
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
	auto program = Default::GLPrograms::ScreenProgram;
	program->Use();
	
	Default::GLPrograms::ScreenVAO->Bind();
	texture->Texture()->Bind(GL_TEXTURE_2D);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glfwSwapBuffers(_Window);
}

void UniEngine::Window::Update()
{
	glfwMakeContextCurrent(_Window);
	RenderTarget::BindDefault();
	/* Make the window's context current */
	glViewport(0, 0, _Width, _Height);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	/* Render here */
	glDisable(GL_DEPTH_TEST);
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	auto program = Default::GLPrograms::ScreenProgram;
	program->Use();

	Default::GLPrograms::ScreenVAO->Bind();
	//Default::Textures::UV->Texture()->Bind(GL_TEXTURE_2D);
	_ColorTexture->Bind(GL_TEXTURE_2D);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glfwSwapBuffers(_Window);
}
