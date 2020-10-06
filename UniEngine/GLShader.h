#pragma once
#include "GLObject.h"
namespace UniEngine {
	enum class UNIENGINE_API ShaderType {
		Vertex,
		Geometry,
		Fragment
	};
	class UNIENGINE_API GLShader : public GLObject
	{
		std::string* _Code;
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

