#include "pch.h"
#include "GLShader.h"
#include "Debug.h"
using namespace UniEngine;

std::string GLShader::GetCode() const
{
	return _Code;
}

bool GLShader::HasCode() const
{
	return _HasCode;
}

inline UniEngine::GLShader::GLShader(UniEngine::ShaderType type) : _Type(type)
{
	_ID = 0;
	_Code = "";
	_HasCode = false;
	_Attachable = false;
	switch (_Type)
	{
	case UniEngine::ShaderType::Vertex:
		_ID = glCreateShader(GL_VERTEX_SHADER);
		break;
	case UniEngine::ShaderType::Geometry:
		_ID = glCreateShader(GL_GEOMETRY_SHADER);
		break;
	case UniEngine::ShaderType::Fragment:
		_ID = glCreateShader(GL_FRAGMENT_SHADER);
		break;
	default:
		break;
	}
}

inline UniEngine::GLShader::GLShader(ShaderType type, const std::string& code, bool store) : _Type(type)
{
	if (store) {
		_Code = code;
		_HasCode = true;
	}
	_ID = 0;
	_Attachable = false;
	switch (_Type)
	{
	case UniEngine::ShaderType::Vertex:
		_ID = glCreateShader(GL_VERTEX_SHADER);
		break;
	case UniEngine::ShaderType::Geometry:
		_ID = glCreateShader(GL_GEOMETRY_SHADER);
		break;
	case UniEngine::ShaderType::Fragment:
		_ID = glCreateShader(GL_FRAGMENT_SHADER);
		break;
	default:
		break;
	}
	Compile(code);
}

inline UniEngine::GLShader::~GLShader()
{
	glDeleteShader(_ID);
}

inline ShaderType UniEngine::GLShader::Type() const
{
	return _Type;
}

inline bool UniEngine::GLShader::Attachable() const
{
	return _Attachable;
}


inline void UniEngine::GLShader::Compile(const std::string& code, bool store)
{
	if (store) {
		_Code = code;
		_HasCode = true;
	}
	const char* ptr = code.c_str();
	glShaderSource(_ID, 1, &ptr, nullptr);
	glCompileShader(_ID);
	GLint success;
	GLchar infoLog[1024];
	glGetShaderiv(_ID, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(_ID, 1024, NULL, infoLog);
		std::string type;
		switch (_Type)
		{
		case UniEngine::ShaderType::Vertex:
			type = "Vertex";
			break;
		case UniEngine::ShaderType::Geometry:
			type = "Geometry";
			break;
		case UniEngine::ShaderType::Fragment:
			type = "Fragment";
			break;
		default:
			break;
		}
		Debug::Error("ERROR::SHADER_COMPILATION_ERROR of type: " + type + "\n" + infoLog + "\n -- --------------------------------------------------- -- ");
	}
	_Attachable = true;
}

inline void UniEngine::GLShader::Attach(GLuint programID)
{
	if (!_Attachable) {
		if(_HasCode)Compile(_Code);
		else
		{
			Debug::Log("No code!");
		}
	}
	glAttachShader(programID, _ID);
}

inline void UniEngine::GLShader::Detach(GLuint programID) const
{
	glDetachShader(programID, _ID);
}

