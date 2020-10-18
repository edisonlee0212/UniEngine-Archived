#include "pch.h"
#include "Material.h"
using namespace UniEngine;

void Material::OnGui()
{
	ImGui::Text("Name: %s", Name.c_str());
	ImGui::DragFloat("Shininess", &_Shininess, 1.0f);
	if (_DiffuseMap) {
		ImGui::Spacing();
		ImGui::Text("Diffuse: ");
		ImGui::Spacing();
		ImGui::Image((ImTextureID)_DiffuseMap->Texture()->ID(), ImVec2(100, 100));
	}
	if (_SpecularMap) {
		ImGui::Spacing();
		ImGui::Separator();
		ImGui::Text("Specular: ");
		ImGui::Spacing();
		ImGui::Image((ImTextureID)_SpecularMap->Texture()->ID(), ImVec2(100, 100));
	}
	if (_NormalMap) {
		ImGui::Spacing();
		ImGui::Separator();
		ImGui::Text("Normal: ");
		ImGui::Spacing();
		ImGui::Image((ImTextureID)_NormalMap->Texture()->ID(), ImVec2(100, 100));
	}
	if (_HeightMap) {
		ImGui::Spacing();
		ImGui::Separator();
		ImGui::Text("Height: ");
		ImGui::Spacing();
		ImGui::Image((ImTextureID)_HeightMap->Texture()->ID(), ImVec2(100, 100));
	}
}

void Material::SetShininess(float value)
{
	_Shininess = value;
}

void UniEngine::Material::SetMaterialProperty(const std::string& name, float value)
{
	for (auto& property : _FloatPropertyList)
	{
		if (property.Name._Equal(name))
		{
			property.Value = value;
			return;
		}
	}
	_FloatPropertyList.emplace_back(name, value);
}

void UniEngine::Material::SetMaterialProperty(const std::string& name, glm::mat4 value)
{
	for (auto& property : _Float4x4PropertyList)
	{
		if (property.Name._Equal(name))
		{
			property.Value = value;
			return;
		}
	}
	_Float4x4PropertyList.emplace_back(name, value);
}

void Material::SetTexture(std::shared_ptr<Texture2D> texture)
{
	switch (texture->Type())
	{
	case TextureType::DIFFUSE:
		_DiffuseMap = std::move(texture);
		break;
	case TextureType::NORMAL:
		_NormalMap = std::move(texture);
		break;
	case TextureType::SPECULAR:
		_SpecularMap = std::move(texture);
		break;
	case TextureType::HEIGHT:
		_HeightMap = std::move(texture);
		break;
	default:
		break;
	}
}

void Material::RemoveTexture(TextureType type)
{
	switch (type)
	{
	case TextureType::DIFFUSE:
		_DiffuseMap.reset();
		break;
	case TextureType::NORMAL:
		_NormalMap.reset();
		break;
	case TextureType::SPECULAR:
		_SpecularMap.reset();
		break;
	case TextureType::HEIGHT:
		_HeightMap.reset();
		break;
	}
}

void Material::SetProgram(std::shared_ptr<GLProgram> program)
{
	_Program = std::move(program);
}

