#include "Core.h"
using namespace UniEngine;

UniEngine::GLProgram::GLProgram()
{
    _ID = glCreateProgram();
}

UniEngine::GLProgram::~GLProgram()
{
    glDeleteProgram(_ID);
}

void UniEngine::GLProgram::Use()
{
    glUseProgram(_ID);
}

void UniEngine::GLProgram::Link()
{
    _VertexShader->Attach(_ID);
    _FragmentShader->Attach(_ID);
    if (_GeometryShader) _GeometryShader->Attach(_ID);
    glLinkProgram(_ID);
    GLint success;
    GLchar infoLog[1024];
    glGetShaderiv(_ID, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(_ID, 1024, NULL, infoLog);
        std::string type = "PROGRAM";
        Debug::Error("ERROR::SHADER_COMPILATION_ERROR of type: " + type + "\n" + infoLog + "\n");
    }
}

void UniEngine::GLProgram::Attach(ShaderType type)
{
    switch (type)
    {
    case UniEngine::ShaderType::Vertex:
        _VertexShader->Attach(_ID);
        break;
    case UniEngine::ShaderType::Geometry:
        _GeometryShader->Attach(_ID);
        break;
    case UniEngine::ShaderType::Fragment:
        _FragmentShader->Attach(_ID);
        break;
    default:
        break;
    }
}

void UniEngine::GLProgram::Detach(ShaderType type)
{
    switch (type)
    {
    case UniEngine::ShaderType::Vertex:
        _VertexShader->Detach(_ID);
        break;
    case UniEngine::ShaderType::Geometry:
        _GeometryShader->Detach(_ID);
        break;
    case UniEngine::ShaderType::Fragment:
        _FragmentShader->Detach(_ID);
        break;
    }
}

void GLProgram::SetBool(const std::string& name, bool value) const
{
    glUniform1i(glGetUniformLocation(_ID, name.c_str()), (int)value);
}
void GLProgram::SetInt(const std::string& name, int value) const
{
    glUniform1i(glGetUniformLocation(_ID, name.c_str()), value);
}
void GLProgram::SetFloat(const std::string& name, float value) const
{
    glUniform1f(glGetUniformLocation(_ID, name.c_str()), value);
}
void GLProgram::SetFloat2(const std::string& name, const float2& value) const
{
    glUniform2fv(glGetUniformLocation(_ID, name.c_str()), 1, &value.x);
}
void GLProgram::SetFloat2(const std::string& name, float x, float y) const
{
    glUniform2f(glGetUniformLocation(_ID, name.c_str()), x, y);
}
void GLProgram::SetFloat3(const std::string& name, const float3& value) const
{
    glUniform3fv(glGetUniformLocation(_ID, name.c_str()), 1, &value.x);
}
void GLProgram::SetFloat3(const std::string& name, float x, float y, float z) const
{
    glUniform3f(glGetUniformLocation(_ID, name.c_str()), x, y, z);
}
void GLProgram::SetFloat4(const std::string& name, const float4& value) const
{
    glUniform4fv(glGetUniformLocation(_ID, name.c_str()), 1, &value.x);
}
void GLProgram::SetFloat4(const std::string& name, float x, float y, float z, float w)
{
    glUniform4f(glGetUniformLocation(_ID, name.c_str()), x, y, z, w);
}
void GLProgram::SetFloat2x2(const std::string& name, const float2x2& mat) const
{
    glUniformMatrix2fv(glGetUniformLocation(_ID, name.c_str()), 1, GL_FALSE, &mat.c0.x);
}
void GLProgram::SetFloat3x3(const std::string& name, const float3x3& mat) const
{
    glUniformMatrix3fv(glGetUniformLocation(_ID, name.c_str()), 1, GL_FALSE, &mat.c0.x);
}
void GLProgram::SetFloat4x4(const std::string& name, const float4x4& mat) const
{
    glUniformMatrix4fv(glGetUniformLocation(_ID, name.c_str()), 1, GL_FALSE, &mat.c0.x);
}