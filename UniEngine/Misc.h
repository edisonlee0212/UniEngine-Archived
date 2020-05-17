#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <list>
#include <vector>
#include <memory>
#include <utility>
#include <unordered_map>
#include <cstddef>
#include <omp.h>
#define OMP_THREAD_AMOUNT 8


#include <ImGUI/imgui.h>
#include <ImGUI/examples/imgui_impl_glfw.h>
#include <ImGUI/examples/imgui_impl_opengl3.h>
#include <ImGUI/examples/imgui_impl_win32.h>

#include <glad/include/glad/glad.h>

#include <glfw-3.3.2/include/GLFW/glfw3.h>

#include <stb/stb_image.h>

#include <assimp-5.0.1/include/assimp/scene.h>
#include <assimp-5.0.1/include/assimp/postprocess.h>
#include <assimp-5.0.1/include/assimp/Importer.hpp>

#include "Math.h"