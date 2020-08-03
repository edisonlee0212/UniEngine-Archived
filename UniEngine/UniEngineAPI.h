#pragma once
#include "pch.h"
#include "Core.h"
#include "Entities.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "imgui_impl_win32.h"
#include <GLFW/glfw3.h>

using namespace UniEngine::Entities;

#ifdef UNIENGINE_EXPORTS
#define UNIENGINE_API __declspec(dllexport)
#else
#define UNIENGINE_API __declspec(dllimport)
#endif