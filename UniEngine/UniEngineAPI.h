#pragma once
#include "Core.h"
#include "Entities.h"

using namespace UniEngine::Entities;

#ifdef UNIENGINE_EXPORTS
#define UNIENGINE_API __declspec(dllexport)
#else
#define UNIENGINE_API __declspec(dllimport)
#endif