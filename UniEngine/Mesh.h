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
	};
	enum VertexAttribute
	{
		Position = 1,
		Normal = 2,
		Tangent = 4,
		Bitangent = 8,
		Color = 16,
		TexCoord0 = 32,
		TexCoord1 = 64
	};
	class Mesh : public SharedComponent
	{
		std::vector<float3>* _Vertices;
		GLVAO* _VAO;
		size_t _Size;
	public:
		Mesh();
		~Mesh();
		void SetVertices(uint mask, size_t size, Vertex* vertices, unsigned* indices);
		void SetVertices(size_t size, float3* vertices, unsigned* indices);
		void ClearVertices();
		float3* GetVertices(size_t* size);
		size_t GetVerticesAmount();
		size_t Size();
		void RecalculateNormal();
		GLVAO* VAO();
		
		void* GetAttributeArray(VertexAttribute channel);
		void SetAttributeArray(VertexAttribute channel, void* data);
	};
}
