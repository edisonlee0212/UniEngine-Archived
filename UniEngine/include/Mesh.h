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
		size_t m_indicesSize;
		unsigned m_mask;
		Bound m_bound;
		friend class MeshRenderer;
		friend class Particles;
		friend class EditorManager;
		bool m_localStored;
		std::vector<Vertex> m_vertices;
		std::vector<unsigned> m_indices;
	public:
		void OnGui();
		glm::vec3 GetCenter() const;
		Bound GetBound() const;
		Mesh();
		void SetVertices(unsigned mask, std::vector<Vertex>& vertices, std::vector<unsigned>& indices, bool store = true);
		size_t GetVerticesAmount();
		size_t Size();
		void RecalculateNormal(std::vector<Vertex>& vertices, std::vector<unsigned>& indices);
		void RecalculateTangent(std::vector<Vertex>& vertices, std::vector<unsigned>& indices);
		std::shared_ptr<GLVAO> Vao();
		void Enable();
		std::vector<Vertex>& GetVerticesUnsafe();
		std::vector<unsigned>& GetIndicesUnsafe();
		void LoadBin(std::string& fileName);
	};
}
