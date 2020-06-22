#pragma once
#include "UniEngineAPI.h"
#include "RenderTarget.h"

namespace UniEngine {
	const float YAW = -90.0f;
	const float PITCH = 0.0f;
	const float DEFAULTFOV = 45.0f;
	class UNIENGINE_API Camera
	{
		//static unsigned _CameraInfoBufferID;
		static GLUBO* _CameraData;
		RenderTarget* _RenderTarget;
	public:
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
		float Yaw;
		float Pitch;
		// camera options
		float FOV;
		glm::mat4 Projection;
		glm::mat4 View;
		Camera(RenderTarget* renderTarget, float yaw = YAW, float pitch = PITCH, float nearPlane = 0.1f, float farPlane = 1000.0f);
		void ProcessMouseMovement(float xoffset, float yoffset, float sensitivity, GLboolean constrainPitch = true);
		void ProcessMouseScroll(float yoffset);
	};
}