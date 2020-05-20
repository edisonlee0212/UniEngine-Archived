#pragma once
#include "Misc.h"
#include "GLObject.h"
namespace UniEngine {
	class GLRenderBuffer : public GLObject
	{
	public:
		GLRenderBuffer();
		~GLRenderBuffer();
		void AllocateStorage(GLenum internalformat​, GLsizei width​, GLsizei height);
		void Attach(GLenum attachment, GLuint frameBufferID);
		//void Detach();
	};
}

