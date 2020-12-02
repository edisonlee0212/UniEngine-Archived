#pragma once
#include "UniEngineAPI.h"
namespace UniEngine {
	class UNIENGINE_API GLObject
	{
	protected:
		GLuint _ID = 0;
	public:
		GLuint ID() const
		{
			return _ID;
		}
		virtual ~GLObject() {}
	};
}