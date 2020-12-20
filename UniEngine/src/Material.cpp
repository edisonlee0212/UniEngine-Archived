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
	_Textures[TextureType::ALBEDO] = nullptr;
	_Textures[TextureType::NORMAL] = nullptr;
	_Textures[TextureType::METALLIC] = nullptr;
	_Textures[TextureType::ROUGHNESS] = nullptr;
	_Textures[TextureType::AO] = nullptr;

	_Textures[TextureType::AMBIENT] = nullptr;
	_Textures[TextureType::DIFFUSE] = nullptr;
	_Textures[TextureType::SPECULAR] = nullptr;
	_Textures[TextureType::EMISSIVE] = nullptr;
	_Textures[TextureType::DISPLACEMENT] = nullptr;
	
	
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
	if(ImGui::TreeNode("PBR"))
	{
		ImGui::ColorEdit3("Albedo", &AlbedoColor.x);
		ImGui::DragFloat("Metallic", &Metallic, 0.01f, 0.0f, 1.0f);
		ImGui::DragFloat("Roughness", &Roughness, 0.01f, 0.0f, 1.0f);
		ImGui::DragFloat("AO", &AmbientOcclusion, 0.01f, 0.0f, 1.0f);
		ImGui::DragFloat("Shininess", &Shininess, 1.0f, 1.0f, 1024.0f);
		ImGui::TreePop();
	}
	
	ImGui::Checkbox("Enable alpha discard", &AlphaDiscardEnabled);
	if(AlphaDiscardOffset) ImGui::DragFloat("Alpha discard offset", &AlphaDiscardOffset, 0.01f, 0.0f, 0.99f);
	ImGui::Combo("Polygon Mode", reinterpret_cast<int*>(&PolygonMode), MatPolygonMode, IM_ARRAYSIZE(MatPolygonMode));
	ImGui::Combo("Culling Mode", reinterpret_cast<int*>(&CullingMode), MatCullingMode, IM_ARRAYSIZE(MatCullingMode));
	ImGui::Combo("Blending Mode", reinterpret_cast<int*>(&BlendingMode), MatBlendingMode, IM_ARRAYSIZE(MatBlendingMode));

	if (ImGui::TreeNode(("Textures##" + std::to_string(std::hash<std::string>{}(Name))).c_str())) {
		{
			ImGui::Spacing();
			ImGui::Text("Albedo: ");
			ImGui::Spacing();
			EditorManager::DragAndDrop(_Textures[TextureType::ALBEDO]);
		}

		{
			ImGui::Spacing();
			ImGui::Separator();
			ImGui::Text("Normal: ");
			ImGui::Spacing();
			EditorManager::DragAndDrop(_Textures[TextureType::NORMAL]);
		}

		
		{
			ImGui::Spacing();
			ImGui::Text("Metallic: ");
			ImGui::Spacing();
			EditorManager::DragAndDrop(_Textures[TextureType::METALLIC]);
		}
		
		{
			ImGui::Spacing();
			ImGui::Text("Roughness: ");
			ImGui::Spacing();
			EditorManager::DragAndDrop(_Textures[TextureType::ROUGHNESS]);
		}

		{
			ImGui::Spacing();
			ImGui::Separator();
			ImGui::Text("AO: ");
			ImGui::Spacing();
			EditorManager::DragAndDrop(_Textures[TextureType::AO]);
		}

		{
			ImGui::Spacing();
			ImGui::Text("Ambient: ");
			ImGui::Spacing();
			EditorManager::DragAndDrop(_Textures[TextureType::AMBIENT]);
		}

		{
			ImGui::Spacing();
			ImGui::Text("Diffuse: ");
			ImGui::Spacing();
			EditorManager::DragAndDrop(_Textures[TextureType::DIFFUSE]);
		}
		
		{
			ImGui::Spacing();
			ImGui::Separator();
			ImGui::Text("Specular: ");
			ImGui::Spacing();
			EditorManager::DragAndDrop(_Textures[TextureType::SPECULAR]);
		}

		{
			ImGui::Spacing();
			ImGui::Separator();
			ImGui::Text("Emissive: ");
			ImGui::Spacing();
			EditorManager::DragAndDrop(_Textures[TextureType::EMISSIVE]);
		}

		
		{
			ImGui::Spacing();
			ImGui::Separator();
			ImGui::Text("Height: ");
			ImGui::Spacing();
			EditorManager::DragAndDrop(_Textures[TextureType::DISPLACEMENT]);
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

void Material::SetTexture(std::shared_ptr<Texture2D> texture)
{
	_Textures[texture->_Type] = texture;
}

void Material::RemoveTexture(TextureType type)
{
	_Textures.erase(type);
}

void Material::SetProgram(std::shared_ptr<GLProgram> program)
{
	_Program = std::move(program);
}

