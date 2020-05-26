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
		
	public:
		void SetCode(std::string* code);
		GLShader(ShaderType type);
		GLShader(ShaderType type, std::string* code);
		~GLShader();
		ShaderType Type();
		bool Attachable();
		bool Compileable();
		void Compile();
		void Attach(GLuint programID);
		void Detach(GLuint programID);
	};
}

