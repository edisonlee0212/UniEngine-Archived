#include "pch.h"

#include "Debug.h"
using namespace UniEngine;
std::vector<std::string*> Debug::mErrorMessages;
std::vector<std::string*> Debug::mLogMessages;

#include "GLBuffer.h"
GLuint GLVAO::_CurrentBinding = 0;

#include "GLTexture.h"
GLuint GLTexture::_CurrentBinding = 0;

#include "Memory.h"

size_t UniEngine::Memory::_TotalSize;

#include "ManagerBase.h"
World* ManagerBase::_World;
EntityCollection* ManagerBase::_EntityCollection;


#include "InputManager.h"
double InputManager::_CursorX;
double InputManager::_CursorY;
double InputManager::_CursorScrollX;
double InputManager::_CursorScrollY;
bool InputManager::_CursorMoved;
bool InputManager::_CursorScrolled;
bool InputManager::_CursorMovedChecked;
bool InputManager::_CursorScrolledChecked;
bool InputManager::_KeyPressed[349];
bool InputManager::_KeyDown[349];
bool InputManager::_KeyUp[349];
bool InputManager::_KeyDownChecked[349];
bool InputManager::_KeyUpChecked[349];
bool InputManager::_MousePressed[8];
bool InputManager::_MouseDown[8];
bool InputManager::_MouseUp[8];
bool InputManager::_MouseDownChecked[8];
bool InputManager::_MouseUpChecked[8];

#include "WindowManager.h"
using namespace UniEngine;

GLFWmonitor* WindowManager::_PrimaryMonitor;
std::vector<GLFWmonitor*> WindowManager::_Monitors;
std::vector<Window*> WindowManager::_Windows;
Window* WindowManager::_CurrentWindow;

#include "Camera.h"
unsigned Camera::_CameraInfoBufferID;

#include "LightingManager.h"
GLUBO* LightingManager::_DirectionalLightBlock;
GLUBO* LightingManager::_PointLightBlock;
GLUBO* LightingManager::_SpotLightBlock;

DirectionalLight LightingManager::_DirectionalLights[Default::ShaderIncludes::MaxDirectionalLightAmount];
PointLight LightingManager::_PointLights[Default::ShaderIncludes::MaxPointLightAmount];
SpotLight LightingManager::_SpotLights[Default::ShaderIncludes::MaxSpotLightAmount];

bool LightingManager::_UpdateDirectionalLightBlock;
bool LightingManager::_UpdatePointLightBlock;
bool LightingManager::_UpdateSpotLightBlock;

DirectionalLightShadowMap* LightingManager::_DirectionalLightShadowMap;
PointLightShadowMap* LightingManager::_PointLightShadowMap;

GLProgram* LightingManager::_DirectionalLightProgram;
GLProgram* LightingManager::_PointLightProgram;
GLProgram* LightingManager::_DirectionalLightInstancedProgram;
GLProgram* LightingManager::_PointLightInstancedProgram;

#include "RenderManager.h"
using namespace UniEngine;
GLenum RenderManager::_TextureStartIndex = 2;
RenderTarget* RenderManager::_CurrentRenderTarget;
unsigned RenderManager::_DrawCall;
unsigned RenderManager::_Triangles;

#include "Default.h"
GLProgram* Default::GLPrograms::ScreenProgram;
GLProgram* Default::GLPrograms::StandardProgram;
GLProgram* Default::GLPrograms::StandardInstancedProgram;
GLVAO* Default::GLPrograms::ScreenVAO;
std::string* Default::ShaderIncludes::Uniform;
std::string* Default::ShaderIncludes::Lights;
std::string* Default::ShaderIncludes::Shadow;

Texture2D* Default::Textures::MissingTexture;
Texture2D* Default::Textures::UV;
Texture2D* Default::Textures::StandardTexture;

Mesh* Default::Primitives::Sphere;
Mesh* Default::Primitives::Cube;
Mesh* Default::Primitives::Quad;
Mesh* Default::Primitives::Cone;
Mesh* Default::Primitives::Cylinder;

Material* Default::Materials::StandardMaterial;
Material* Default::Materials::StandardInstancedMaterial;