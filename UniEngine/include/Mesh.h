#pragma once
#include "Core.h"
#include "EditorManager.h"
#include "UniEngineAPI.h"
namespace UniEngine {
	struct UNIENGINE_API Vertex {
		glm::vec3 m_position;
		glm::vec3 m_normal;
		glm::vec3 m_tangent;
		glm::vec4 m_color;
		glm::vec2 m_texCoords0;
		glm::vec2 m_texCoords1;
		glm::vec2 m_texCoords2;
		glm::vec2 m_texCoords3;
		glm::vec2 m_texCoords4;
		glm::vec2 m_texCoords5;
		glm::vec2 m_texCoords6;
		glm::vec2 m_texCoords7;
	};
	enum class UNIENGINE_API VertexAttribute
	{
		Position = 1,
		Normal = 1 << 1,//2
		Tangent = 1 << 2,
		Color = 1 << 3,//8
		TexCoord0 = 1 << 4,//16
		TexCoord1 = 1 << 5,
		TexCoord2 = 1 << 6,
		TexCoord3 = 1 << 7,
		TexCoord4 = 1 << 8,
		TexCoord5 = 1 << 9,
		TexCoord6 = 1 << 10,
		TexCoord7 = 1 << 11
	};

	class UNIENGINE_API Mesh : public ResourceBehaviour
	{
		std::shared_ptr<GLVAO> m_vao;
		size_t m_verticesSize;
		size_t m_triangleSize;
		unsigned m_mask;
		Bound m_bound;
		friend class MeshRenderer;
		friend class Particles;
		friend class EditorManager;
		bool m_localStored;
		std::vector<Vertex> m_vertices;
		std::vector<glm::uvec3> m_indices;
	public:
		void OnGui();
		[[nodiscard]] glm::vec3 GetCenter() const;
		[[nodiscard]] Bound GetBound() const;
		Mesh();
		void SetVertices(const unsigned& mask, std::vector<Vertex>& vertices, std::vector<unsigned>& indices, const bool& store = true);
		void SetVertices(const unsigned& mask, std::vector<Vertex>& vertices, std::vector<glm::uvec3>& triangles, const bool& store = true);
		[[nodiscard]] size_t GetVerticesAmount() const;
		[[nodiscard]] size_t GetTriangleAmount() const;
		void RecalculateNormal(std::vector<Vertex>& vertices, std::vector<glm::uvec3>& indices) const;
		void RecalculateTangent(std::vector<Vertex>& vertices, std::vector<glm::uvec3>& indices) const;
		[[nodiscard]] std::shared_ptr<GLVAO> Vao() const;
		void Enable() const;
		std::vector<Vertex>& GetVerticesUnsafe();
		std::vector<glm::uvec3>& GetIndicesUnsafe();
	};
}
