#include "pch.h"
#include "Material.h"
#include "AssetManager.h"
#include "Default.h"
using namespace UniEngine;

void Material::OnGui()
{
	ImGui::Text("Name: %s", Name.c_str());
	ImGui::DragFloat("Shininess", &_Shininess, 1.0f);
	
	{
		ImGui::Spacing();
		ImGui::Text("Diffuse: ");
		ImGui::Spacing();
		ImGui::PushID(0);
		if (_DiffuseMap) {
			
			ImGui::ImageButton((ImTextureID)_DiffuseMap->Texture()->ID(), ImVec2(100, 100), ImVec2(0, 1), ImVec2(1, 0));
			if (ImGui::BeginDragDropSource(ImGuiDragDropFlags_None))
			{
				ImGui::SetDragDropPayload("ASSET_TEXTURE2D", &_DiffuseMap, sizeof(std::shared_ptr<Texture2D>));
				ImGui::Image((ImTextureID)_DiffuseMap->Texture()->ID(), ImVec2(30, 30));
				ImGui::EndDragDropSource();
			}
			
		}
		else
		{
			ImGui::Image((ImTextureID)Default::Textures::MissingTexture->Texture()->ID(), ImVec2(100, 100), ImVec2(0, 1), ImVec2(1, 0));
		}
		if (ImGui::BeginDragDropTarget())
		{
			if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("ASSET_TEXTURE2D"))
			{
				IM_ASSERT(payload->DataSize == sizeof(std::shared_ptr<Texture2D>));
				std::shared_ptr<Texture2D> payload_n = *(std::shared_ptr<Texture2D>*)payload->Data;
				_DiffuseMap = payload_n;
			}
			ImGui::EndDragDropTarget();
		}
		ImGui::PopID();
	}

	{
		ImGui::Spacing();
		ImGui::Separator();
		ImGui::Text("Specular: ");
		ImGui::Spacing();
		ImGui::PushID(1);
		if (_SpecularMap) {
			ImGui::ImageButton((ImTextureID)_SpecularMap->Texture()->ID(), ImVec2(100, 100), ImVec2(0, 1), ImVec2(1, 0));
			if (ImGui::BeginDragDropSource(ImGuiDragDropFlags_None))
			{
				ImGui::SetDragDropPayload("ASSET_TEXTURE2D", &_SpecularMap, sizeof(std::shared_ptr<Texture2D>));
				ImGui::Image((ImTextureID)_SpecularMap->Texture()->ID(), ImVec2(30, 30));
				ImGui::EndDragDropSource();
			}
		}
		else
		{
			ImGui::Image((ImTextureID)Default::Textures::MissingTexture->Texture()->ID(), ImVec2(100, 100), ImVec2(0, 1), ImVec2(1, 0));
		}
		if (ImGui::BeginDragDropTarget())
		{
			if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("ASSET_TEXTURE2D"))
			{
				IM_ASSERT(payload->DataSize == sizeof(std::shared_ptr<Texture2D>));
				std::shared_ptr<Texture2D> payload_n = *(std::shared_ptr<Texture2D>*)payload->Data;
				_SpecularMap = payload_n;
			}
			ImGui::EndDragDropTarget();
		}
		ImGui::PopID();
	}
	
	{
		ImGui::Spacing();
		ImGui::Separator();
		ImGui::Text("Normal: ");
		ImGui::Spacing();
		ImGui::PushID(2);
		if (_NormalMap) {
			ImGui::ImageButton((ImTextureID)_NormalMap->Texture()->ID(), ImVec2(100, 100), ImVec2(0, 1), ImVec2(1, 0));
			if (ImGui::BeginDragDropSource(ImGuiDragDropFlags_None))
			{
				ImGui::SetDragDropPayload("ASSET_TEXTURE2D", &_NormalMap, sizeof(std::shared_ptr<Texture2D>));
				ImGui::Image((ImTextureID)_NormalMap->Texture()->ID(), ImVec2(30, 30));
				ImGui::EndDragDropSource();
			}
		}
		else
		{
			ImGui::Image((ImTextureID)Default::Textures::MissingTexture->Texture()->ID(), ImVec2(100, 100), ImVec2(0, 1), ImVec2(1, 0));
		}
		if (ImGui::BeginDragDropTarget())
		{
			if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("ASSET_TEXTURE2D"))
			{
				IM_ASSERT(payload->DataSize == sizeof(std::shared_ptr<Texture2D>));
				std::shared_ptr<Texture2D> payload_n = *(std::shared_ptr<Texture2D>*)payload->Data;
				_NormalMap = payload_n;
			}
			ImGui::EndDragDropTarget();
		}
		ImGui::PopID();
	}
	
	{
		ImGui::Spacing();
		ImGui::Separator();
		ImGui::Text("Displacement: ");
		ImGui::Spacing();
		ImGui::PushID(3);
		if (_DisplacementMap) {
			ImGui::ImageButton((ImTextureID)_DisplacementMap->Texture()->ID(), ImVec2(100, 100), ImVec2(0, 1), ImVec2(1, 0));
			if (ImGui::BeginDragDropSource(ImGuiDragDropFlags_None))
			{
				ImGui::SetDragDropPayload("ASSET_TEXTURE2D", &_DisplacementMap, sizeof(std::shared_ptr<Texture2D>));
				ImGui::Image((ImTextureID)_DisplacementMap->Texture()->ID(), ImVec2(30, 30));
				ImGui::EndDragDropSource();
			}
		}
		else
		{
			ImGui::Image((ImTextureID)Default::Textures::MissingTexture->Texture()->ID(), ImVec2(100, 100), ImVec2(0, 1), ImVec2(1, 0));
		}
		if (ImGui::BeginDragDropTarget())
		{
			if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("ASSET_TEXTURE2D"))
			{
				IM_ASSERT(payload->DataSize == sizeof(std::shared_ptr<Texture2D>));
				std::shared_ptr<Texture2D> payload_n = *(std::shared_ptr<Texture2D>*)payload->Data;
				_DisplacementMap = payload_n;
			}
			ImGui::EndDragDropTarget();
		}
		ImGui::PopID();
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

void Material::SetTexture(std::shared_ptr<Texture2D> texture, TextureType type)
{
	switch (type)
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

