#pragma once
#include "Core.h"
#include "UniEngineAPI.h"
#include "CameraComponent.h"
#include "MeshRenderer.h"
#include "Particles.h"
#include "RenderTarget.h"

#include "DirectionalLight.h"
#include "PointLight.h"
#include "SpotLight.h"
#include "DirectionalLightShadowMap.h"
#include "PointLightShadowMap.h"
#include "SpotLightShadowMap.h"
#include "Cubemap.h"
#include "Default.h"
#include "Texture2D.h"

#include "PostProcessing.h"

namespace UniEngine {
	struct UNIENGINE_API LightSettingsBlock {
		float SplitDistance[4];
		int PCSSPCFSampleAmount = 16;
		float PCSSScaleFactor = 1.0f;
		int PCSSBSAmount = 2;
		float SeamFixRatio = 0.05f;
		float VSMMaxVariance = 0.001f;
		float LightBleedFactor = 0.5f;
		float EVSMExponent = 40.0f;
		float AmbientLight = 0.3f;
	};

	struct MaterialSettingsBlock
	{
		GLuint64 spotShadowMap = 0;
		GLuint64 directionalShadowMap = 0;
		GLuint64 pointShadowMap = 0;
		
		GLuint64 albedoMap = 0;
		GLuint64 normalMap = 0;
		GLuint64 metallicMap = 0;
		GLuint64 roughnessMap = 0;
		GLuint64 aoMap = 0;
		
		GLuint64 ambient = 0;
		GLuint64 diffuse = 0;
		GLuint64 specular = 0;
		GLuint64 emissive = 0;
		GLuint64 displacement = 0;

		
		int albedoEnabled = 0;
		int normalEnabled = 0;
		int metallicEnabled = 0;
		int roughnessEnabled = 0;
		int aoEnabled = 0;

		int ambientEnabled = 0;
		int diffuseEnabled = 0;
		int specularEnabled = 0;
		int emissiveEnabled = 0;
		int displacementEnabled = 0;

		glm::vec4 albedoColorVal;
		float shininessVal;
		float metallicVal;
		float roughnessVal;
		float aoVal;
		float dispScale;
		
		int receiveShadow;
		int enableShadow = true;
		int alphaDiscardEnabled;
		float alphaDiscardOffset;

		GLuint64 environmentalMap = 0;
		int environmentalMapEnabled = 0;

	};
	
	class UNIENGINE_API RenderManager : public Singleton<RenderManager>
	{
		static CameraComponent* _MainCameraComponent;
#pragma region Global Var
#pragma region GUI
		static bool _EnableLightMenu;
		static bool _EnableRenderMenu;
		static bool _EnableInfoWindow;
#pragma endregion
#pragma region Render
		static std::unique_ptr<GLUBO> _KernelBlock;
		static std::unique_ptr<GLProgram> _GBufferInstancedPrepass;
		static std::unique_ptr<GLProgram> _GBufferPrepass;
		static std::unique_ptr<GLProgram> _GBufferLightingPass;

		static int _MainCameraResolutionX;
		static int _MainCameraResolutionY;
		static EntityQuery _DirectionalLightQuery;
		static EntityQuery _PointLightQuery;
		static EntityQuery _SpotLightQuery;
		friend class RenderTarget;
		static size_t _Triangles;
		static size_t _DrawCall;
		static MaterialSettingsBlock _MaterialSettingsBlock;
		static std::unique_ptr<GLUBO> _MaterialSettingsBuffer;
#pragma endregion
#pragma region Shadow
		static GLUBO* _DirectionalLightBlock;
		static GLUBO* _PointLightBlock;
		static GLUBO* _SpotLightBlock;

		static float _ShadowCascadeSplit[Default::ShaderIncludes::ShadowCascadeAmount];
		static size_t _ShadowMapResolution;
		static GLUBO* _ShadowCascadeInfoBlock;
		static LightSettingsBlock _LightSettings;

		static DirectionalLightInfo _DirectionalLights[Default::ShaderIncludes::MaxDirectionalLightAmount];
		static PointLightInfo _PointLights[Default::ShaderIncludes::MaxPointLightAmount];
		static SpotLightInfo _SpotLights[Default::ShaderIncludes::MaxSpotLightAmount];

		static std::unique_ptr<GLProgram> _DirectionalLightProgram;
		static std::unique_ptr<GLProgram> _DirectionalLightInstancedProgram;
		static std::unique_ptr<GLProgram> _PointLightProgram;
		static std::unique_ptr<GLProgram> _PointLightInstancedProgram;
		static std::unique_ptr<GLProgram> _SpotLightProgram;
		static std::unique_ptr<GLProgram> _SpotLightInstancedProgram;

		
		friend class EditorManager;
		static std::unique_ptr<DirectionalLightShadowMap> _DirectionalLightShadowMap;
		static std::unique_ptr<PointLightShadowMap> _PointLightShadowMap;
		static std::unique_ptr<SpotLightShadowMap> _SpotLightShadowMap;
		
