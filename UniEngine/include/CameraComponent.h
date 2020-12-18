#pragma once
#include "Core.h"
#include "UniEngineAPI.h"
#include "RenderTarget.h"

namespace UniEngine {
	class CameraComponent;
	struct GlobalTransform;

	enum CameraLayer {
		CameraLayer_None = 0,
		CameraLayer_MainCamera = 1 << 0,
		CameraLayer_DebugCamera = 1 << 1,
	};

	struct UNIENGINE_API CameraLayerMask : ComponentBase
	{
		size_t Value;
		bool operator ==(const CameraLayerMask& other) const {
			return other.Value == Value;
		}
		CameraLayerMask();
	};
	struct UNIENGINE_API Plane {
		float a, b, c, d;
		Plane();
		void Normalize();
	};
	
	struct UNIENGINE_API CameraInfoBlock {
		glm::mat4 Projection;
		glm::mat4 View;
		glm::vec4 ReservedParameters;
		glm::vec4 Position;
		void UpdateMatrices(CameraComponent* camera, glm::vec3 position, glm::quat rotation);
		void UploadMatrices(CameraComponent* camera);
	};
	struct Ray;
	
	class Cubemap;
	class UNIENGINE_API CameraComponent final :
		public PrivateComponentBase, public RenderTarget
	{
		friend class RenderManager;
		friend class EditorManager;
		friend struct CameraInfoBlock;
		std::shared_ptr<Texture2D> _ColorTexture;
		std::unique_ptr<GLRenderBuffer> _DepthStencilBuffer;

		
		std::unique_ptr<RenderTarget> _SSAO;
		std::unique_ptr<RenderTarget> _SSAOBlurFilter;
		std::unique_ptr<GLTexture2D> _SSAONoise;
		std::unique_ptr<GLTexture2D> _SSAOColor;
		std::unique_ptr<GLTexture2D> _SSAOBlur;

		std::unique_ptr<RenderTarget> _GBuffer;
		std::unique_ptr<GLRenderBuffer> _GDepthBuffer;
		std::unique_ptr<GLTexture2D> _GPositionBuffer;
		std::unique_ptr<GLTexture2D> _GNormalBuffer;
		std::unique_ptr<GLTexture2D> _GColorSpecularBuffer;
		static CameraInfoBlock _CameraInfoBlock;
		static std::unique_ptr<GLUBO> _CameraUniformBufferBlock;
		bool _IsMainCamera = false;
	public:
		float NearDistance = 0.1f;
		float FarDistance = 500.0f;
		float FOV = 90;
		void StoreToJpg(const std::string& path, int resizeX = -1, int resizeY = -1) const;
		void StoreToPng(const std::string& path, int resizeX = -1, int resizeY = -1) const;
		
		
		static void CalculatePlanes(std::vector<Plane>& planes, glm::mat4 projection, glm::mat4 view);
		void CalculateFrustumPoints(float nearPlane, float farPlane, glm::vec3 cameraPos, glm::quat cameraRot, glm::vec3* points) const;
		static glm::quat ProcessMouseMovement(float yawAngle, float pitchAngle, bool constrainPitch = true);
		std::shared_ptr<Texture2D> GetTexture() const;
		glm::mat4 GetProjection() const;
		static glm::vec3 Project(GlobalTransform& ltw, glm::vec3 position);

		glm::vec3 UnProject(GlobalTransform& ltw, glm::vec3 position) const;

		glm::vec3 GetMouseWorldPoint(GlobalTransform& ltw, glm::vec2 mousePosition) const;
		void SetClearColor(glm::vec3 color) const;
		Ray ScreenPointToRay(GlobalTransform& ltw, glm::vec2 mousePosition) const;
		static void GenerateMatrices();
		
		void Serialize(YAML::Emitter& out) override;
		void Deserialize(const YAML::Node& in) override;
		void ResizeResolution(int x, int y);
		CameraComponent();
		~CameraComponent() override;
		bool DrawSkyBox = true;
		glm::vec3 ClearColor;
		std::shared_ptr<Cubemap> SkyBox;
		void OnGui() override;
	};
	
}
