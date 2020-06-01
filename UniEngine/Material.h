#pragma once
#include "Misc.h"
#include "Core.h"
#include "Texture2D.h"
#include "Cubemap.h"
namespace UniEngine {
	class Material
	{
		std::vector<Texture2D*> _Texture2Ds;
		std::vector<Cubemap*> _Cubemaps;
		std::vector<GLProgram*> _Programs;
		float _Shininess;
		float _Reflectivity;
		float _Opacity;
		float _TransparencyFactor;
		float _BumpScaling;
	public:
		float Shininess();
		void SetShininess(float value);

		std::vector<Texture2D*>* Textures2Ds();
		std::vector<Cubemap*>* Cubemaps();
		std::vector<GLProgram*>* Programs();
	};
}

