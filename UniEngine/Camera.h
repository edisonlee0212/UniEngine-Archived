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

	struct UNIENGINE_API CameraInfoBlock {
		glm::mat4 projection;
		glm::mat4 view;
		glm::vec4 ReservedParameters;
		glm::vec4 position;
	};

	class UNIENGINE_API Camera
	{
		//static unsigned _CameraInfoBufferID;
		static CameraInfoBlock _MainCameraInfoBlock;
		static GLUBO* _CameraData;
		RenderTarget* _RenderTarget;
	public:
		void CalculatePlanes(Plane* planes);

		void CalculateFrustumPoints(float nearPlane, float farPlane, glm::vec3 cameraPos, glm::vec3* points);

		void UpdateMatrices(glm::vec3 position);
		static void GenerateMatrices();
		RenderTarget* GetRenderTarget();
		// camera Attributes
		glm::vec3 _Front;
		glm::vec3 _Up;
		glm::vec3 _Right;

		float _Near;
		float _Far;
		// Euler Angles
		float _Yaw;
		float _Pitch;
		// camera options
		float _FOV;
		glm::mat4 _Projection;
		glm::mat4 _View;
		Camera(RenderTarget* renderTarget, float nearPlane = 0.1f, float farPlane = 100.0f);
		void ProcessMouseMovement(float xoffset, float yoffset, float sensitivity, GLboolean constrainPitch = true);
		void ProcessMouseScroll(float yoffset);
	};
}