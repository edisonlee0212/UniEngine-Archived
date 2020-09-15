#pragma once
#include "GLObject.h"
#include "GLShader.h"
namespace UniEngine {
	class CORE_API GLProgram : public GLObject
	{
        GLShader* _VertexShader;
        GLShader* _FragmentShader;
        GLShader* _GeometryShader;
    public:
        void Bind() const;
        static void BindDefault();
        GLProgram();
        GLProgram(GLShader* vertexShader, GLShader* fragmentShader, GLShader* geometryShader = nullptr);
        ~GLProgram();
        void Link();
        void Attach(ShaderType type, GLShader* shader);
        void Detach(ShaderType type);
        void SetBool(const std::string& name, bool value) const;
        void SetInt(const std::string& name, int value) const;
        void SetFloat(const std::string& name, float value) const;
        void SetFloat2(const std::string& name, const glm::vec2& value) const;
        void SetFloat2(const std::string& name, float x, float y) const;
        void SetFloat3(const std::string& name, const glm::vec3& value) const;
        void SetFloat3(const std::string& name, float x, float y, float z) const;
        void SetFloat4(const std::string& name, const glm::vec4& value) const;
        void SetFloat4(const std::string& name, float x, float y, float z, float w);
        void SetFloat2x2(const std::string& name, const glm::mat2& mat) const;
        void SetFloat3x3(const std::string& name, const glm::mat3& mat) const;
        void SetFloat4x4(const std::string& name, const glm::mat4& mat) const;
	};
}
