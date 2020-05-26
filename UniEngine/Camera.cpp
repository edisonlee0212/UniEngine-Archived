#include "Camera.h"
#include "WindowManager.h"
using namespace UniEngine;

Camera::Camera(float3 position, float3 up, float yaw, float pitch) : Front(float3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
{
	Position = position;
	WorldUp = up;
	Yaw = yaw;
	Pitch = pitch;
	UpdateCameraVectors();
}
// Constructor with scalar values
Camera::Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch) : Front(float3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
{
	Position = float3(posX, posY, posZ);
	WorldUp = float3(upX, upY, upZ);
	Yaw = yaw;
	Pitch = pitch;
	UpdateCameraVectors();
}

float3 UniEngine::Camera::ProcessKeyboard(Camera_Movement direction, float deltaTime)
{
	float velocity = MovementSpeed * deltaTime;
	if (direction == FORWARD)
		Position = float3(Front.x, 0.0f, Front.z) * velocity + Position;
	if (direction == BACKWARD)
		Position = float3(Front.x, 0.0f, Front.z) * velocity - Position;
	if (direction == LEFT)
		Position = float3(Right.x, 0.0f, Right.z) * velocity - Position;
	if (direction == RIGHT)
		Position = float3(Right.x, 0.0f, Right.z) * velocity + Position;
	if (direction == UP)
		Position.y += velocity;
	if (direction == DOWN)
		Position.y -= velocity;
	return Position;
}

void UniEngine::Camera::ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch)
{
	xoffset *= MouseSensitivity;
	yoffset *= MouseSensitivity;

	Yaw += xoffset;
	Pitch += yoffset;

	// Make sure that when pitch is out of bounds, screen doesn't get flipped
	if (constrainPitch)
	{
		if (Pitch > 89.0f)
			Pitch = 89.0f;
		if (Pitch < -89.0f)
			Pitch = -89.0f;
	}

	// Update Front, Right and Up Vectors using the updated Euler angles
	UpdateCameraVectors();
}

void UniEngine::Camera::ProcessMouseScroll(float yoffset)
{
	if (Zoom >= 1.0f && Zoom <= 45.0f)
		Zoom -= yoffset;
	if (Zoom <= 1.0f)
		Zoom = 1.0f;
	if (Zoom >= 45.0f)
		Zoom = 45.0f;
}

void UniEngine::Camera::UpdateCameraVectors()
{
	// Calculate the new Front vector
	float3 front;
	front.x = Cos(Yaw / 180.0f * 3.1415926) * Cos(Pitch / 180.0f * 3.1415926);
	front.y = Sin(Pitch / 180.0f * 3.1415926);
	front.z = Sin(Yaw / 180.0f * 3.1415926) * Cos(Pitch / 180.0f * 3.1415926);
	Front = Normalize(front);
	// Also re-calculate the Right and Up vector
	Right = Normalize(Cross(Front, WorldUp));  // Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
	Up = Normalize(Cross(Right, Front));
	UpdateViewProj();
}

void Camera::UpdateViewProj() {
	View = LookAt4x4(Position, Position + Front, Up);
	auto size = WindowManager::CurrentWindow()->GetSize();
	if (size.x == 0 || size.y == 0) return;
	Projection = PerspectiveFov(Zoom / 180.0f * 3.1415926, size.x / size.y, 0.1f, 100.0f);
}
