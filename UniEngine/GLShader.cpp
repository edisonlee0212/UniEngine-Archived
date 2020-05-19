#include "Core.h"
using namespace UniEngine;

void UniEngine::GLShader::SetCode(std::string* code)
{
	_Code = code;
	_Compileable = true;
}

UniEngine::GLShader::GLShader(UniEngine::ShaderType type) : _Type(type)
{
	_Code = nullptr;
	_ID = 0;
	_Attachable = false;
	_Compileable = false;
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

UniEngine::GLShader::~GLShader()
{
	glDeleteShader(_ID);
}

ShaderType UniEngine::GLShader::Type()
{
	return _Type;
}

bool UniEngine::GLShader::Attachable()
{
	return _Attachable;
}

bool UniEngine::GLShader::Compileable()
{
	return _Compileable;
}

void UniEngine::GLShader::Compile()
{
	const char* code = _Code->c_str();
	glShaderSource(_ID, 1, &code, nullptr);
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

void UniEngine::GLShader::Attach(GLuint programID)
{
	if (!_Compileable) {
		Debug::Error("Error");
		return;
	}
	if (!_Attachable) Compile();
	glAttachShader(programID, _ID);
}

void UniEngine::GLShader::Detach(GLuint programID)
{
	glDetachShader(programID, _ID);
}

