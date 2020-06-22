#pragma once
#include "GLObject.h"
namespace UniEngine {
	class CORE_API GLRenderBuffer : public GLObject
	{
	public:
		GLRenderBuffer();
		~GLRenderBuffer();
		void AllocateStorage(GLenum internalformat​, GLsizei width​, GLsizei height);
		void Attach(GLenum attachment, GLuint frameBufferID);
		//void Detach();
	};
}

