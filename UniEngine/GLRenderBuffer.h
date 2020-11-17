#pragma once
#include "GLObject.h"
namespace UniEngine {
	class UNIENGINE_API GLRenderBuffer : public GLObject
	{
	public:
		void Bind();
		static void BindDefault();
		GLRenderBuffer();
		~GLRenderBuffer();
		void AllocateStorage(GLenum internalFormat​, GLsizei width​, GLsizei height);
	};
}

