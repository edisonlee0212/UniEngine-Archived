#include "pch.h"
#include "GLProgram.h"
#include "Debug.h"
#include "GLShader.h"
using namespace UniEngine;


inline void UniEngine::GLProgram::Bind() const
{
	glUseProgram(_ID);
}

inline void UniEngine::GLProgram::BindDefault()
{
	glUseProgram(0);
}

inline UniEngine::GLProgram::GLProgram()
{
	Name = "New Program";
	_ID = glCreateProgram();
}

GLProgram::GLProgram(const std::shared_ptr<GLShader>& shader1, const std::shared_ptr<GLShader>& shader2)
{
	Name = "New Program";
	_ID = glCreateProgram();
	Attach(shader1);
	Attach(shader2);
	_Shaders.push_back(shader1);
	_Shaders.push_back(shader2);
	Link();
}

inline UniEngine::GLProgram::GLProgram(const std::shared_ptr<GLShader>& shader1, const std::shared_ptr<GLShader>& shader2, const std::shared_ptr<GLShader>& shader3)
{
	Name = "New Program";
	_ID = glCreateProgram();
	Attach(shader1);
	Attach(shader2);
	Attach(shader3);
	_Shaders.push_back(shader1);
	_Shaders.push_back(shader2);
	_Shaders.push_back(shader3);
	Link();
}

inline UniEngine::GLProgram::~GLProgram()
{
	BindDefault();
	glDeleteProgram(_ID);
}

std::shared_ptr<GLShader> GLProgram::GetShader(ShaderType type)
{
	for (const auto& i : _Shaders)
	{
		if (i->Type() == type) return i;
	}
	return nullptr;
}

bool GLProgram::HasShader(ShaderType type)
{
	for(const auto& i : _Shaders)
	{
		if(i->Type() == type) return true;
	}
	return false;
}


inline void UniEngine::GLProgram::Link() const
{
	glLinkProgram(_ID);
	GLint status = 0;
	glGetProgramiv(_ID, GL_LINK_STATUS, &status);
	if (!status) {
		GLchar infoLog[1024];
		const std::string type = "PROGRAM";
		glGetProgramInfoLog(_ID, 1024, nullptr, infoLog);
		Debug::Error("ERROR::PROGRAM_LINKING_ERROR of type: " + type + "\n" + infoLog + "\n -- --------------------------------------------------- -- ");
	}
}

inline void UniEngine::GLProgram::Attach(std::shared_ptr<GLShader> shader)
{
	const auto type = shader->Type();
	if (HasShader(type)) Detach(type);
	_Shaders.push_back(shader);
	shader->Attach(_ID);
}

inline void UniEngine::GLProgram::Detach(ShaderType type)
{
	for (int index = 0; index < _Shaders.size(); index++)
	{
		auto& i = _Shaders[index];
		if (i->Type() == type) {
			i->Detach(_ID);
			_Shaders.erase(_Shaders.begin() + index);
			break;
		}
	}
}

inline void GLProgram::SetBool(const std::string& name, bool value) const
{
	Bind();
	glUniform1i(glGetUniformLocation(_ID, name.c_str()), static_cast<int>(value));
}
inline void GLProgram::SetInt(const std::string& name, int value) const
{
	Bind();
	glUniform1i(glGetUniformLocation(_ID, name.c_str()), value);
}
inline void GLProgram::SetFloat(const std::string& name, float value) const
{
	Bind();
	glUniform1f(glGetUniformLocation(_ID, name.c_str()), value);
}
inline void GLProgram::SetFloat2(const std::string& name, const glm::vec2& value) const
{
	Bind();
	glUniform2fv(glGetUniformLocation(_ID, name.c_str()), 1, &value[0]);
}
inline void GLProgram::SetFloat2(const std::string& name, float x, float y) const
{
	Bind();
	glUniform2f(glGetUniformLocation(_ID, name.c_str()), x, y);
}
inline void GLProgram::SetFloat3(const std::string& name, const glm::vec3& value) const
{
	Bind();
	glUniform3fv(glGetUniformLocation(_ID, name.c_str()), 1, &value[0]);
}
inline void GLProgram::SetFloat3(const std::string& name, float x, float y, float z) const
{
	Bind();
	glUniform3f(glGetUniformLocation(_ID, name.c_str()), x, y, z);
}
inline void GLProgram::SetFloat4(const std::string& name, const glm::vec4& value) const
{
	Bind();
	glUniform4fv(glGetUniformLocation(_ID, name.c_str()), 1, &value[0]);
}
inline void GLProgram::SetFloat4(const std::string& name, float x, float y, float z, float w) const
{
	Bind();
	glUniform4f(glGetUniformLocation(_ID, name.c_str()), x, y, z, w);
}
inline void GLProgram::SetFloat2x2(const std::string& name, const glm::mat2& mat) const
{
	Bind();
	glUniformMatrix2fv(glGetUniformLocation(_ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}
inline void GLProgram::SetFloat3x3(const std::string& name, const glm::mat3& mat) const
{
	Bind();
	glUniformMatrix3fv(glGetUniformLocation(_ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}
inline void GLProgram::SetFloat4x4(const std::string& name, const glm::mat4& mat) const
{
	Bind();
	glUniformMatrix4fv(glGetUniformLocation(_ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}