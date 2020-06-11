#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <list>
#include <set>
#include <vector>
#include <memory>
#include <utility>
#include <unordered_map>
#include <cstddef>
#include <omp.h>
#include <cstdarg>

#define OMP_THREAD_AMOUNT 8


#include "glad.h"

#include <GLFW/glfw3.h>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "imgui_impl_win32.h"

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtx/transform.hpp>
#include <gtc/type_ptr.hpp>

#ifdef UNIENGINE_EXPORTS
#define UECORE_API __declspec(dllexport)
#else
#define UECORE_API __declspec(dllimport)
#endif