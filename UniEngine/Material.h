#pragma once
#include "UniEngineAPI.h"
#include "Texture2D.h"
#include "Cubemap.h"
namespace UniEngine {
	class UNIENGINE_API Material
	{
		friend class RenderManager;
		std::vector<Texture2D*> _Texture2Ds;
		std::vector<Cubemap*> _Cubemaps;
		std::vector<GLProgram*> _Programs;
		std::unordered_map<std::string, float> _FloatPropertyList;
		std::unordered_map<std::string, glm::mat4> _Float4x4PropertyList;
	public:
		void SetMaterialProperty(std::string name, float value);
		void SetMaterialProperty(std::string name, glm::mat4 value);
		std::vector<Texture2D*>* Textures2Ds();
		std::vector<Cubemap*>* Cubemaps();
		std::vector<GLProgram*>* Programs();
	};
}

