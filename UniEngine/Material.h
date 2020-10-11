#pragma once
#include "Core.h"
#include "UniEngineAPI.h"
#include "Texture2D.h"
#include "Cubemap.h"
namespace UniEngine {
	struct MaterialFloatProperty
	{
		std::string Name;
		float Value;
		MaterialFloatProperty(std::string name, float value)
		{
			Name = name;
			Value = value;
		}
	};
	struct MaterialMat4Property
	{
		std::string Name;
		glm::mat4 Value;
		MaterialMat4Property(std::string name, glm::mat4 value)
		{
			Name = name;
			Value = value;
		}
	};
	class UNIENGINE_API Material
	{
		friend class RenderManager;
		float _Shininess = 32.0f;

		std::shared_ptr<Texture2D> _DiffuseMap;
		std::shared_ptr<Texture2D> _SpecularMap; 
		std::shared_ptr<Texture2D> _NormalMap;
		std::shared_ptr<Texture2D> _HeightMap;
		
		
		std::shared_ptr<GLProgram> _Program;
		std::vector<MaterialFloatProperty> _FloatPropertyList;
		std::vector<MaterialMat4Property> _Float4x4PropertyList;
	public:
		Material()
		{
			_Shininess = 32.0f;
		}
		void SetShininess(float value);
		void SetMaterialProperty(const std::string& name, float value);
		void SetMaterialProperty(const std::string& name, glm::mat4 value);
		void SetTexture(std::shared_ptr<Texture2D> texture);
		void RemoveTexture(TextureType type);
		void SetProgram(std::shared_ptr<GLProgram> program);
	};
}

