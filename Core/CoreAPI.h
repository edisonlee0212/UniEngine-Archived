#pragma once
#include "pch.h"
#ifdef CORE_EXPORTS
#define CORE_API __declspec(dllexport)
#else
#define CORE_API __declspec(dllimport)
#endif