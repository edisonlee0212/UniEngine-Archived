#pragma once
#include "Core.h"
#include "UniEngineAPI.h"
#include "Texture2D.h"
#include "Cubemap.h"
namespace UniEngine {
	enum class UNIENGINE_API MaterialPolygonMode
	{
		FILL,
		LINE,
		POINT
	};

	enum class UNIENGINE_API MaterialCullingMode {
		BACK,
		FRONT,
		OFF
	};

	enum class UNIENGINE_API MaterialBlendingMode {
		OFF,
		ONE_MINUS_SRC_ALPHA,
	};
	
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
		
		std::shared_ptr<Texture2D> _DiffuseMap;
		std::shared_ptr<Texture2D> _SpecularMap; 
		std::shared_ptr<Texture2D> _NormalMap;
		std::shared_ptr<Texture2D> _DisplacementMap;
		
		
		std::shared_ptr<GLProgram> _Program;
		std::vector<MaterialFloatProperty> _FloatPropertyList;
		std::vector<MaterialMat4Property> _Float4x4PropertyList;
	public:
		MaterialPolygonMode PolygonMode = MaterialPolygonMode::FILL;
		MaterialCullingMode CullingMode = MaterialCullingMode::BACK;
		MaterialBlendingMode BlendingMode = MaterialBlendingMode::OFF;
		float Shininess = 32.0f;
		bool TransparentDiscard = false;
		float TransparentDiscardLimit = 0.99f;
		std::string Name;
		Material();
		void OnGui();
		void SetMaterialProperty(const std::string& name, float value);
		void SetMaterialProperty(const std::string& name, glm::mat4 value);
		void SetTexture(std::shared_ptr<Texture2D> texture, TextureType type);
		void RemoveTexture(TextureType type);
		void SetProgram(std::shared_ptr<GLProgram> program);
	};
}

