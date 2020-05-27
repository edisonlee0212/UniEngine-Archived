#include "Mesh.h"
using namespace UniEngine;
UniEngine::Mesh::Mesh()
{
	_Vertices = nullptr;
	_VAO = new GLVAO();
	_Size = 0;
}

UniEngine::Mesh::~Mesh()
{
	delete _VAO;
}

void UniEngine::Mesh::SetVertices(unsigned mask, std::vector<Vertex>* vertices, std::vector<unsigned>* indices)
{
	/*
	_Size = size;
	_Vertices = vertices;
	_VAO->SetData(vertices->size() * sizeof(Vertex), &vertices->at(0), GL_STATIC_DRAW, 0);
	_VAO->EBO()->SetData(size * sizeof(unsigned), &indices->at(0), GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	// vertex normals
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
	// vertex texture coords
	glEnableVertexAttribArray(5);
	glVertexAttribPointer(5, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords0));
	*/
	//TODO: Attribute Pointer 格式需要更改
	size_t vsize = vertices->size();
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
	_Vertices = vertices;
	_Size = indices->size();
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
	_VAO->SetData(vsize * attributeSize, nullptr, GL_STATIC_DRAW);
#pragma endregion

#pragma region Copy
	for (size_t i = 0; i < vsize; i++) {
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
	_VAO->SubData(0, vsize * sizeof(glm::vec3), &positions[0]);
	if (mask & (unsigned)VertexAttribute::Normal)
		_VAO->SubData(vsize * sizeof(glm::vec3), vsize * sizeof(glm::vec3), &normals[0]);
	else {
		RecalculateNormal(indices);
	}
	attributeSize = 24;
	if (mask & (unsigned)VertexAttribute::Tangent) {
		_VAO->SubData(vsize * attributeSize, vsize * sizeof(glm::vec3), &tangents[0]);
		attributeSize += 12;
	}
	if (mask & (unsigned)VertexAttribute::Bitangent) {
		_VAO->SubData(vsize * attributeSize, vsize * sizeof(glm::vec3), &bitangents[0]);
		attributeSize += 12;
	}
	if (mask & (unsigned)VertexAttribute::Color) {
		_VAO->SubData(vsize * attributeSize, vsize * sizeof(glm::vec4), &colors[0]);
		attributeSize += 16;
	}
	if (mask & (unsigned)VertexAttribute::TexCoord0) {
		_VAO->SubData(vsize * attributeSize, vsize * sizeof(glm::vec2), &texcoords0s[0]);
		attributeSize += 8;
	}
	if (mask & (unsigned)VertexAttribute::TexCoord1) {
		_VAO->SubData(vsize * attributeSize, vsize * sizeof(glm::vec2), &texcoords1s[0]);
		attributeSize += 8;
	}
	if (mask & (unsigned)VertexAttribute::TexCoord2) {
		_VAO->SubData(vsize * attributeSize, vsize * sizeof(glm::vec2), &texcoords2s[0]);
		attributeSize += 8;
	}
	if (mask & (unsigned)VertexAttribute::TexCoord3) {
		_VAO->SubData(vsize * attributeSize, vsize * sizeof(glm::vec2), &texcoords3s[0]);
		attributeSize += 8;
	}
	if (mask & (unsigned)VertexAttribute::TexCoord4) {
		_VAO->SubData(vsize * attributeSize, vsize * sizeof(glm::vec2), &texcoords4s[0]);
		attributeSize += 8;
	}
	if (mask & (unsigned)VertexAttribute::TexCoord5) {
		_VAO->SubData(vsize * attributeSize, vsize * sizeof(glm::vec2), &texcoords5s[0]);
		attributeSize += 8;
	}
	if (mask & (unsigned)VertexAttribute::TexCoord6) {
		_VAO->SubData(vsize * attributeSize, vsize * sizeof(glm::vec2), &texcoords6s[0]);
		attributeSize += 8;
	}
	if (mask & (unsigned)VertexAttribute::TexCoord7) {
		_VAO->SubData(vsize * attributeSize, vsize * sizeof(glm::vec2), &texcoords7s[0]);
		attributeSize += 8;
	}
#pragma endregion
#pragma region AttributePointer
	_VAO->EnableAttributeArray(0);
	_VAO->SetAttributePointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), 0);
	_VAO->EnableAttributeArray(1);
	_VAO->SetAttributePointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)(sizeof(glm::vec3) * vsize));
	
	attributeSize = 2 * sizeof(glm::vec3);
	if (mask & (unsigned)VertexAttribute::Tangent) {
		_VAO->EnableAttributeArray(2);
		_VAO->SetAttributePointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)(attributeSize * vsize));
		attributeSize += 12;
	}
	if (mask & (unsigned)VertexAttribute::Bitangent) {
		_VAO->EnableAttributeArray(3);
		_VAO->SetAttributePointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)(attributeSize * vsize));
		attributeSize += 12;
	}
	if (mask & (unsigned)VertexAttribute::Color) {
		_VAO->EnableAttributeArray(4);
		_VAO->SetAttributePointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(glm::vec4), (void*)(attributeSize * vsize));
		attributeSize += 16;
	}
	if (mask & (unsigned)VertexAttribute::TexCoord0) {
		_VAO->EnableAttributeArray(5);
		_VAO->SetAttributePointer(5, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), (void*)(attributeSize * vsize));
		attributeSize += 8;
	}
	if (mask & (unsigned)VertexAttribute::TexCoord1) {
		_VAO->EnableAttributeArray(6);
		_VAO->SetAttributePointer(6, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), (void*)(attributeSize * vsize));
		attributeSize += 8;
	}
	if (mask & (unsigned)VertexAttribute::TexCoord2) {
		_VAO->EnableAttributeArray(7);
		_VAO->SetAttributePointer(7, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), (void*)(attributeSize * vsize));
		attributeSize += 8;
	}
	if (mask & (unsigned)VertexAttribute::TexCoord3) {
		_VAO->EnableAttributeArray(8);
		_VAO->SetAttributePointer(8, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), (void*)(attributeSize * vsize));
		attributeSize += 8;
	}
	if (mask & (unsigned)VertexAttribute::TexCoord4) {
		_VAO->EnableAttributeArray(9);
		_VAO->SetAttributePointer(9, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), (void*)(attributeSize * vsize));
		attributeSize += 8;
	}
	if (mask & (unsigned)VertexAttribute::TexCoord5) {
		_VAO->EnableAttributeArray(10);
		_VAO->SetAttributePointer(10, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), (void*)(attributeSize * vsize));
		attributeSize += 8;
	}
	if (mask & (unsigned)VertexAttribute::TexCoord6) {
		_VAO->EnableAttributeArray(11);
		_VAO->SetAttributePointer(11, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), (void*)(attributeSize * vsize));
		attributeSize += 8;
	}
	if (mask & (unsigned)VertexAttribute::TexCoord7) {
		_VAO->EnableAttributeArray(12);
		_VAO->SetAttributePointer(12, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), (void*)(attributeSize * vsize));
		attributeSize += 8;
	}
