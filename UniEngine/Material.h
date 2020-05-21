#pragma once
#include "Misc.h"
#include "GLProgram.h"
#include "Texture2D.h"
#include "Cubemap.h"
#include "SharedComponent.h"
namespace UniEngine {
	class Material : public SharedComponent
	{
		std::vector<Texture2D*> _Texture2Ds;
		std::vector<Cubemap*> _Cubemaps;
		std::vector<GLProgram*> _Programs;
	public:
		std::vector<Texture2D*>* Textures2Ds();
		std::vector<Cubemap*>* Cubemaps();
		std::vector<GLProgram*>* Programs();
	};
}

