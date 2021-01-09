#include "pch.h"
#include "SpotLight.h"
using namespace UniEngine;

void SpotLight::OnGui()
{
	ImGui::Checkbox("Cast Shadow", &CastShadow);
	ImGui::ColorEdit3("Diffuse", &diffuse[0]);
	ImGui::DragFloat("Diffuse Brightness", &diffuseBrightness, 0.1f, 0.0f, 999.0f);
	ImGui::ColorEdit3("Specular", &specular[0]);
	ImGui::DragFloat("Specular Brightness", &specularBrightness, 0.1f, 0.0f, 999.0f);
	ImGui::DragFloat("Bias", &bias, 0.001f, 0.0f, 999.0f);

	ImGui::DragFloat("Constant", &constant, 0.01f, 0.0f, 999.0f);
	ImGui::DragFloat("Linear", &linear, 0.001f, 0, 1, "%.3f");
	ImGui::DragFloat("Quadratic", &quadratic, 0.001f, 0, 10, "%.4f");

	ImGui::DragFloat("Inner Degrees", &innerDegrees, 0.1f, 0.0f, outerDegrees);
	ImGui::DragFloat("Outer Degrees", &outerDegrees, 0.1f, innerDegrees, 180.0f);
	ImGui::DragFloat("Light Size", &lightSize, 0.01f, 0.0f, 999.0f);
}