#pragma endregion

	_VAO->EBO()->SetData(_Size * sizeof(unsigned), &indices->at(0), GL_STATIC_DRAW);
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

void UniEngine::Mesh::RecalculateNormal(std::vector<unsigned>* indices)
{
	//if (mask & (unsigned)VertexAttribute::Normal)
	//	_VAO->SubData(vsize * sizeof(glm::vec3), vsize * sizeof(glm::vec3), &normals[0]);
	std::vector<std::vector<glm::vec3>> normalLists = std::vector<std::vector<glm::vec3>>();
	auto size = _Vertices->size();
	for (auto i = 0; i < size; i++) {
		normalLists.push_back(std::vector<glm::vec3>());
	}
	for (size_t i = 0; i < _Size / 3; i++) {
		auto v1 = _Vertices->at(indices->at(3 * i)).Position;
		auto v2 = _Vertices->at(indices->at(3 * i + 1)).Position;
		auto v3 = _Vertices->at(indices->at(3 * i + 2)).Position;
		auto normal = glm::normalize(glm::cross(v1 - v2, v1 - v3));
		normalLists[indices->at(3 * i)].push_back(normal);
		normalLists[indices->at(3 * i + 1)].push_back(normal);
		normalLists[indices->at(3 * i + 2)].push_back(normal);
	}
	std::vector<glm::vec3> normals = std::vector<glm::vec3>();
	for (auto i = 0; i < size; i++) {
		glm::vec3 normal;
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


void* UniEngine::Mesh::GetAttributeArray(VertexAttribute channel)
{
	return nullptr;
}
