#pragma once
#include "Math.h"
#include "Core.h"
namespace UniEngine {
	struct Vertex {
		glm::vec3 Position;
		glm::vec3 Normal;
		glm::vec3 Tangent;
		glm::vec3 Bitangent;
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
	enum class VertexAttribute
	{
		Position = 1,
		Normal = 1 << 1,
		Tangent = 1 << 2,
		Bitangent = 1 << 3,
		Color = 1 << 4,
		TexCoord0 = 1 << 5,
		TexCoord1 = 1 << 6,
		TexCoord2 = 1 << 7,
		TexCoord3 = 1 << 8,
		TexCoord4 = 1 << 9,
		TexCoord5 = 1 << 10,
		TexCoord6 = 1 << 11,
		TexCoord7 = 1 << 12
	};
	class Mesh : public SharedComponent
	{
		std::vector<Vertex>* _Vertices;
		GLVAO* _VAO;
		size_t _Size;
	public:
		Mesh();
		~Mesh();
		void SetVertices(unsigned mask, std::vector<Vertex>* vertices, std::vector<unsigned>* indices);
		void ClearVertices();
		size_t GetVerticesAmount();
		size_t Size();
		void RecalculateNormal(std::vector<unsigned>* indices);
		GLVAO* VAO();
		
		void* GetAttributeArray(VertexAttribute channel);
	};
}
