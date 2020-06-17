#pragma once
#include "UniEngineAPI.h"
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