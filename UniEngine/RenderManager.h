#pragma once
#include "Core.h"
#include "UniEngineAPI.h"
#include "CameraComponent.h"
#include "MeshRenderer.h"
#include "InstancedMeshRenderer.h"
#include "RenderTarget.h"

#include "DirectionalLightComponent.h"
#include "PointLightComponent.h"
#include "SpotLightComponent.h"
#include "DirectionalLightShadowMap.h"
#include "PointLightShadowMap.h"

#include "Cubemap.h"
#include "Default.h"
#include "Texture2D.h"


namespace UniEngine {
	enum class UNIENGINE_API ShadowMode {
		PCF,
		PCSS,
		HARD
	};

	struct UNIENGINE_API ShadowSettings {
		float SplitDistance[4];
		int SoftShadowMode = (int)ShadowMode::PCSS;
		float PCSSScaleFactor = 0.0f;
		float DisplaySplit = 0.0f;
		float SeamFixRatio = 0.05f;
		float VSMMaxVariance = 0.001f;
		float LightBleedFactor = 0.5f;
		float EVSMExponent = 40.0f;
		float AmbientLight = 0.1f;
	};
	
	class UNIENGINE_API RenderManager : public ManagerBase
	{
		friend class RenderSystem;
#pragma region Render
		friend class RenderTarget;
		static size_t _Triangles;
		static size_t _DrawCall;
		static void DrawMeshInstanced(Mesh* mesh, Material* material, glm::mat4 model, glm::mat4* matrices, size_t count, bool receiveShadow);
		static void DrawMesh(Mesh* mesh, Material* material, glm::mat4 model, bool receiveShadow);

		static void DrawGizmoInstanced(Mesh* mesh, glm::vec4 color, glm::mat4 model, glm::mat4* matrices, size_t count, glm::mat4 scaleMatrix);
		static void DrawGizmo(Mesh* mesh, glm::vec4 color, glm::mat4 matrix, glm::mat4 scaleMatrix);

		static void DrawTexture2D(GLTexture2D* texture, float depth, glm::vec2 center, glm::vec2 size);
#pragma endregion
#pragma region Shadow
		static GLUBO* _DirectionalLightBlock;
		static GLUBO* _PointLightBlock;
		static GLUBO* _SpotLightBlock;

		static float _ShadowCascadeSplit[Default::ShaderIncludes::ShadowCascadeAmount];
		static size_t _DirectionalShadowMapResolution;
		static GLUBO* _ShadowCascadeInfoBlock;
		static ShadowSettings _ShadowSettings;

		static DirectionalLight _DirectionalLights[Default::ShaderIncludes::MaxDirectionalLightAmount];
		static PointLight _PointLights[Default::ShaderIncludes::MaxPointLightAmount];
		static SpotLight _SpotLights[Default::ShaderIncludes::MaxSpotLightAmount];

		static bool _EnableShadow;

		static GLProgram* _DirectionalLightProgram;
		static GLProgram* _PointLightProgram;
		static GLProgram* _DirectionalLightInstancedProgram;
		static GLProgram* _PointLightInstancedProgram;

		friend class RenderManager;
		static DirectionalLightShadowMap* _DirectionalLightShadowMap;
		static RenderTarget* _DirectionalLightShadowMapFilter;
		static PointLightShadowMap* _PointLightShadowMap;
		static GLProgram* _DirectionalLightVFilterProgram;
		static GLProgram* _DirectionalLightHFilterProgram;


		static GLTexture* _DLVSMVFilter;
		static bool _StableFit;
		static float _MaxShadowDistance;
#pragma endregion
	public:
		static void Init();
		static void Start();
#pragma region Shadow
		static void SetSplitRatio(float r1, float r2, float r3, float r4);
		static void SetDirectionalLightResolution(size_t value);
		static void SetShadowMode(ShadowMode value);
		static void SetEnableSplitDisplay(bool value);
		static void SetStableFit(bool value);
		static void SetSeamFixRatio(float value);
		static void SetMaxShadowDistance(float value);
		static void SetPCSSScaleFactor(float value);
		static void SetVSMMaxVariance(float value);
		static void SetLightBleedControlFactor(float value);
		static void SetEVSMExponent(float value);
		static void SetAmbientLight(float value);
		static void SetEnableShadow(bool value);
		static glm::vec3 ClosestPointOnLine(glm::vec3 point, glm::vec3 a, glm::vec3 b);
#pragma endregion

		
#pragma region Render
		
		static size_t Triangles();
		static size_t DrawCall();

		static void DrawTexture2D(GLTexture2D* texture, float depth, glm::vec2 center, glm::vec2 size, RenderTarget* target);
		static void DrawTexture2D(Texture2D* texture, float depth, glm::vec2 center, glm::vec2 size, RenderTarget* target);
		static void DrawTexture2D(Texture2D* texture, float depth, float centerX, float centerY, float sizeX, float sizeY, RenderTarget* target);

		static void DrawMesh(Mesh* mesh, Material* material, glm::mat4 model, RenderTarget* target, bool receiveShadow = true);
		static void DrawMeshInstanced(Mesh* mesh, Material* material, glm::mat4 model, glm::mat4* matrices, size_t count, RenderTarget* target, bool receiveShadow = true);

		static void DrawGizmoPoint(glm::vec4 color, RenderTarget* target, glm::mat4 model = glm::mat4(1.0f), float size = 1.0f);
		static void DrawGizmoPointInstanced(glm::vec4 color, glm::mat4* matrices, size_t count, RenderTarget* target, glm::mat4 model = glm::mat4(1.0f), float size = 1.0f);
		static void DrawGizmoCube(glm::vec4 color, RenderTarget* target, glm::mat4 model = glm::mat4(1.0f), float size = 1.0f);
		static void DrawGizmoCubeInstanced(glm::vec4 color, glm::mat4* matrices, size_t count, RenderTarget* target, glm::mat4 model = glm::mat4(1.0f), float size = 1.0f);
		static void DrawGizmoQuad(glm::vec4 color, RenderTarget* target, glm::mat4 model = glm::mat4(1.0f), float size = 1.0f);
		static void DrawGizmoQuadInstanced(glm::vec4 color, glm::mat4* matrices, size_t count, RenderTarget* target, glm::mat4 model = glm::mat4(1.0f), float size = 1.0f);
		static void DrawGizmoMesh(Mesh* mesh, glm::vec4 color, RenderTarget* target, glm::mat4 model = glm::mat4(1.0f), float size = 1.0f);
		static void DrawGizmoMeshInstanced(Mesh* mesh, glm::vec4 color, glm::mat4* matrices, size_t count, RenderTarget* target, glm::mat4 model = glm::mat4(1.0f), float size = 1.0f);

		static void DrawGizmoRay(glm::vec4 color, RenderTarget* target, glm::vec3 start, glm::vec3 end, float width = 0.01f);
		static void DrawGizmoRay(glm::vec4 color, RenderTarget* target, Ray& ray, float width = 0.01f);
#pragma endregion
	};
}
