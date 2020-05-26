#include "Mesh.h"
using namespace UniEngine;
UniEngine::Mesh::Mesh()
{
	_Vertices = new std::vector<float3>();
	_VAO = new GLVAO();
	_Size = 0;
}

UniEngine::Mesh::~Mesh()
{
	delete _VAO;
}

void UniEngine::Mesh::SetVertices(uint mask, size_t size, Vertex* vertices, uint* indices)
{
	_Vertices->clear();

	_VAO->SetData(size * sizeof(Vertex), vertices, GL_STATIC_DRAW, 13);
	_VAO->EBO()->SetData(size * sizeof(uint), indices, GL_STATIC_DRAW);


	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	// vertex normals
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
	// vertex texture coords
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords0));



	/*
	std::vector<float3> normals = std::vector<float3>();
	std::vector<float3> tangents = std::vector<float3>();
	std::vector<float3> bitangents = std::vector<float3>();
	std::vector<float4> colors = std::vector<float4>();
	std::vector<float2> texcoords0s = std::vector<float2>();
	std::vector<float2> texcoords1s = std::vector<float2>();
	std::vector<float2> texcoords2s = std::vector<float2>();
	std::vector<float2> texcoords3s = std::vector<float2>();
	std::vector<float2> texcoords4s = std::vector<float2>();
	std::vector<float2> texcoords5s = std::vector<float2>();
	std::vector<float2> texcoords6s = std::vector<float2>();
	std::vector<float2> texcoords7s = std::vector<float2>();
#pragma region DataAllocation
	if (_Vertices->size()) _Vertices->clear();
	_Size = size;
	size_t attributeAmount = 2;
	size_t attributeSize = 24;
	if (mask & (uint)VertexAttribute::Tangent) {
		attributeAmount++;
		attributeSize += 12;
	}
	if (mask & (uint)VertexAttribute::Bitangent) {
		attributeAmount++;
		attributeSize += 12;
	}
	if (mask & (uint)VertexAttribute::Color) {
		attributeAmount++;
		attributeSize += 16;
	}
	if (mask & (uint)VertexAttribute::TexCoord0) {
		attributeAmount++;
		attributeSize += 8;
	}
	if (mask & (uint)VertexAttribute::TexCoord1) {
		attributeAmount++;
		attributeSize += 8;
	}
	if (mask & (uint)VertexAttribute::TexCoord2) {
		attributeAmount++;
		attributeSize += 8;
	}
	if (mask & (uint)VertexAttribute::TexCoord3) {
		attributeAmount++;
		attributeSize += 8;
	}
	if (mask & (uint)VertexAttribute::TexCoord4) {
		attributeAmount++;
		attributeSize += 8;
	}
	if (mask & (uint)VertexAttribute::TexCoord5) {
		attributeAmount++;
		attributeSize += 8;
	}
	if (mask & (uint)VertexAttribute::TexCoord6) {
		attributeAmount++;
		attributeSize += 8;
	}
	if (mask & (uint)VertexAttribute::TexCoord7) {
		attributeAmount++;
		attributeSize += 8;
	}
	_VAO->SetData(attributeSize, nullptr, GL_STATIC_DRAW, attributeAmount);
#pragma endregion
#pragma region AttributePointer
	auto total = attributeSize;
	_VAO->SetAttributePointer(0, 3, GL_FLOAT, GL_FALSE, total, 0);
	_VAO->SetAttributePointer(1, 3, GL_FLOAT, GL_FALSE, total, (void *)sizeof(float3));
	attributeAmount = 2;
	
	attributeSize = 24;
	if (mask & (uint)VertexAttribute::Tangent) {
		_VAO->SetAttributePointer(attributeAmount, 3, GL_FLOAT, GL_FALSE, total, (void*)attributeSize);
		attributeAmount++;
		attributeSize += 12;
	}
	if (mask & (uint)VertexAttribute::Bitangent) {
		_VAO->SetAttributePointer(attributeAmount, 3, GL_FLOAT, GL_FALSE, total, (void*)attributeSize);
		attributeAmount++;
		attributeSize += 12;
	}
	if (mask & (uint)VertexAttribute::Color) {
		_VAO->SetAttributePointer(attributeAmount, 4, GL_FLOAT, GL_FALSE, total, (void*)attributeSize);
		attributeAmount++;
		attributeSize += 16;
	}
	if (mask & (uint)VertexAttribute::TexCoord0) {
		_VAO->SetAttributePointer(attributeAmount, 2, GL_FLOAT, GL_FALSE, total, (void*)attributeSize);
		attributeAmount++;
		attributeSize += 8;
	}
	if (mask & (uint)VertexAttribute::TexCoord1) {
		_VAO->SetAttributePointer(attributeAmount, 2, GL_FLOAT, GL_FALSE, total, (void*)attributeSize);
		attributeAmount++;
		attributeSize += 8;
	}
	if (mask & (uint)VertexAttribute::TexCoord2) {
		_VAO->SetAttributePointer(attributeAmount, 2, GL_FLOAT, GL_FALSE, total, (void*)attributeSize);
		attributeAmount++;
		attributeSize += 8;
	}
	if (mask & (uint)VertexAttribute::TexCoord3) {
		_VAO->SetAttributePointer(attributeAmount, 2, GL_FLOAT, GL_FALSE, total, (void*)attributeSize);
		attributeAmount++;
		attributeSize += 8;
	}
	if (mask & (uint)VertexAttribute::TexCoord4) {
		_VAO->SetAttributePointer(attributeAmount, 2, GL_FLOAT, GL_FALSE, total, (void*)attributeSize);
		attributeAmount++;
		attributeSize += 8;
	}
	if (mask & (uint)VertexAttribute::TexCoord5) {
		_VAO->SetAttributePointer(attributeAmount, 2, GL_FLOAT, GL_FALSE, total, (void*)attributeSize);
		attributeAmount++;
		attributeSize += 8;
	}
	if (mask & (uint)VertexAttribute::TexCoord6) {
		_VAO->SetAttributePointer(attributeAmount, 2, GL_FLOAT, GL_FALSE, total, (void*)attributeSize);
		attributeAmount++;
		attributeSize += 8;
	}
	if (mask & (uint)VertexAttribute::TexCoord7) {
		_VAO->SetAttributePointer(attributeAmount, 2, GL_FLOAT, GL_FALSE, total, (void*)attributeSize);
		attributeAmount++;
		attributeSize += 8;
	}
#pragma endregion
#pragma region Copy
	for (size_t i = 0; i < size; i++) {
		_Vertices->push_back(vertices[indices[i]].Position);
		if (mask & (uint)VertexAttribute::Normal) {
			normals.push_back(vertices[indices[i]].Normal);
		}
		if (mask & (uint)VertexAttribute::Tangent) {
			tangents.push_back(vertices[indices[i]].Tangent);
		}
		if (mask & (uint)VertexAttribute::Bitangent) {
			bitangents.push_back(vertices[indices[i]].Bitangent);
		}
		if (mask & (uint)VertexAttribute::Color) {
			colors.push_back(vertices[indices[i]].Color);
		}
		if (mask & (uint)VertexAttribute::TexCoord0) {
			texcoords0s.push_back(vertices[indices[i]].TexCoords0);
		}
		if (mask & (uint)VertexAttribute::TexCoord1) {
			texcoords1s.push_back(vertices[indices[i]].TexCoords1);
		}
		if (mask & (uint)VertexAttribute::TexCoord2) {
			texcoords2s.push_back(vertices[indices[i]].TexCoords2);
		}
		if (mask & (uint)VertexAttribute::TexCoord3) {
			texcoords3s.push_back(vertices[indices[i]].TexCoords3);
		}
		if (mask & (uint)VertexAttribute::TexCoord4) {
			texcoords4s.push_back(vertices[indices[i]].TexCoords4);
		}
		if (mask & (uint)VertexAttribute::TexCoord5) {
			texcoords5s.push_back(vertices[indices[i]].TexCoords5);
		}
		if (mask & (uint)VertexAttribute::TexCoord6) {
			texcoords6s.push_back(vertices[indices[i]].TexCoords6);
		}
		if (mask & (uint)VertexAttribute::TexCoord7) {
			texcoords7s.push_back(vertices[indices[i]].TexCoords7);
		}
	}
#pragma endregion
#pragma region ToGPU
	_VAO->SubData(0, sizeof(float3), &_Vertices->at(0));
	if(mask & (uint)VertexAttribute::Normal)_VAO->SubData(sizeof(float3), sizeof(float3), &normals[0]);
	else {
		RecalculateNormal();
	}
	attributeSize = 24;
	if (mask & (uint)VertexAttribute::Tangent) {
		_VAO->SubData(attributeSize, sizeof(float3), &tangents[0]);
		attributeSize += 12;
	}
	if (mask & (uint)VertexAttribute::Bitangent) {
		_VAO->SubData(attributeSize, sizeof(float3), &bitangents[0]);
		attributeSize += 12;
	}
	if (mask & (uint)VertexAttribute::Color) {
		_VAO->SubData(attributeSize, sizeof(float4), &colors[0]);
		attributeSize += 16;
	}
	if (mask & (uint)VertexAttribute::TexCoord0) {
		_VAO->SubData(attributeSize, sizeof(float2), &texcoords0s[0]);
		attributeSize += 8;
	}
	if (mask & (uint)VertexAttribute::TexCoord1) {
		_VAO->SubData(attributeSize, sizeof(float2), &texcoords1s[0]);
		attributeSize += 8;
	}
	if (mask & (uint)VertexAttribute::TexCoord2) {
		_VAO->SubData(attributeSize, sizeof(float2), &texcoords2s[0]);
		attributeSize += 8;
	}
	if (mask & (uint)VertexAttribute::TexCoord3) {
		_VAO->SubData(attributeSize, sizeof(float2), &texcoords3s[0]);
		attributeSize += 8;
	}
	if (mask & (uint)VertexAttribute::TexCoord4) {
		_VAO->SubData(attributeSize, sizeof(float2), &texcoords4s[0]);
		attributeSize += 8;
	}
	if (mask & (uint)VertexAttribute::TexCoord5) {
		_VAO->SubData(attributeSize, sizeof(float2), &texcoords5s[0]);
		attributeSize += 8;
	}
	if (mask & (uint)VertexAttribute::TexCoord6) {
		_VAO->SubData(attributeSize, sizeof(float2), &texcoords6s[0]);
		attributeSize += 8;
	}
	if (mask & (uint)VertexAttribute::TexCoord7) {
		_VAO->SubData(attributeSize, sizeof(float2), &texcoords7s[0]);
		attributeSize += 8;
	}
#pragma endregion
	_VAO->EBO()->SetData(size * sizeof(unsigned), indices, GL_STATIC_DRAW);*/
}

void UniEngine::Mesh::ClearVertices()
{
	_Vertices->clear();
}


size_t UniEngine::Mesh::GetVerticesAmount()
{
	return _Size;
}

size_t UniEngine::Mesh::Size()
{
	return _Size;
}

void UniEngine::Mesh::RecalculateNormal()
{
	if (_Size == 0 || _Vertices->size() == 0) return;
	std::vector<float3> normals = std::vector<float3>();
	for (size_t i = 0; i < _Size / 3; i++) {
		auto v1 = _Vertices->at(3 * i);
		auto v2 = _Vertices->at(3 * i + 1);
		auto v3 = _Vertices->at(3 * i + 2);
		auto normal = Cross(v1 - v2, v1 - v3);
		normals.push_back(normal);
		normals.push_back(normal);
		normals.push_back(normal);
	}
	_VAO->SubData(12, sizeof(float3), &normals[0]);
}

GLVAO* UniEngine::Mesh::VAO()
{
	return _VAO;
}


void* UniEngine::Mesh::GetAttributeArray(VertexAttribute channel)
{
	return nullptr;
}
