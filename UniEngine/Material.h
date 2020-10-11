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
		std::vector<Texture2D*> _Texture2Ds;
		std::vector<Cubemap*> _Cubemaps;
		std::vector<GLProgram*> _Programs;
		std::vector<MaterialFloatProperty> _FloatPropertyList;
		std::vector<MaterialMat4Property> _Float4x4PropertyList;
	public:
		Material()
		{
			_Shininess = 32.0f;
		}
		void SetShininess(float value);
		void SetMaterialProperty(std::string name, float value);
		void SetMaterialProperty(std::string name, glm::mat4 value);
		std::vector<Texture2D*>* Textures2Ds();
		std::vector<Cubemap*>* Cubemaps();
		std::vector<GLProgram*>* Programs();
	};
}

