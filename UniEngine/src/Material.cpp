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
	
	
	m_name = "New material";
}

void Material::OnGui()
{
	ImGui::Text("Name: %s", m_name.c_str());
	if (ImGui::BeginPopupContextItem(m_name.c_str()))
	{
		if (ImGui::BeginMenu("Rename##Material"))
		{
			static char newName[256];
			ImGui::InputText("New name##Material", newName, 256);
			if (ImGui::Button("Confirm##Material")) m_name = std::string(newName);
			ImGui::EndMenu();
		}
		ImGui::EndPopup();
	}
	ImGui::Separator();
	ImGui::Text("Program:");
	ImGui::SameLine();
	EditorManager::DragAndDrop(_Program);
	ImGui::Separator();
	if(ImGui::TreeNodeEx("PBR##Material", ImGuiTreeNodeFlags_DefaultOpen))
	{
		if (!_Textures[TextureType::ALBEDO])ImGui::ColorEdit3("Albedo##Material", &AlbedoColor.x);
		if (!_Textures[TextureType::METALLIC])ImGui::DragFloat("Metallic##Material", &Metallic, 0.01f, 0.0f, 1.0f);
		if (!_Textures[TextureType::ROUGHNESS])ImGui::DragFloat("Roughness##Material", &Roughness, 0.01f, 0.0f, 1.0f);
		if (!_Textures[TextureType::AO])ImGui::DragFloat("AO##Material", &AmbientOcclusion, 0.01f, 0.0f, 1.0f);
		if(_Textures[TextureType::DISPLACEMENT]) ImGui::DragFloat("DisplacementMapScale##Material", &DisplacementMapScale, 0.01f, -1.0f, 1.0f);
		ImGui::TreePop();
	}
	if (ImGui::TreeNodeEx("Others##Material"))
	{
		ImGui::DragFloat("Shininess##Material", &Shininess, 1.0f, 1.0f, 1024.0f);
		ImGui::Checkbox("Enable alpha discard##Material", &AlphaDiscardEnabled);
		if (AlphaDiscardEnabled) ImGui::DragFloat("Alpha discard offset##Material", &AlphaDiscardOffset, 0.01f, 0.0f, 0.99f);
		ImGui::Combo("Polygon Mode##Material", reinterpret_cast<int*>(&PolygonMode), MatPolygonMode, IM_ARRAYSIZE(MatPolygonMode));
		ImGui::Combo("Culling Mode##Material", reinterpret_cast<int*>(&CullingMode), MatCullingMode, IM_ARRAYSIZE(MatCullingMode));
		ImGui::Combo("Blending Mode##Material", reinterpret_cast<int*>(&BlendingMode), MatBlendingMode, IM_ARRAYSIZE(MatBlendingMode));
		ImGui::TreePop();
	}
	if (ImGui::TreeNode(("Textures##Material" + std::to_string(std::hash<std::string>{}(m_name))).c_str())) {
		{
			ImGui::Spacing();
			ImGui::Separator();
			ImGui::Text("Albedo:");
			ImGui::SameLine();
			EditorManager::DragAndDrop(_Textures[TextureType::ALBEDO]);
			if (_Textures[TextureType::ALBEDO]) _Textures[TextureType::ALBEDO]->SetType(TextureType::ALBEDO);
		}

		{
			ImGui::Spacing();
			ImGui::Separator();
			ImGui::Text("Normal:");
			ImGui::SameLine();
			EditorManager::DragAndDrop(_Textures[TextureType::NORMAL]);
			if (_Textures[TextureType::NORMAL]) _Textures[TextureType::NORMAL]->SetType(TextureType::NORMAL);
		}

		
		{
			ImGui::Spacing();
			ImGui::Separator();
			ImGui::Text("Metallic:");
			ImGui::SameLine();
			EditorManager::DragAndDrop(_Textures[TextureType::METALLIC]);
			if (_Textures[TextureType::METALLIC]) _Textures[TextureType::METALLIC]->SetType(TextureType::METALLIC);
		}
		
		{
			ImGui::Spacing();
			ImGui::Separator();
			ImGui::Text("Roughness:");
			ImGui::SameLine();
			EditorManager::DragAndDrop(_Textures[TextureType::ROUGHNESS]);
			if (_Textures[TextureType::ROUGHNESS]) _Textures[TextureType::ROUGHNESS]->SetType(TextureType::ROUGHNESS);
		}

		{
			ImGui::Spacing();
			ImGui::Separator();
			ImGui::Text("AO:");
			ImGui::SameLine();
			EditorManager::DragAndDrop(_Textures[TextureType::AO]);
			if (_Textures[TextureType::AO]) _Textures[TextureType::AO]->SetType(TextureType::AO);
		}

		{
			ImGui::Spacing();
			ImGui::Separator();
			ImGui::Text("Ambient:");
			ImGui::SameLine();
			EditorManager::DragAndDrop(_Textures[TextureType::AMBIENT]);
			if (_Textures[TextureType::AMBIENT]) _Textures[TextureType::AMBIENT]->SetType(TextureType::AMBIENT);
		}

		{
			ImGui::Spacing();
			ImGui::Separator();
			ImGui::Text("Diffuse:");
			ImGui::SameLine();
			EditorManager::DragAndDrop(_Textures[TextureType::DIFFUSE]);
			if (_Textures[TextureType::DIFFUSE]) _Textures[TextureType::DIFFUSE]->SetType(TextureType::DIFFUSE);
		}
		
		{
			ImGui::Spacing();
			ImGui::Separator();
			ImGui::Text("Specular:");
			ImGui::SameLine();
			EditorManager::DragAndDrop(_Textures[TextureType::SPECULAR]);
			if (_Textures[TextureType::SPECULAR]) _Textures[TextureType::SPECULAR]->SetType(TextureType::SPECULAR);
		}

		{
			ImGui::Spacing();
			ImGui::Separator();
			ImGui::Text("Emissive:");
			ImGui::SameLine();
			EditorManager::DragAndDrop(_Textures[TextureType::EMISSIVE]);
			if (_Textures[TextureType::EMISSIVE]) _Textures[TextureType::EMISSIVE]->SetType(TextureType::EMISSIVE);
		}

		
		{
			ImGui::Spacing();
			ImGui::Separator();
			ImGui::Text("Height:");
			ImGui::SameLine();
			EditorManager::DragAndDrop(_Textures[TextureType::DISPLACEMENT]);
			if (_Textures[TextureType::DISPLACEMENT]) _Textures[TextureType::DISPLACEMENT]->SetType(TextureType::DISPLACEMENT);
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

