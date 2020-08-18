#pragma once
#include "pch.h"
#include "UniEngine.h"
#ifdef ENTITYEDITOR_EXPORTS
#define ENTITYEDITOR_API __declspec(dllexport)
#else
#define ENTITYEDITOR_API __declspec(dllimport)
#endif