		static bool _StableFit;
		static float _MaxShadowDistance;
#pragma endregion
#pragma endregion
		static void MaterialPropertySetter(Material* material, bool disableBlending = false);
		static void ApplyMaterialSettings(Material* material, GLProgram* program);
		static void DeferredPrepass(Mesh* mesh, Material* material, glm::mat4 model);
		static void DeferredPrepassInstanced(Mesh* mesh, Material* material, glm::mat4 model, glm::mat4* matrices, size_t count);

		static void DrawMeshInstanced(Mesh* mesh, Material* material, glm::mat4 model, const glm::mat4* matrices, size_t count, bool receiveShadow);
		static void DrawMesh(Mesh* mesh, Material* material, glm::mat4 model, bool receiveShadow);

		static void DrawGizmoInstanced(Mesh* mesh, glm::vec4 color, glm::mat4 model, glm::mat4* matrices, size_t count, glm::mat4 scaleMatrix);
		static void DrawGizmo(Mesh* mesh, glm::vec4 color, glm::mat4 model, glm::mat4 scaleMatrix);
		static float Lerp(float a, float b, float f);
	public:
		static void RenderToCameraDeferred(const std::unique_ptr<CameraComponent>& cameraComponent, const GlobalTransform& cameraTransform, glm::vec3& minBound, glm::vec3& maxBound, bool calculateBounds = false);
		static void RenderBackGround(const std::unique_ptr<CameraComponent>& cameraComponent);
		static void RenderToCameraForward(const std::unique_ptr<CameraComponent>& cameraComponent, const GlobalTransform& cameraTransform, glm::vec3& minBound, glm::vec3& maxBound, bool calculateBounds = false);
		static void Init();
		//Main rendering happens here.
		static void PreUpdate();
#pragma region Shadow
		static void SetSplitRatio(float r1, float r2, float r3, float r4);
		static void SetShadowMapResolution(size_t value);
		static void SetPCSSPCFSampleAmount(int value);
		static void SetPCSSBSAmount(int value);
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
#pragma region RenderAPI
		static void LateUpdate();
		static size_t Triangles();
		static size_t DrawCall();


		static void DrawTexture2D(GLTexture2D* texture, float depth, glm::vec2 center, glm::vec2 size);
		static void DrawTexture2D(GLTexture2D* texture, float depth, glm::vec2 center, glm::vec2 size, RenderTarget* target);
		static void DrawTexture2D(Texture2D* texture, float depth, glm::vec2 center, glm::vec2 size, RenderTarget* target);
		static void DrawTexture2D(Texture2D* texture, float depth, glm::vec2 center, glm::vec2 size, CameraComponent* cameraComponent);

		static void SetMainCamera(CameraComponent* value);
		static CameraComponent* GetMainCamera();
		static void DrawGizmoPoint(glm::vec4 color, glm::mat4 model = glm::mat4(1.0f), float size = 1.0f);
		static void DrawGizmoPointInstanced(glm::vec4 color, glm::mat4* matrices, size_t count, glm::mat4 model = glm::mat4(1.0f), float size = 1.0f);
		static void DrawGizmoCube(glm::vec4 color, glm::mat4 model = glm::mat4(1.0f), float size = 1.0f);
		static void DrawGizmoCubeInstanced(glm::vec4 color, glm::mat4* matrices, size_t count, glm::mat4 model = glm::mat4(1.0f), float size = 1.0f);
		static void DrawGizmoQuad(glm::vec4 color, glm::mat4 model = glm::mat4(1.0f), float size = 1.0f);
		static void DrawGizmoQuadInstanced(glm::vec4 color, glm::mat4* matrices, size_t count, glm::mat4 model = glm::mat4(1.0f), float size = 1.0f);
		static void DrawGizmoMesh(Mesh* mesh, glm::vec4 color, glm::mat4 model = glm::mat4(1.0f), float size = 1.0f);
		static void DrawGizmoMeshInstanced(Mesh* mesh, glm::vec4 color, glm::mat4* matrices, size_t count, glm::mat4 model = glm::mat4(1.0f), float size = 1.0f);

		static void DrawGizmoRay(glm::vec4 color, glm::vec3 start, glm::vec3 end, float width = 0.01f);
		static void DrawGizmoRays(glm::vec4 color, std::vector<std::pair<glm::vec3, glm::vec3>> connections, float width = 0.01f);
		static void DrawGizmoRays(glm::vec4 color, std::vector<Ray>& rays, float width = 0.01f);
		static void DrawGizmoRay(glm::vec4 color, Ray& ray, float width = 0.01f);

		static void DrawMesh(Mesh* mesh, Material* material, glm::mat4 model, RenderTarget* target, bool receiveShadow = true);
		static void DrawMeshInstanced(Mesh* mesh, Material* material, glm::mat4 model, glm::mat4* matrices, size_t count, RenderTarget* target, bool receiveShadow = true);
		
		static void DrawMesh(Mesh* mesh, Material* material, glm::mat4 model, CameraComponent* cameraComponent, bool receiveShadow = true);
		static void DrawMeshInstanced(Mesh* mesh, Material* material, glm::mat4 model, glm::mat4* matrices, size_t count, CameraComponent* cameraComponent, bool receiveShadow = true);

#pragma endregion
	};

	
}
