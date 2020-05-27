#pragma once
#include "Misc.h"
#include "Core.h"
#include "RenderTarget.h"

namespace UniEngine {
	enum Camera_Movement {
		FORWARD,
		BACKWARD,
		LEFT,
		RIGHT,
		UP,
		DOWN
	};
	const float YAW = -90.0f;
	const float PITCH = 0.0f;
	const float SPEED = 2.5f;
	const float SENSITIVITY = 0.1f;
	const float ZOOM = 45.0f;
	class Camera :
		public SharedComponent
	{
		static unsigned _CameraInfoBufferID;
		RenderTarget* _RenderTarget;
	public:
		void UpdateMatrices();
		static void GenerateMatrices();
		RenderTarget* GetRenderTarget();
		// camera Attributes
		glm::vec3 _Position;
		glm::vec3 _Front;
		glm::vec3 _Up;
		glm::vec3 _Right;
		glm::vec3 _WorldUp;
		// Euler Angles
		float Yaw;
		float Pitch;
		// camera options
		float MovementSpeed;
		float MouseSensitivity;
		float Zoom;
		glm::mat4 Projection;
		glm::mat4 View;
		Camera(RenderTarget* renderTarget, glm::vec3 position = glm::vec3(0.0f, 5.0f, 5.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH);
		// Constructor with scalar values
		Camera(RenderTarget* renderTarget, float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch);
		glm::vec3 ProcessKeyboard(Camera_Movement direction, float deltaTime);
		void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true);
		void ProcessMouseScroll(float yoffset);
		void UpdateCameraVectors();
		void UpdateViewProj();
	};
}