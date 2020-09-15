#pragma once
#include "UniEngineAPI.h"
namespace UniEngine {
	struct UNIENGINE_API Vertex {
		glm::vec3 Position;
		glm::vec3 Normal;
		glm::vec3 Tangent;
		glm::vec4 Color;
		glm::vec2 TexCoords0;
		glm::vec2 TexCoords1;
		glm::vec2 TexCoords2;
		glm::vec2 TexCoords3;
		glm::vec2 TexCoords4;
		glm::vec2 TexCoords5;
		glm::vec2 TexCoords6;
		glm::vec2 TexCoords7;
	};
	enum class UNIENGINE_API VertexAttribute
	{
		Position = 1,
		Normal = 1 << 1,
		Tangent = 1 << 2,
		Color = 1 << 3,
		TexCoord0 = 1 << 4,
		TexCoord1 = 1 << 5,
		TexCoord2 = 1 << 6,
		TexCoord3 = 1 << 7,
		TexCoord4 = 1 << 8,
		TexCoord5 = 1 << 9,
		TexCoord6 = 1 << 10,
		TexCoord7 = 1 << 11
	};

	class UNIENGINE_API Mesh
	{
		GLVAO* _VAO;
		size_t _VerticesSize;
		size_t _IndicesSize;
		unsigned _Mask;
		Bound _Bound;
	public:
		glm::vec3 GetCenter();
		Bound GetBound();
		float GetRadius();
		Mesh();
		~Mesh();
		void SetVertices(unsigned mask, std::vector<Vertex>& vertices, std::vector<unsigned>& indices);
		size_t GetVerticesAmount();
		size_t Size();
		void RecalculateNormal(std::vector<Vertex>& vertices, std::vector<unsigned>& indices);
		void RecalculateTangent(std::vector<Vertex>& vertices, std::vector<unsigned>& indices);
		GLVAO* VAO();
		void Enable();
		void* GetAttributeArray(VertexAttribute channel);
	};
}
