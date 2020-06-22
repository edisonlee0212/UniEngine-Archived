#include "pch.h"
#include "Mesh.h"
using namespace UniEngine;
UniEngine::Mesh::Mesh()
{
	_VAO = new GLVAO();
	_IndicesSize = 0;
}

UniEngine::Mesh::~Mesh()
{
	delete _VAO;
}

void UniEngine::Mesh::SetVertices(unsigned mask, std::vector<Vertex>* vertices, std::vector<unsigned>* indices)
{
	_Mask = mask;
	_IndicesSize = indices->size();
	_VerticesSize = vertices->size();
	std::vector<glm::vec3> positions = std::vector<glm::vec3>();
	std::vector<glm::vec3> normals = std::vector<glm::vec3>();
	std::vector<glm::vec3> tangents = std::vector<glm::vec3>();
	std::vector<glm::vec3> bitangents = std::vector<glm::vec3>();
	std::vector<glm::vec4> colors = std::vector<glm::vec4>();
	std::vector<glm::vec2> texcoords0s = std::vector<glm::vec2>();
	std::vector<glm::vec2> texcoords1s = std::vector<glm::vec2>();
	std::vector<glm::vec2> texcoords2s = std::vector<glm::vec2>();
	std::vector<glm::vec2> texcoords3s = std::vector<glm::vec2>();
	std::vector<glm::vec2> texcoords4s = std::vector<glm::vec2>();
	std::vector<glm::vec2> texcoords5s = std::vector<glm::vec2>();
	std::vector<glm::vec2> texcoords6s = std::vector<glm::vec2>();
	std::vector<glm::vec2> texcoords7s = std::vector<glm::vec2>();
#pragma region DataAllocation
	size_t attributeSize = 2 * sizeof(glm::vec3);
	if (mask & (unsigned)VertexAttribute::Tangent) {
		attributeSize += sizeof(glm::vec3);
	}
	if (mask & (unsigned)VertexAttribute::Bitangent) {
		attributeSize += sizeof(glm::vec3);
	}
	if (mask & (unsigned)VertexAttribute::Color) {
		attributeSize += sizeof(glm::vec4);
	}
	if (mask & (unsigned)VertexAttribute::TexCoord0) {
		attributeSize += sizeof(glm::vec2);
	}
	if (mask & (unsigned)VertexAttribute::TexCoord1) {
		attributeSize += sizeof(glm::vec2);
	}
	if (mask & (unsigned)VertexAttribute::TexCoord2) {
		attributeSize += sizeof(glm::vec2);
	}
	if (mask & (unsigned)VertexAttribute::TexCoord3) {
		attributeSize += sizeof(glm::vec2);
	}
	if (mask & (unsigned)VertexAttribute::TexCoord4) {
		attributeSize += sizeof(glm::vec2);
	}
	if (mask & (unsigned)VertexAttribute::TexCoord5) {
		attributeSize += sizeof(glm::vec2);
	}
	if (mask & (unsigned)VertexAttribute::TexCoord6) {
		attributeSize += sizeof(glm::vec2);
	}
	if (mask & (unsigned)VertexAttribute::TexCoord7) {
		attributeSize += sizeof(glm::vec2);
	}
	_VAO->SetData(_VerticesSize * attributeSize, nullptr, GL_STATIC_DRAW);
#pragma endregion
#pragma region Copy
	for (size_t i = 0; i < _VerticesSize; i++) {
		positions.push_back(vertices->at(i).Position);
		if (mask & (unsigned)VertexAttribute::Normal) {
			normals.push_back(vertices->at(i).Normal);
		}
		if (mask & (unsigned)VertexAttribute::Tangent) {
			tangents.push_back(vertices->at(i).Tangent);
		}
		if (mask & (unsigned)VertexAttribute::Bitangent) {
			bitangents.push_back(vertices->at(i).Bitangent);
		}
		if (mask & (unsigned)VertexAttribute::Color) {
			colors.push_back(vertices->at(i).Color);
		}
		if (mask & (unsigned)VertexAttribute::TexCoord0) {
			texcoords0s.push_back(vertices->at(i).TexCoords0);
		}
		if (mask & (unsigned)VertexAttribute::TexCoord1) {
			texcoords1s.push_back(vertices->at(i).TexCoords1);
		}
		if (mask & (unsigned)VertexAttribute::TexCoord2) {
			texcoords2s.push_back(vertices->at(i).TexCoords2);
		}
		if (mask & (unsigned)VertexAttribute::TexCoord3) {
			texcoords3s.push_back(vertices->at(i).TexCoords3);
		}
		if (mask & (unsigned)VertexAttribute::TexCoord4) {
			texcoords4s.push_back(vertices->at(i).TexCoords4);
		}
		if (mask & (unsigned)VertexAttribute::TexCoord5) {
			texcoords5s.push_back(vertices->at(i).TexCoords5);
		}
		if (mask & (unsigned)VertexAttribute::TexCoord6) {
			texcoords6s.push_back(vertices->at(i).TexCoords6);
		}
		if (mask & (unsigned)VertexAttribute::TexCoord7) {
			texcoords7s.push_back(vertices->at(i).TexCoords7);
		}
	}
#pragma endregion
#pragma region ToGPU
	_VAO->SubData(0, _VerticesSize * sizeof(glm::vec3), &positions[0]);
	if (mask & (unsigned)VertexAttribute::Normal)
		_VAO->SubData(_VerticesSize * sizeof(glm::vec3), _VerticesSize * sizeof(glm::vec3), &normals[0]);
	else {
		RecalculateNormal(vertices, indices);
	}
	attributeSize = 24;
	if (mask & (unsigned)VertexAttribute::Tangent) {
		_VAO->SubData(_VerticesSize * attributeSize, _VerticesSize * sizeof(glm::vec3), &tangents[0]);
		attributeSize += 12;
	}
	if (mask & (unsigned)VertexAttribute::Bitangent) {
		_VAO->SubData(_VerticesSize * attributeSize, _VerticesSize * sizeof(glm::vec3), &bitangents[0]);
		attributeSize += 12;
	}
	if (mask & (unsigned)VertexAttribute::Color) {
		_VAO->SubData(_VerticesSize * attributeSize, _VerticesSize * sizeof(glm::vec4), &colors[0]);
		attributeSize += 16;
	}
	if (mask & (unsigned)VertexAttribute::TexCoord0) {
		_VAO->SubData(_VerticesSize * attributeSize, _VerticesSize * sizeof(glm::vec2), &texcoords0s[0]);
		attributeSize += 8;
	}
	if (mask & (unsigned)VertexAttribute::TexCoord1) {
		_VAO->SubData(_VerticesSize * attributeSize, _VerticesSize * sizeof(glm::vec2), &texcoords1s[0]);
		attributeSize += 8;
	}
	if (mask & (unsigned)VertexAttribute::TexCoord2) {
		_VAO->SubData(_VerticesSize * attributeSize, _VerticesSize * sizeof(glm::vec2), &texcoords2s[0]);
		attributeSize += 8;
	}
	if (mask & (unsigned)VertexAttribute::TexCoord3) {
		_VAO->SubData(_VerticesSize * attributeSize, _VerticesSize * sizeof(glm::vec2), &texcoords3s[0]);
		attributeSize += 8;
	}
	if (mask & (unsigned)VertexAttribute::TexCoord4) {
		_VAO->SubData(_VerticesSize * attributeSize, _VerticesSize * sizeof(glm::vec2), &texcoords4s[0]);
		attributeSize += 8;
	}
	if (mask & (unsigned)VertexAttribute::TexCoord5) {
		_VAO->SubData(_VerticesSize * attributeSize, _VerticesSize * sizeof(glm::vec2), &texcoords5s[0]);
		attributeSize += 8;
	}
	if (mask & (unsigned)VertexAttribute::TexCoord6) {
		_VAO->SubData(_VerticesSize * attributeSize, _VerticesSize * sizeof(glm::vec2), &texcoords6s[0]);
		attributeSize += 8;
	}
	if (mask & (unsigned)VertexAttribute::TexCoord7) {
		_VAO->SubData(_VerticesSize * attributeSize, _VerticesSize * sizeof(glm::vec2), &texcoords7s[0]);
		attributeSize += 8;
	}
#pragma endregion
#pragma region AttributePointer
	GLVAO::EnableAttributeArray(0);
	GLVAO::SetAttributePointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), 0);
	GLVAO::EnableAttributeArray(1);
	GLVAO::SetAttributePointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)(sizeof(glm::vec3) * _VerticesSize));
	
	attributeSize = 2 * sizeof(glm::vec3);
	if (mask & (unsigned)VertexAttribute::Tangent) {
		GLVAO::EnableAttributeArray(2);
		GLVAO::SetAttributePointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)(attributeSize * _VerticesSize));
		attributeSize += 12;
	}
	if (mask & (unsigned)VertexAttribute::Bitangent) {
		GLVAO::EnableAttributeArray(3);
		GLVAO::SetAttributePointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)(attributeSize * _VerticesSize));
		attributeSize += 12;
	}
	if (mask & (unsigned)VertexAttribute::Color) {
		GLVAO::EnableAttributeArray(4);
		GLVAO::SetAttributePointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(glm::vec4), (void*)(attributeSize * _VerticesSize));
		attributeSize += 16;
	}
	if (mask & (unsigned)VertexAttribute::TexCoord0) {
		GLVAO::EnableAttributeArray(5);
		GLVAO::SetAttributePointer(5, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), (void*)(attributeSize * _VerticesSize));
		attributeSize += 8;
	}
	if (mask & (unsigned)VertexAttribute::TexCoord1) {
		GLVAO::EnableAttributeArray(6);
		GLVAO::SetAttributePointer(6, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), (void*)(attributeSize * _VerticesSize));
		attributeSize += 8;
	}
	if (mask & (unsigned)VertexAttribute::TexCoord2) {
		GLVAO::EnableAttributeArray(7);
		GLVAO::SetAttributePointer(7, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), (void*)(attributeSize * _VerticesSize));
		attributeSize += 8;
	}
	if (mask & (unsigned)VertexAttribute::TexCoord3) {
		GLVAO::EnableAttributeArray(8);
		GLVAO::SetAttributePointer(8, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), (void*)(attributeSize * _VerticesSize));
		attributeSize += 8;
	}
	if (mask & (unsigned)VertexAttribute::TexCoord4) {
		GLVAO::EnableAttributeArray(9);
		GLVAO::SetAttributePointer(9, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), (void*)(attributeSize * _VerticesSize));
		attributeSize += 8;
	}
	if (mask & (unsigned)VertexAttribute::TexCoord5) {
		GLVAO::EnableAttributeArray(10);
		GLVAO::SetAttributePointer(10, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), (void*)(attributeSize * _VerticesSize));
		attributeSize += 8;
	}
	if (mask & (unsigned)VertexAttribute::TexCoord6) {
		GLVAO::EnableAttributeArray(11);
		GLVAO::SetAttributePointer(11, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), (void*)(attributeSize * _VerticesSize));
		attributeSize += 8;
	}
	if (mask & (unsigned)VertexAttribute::TexCoord7) {
		GLVAO::EnableAttributeArray(12);
		GLVAO::SetAttributePointer(12, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), (void*)(attributeSize * _VerticesSize));
		attributeSize += 8;
	}
