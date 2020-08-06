#pragma once
#include "pch.h"
#include "UniEngine.h"
#ifdef TREEUTILITIES_EXPORTS
#define TREEUTILITIES_API __declspec(dllexport)
#else
#define TREEUTILITIES_API __declspec(dllimport)
#endif