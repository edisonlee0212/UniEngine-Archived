#pragma once
#include "Misc.h"
namespace UniEngine {
	class GLObject
	{
	protected:
		GLuint _ID;
	public:
		GLuint ID() {
			return _ID;
		}
	};
}