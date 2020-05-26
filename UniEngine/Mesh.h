#pragma once
#include "Math.h"
#include "GLBuffer.h"
#include "SharedComponent.h"
namespace UniEngine {
	struct Vertex {
		float3 Position;
		float3 Normal;
		float3 Tangent;
		float3 Bitangent;
		float4 Color;
		float2 TexCoords0;
		float2 TexCoords1;
		float2 TexCoords2;
		float2 TexCoords3;
		float2 TexCoords4;
		float2 TexCoords5;
		float2 TexCoords6;
		float2 TexCoords7;
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
		std::vector<float3>* _Vertices;
		GLVAO* _VAO;
		size_t _Size;
	public:
		Mesh();
		~Mesh();
		void SetVertices(uint mask, size_t size, Vertex* vertices, uint* indices);
		void ClearVertices();
		size_t GetVerticesAmount();
		size_t Size();
		void RecalculateNormal();
		GLVAO* VAO();
		
		void* GetAttributeArray(VertexAttribute channel);
	};
}
