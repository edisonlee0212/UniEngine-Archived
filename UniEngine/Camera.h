#pragma once
#include "UniEngineAPI.h"
#include "RenderTarget.h"

namespace UniEngine {
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

	class UNIENGINE_API Camera
	{
		//static unsigned _CameraInfoBufferID;
		
		
		RenderTarget* _RenderTarget;
	public:
		static GLUBO* _CameraData;
		static CameraInfoBlock _MainCameraInfoBlock;
		void CalculatePlanes(Plane* planes, glm::mat4 projection, glm::mat4 view);
		void CalculateFrustumPoints(float nearPlane, float farPlane, glm::vec3 cameraPos, glm::quat cameraRot, glm::vec3* points);
		static void GenerateMatrices();
		RenderTarget* GetRenderTarget();

		float _Near;
		float _Far;
		// Euler Angles
		float _Yaw;
		float _Pitch;
		// camera options
		float _FOV;
		Camera(RenderTarget* renderTarget, float nearPlane = 0.1f, float farPlane = 100.0f);
		glm::quat ProcessMouseMovement(float xoffset, float yoffset, float sensitivity, GLboolean constrainPitch = true);
		void ProcessMouseScroll(float yoffset);
	};
}