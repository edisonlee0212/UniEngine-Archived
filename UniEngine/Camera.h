#pragma once
#include "Math.h"
#include "SharedComponent.h"
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
	public:
		// camera Attributes
		float3 Position;
		float3 Front;
		float3 Up;
		float3 Right;
		float3 WorldUp;
		// Euler Angles
		float Yaw;
		float Pitch;
		// camera options
		float MovementSpeed;
		float MouseSensitivity;
		float Zoom;
		float4x4 Projection;
		float4x4 View;
		Camera(float3 position = float3(0.0f, 1.0f, 3.0f), float3 up = float3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH);
		// Constructor with scalar values
		Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch);
		float3 ProcessKeyboard(Camera_Movement direction, float deltaTime);
		void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true);
		void ProcessMouseScroll(float yoffset);
		void UpdateCameraVectors();
		void UpdateViewProj();
	};
}