#pragma endregion
	_VAO->EBO()->SetData(_IndicesSize * sizeof(unsigned), &indices->at(0), GL_STATIC_DRAW);
}

void UniEngine::Mesh::ClearVertices()
{
	
}


size_t UniEngine::Mesh::GetVerticesAmount()
{
	return _IndicesSize;
}

size_t UniEngine::Mesh::Size()
{
	return _IndicesSize;
}

void UniEngine::Mesh::RecalculateNormal(std::vector<Vertex>* vertices, std::vector<unsigned>* indices)
{
	std::vector<std::vector<glm::vec3>> normalLists = std::vector<std::vector<glm::vec3>>();
	auto size = vertices->size();
	for (auto i = 0; i < size; i++) {
		normalLists.push_back(std::vector<glm::vec3>());
	}
	for (size_t i = 0; i < _IndicesSize / 3; i++) {
		auto v1 = vertices->at(indices->at(3 * i)).Position;
		auto v2 = vertices->at(indices->at(3 * i + 1)).Position;
		auto v3 = vertices->at(indices->at(3 * i + 2)).Position;
		auto normal = glm::normalize(glm::cross(v1 - v2, v1 - v3));
		normalLists[indices->at(3 * i)].push_back(normal);
		normalLists[indices->at(3 * i + 1)].push_back(normal);
		normalLists[indices->at(3 * i + 2)].push_back(normal);
	}
	std::vector<glm::vec3> normals = std::vector<glm::vec3>();
	for (auto i = 0; i < size; i++) {
		glm::vec3 normal = glm::vec3(0.0f);
		for (auto j : normalLists[i]) {
			normal += j;
		}
		normals.push_back(glm::normalize(normal));
	}

	_VAO->SubData(size * sizeof(glm::vec3), size * sizeof(glm::vec3), &normals[0]);
}

