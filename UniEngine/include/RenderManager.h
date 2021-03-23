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
		float m_splitDistance[4];
		int m_pcfSampleAmount = 16;
		float m_scaleFactor = 1.0f;
		int m_blockerSearchAmount = 2;
		float m_seamFixRatio = 0.05f;
		float m_vsmMaxVariance = 0.001f;
		float m_lightBleedFactor = 0.5f;
		float m_evsmExponent = 40.0f;
		float m_ambientLight = 0.3f;
	};

	struct MaterialSettingsBlock
	{
		GLuint64 m_spotShadowMap = 0;
		GLuint64 m_directionalShadowMap = 0;
		GLuint64 m_pointShadowMap = 0;
		
		GLuint64 m_albedoMap = 0;
		GLuint64 m_normalMap = 0;
		GLuint64 m_metallicMap = 0;
		GLuint64 m_roughnessMap = 0;
		GLuint64 m_aoMap = 0;
		
		GLuint64 m_ambient = 0;
		GLuint64 m_diffuse = 0;
		GLuint64 m_specular = 0;
		GLuint64 m_emissive = 0;
		GLuint64 m_displacement = 0;

		
		int m_albedoEnabled = 0;
		int m_normalEnabled = 0;
		int m_metallicEnabled = 0;
		int m_roughnessEnabled = 0;
		int m_aoEnabled = 0;

		int m_ambientEnabled = 0;
		int m_diffuseEnabled = 0;
		int m_specularEnabled = 0;
		int m_emissiveEnabled = 0;
		int m_displacementEnabled = 0;

		glm::vec4 m_albedoColorVal = glm::vec4(1.0f);
		float m_shininessVal = 32.0f;
		float m_metallicVal = 0.5f;
		float m_roughnessVal = 0.5f;
		float m_aoVal = 1.0f;
		float m_displacementScale = 0.0f;
		
		int m_receiveShadow = true;
		int m_enableShadow = true;
		int m_alphaDiscardEnabled = true;
		float m_alphaDiscardOffset = 0.1f;

		GLuint64 m_environmentalMap = 0;
		int m_environmentalMapEnabled = 0;
	};
	
	class UNIENGINE_API RenderManager : public Singleton<RenderManager>
	{
		CameraComponent* m_mainCameraComponent = nullptr;
#pragma region Global Var
#pragma region GUI
		bool m_enableLightMenu = true;
		bool m_enableRenderMenu = false;
		bool m_enableInfoWindow = false;
#pragma endregion
#pragma region Render
		std::unique_ptr<GLUBO> m_kernelBlock;
		std::unique_ptr<GLProgram> m_gBufferInstancedPrepass;
		std::unique_ptr<GLProgram> m_gBufferPrepass;
		std::unique_ptr<GLProgram> m_gBufferLightingPass;

		int m_mainCameraResolutionX = 1;
		int m_mainCameraResolutionY = 1;
		friend class RenderTarget;
		size_t m_triangles = 0;
		size_t m_drawCall = 0;
		
		std::unique_ptr<GLUBO> m_materialSettingsBuffer;
#pragma endregion
#pragma region Shadow
		GLUBO m_directionalLightBlock;
		GLUBO m_pointLightBlock;
		GLUBO m_spotLightBlock;

		size_t m_shadowMapResolution = 4096;
		GLUBO m_shadowCascadeInfoBlock;
		

		DirectionalLightInfo m_directionalLights[Default::ShaderIncludes::MaxDirectionalLightAmount];
		PointLightInfo m_pointLights[Default::ShaderIncludes::MaxPointLightAmount];
		SpotLightInfo m_spotLights[Default::ShaderIncludes::MaxSpotLightAmount];

		std::unique_ptr<GLProgram> m_directionalLightProgram;
		std::unique_ptr<GLProgram> m_directionalLightInstancedProgram;
		std::unique_ptr<GLProgram> m_pointLightProgram;
		std::unique_ptr<GLProgram> m_pointLightInstancedProgram;
		std::unique_ptr<GLProgram> m_spotLightProgram;
		std::unique_ptr<GLProgram> m_spotLightInstancedProgram;

		
		friend class EditorManager;
		std::unique_ptr<DirectionalLightShadowMap> m_directionalLightShadowMap;
		std::unique_ptr<PointLightShadowMap> m_pointLightShadowMap;
		std::unique_ptr<SpotLightShadowMap> m_spotLightShadowMap;
		
		
		
#pragma endregion
#pragma endregion
		
		static void DeferredPrepass(Mesh* mesh, Material* material, glm::mat4 model);
		static void DeferredPrepassInstanced(Mesh* mesh, Material* material, glm::mat4 model, glm::mat4* matrices, size_t count);

		static void DrawMeshInstanced(Mesh* mesh, Material* material, glm::mat4 model, const glm::mat4* matrices, size_t count, bool receiveShadow);
		static void DrawMesh(Mesh* mesh, Material* material, glm::mat4 model, bool receiveShadow);

		static void DrawGizmoInstanced(Mesh* mesh, glm::vec4 color, glm::mat4 model, glm::mat4* matrices, size_t count, glm::mat4 scaleMatrix);
		static void DrawGizmo(Mesh* mesh, glm::vec4 color, glm::mat4 model, glm::mat4 scaleMatrix);
		static float Lerp(float a, float b, float f);
	public:
		bool m_stableFit = true;
		float m_maxShadowDistance = 500;
		float m_shadowCascadeSplit[Default::ShaderIncludes::ShadowCascadeAmount] = { 0.15f, 0.3f, 0.5f, 1.0f };
		LightSettingsBlock m_lightSettings;
		MaterialSettingsBlock m_materialSettings;

		static void MaterialPropertySetter(Material* material, bool disableBlending = false);
		static void ApplyMaterialSettings(Material* material, GLProgram* program);
		static void BindTextureHandles(Material* material);
		static void ReleaseTextureHandles(Material* material);
		static void RenderToCameraDeferred(const std::unique_ptr<CameraComponent>& cameraComponent, const GlobalTransform& cameraTransform, glm::vec3& minBound, glm::vec3& maxBound, bool calculateBounds = false);
		static void RenderBackGround(const std::unique_ptr<CameraComponent>& cameraComponent);
		static void RenderToCameraForward(const std::unique_ptr<CameraComponent>& cameraComponent, const GlobalTransform& cameraTransform, glm::vec3& minBound, glm::vec3& maxBound, bool calculateBounds = false);
		static void Init();
		//Main rendering happens here.
		static void PreUpdate();
#pragma region Shadow
		static void SetSplitRatio(float r1, float r2, float r3, float r4);
		static void SetShadowMapResolution(size_t value);

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
