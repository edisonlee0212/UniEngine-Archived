#include "pch.h"
#include "GLShader.h"
#include "Debug.h"
using namespace UniEngine;

inline void GLShader::SetCode(std::string* code)
{
	_Code = code;
	_Compileable = true;
	Compile();
}

inline GLShader::GLShader(ShaderType type) : _Type(type)
{
	_Code = nullptr;
	_ID = 0;
	_Attachable = false;
	_Compileable = false;
	switch (_Type)
	{
	case ShaderType::Vertex:
		_ID = glCreateShader(GL_VERTEX_SHADER);
		break;
	case ShaderType::Geometry:
		_ID = glCreateShader(GL_GEOMETRY_SHADER);
		break;
	case ShaderType::Fragment:
		_ID = glCreateShader(GL_FRAGMENT_SHADER);
		break;
	default:
		break;
	}
}

inline GLShader::GLShader(ShaderType type, std::string* code) : _Type(type)
{
	_Code = code;
	_ID = 0;
	_Attachable = false;
	_Compileable = false;
	switch (_Type)
	{
	case ShaderType::Vertex:
		_ID = glCreateShader(GL_VERTEX_SHADER);
		break;
	case ShaderType::Geometry:
		_ID = glCreateShader(GL_GEOMETRY_SHADER);
		break;
	case ShaderType::Fragment:
		_ID = glCreateShader(GL_FRAGMENT_SHADER);
		break;
	default:
		break;
	}
	SetCode(_Code);
}

inline GLShader::~GLShader()
{
	glDeleteShader(_ID);
}

inline ShaderType GLShader::Type()
{
	return _Type;
}

inline bool GLShader::Attachable()
{
	return _Attachable;
}

inline bool GLShader::Compileable()
{
	return _Compileable;
}

inline void GLShader::Compile()
{
	const char* code = _Code->c_str();
	glShaderSource(_ID, 1, &code, nullptr);
	glCompileShader(_ID);
	GLint success;
	GLchar infoLog[1024];
	glGetShaderiv(_ID, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(_ID, 1024, nullptr, infoLog);
		std::string type;
		switch (_Type)
		{
		case ShaderType::Vertex:
			type = "Vertex";
			break;
		case ShaderType::Geometry:
			type = "Geometry";
			break;
		case ShaderType::Fragment:
			type = "Fragment";
			break;
		default:
			break;
		}
		Debug::Error(
			"ERROR::SHADER_COMPILATION_ERROR of type: " + type + "\n" + infoLog +
			"\n -- --------------------------------------------------- -- ");
	}
	_Attachable = true;
}

inline void GLShader::Attach(GLuint programID)
{
	if (!_Compileable)
	{
		Debug::Error("Error");
		return;
	}
	if (!_Attachable) Compile();
	glAttachShader(programID, _ID);
}

inline void GLShader::Detach(GLuint programID)
{
	glDetachShader(programID, _ID);
}
