#include "pch.h"
#include "Material.h"
#include "AssetManager.h"
#include "Default.h"
using namespace UniEngine;

void Material::OnGui()
{
	ImGui::Text("Name: %s", Name.c_str());
	ImGui::DragFloat("Shininess", &_Shininess, 1.0f);
	
	ImGui::Spacing();
	ImGui::Text("Diffuse: ");
	ImGui::Spacing();
	if (_DiffuseMap) {
		ImGui::Image((ImTextureID)_DiffuseMap->Texture()->ID(), ImVec2(100, 100), ImVec2(0, 1), ImVec2(1, 0));
	}else
	{
		ImGui::Image((ImTextureID)Default::Textures::MissingTexture->Texture()->ID(), ImVec2(100, 100), ImVec2(0, 1), ImVec2(1, 0));
	}
	if (ImGui::BeginDragDropTarget())
	{
		if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("ASSET_TEXTURE_DIFFUSE"))
		{
			IM_ASSERT(payload->DataSize == sizeof(int));
			int payload_n = *(const int*)payload->Data;
			_DiffuseMap.reset();
			_DiffuseMap = std::shared_ptr<Texture2D>(AssetManager::GetTexture2D(payload_n));
		}
		ImGui::EndDragDropTarget();
	}
	ImGui::Spacing();
	ImGui::Separator();
	ImGui::Text("Specular: ");
	ImGui::Spacing();
	if (_SpecularMap) {
		ImGui::Image((ImTextureID)_SpecularMap->Texture()->ID(), ImVec2(100, 100), ImVec2(0, 1), ImVec2(1, 0));
	}else
	{
		ImGui::Image((ImTextureID)Default::Textures::MissingTexture->Texture()->ID(), ImVec2(100, 100), ImVec2(0, 1), ImVec2(1, 0));
	}
	if (ImGui::BeginDragDropTarget())
	{
		if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("ASSET_TEXTURE_SPECULAR"))
		{
			IM_ASSERT(payload->DataSize == sizeof(int));
			int payload_n = *(const int*)payload->Data;
			_SpecularMap = std::shared_ptr<Texture2D>(AssetManager::GetTexture2D(payload_n));
		}
		ImGui::EndDragDropTarget();
	}
	ImGui::Spacing();
	ImGui::Separator();
	ImGui::Text("Normal: ");
	ImGui::Spacing();
	if (_NormalMap) {
		ImGui::Image((ImTextureID)_NormalMap->Texture()->ID(), ImVec2(100, 100), ImVec2(0, 1), ImVec2(1, 0));
	}else
	{
		ImGui::Image((ImTextureID)Default::Textures::MissingTexture->Texture()->ID(), ImVec2(100, 100), ImVec2(0, 1), ImVec2(1, 0));
	}
	if (ImGui::BeginDragDropTarget())
	{
		if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("ASSET_TEXTURE_NORMAL"))
		{
			IM_ASSERT(payload->DataSize == sizeof(int));
			int payload_n = *(const int*)payload->Data;
			_NormalMap = std::shared_ptr<Texture2D>(AssetManager::GetTexture2D(payload_n));
		}
		ImGui::EndDragDropTarget();
	}
	ImGui::Spacing();
	ImGui::Separator();
	ImGui::Text("Displacement: ");
	ImGui::Spacing();
	if (_DisplacementMap) {
		
		ImGui::Image((ImTextureID)_DisplacementMap->Texture()->ID(), ImVec2(100, 100), ImVec2(0, 1), ImVec2(1, 0));
		
	}else
	{
		ImGui::Image((ImTextureID)Default::Textures::MissingTexture->Texture()->ID(), ImVec2(100, 100), ImVec2(0, 1), ImVec2(1, 0));
	}
	if (ImGui::BeginDragDropTarget())
	{
		if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("ASSET_TEXTURE_DISPLACEMENT"))
		{
			IM_ASSERT(payload->DataSize == sizeof(int));
			int payload_n = *(const int*)payload->Data;
			_DisplacementMap = std::shared_ptr<Texture2D>(AssetManager::GetTexture2D(payload_n));
		}
		ImGui::EndDragDropTarget();
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
	case TextureType::DISPLACEMENT:
		_DisplacementMap = std::move(texture);
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
	case TextureType::DISPLACEMENT:
		_DisplacementMap.reset();
		break;
	}
}

void Material::SetProgram(std::shared_ptr<GLProgram> program)
{
	_Program = std::move(program);
}

