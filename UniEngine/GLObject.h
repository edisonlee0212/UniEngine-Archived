#pragma once
#include "UniEngineAPI.h"
namespace UniEngine {
	class UNIENGINE_API GLObject
	{
	protected:
		GLuint _ID;
	public:
		GLuint ID() {
			return _ID;
		}
	};
}