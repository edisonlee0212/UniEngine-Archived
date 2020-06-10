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
#define OMP_THREAD_AMOUNT 8


#include <ImGUI/imgui.h>
#include <ImGUI/examples/imgui_impl_glfw.h>
#include <ImGUI/examples/imgui_impl_opengl3.h>
#include <ImGUI/examples/imgui_impl_win32.h>

#include <glad/glad.h>

#include <GLFW/glfw3.h>

#include <stb/stb_image.h>

#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <assimp/Importer.hpp>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>