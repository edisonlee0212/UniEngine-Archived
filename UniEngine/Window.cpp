#include "pch.h"
#include "UniEngineAPI.h"
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
	_ColorTexture = SetTexture2D(GL_COLOR_ATTACHMENT0, 1, GL_RGB32F);
	_ColorTexture->SetInt(GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	_ColorTexture->SetInt(GL_TEXTURE_MAG_FILTER, GL_NEAREST);
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

void UniEngine::Window::Update()
{
	glfwMakeContextCurrent(_Window);
	RenderTarget::BindDefault();
	/* Make the window's context current */
	glViewport(0, 0, _Width, _Height);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	/* Render here */
	glDisable(GL_DEPTH_TEST);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	auto program = Default::GLPrograms::ScreenProgram;
	program->Bind();
	program->SetFloat("depth", 0);
	Default::GLPrograms::ScreenVAO->Bind();
	//Default::Textures::UV->Texture()->Bind(GL_TEXTURE_2D);
	_ColorTexture->Bind(0);
	program->SetInt("screenTexture", 0);
	program->SetFloat2("center", glm::vec2(0));
	program->SetFloat2("size", glm::vec2(1.0));
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glfwSwapBuffers(_Window);

	Bind();
	glEnable(GL_DEPTH_TEST);
	//glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	glEnable(GL_CULL_FACE);
	BindDefault();
}
