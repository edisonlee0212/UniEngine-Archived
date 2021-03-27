#pragma once
#include "ResourceBehaviour.h"
#include "GLObject.h"
#include "GLShader.h"
namespace UniEngine {
	class UNIENGINE_API GLProgram : public GLObject, public ResourceBehaviour
	{
        friend class ResourceManager;
        friend class GLCore;
        std::vector<std::shared_ptr<GLShader>> m_shaders;
        static GLuint m_currentBoundGLProgram;
    public:
        GLProgram(const std::shared_ptr<GLShader>& shader1, const std::shared_ptr<GLShader>& shader2);
        GLProgram(const std::shared_ptr<GLShader>& shader1, const std::shared_ptr<GLShader>& shader2, const std::shared_ptr<GLShader>& shader3);
        GLProgram();
        ~GLProgram() override;
        std::shared_ptr<GLShader> GetShader(ShaderType type);
        bool HasShader(ShaderType type);
        void Bind() const;
        static void BindDefault();
        void Link() const;
        void Attach(std::shared_ptr<GLShader> shader);
        void Detach(ShaderType type);
        void SetBool(const std::string& name, bool value) const;
        void SetInt(const std::string& name, int value) const;
        void SetFloat(const std::string& name, float value) const;
        void SetFloat2(const std::string& name, const glm::vec2& value) const;
        void SetFloat2(const std::string& name, float x, float y) const;
        void SetFloat3(const std::string& name, const glm::vec3& value) const;
        void SetFloat3(const std::string& name, float x, float y, float z) const;
        void SetFloat4(const std::string& name, const glm::vec4& value) const;
        void SetFloat4(const std::string& name, float x, float y, float z, float w) const;
        void SetFloat2x2(const std::string& name, const glm::mat2& mat) const;
        void SetFloat3x3(const std::string& name, const glm::mat3& mat) const;
        void SetFloat4x4(const std::string& name, const glm::mat4& mat) const;
	};
}
