#pragma once
#include "GLObject.h"
namespace UniEngine {
	enum class UNIENGINE_API ShaderType {
		Vertex,
		Geometry,
		Fragment
	};
	class UNIENGINE_API GLShader : public GLObject
	{
		std::string m_code;
		bool m_hasCode = false;
		ShaderType m_type;
		bool m_attachable;
	public:
		std::string GetCode() const;
		bool HasCode() const;
		GLShader(ShaderType type);
		GLShader(ShaderType type, const std::string& code, bool store = false);
		~GLShader() override;
		ShaderType Type() const;
		bool Attachable() const;
		void Compile(const std::string& code, bool store = false);
		void Attach(GLuint programID);
		void Detach(GLuint programID) const;
	};
}

