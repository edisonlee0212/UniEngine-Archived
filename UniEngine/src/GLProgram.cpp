#include "pch.h"
#include "GLProgram.h"
#include "Debug.h"
#include "GLShader.h"
using namespace UniEngine;

GLuint GLProgram::m_currentBoundGLProgram = 0;

inline void UniEngine::GLProgram::Bind() const
{
	if(m_currentBoundGLProgram == m_id) return;
	glUseProgram(m_id);
	m_currentBoundGLProgram = m_id;
}

inline void UniEngine::GLProgram::BindDefault()
{
	glUseProgram(0);
	m_currentBoundGLProgram = 0;
}

inline UniEngine::GLProgram::GLProgram()
{
	m_name = "New Program";
	m_id = glCreateProgram();
}

GLProgram::GLProgram(const std::shared_ptr<GLShader>& shader1, const std::shared_ptr<GLShader>& shader2)
{
	m_name = "New Program";
	m_id = glCreateProgram();
	Attach(shader1);
	Attach(shader2);
	m_shaders.push_back(shader1);
	m_shaders.push_back(shader2);
	Link();
}

inline UniEngine::GLProgram::GLProgram(const std::shared_ptr<GLShader>& shader1, const std::shared_ptr<GLShader>& shader2, const std::shared_ptr<GLShader>& shader3)
{
	m_name = "New Program";
	m_id = glCreateProgram();
	Attach(shader1);
	Attach(shader2);
	Attach(shader3);
	m_shaders.push_back(shader1);
	m_shaders.push_back(shader2);
	m_shaders.push_back(shader3);
	Link();
}

inline UniEngine::GLProgram::~GLProgram()
{
	BindDefault();
	glDeleteProgram(m_id);
}

std::shared_ptr<GLShader> GLProgram::GetShader(ShaderType type)
{
	for (const auto& i : m_shaders)
	{
		if (i->Type() == type) return i;
	}
	return nullptr;
}

bool GLProgram::HasShader(ShaderType type)
{
	for(const auto& i : m_shaders)
	{
		if(i->Type() == type) return true;
	}
	return false;
}


inline void UniEngine::GLProgram::Link() const
{
	glLinkProgram(m_id);
	GLint status = 0;
	glGetProgramiv(m_id, GL_LINK_STATUS, &status);
	if (!status) {
		GLchar infoLog[1024];
		const std::string type = "PROGRAM";
		glGetProgramInfoLog(m_id, 1024, nullptr, infoLog);
		Debug::Error("ERROR::PROGRAM_LINKING_ERROR of type: " + type + "\n" + infoLog + "\n -- --------------------------------------------------- -- ");
	}
}

inline void UniEngine::GLProgram::Attach(std::shared_ptr<GLShader> shader)
{
	const auto type = shader->Type();
	if (HasShader(type)) Detach(type);
	m_shaders.push_back(shader);
	shader->Attach(m_id);
}

inline void UniEngine::GLProgram::Detach(ShaderType type)
{
	for (int index = 0; index < m_shaders.size(); index++)
	{
		auto& i = m_shaders[index];
		if (i->Type() == type) {
			i->Detach(m_id);
			m_shaders.erase(m_shaders.begin() + index);
			break;
		}
	}
}

inline void GLProgram::SetBool(const std::string& name, bool value) const
{
	Bind();
	glUniform1i(glGetUniformLocation(m_id, name.c_str()), static_cast<int>(value));
}
inline void GLProgram::SetInt(const std::string& name, int value) const
{
	Bind();
	glUniform1i(glGetUniformLocation(m_id, name.c_str()), value);
}
inline void GLProgram::SetFloat(const std::string& name, float value) const
{
	Bind();
	glUniform1f(glGetUniformLocation(m_id, name.c_str()), value);
}
inline void GLProgram::SetFloat2(const std::string& name, const glm::vec2& value) const
{
	Bind();
	glUniform2fv(glGetUniformLocation(m_id, name.c_str()), 1, &value[0]);
}
inline void GLProgram::SetFloat2(const std::string& name, float x, float y) const
{
	Bind();
	glUniform2f(glGetUniformLocation(m_id, name.c_str()), x, y);
}
inline void GLProgram::SetFloat3(const std::string& name, const glm::vec3& value) const
{
	Bind();
	glUniform3fv(glGetUniformLocation(m_id, name.c_str()), 1, &value[0]);
}
inline void GLProgram::SetFloat3(const std::string& name, float x, float y, float z) const
{
	Bind();
	glUniform3f(glGetUniformLocation(m_id, name.c_str()), x, y, z);
}
inline void GLProgram::SetFloat4(const std::string& name, const glm::vec4& value) const
{
	Bind();
	glUniform4fv(glGetUniformLocation(m_id, name.c_str()), 1, &value[0]);
}
inline void GLProgram::SetFloat4(const std::string& name, float x, float y, float z, float w) const
{
	Bind();
	glUniform4f(glGetUniformLocation(m_id, name.c_str()), x, y, z, w);
}
inline void GLProgram::SetFloat2x2(const std::string& name, const glm::mat2& mat) const
{
	Bind();
	glUniformMatrix2fv(glGetUniformLocation(m_id, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}
inline void GLProgram::SetFloat3x3(const std::string& name, const glm::mat3& mat) const
{
	Bind();
	glUniformMatrix3fv(glGetUniformLocation(m_id, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}
inline void GLProgram::SetFloat4x4(const std::string& name, const glm::mat4& mat) const
{
	Bind();
	glUniformMatrix4fv(glGetUniformLocation(m_id, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}