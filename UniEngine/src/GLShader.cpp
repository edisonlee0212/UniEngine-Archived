#include "pch.h"
#include "GLShader.h"
#include "Debug.h"
using namespace UniEngine;

std::string GLShader::GetCode() const
{
	return m_code;
}

bool GLShader::HasCode() const
{
	return m_hasCode;
}

inline UniEngine::GLShader::GLShader(UniEngine::ShaderType type) : m_type(type)
{
	m_id = 0;
	m_code = "";
	m_hasCode = false;
	m_attachable = false;
	switch (m_type)
	{
	case UniEngine::ShaderType::Vertex:
		m_id = glCreateShader(GL_VERTEX_SHADER);
		break;
	case UniEngine::ShaderType::Geometry:
		m_id = glCreateShader(GL_GEOMETRY_SHADER);
		break;
	case UniEngine::ShaderType::Fragment:
		m_id = glCreateShader(GL_FRAGMENT_SHADER);
		break;
	default:
		break;
	}
}

inline UniEngine::GLShader::GLShader(ShaderType type, const std::string& code, bool store) : m_type(type)
{
	if (store) {
		m_code = code;
		m_hasCode = true;
	}
	m_id = 0;
	m_attachable = false;
	switch (m_type)
	{
	case UniEngine::ShaderType::Vertex:
		m_id = glCreateShader(GL_VERTEX_SHADER);
		break;
	case UniEngine::ShaderType::Geometry:
		m_id = glCreateShader(GL_GEOMETRY_SHADER);
		break;
	case UniEngine::ShaderType::Fragment:
		m_id = glCreateShader(GL_FRAGMENT_SHADER);
		break;
	default:
		break;
	}
	Compile(code);
}

inline UniEngine::GLShader::~GLShader()
{
	glDeleteShader(m_id);
}

inline ShaderType UniEngine::GLShader::Type() const
{
	return m_type;
}

inline bool UniEngine::GLShader::Attachable() const
{
	return m_attachable;
}


inline void UniEngine::GLShader::Compile(const std::string& code, bool store)
{
	if (store) {
		m_code = code;
		m_hasCode = true;
	}
	const char* ptr = code.c_str();
	glShaderSource(m_id, 1, &ptr, nullptr);
	glCompileShader(m_id);
	GLint success;
	GLchar infoLog[1024];
	glGetShaderiv(m_id, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(m_id, 1024, NULL, infoLog);
		std::string type;
		switch (m_type)
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
	m_attachable = true;
}

inline void UniEngine::GLShader::Attach(GLuint programID)
{
	if (!m_attachable) {
		if(m_hasCode)Compile(m_code);
		else
		{
			Debug::Log("No code!");
		}
	}
	glAttachShader(programID, m_id);
}

inline void UniEngine::GLShader::Detach(GLuint programID) const
{
	glDetachShader(programID, m_id);
}

