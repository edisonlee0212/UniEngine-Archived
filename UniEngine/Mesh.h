#pragma once
#include "Core.h"
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
		Position,
		Normal,
		Tangent,
		Bitangent,
		Color,
		TexCoord0,
		TexCoord1
	};
	class Mesh
	{
		std::vector<float3>* _Vertices;
		GLVAO* _VAO;
		size_t _Size;
	public:
		Mesh();
		~Mesh();
		
		void SetVertices(size_t size, float3* vertices, unsigned* indices);
		void ClearVertices();
		float3* GetVertices(size_t* size);
		size_t GetVerticesAmount();

		void RecalculateNormal();

		
		void* GetAttributeArray(VertexAttribute channel);
		void SetAttributeArray(VertexAttribute channel, void* data);
	};
}
