#pragma once
#ifdef ENTITIES_EXPORTS
#define ENTITIES_API __declspec(dllexport)
#else
#define ENTITIES_API __declspec(dllimport)
#endif
#include "Core.h"