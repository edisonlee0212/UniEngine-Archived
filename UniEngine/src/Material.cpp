#include "pch.h"
#include "Material.h"
#include "ResourceManager.h"
#include "Default.h"
using namespace UniEngine;

static const char* MatPolygonMode[]{ "Fill", "Line", "Point" };
static const char* MatCullingMode[]{ "BACK", "FRONT", "OFF" };
static const char* MatBlendingMode[]{ "OFF", "ONE_MINUS_SRC_ALPHA" };

Material::Material()
{
	Name = "New material";
	Shininess = 32.0f;
}

void Material::OnGui()
{
	ImGui::Text("Name: %s", Name.c_str());
	if (ImGui::BeginPopupContextItem(Name.c_str()))
	{
		if (ImGui::BeginMenu("Rename"))
		{
			static char newName[256];
			ImGui::InputText("New name", newName, 256);
			if (ImGui::Button("Confirm")) Name = std::string(newName);
			ImGui::EndMenu();
		}
		ImGui::EndPopup();
	}
	ImGui::Text("Program: ");
	ImGui::SameLine();
	EditorManager::DragAndDrop(_Program);
	
	ImGui::DragFloat("Shininess", &Shininess, 1.0f, 1.0f, 1024.0f);
	ImGui::Checkbox("Enable Transparent Discard", &TransparentDiscard);
	ImGui::DragFloat("Transparent Discard Limit", &TransparentDiscardLimit, 0.01f, 0.0f, 0.99f);
	ImGui::Combo("Polygon Mode", reinterpret_cast<int*>(&PolygonMode), MatPolygonMode, IM_ARRAYSIZE(MatPolygonMode));
	ImGui::Combo("Culling Mode", reinterpret_cast<int*>(&CullingMode), MatCullingMode, IM_ARRAYSIZE(MatCullingMode));
	ImGui::Combo("Blending Mode", reinterpret_cast<int*>(&BlendingMode), MatBlendingMode, IM_ARRAYSIZE(MatBlendingMode));

	if (ImGui::TreeNode(("Textures##" + std::to_string(std::hash<std::string>{}(Name))).c_str())) {
		{
			ImGui::Spacing();
			ImGui::Text("Diffuse: ");
			ImGui::Spacing();
			EditorManager::DragAndDrop(_DiffuseMap);
		}

		{
			ImGui::Spacing();
			ImGui::Separator();
			ImGui::Text("Specular: ");
			ImGui::Spacing();
			EditorManager::DragAndDrop(_SpecularMap);
		}

		{
			ImGui::Spacing();
			ImGui::Separator();
			ImGui::Text("Normal: ");
			ImGui::Spacing();
			EditorManager::DragAndDrop(_NormalMap);
		}

		{
			ImGui::Spacing();
			ImGui::Separator();
			ImGui::Text("Displacement: ");
			ImGui::Spacing();
			EditorManager::DragAndDrop(_DisplacementMap);
		}
		ImGui::TreePop();
	}
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

