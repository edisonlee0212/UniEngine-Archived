#pragma once
#include "Misc.h"
#include "Core.h"
#include "RenderTarget.h"

namespace UniEngine {
	const float YAW = -90.0f;
	const float PITCH = 0.0f;
	const float ZOOM = 45.0f;
	class Camera
	{
		static unsigned _CameraInfoBufferID;
		RenderTarget* _RenderTarget;
	public:
		void UpdateMatrices(glm::vec3 position);
		static void GenerateMatrices();
		RenderTarget* GetRenderTarget();
		// camera Attributes
		glm::vec3 _Front;
		glm::vec3 _Up;
		glm::vec3 _Right;
		// Euler Angles
		float Yaw;
		float Pitch;
		// camera options
		float Zoom;
		glm::mat4 Projection;
		glm::mat4 View;
		Camera(RenderTarget* renderTarget, float yaw = YAW, float pitch = PITCH);
		void ProcessMouseMovement(float xoffset, float yoffset, float sensitivity, GLboolean constrainPitch = true);
		void ProcessMouseScroll(float yoffset);
	};
}