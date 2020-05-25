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
	
		float3 ProcessKeyboard(Camera_Movement direction, float deltaTime);
		void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true);
		void ProcessMouseScroll(float yoffset);
		void UpdateCameraVectors();
		void UpdateViewProj();
	};
}