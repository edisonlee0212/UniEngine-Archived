#pragma once
#include "Core.h"
#include "UniEngineAPI.h"
#include "RenderTarget.h"
#include "Ray.h"
namespace UniEngine {
	struct LocalToWorld;

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
		CameraLayerMask() { Value = 0; }
	};


	const float YAW = -90.0f;
	const float PITCH = 0.0f;
	const float DEFAULTFOV = 90.0f;

	struct UNIENGINE_API Plane {
		float a, b, c, d;
		Plane() : a(0), b(0), c(0), d(0) {};
		void Normalize();
	};
	class Camera;
	struct UNIENGINE_API CameraInfoBlock {
		glm::mat4 Projection;
		glm::mat4 View;
		glm::vec4 ReservedParameters;
		glm::vec4 Position;
		void UpdateMatrices(Camera* mainCamera, glm::vec3 position, glm::quat rotation);
		void UploadMatrices(GLUBO* target);
	};

	class UNIENGINE_API Camera : public RenderTarget
	{
		size_t _LayerMask;
		GLTexture2D* _ColorTexture;
		GLRenderBuffer* _RenderBuffer;
		// Euler Angles
		float YawAngle;
		float PitchAngle;
	public:
		void StoreToJpg(std::string path, int resizeX = -1, int resizeY = -1);
		void StoreToPng(std::string path);
		void OnGui();
		size_t GetLayerMask();
		static GLUBO* CameraUniformBufferBlock;
		static CameraInfoBlock CameraInfoBlock;
		void CalculatePlanes(Plane* planes, glm::mat4 projection, glm::mat4 view);
		void CalculateFrustumPoints(float nearPlane, float farPlane, glm::vec3 cameraPos, glm::quat cameraRot, glm::vec3* points);
		static void GenerateMatrices();

		float NearDistance;
		float FarDistance;
		
		// camera options
		float FieldOfView;
		Camera(int resolutionX, int resolutionY, float nearPlane = 0.1f, float farPlane = 100.0f, size_t layerMask = 0);
		glm::quat ProcessMouseMovement(float xOffset, float yOffset, float sensitivity, GLboolean constrainPitch = true);
		void ProcessMouseScroll(float yOffset);
		void SetResolution(int x, int y);
		GLTexture2D* GetTexture() const;

		static glm::vec3 Project(LocalToWorld& ltw, glm::vec3 position);

		glm::vec3 UnProject(LocalToWorld& ltw, glm::vec3 position) const;

		glm::vec3 GetMouseWorldPoint(LocalToWorld& ltw, glm::vec2 mousePosition) const;
		void ClearColor(glm::vec3 color) const;
		Ray ScreenPointToRay(LocalToWorld& ltw, glm::vec2 mousePosition) const;
	};
}