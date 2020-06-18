#pragma once
#include "CoreAPI.h"
namespace UniEngine {
	class CORE_API GLObject
	{
	protected:
		GLuint _ID;
	public:
		GLuint ID() {
			return _ID;
		}
	};
}