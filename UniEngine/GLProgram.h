#pragma once
#include "Misc.h"
#include "Math.h"
#include "GLObject.h"
#include "GLShader.h"
namespace UniEngine {
	class GLProgram : public GLObject
	{
        GLuint _ID;
        GLShader* _VertexShader;
        GLShader* _FragmentShader;
        GLShader* _GeometryShader;
    public:
        GLProgram();
        ~GLProgram();
        void Use();
        void Link();
        void Attach(ShaderType type, GLShader* shader);
        void Detach(ShaderType type);
        void SetBool(const std::string& name, bool value) const;
        void SetInt(const std::string& name, int value) const;
        void SetFloat(const std::string& name, float value) const;
        void SetFloat2(const std::string& name, const float2& value) const;
        void SetFloat2(const std::string& name, float x, float y) const;
        void SetFloat3(const std::string& name, const float3& value) const;
        void SetFloat3(const std::string& name, float x, float y, float z) const;
        void SetFloat4(const std::string& name, const float4& value) const;
        void SetFloat4(const std::string& name, float x, float y, float z, float w);
        void SetFloat2x2(const std::string& name, const float2x2& mat) const;
        void SetFloat3x3(const std::string& name, const float3x3& mat) const;
        void SetFloat4x4(const std::string& name, const float4x4& mat) const;
	};
}