GLVAO* UniEngine::Mesh::VAO()
{
	return _VAO;
}

void UniEngine::Mesh::Enable()
{
	_VAO->Bind();
/*
#pragma region AttributePointer
	GLVAO::EnableAttributeArray(0);
	GLVAO::SetAttributePointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), 0);
	GLVAO::EnableAttributeArray(1);
	GLVAO::SetAttributePointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)(sizeof(glm::vec3) * _VerticesSize));
	size_t attributeSize = 2 * sizeof(glm::vec3);
	if (_Mask & (unsigned)VertexAttribute::Tangent) {
		GLVAO::EnableAttributeArray(2);
		GLVAO::SetAttributePointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)(attributeSize * _VerticesSize));
		attributeSize += 12;
	}
	if (_Mask & (unsigned)VertexAttribute::Bitangent) {
		GLVAO::EnableAttributeArray(3);
		GLVAO::SetAttributePointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)(attributeSize * _VerticesSize));
		attributeSize += 12;
	}
	if (_Mask & (unsigned)VertexAttribute::Color) {
		GLVAO::EnableAttributeArray(4);
		GLVAO::SetAttributePointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(glm::vec4), (void*)(attributeSize * _VerticesSize));
		attributeSize += 16;
	}
	if (_Mask & (unsigned)VertexAttribute::TexCoord0) {
		GLVAO::EnableAttributeArray(5);
		GLVAO::SetAttributePointer(5, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), (void*)(attributeSize * _VerticesSize));
		attributeSize += 8;
	}
	if (_Mask & (unsigned)VertexAttribute::TexCoord1) {
		GLVAO::EnableAttributeArray(6);
		GLVAO::SetAttributePointer(6, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), (void*)(attributeSize * _VerticesSize));
		attributeSize += 8;
	}
	if (_Mask & (unsigned)VertexAttribute::TexCoord2) {
		GLVAO::EnableAttributeArray(7);
		GLVAO::SetAttributePointer(7, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), (void*)(attributeSize * _VerticesSize));
		attributeSize += 8;
	}
	if (_Mask & (unsigned)VertexAttribute::TexCoord3) {
		GLVAO::EnableAttributeArray(8);
		GLVAO::SetAttributePointer(8, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), (void*)(attributeSize * _VerticesSize));
		attributeSize += 8;
	}
	if (_Mask & (unsigned)VertexAttribute::TexCoord4) {
		GLVAO::EnableAttributeArray(9);
		GLVAO::SetAttributePointer(9, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), (void*)(attributeSize * _VerticesSize));
		attributeSize += 8;
	}
	if (_Mask & (unsigned)VertexAttribute::TexCoord5) {
		GLVAO::EnableAttributeArray(10);
		GLVAO::SetAttributePointer(10, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), (void*)(attributeSize * _VerticesSize));
		attributeSize += 8;
	}
	if (_Mask & (unsigned)VertexAttribute::TexCoord6) {
		GLVAO::EnableAttributeArray(11);
		GLVAO::SetAttributePointer(11, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), (void*)(attributeSize * _VerticesSize));
		attributeSize += 8;
	}
	if (_Mask & (unsigned)VertexAttribute::TexCoord7) {
		GLVAO::EnableAttributeArray(12);
		GLVAO::SetAttributePointer(12, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), (void*)(attributeSize * _VerticesSize));
		attributeSize += 8;
	}
#pragma endregion	
*/
}


void* UniEngine::Mesh::GetAttributeArray(VertexAttribute channel)
{
	return nullptr;
}
