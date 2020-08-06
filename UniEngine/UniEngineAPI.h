#pragma once
#include "pch.h"
#include "Entities.h"
#include <GLFW/glfw3.h>

#ifdef UNIENGINE_EXPORTS
#define UNIENGINE_API __declspec(dllexport)
#else
#define UNIENGINE_API __declspec(dllimport)
#endif