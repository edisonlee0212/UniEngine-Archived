#include "pch.h"
#include "CameraControlSystem.h"

#include "imgui_internal.h"
#include "InputManager.h"
#include "UniEngine.h"
using namespace UniEngine;
void CameraControlSystem::LateUpdate()
{
	auto mainCamera = RenderManager::GetMainCamera();
	ImVec2 viewPortSize;
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0, 0 });
	ImGui::Begin("Camera");
	{
		// Using a Child allow to fill all the space of the window.
		// It also allows customization
		if (ImGui::BeginChild("CameraRenderer")) {
			if (ImGui::IsWindowFocused())
			{
#pragma region Scene Camera Controller
				auto transform = mainCamera->GetOwner().GetComponentData<Transform>();
				auto rotation = transform.GetRotation();
				auto position = transform.GetPosition();
				glm::vec3 front = rotation * glm::vec3(0, 0, -1);
				glm::vec3 right = rotation * glm::vec3(1, 0, 0);
				bool moved = false;
				if (InputManager::GetKey(GLFW_KEY_W)) {
					position += glm::vec3(front.x, 0.0f, front.z) * (float)Application::GetWorld()->Time()->DeltaTime() * _Velocity;
					moved = true;
				}
				if (InputManager::GetKey(GLFW_KEY_S)) {
					position -= glm::vec3(front.x, 0.0f, front.z) * (float)Application::GetWorld()->Time()->DeltaTime() * _Velocity;
					moved = true;
				}
				if (InputManager::GetKey(GLFW_KEY_A)) {
					position -= glm::vec3(right.x, 0.0f, right.z) * (float)Application::GetWorld()->Time()->DeltaTime() * _Velocity;
					moved = true;
				}
				if (InputManager::GetKey(GLFW_KEY_D)) {
					position += glm::vec3(right.x, 0.0f, right.z) * (float)Application::GetWorld()->Time()->DeltaTime() * _Velocity;
					moved = true;
				}
				if (InputManager::GetKey(GLFW_KEY_LEFT_SHIFT)) {
					position.y += _Velocity * (float)Application::GetWorld()->Time()->DeltaTime();
					moved = true;
				}
				if (InputManager::GetKey(GLFW_KEY_LEFT_CONTROL)) {
					position.y -= _Velocity * (float)Application::GetWorld()->Time()->DeltaTime();
					moved = true;
				}
				if(moved)
				{
					transform.SetPosition(position);
				}
				auto mousePosition = InputManager::GetMouseAbsolutePosition();
				if (!_StartMouse) {
					_LastX = mousePosition.x;
					_LastY = mousePosition.y;
					_StartMouse = true;
				}
				float xoffset = mousePosition.x - _LastX;
				float yoffset = -mousePosition.y + _LastY;
				_LastX = mousePosition.x;
				_LastY = mousePosition.y;
				if (InputManager::GetMouse(GLFW_MOUSE_BUTTON_RIGHT)) {
					if (xoffset != 0 || yoffset != 0) {
						moved = true;
						transform.SetRotation(mainCamera->GetCamera()->ProcessMouseMovement(xoffset, yoffset, _Sensitivity));
					}
				}
				if(moved)
				{
					EntityManager::SetComponentData(mainCamera->GetOwner(), transform);
				}
#pragma endregion
			}
		}
		ImGui::EndChild();
	}
	ImGui::End();
	ImGui::PopStyleVar();
}



void CameraControlSystem::SetVelocity(float velocity)
{
	_Velocity = velocity;
}

void CameraControlSystem::SetSensitivity(float sensitivity)
{
	_Sensitivity = sensitivity;
}
