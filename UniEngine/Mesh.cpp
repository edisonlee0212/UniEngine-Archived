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

void UniEngine::Mesh::SetVertices(uint mask, size_t size, Vertex* vertices, unsigned* indices)
{
	std::vector<float3> normals = std::vector<float3>();
	std::vector<float3> tangents = std::vector<float3>();
	std::vector<float3> bitangents = std::vector<float3>();
	std::vector<float4> colors = std::vector<float4>();
	std::vector<float2> texcoords0s = std::vector<float2>();
	std::vector<float2> texcoords1s = std::vector<float2>();
	if (_Vertices->size()) _Vertices->clear();
	_Size = size;
	for (size_t i = 0; i < size; i++) {
		_Vertices->push_back(vertices[indices[i]].Position);
		if (mask & VertexAttribute::Normal)normals.push_back(vertices[indices[i]].Normal);
		if (mask & VertexAttribute::Tangent)tangents.push_back(vertices[indices[i]].Tangent);
		if (mask & VertexAttribute::Bitangent)bitangents.push_back(vertices[indices[i]].Bitangent);
		if (mask & VertexAttribute::Color)colors.push_back(vertices[indices[i]].Color);
		if (mask & VertexAttribute::TexCoord0)texcoords0s.push_back(vertices[indices[i]].TexCoords0);
		if (mask & VertexAttribute::TexCoord1)texcoords1s.push_back(vertices[indices[i]].TexCoords1);
	}

	_VAO->SetData(sizeof(Vertex) * size, nullptr, GL_STATIC_DRAW, 7);
	_VAO->SetAttributePointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float3), 0);
	_VAO->SetAttributePointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float3), (void*)(_Size * 12));
	_VAO->SetAttributePointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(float3), (void*)(_Size * 24));
	_VAO->SetAttributePointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(float3), (void*)(_Size * 36));
	_VAO->SetAttributePointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(float4), (void*)(_Size * 48));
	_VAO->SetAttributePointer(5, 2, GL_FLOAT, GL_FALSE, sizeof(float2), (void*)(_Size * 64));
	_VAO->SetAttributePointer(6, 2, GL_FLOAT, GL_FALSE, sizeof(float2), (void*)(_Size * 72));
	_VAO->SubData(0, sizeof(float3) * size, &_Vertices->at(0));

	if (mask & VertexAttribute::Normal)SetAttributeArray(VertexAttribute::Normal, &normals[0]);
	if (mask & VertexAttribute::Tangent)SetAttributeArray(VertexAttribute::Tangent, &tangents[0]);
	if (mask & VertexAttribute::Bitangent)SetAttributeArray(VertexAttribute::Bitangent, &bitangents[0]);
	if (mask & VertexAttribute::Color)SetAttributeArray(VertexAttribute::Color, &colors[0]);
	if (mask & VertexAttribute::TexCoord0)SetAttributeArray(VertexAttribute::TexCoord0, &texcoords0s[0]);
	if (mask & VertexAttribute::TexCoord1)SetAttributeArray(VertexAttribute::TexCoord1, &texcoords1s[0]);
}

void UniEngine::Mesh::SetVertices(size_t size, float3* vertices, unsigned* indices)
{
	if (_Vertices->size()) _Vertices->clear();
	_Size = size;
	for (size_t i = 0; i < size; i++) {
		_Vertices->push_back(vertices[indices[i]]);
	}
	_VAO->SetData(sizeof(Vertex) * size, nullptr, GL_STATIC_DRAW, 7);
	_VAO->SetAttributePointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float3), 0);
	_VAO->SetAttributePointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float3), (void*)(_Size * 12));
	_VAO->SetAttributePointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(float3), (void*)(_Size * 24));
	_VAO->SetAttributePointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(float3), (void*)(_Size * 36));
	_VAO->SetAttributePointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(float4), (void*)(_Size * 48));
	_VAO->SetAttributePointer(5, 2, GL_FLOAT, GL_FALSE, sizeof(float2), (void*)(_Size * 64));
	_VAO->SetAttributePointer(6, 2, GL_FLOAT, GL_FALSE, sizeof(float2), (void*)(_Size * 72));
	_VAO->SubData(0, sizeof(float3) * size, &_Vertices->at(0));
}

void UniEngine::Mesh::ClearVertices()
{
	_Vertices->clear();
}

float3* UniEngine::Mesh::GetVertices(size_t* size)
{
	return nullptr;
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
	SetAttributeArray(VertexAttribute::Normal, &normals[0]);
}

GLVAO* UniEngine::Mesh::VAO()
{
	return _VAO;
}


void* UniEngine::Mesh::GetAttributeArray(VertexAttribute channel)
{
	return nullptr;
}

void UniEngine::Mesh::SetAttributeArray(VertexAttribute channel, void* data)
{
	switch (channel)
	{
	case UniEngine::Position:
		_VAO->SubData(0, _Size * 12, data);
		break;
	case UniEngine::Normal:
		_VAO->SubData(_Size * 12, _Size * 12, data);
		break;
	case UniEngine::Tangent:
		_VAO->SubData(_Size * 24, _Size * 12, data);
		break;
	case UniEngine::Bitangent:
		_VAO->SubData(_Size * 36, _Size * 12, data);
		break;
	case UniEngine::Color:
		_VAO->SubData(_Size * 48, _Size * 16, data);
		break;
	case UniEngine::TexCoord0:
		_VAO->SubData(_Size * 64, _Size * 8, data);
		break;
	case UniEngine::TexCoord1:
		_VAO->SubData(_Size * 72, _Size * 8, data);
		break;
	default:
		break;
	}
}
