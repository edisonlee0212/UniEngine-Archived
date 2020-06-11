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


#include <ImGUI/imgui.h>
#include <ImGUI/examples/imgui_impl_glfw.h>
#include <ImGUI/examples/imgui_impl_opengl3.h>
#include <ImGUI/examples/imgui_impl_win32.h>

#include <glad/glad.h>

#include <GLFW/glfw3.h>


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#ifdef CORE_EXPORTS
#define UECORE_API __declspec(dllexport)
#else
#define UECORE_API __declspec(dllimport)
#endif