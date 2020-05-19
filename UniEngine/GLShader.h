#pragma once
#include "Misc.h"
#include "Math.h"
#include "GLObject.h"
namespace UniEngine {
	enum class ShaderType {
		Vertex,
		Geometry,
		Fragment
	};
	class GLShader : public GLObject
	{
		std::string* _Code;
		GLuint _ID;
		ShaderType _Type;
		bool _Attachable;
		bool _Compileable;
		void SetCode(std::string* code);
	public:
		GLShader(ShaderType type);
		~GLShader();
		ShaderType Type();
		bool Attachable();
		bool Compileable();
		void Compile();
		void Attach(GLuint programID);
		void Detach(GLuint programID);
	};
}

