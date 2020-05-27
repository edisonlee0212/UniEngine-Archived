#pragma once
#include "Misc.h"
#include "Core.h"
namespace UniEngine {
	class Cubemap
	{
		GLTexture* texture0;
		GLTexture* texture1;
		GLTexture* texture2;
		GLTexture* texture3;
		GLTexture* texture4;
		GLTexture* texture5;
	public:
		Cubemap();
	};
}

