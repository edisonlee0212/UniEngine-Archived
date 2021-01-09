#include "pch.h"
#include "PointLight.h"
using namespace UniEngine;

void PointLight::OnGui()
{
	ImGui::Checkbox("Cast Shadow", &CastShadow);
	ImGui::ColorEdit3("Diffuse", &diffuse[0]);
	ImGui::DragFloat("Diffuse Brightness", &diffuseBrightness, 0.1f, 0.0f, 999.0f);
	ImGui::ColorEdit3("Specular", &specular[0]);
	ImGui::DragFloat("Specular Brightness", &specularBrightness, 0.1f, 0.0f, 999.0f);
	ImGui::DragFloat("Bias", &bias, 0.001f, 0.0f, 999.0f);

	ImGui::DragFloat("Constant", &constant, 0.01f, 0.0f, 999.0f);
	ImGui::DragFloat("Linear", &linear, 0.0001f, 0, 1, "%.4f");
	ImGui::DragFloat("Quadratic", &quadratic, 0.00001f, 0, 10, "%.5f");

	//ImGui::InputFloat("Normal Offset", &dl->normalOffset, 0.01f);
	ImGui::DragFloat("Light Size", &lightSize, 0.01f, 0.0f, 999.0f);
}
