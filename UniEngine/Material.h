#pragma once
#include "Misc.h"
#include "GLProgram.h"
#include "GLTexture.h"
namespace UniEngine {
	class Material
	{
		std::vector<GLTexture*> _Textures;
		std::vector<GLProgram*> _Programs;
	public:
		std::vector<GLTexture*>* Textures();
		std::vector<GLProgram*>* Programs();
	};
}

