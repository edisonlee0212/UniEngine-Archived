#include "pch.h"
#include "Mesh.h"
using namespace UniEngine;
glm::vec3 UniEngine::Mesh::GetCenter()
{
	return _Bound.Center;
}
Bound UniEngine::Mesh::GetBound()
{
	return _Bound;
}
float UniEngine::Mesh::GetRadius()
{
	return _Bound.Radius;
}
UniEngine::Mesh::Mesh()
{
	_VAO = new GLVAO();
	_IndicesSize = 0;
	_Bound = Bound();
}

UniEngine::Mesh::~Mesh()
{
	delete _VAO;
}

void UniEngine::Mesh::SetVertices(unsigned mask, std::vector<Vertex>& vertices, std::vector<unsigned>& indices)
{
	_Mask = mask;
	_IndicesSize = indices.size();
	_VerticesSize = vertices.size();
	if (_VerticesSize == 0) {
		Debug::Log("Mesh: SetVertices empty!");
		return;
	}
	if (!(mask & (unsigned)VertexAttribute::Position)) {
		Debug::Error("No Position Data!");
		return;
	}
	if (!(mask & (unsigned)VertexAttribute::TexCoord0)) {
		Debug::Error("No TexCoord0!");
		//return;
	}
	std::vector<glm::vec3> positions = std::vector<glm::vec3>();
	std::vector<glm::vec3> normals = std::vector<glm::vec3>();
	std::vector<glm::vec3> tangents = std::vector<glm::vec3>();
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
	size_t attributeSize = 3 * sizeof(glm::vec3);
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
	_VAO->SetData((GLsizei)(_VerticesSize * attributeSize), nullptr, GL_STATIC_DRAW);
#pragma endregion
#pragma region Copy
	glm::vec3 minBound = vertices.at(0).Position;
	glm::vec3 maxBound = vertices.at(0).Position;
	for (size_t i = 0; i < _VerticesSize; i++) {
		auto position = vertices.at(i).Position;
		minBound = glm::vec3(glm::min(minBound.x, position.x), glm::min(minBound.y, position.y), glm::min(minBound.z, position.z));
		maxBound = glm::vec3(glm::max(maxBound.x, position.x), glm::max(maxBound.y, position.y), glm::max(maxBound.z, position.z));
		positions.push_back(vertices.at(i).Position);
		if (mask & (unsigned)VertexAttribute::Normal) {
			normals.push_back(vertices.at(i).Normal);
		}
		if (mask & (unsigned)VertexAttribute::Tangent) {
			tangents.push_back(vertices.at(i).Tangent);
		}
		if (mask & (unsigned)VertexAttribute::Color) {
			colors.push_back(vertices.at(i).Color);
		}
		if (mask & (unsigned)VertexAttribute::TexCoord0) {
			texcoords0s.push_back(vertices.at(i).TexCoords0);
		}
		if (mask & (unsigned)VertexAttribute::TexCoord1) {
			texcoords1s.push_back(vertices.at(i).TexCoords1);
		}
		if (mask & (unsigned)VertexAttribute::TexCoord2) {
			texcoords2s.push_back(vertices.at(i).TexCoords2);
		}
		if (mask & (unsigned)VertexAttribute::TexCoord3) {
			texcoords3s.push_back(vertices.at(i).TexCoords3);
		}
		if (mask & (unsigned)VertexAttribute::TexCoord4) {
			texcoords4s.push_back(vertices.at(i).TexCoords4);
		}
		if (mask & (unsigned)VertexAttribute::TexCoord5) {
			texcoords5s.push_back(vertices.at(i).TexCoords5);
		}
		if (mask & (unsigned)VertexAttribute::TexCoord6) {
			texcoords6s.push_back(vertices.at(i).TexCoords6);
		}
		if (mask & (unsigned)VertexAttribute::TexCoord7) {
			texcoords7s.push_back(vertices.at(i).TexCoords7);
		}
	}
	_Bound.Size = (maxBound - minBound) / 2.0f;
	_Bound.Center = (maxBound + minBound) / 2.0f;
	_Bound.Radius = glm::length(_Bound.Size);
#pragma endregion
#pragma region ToGPU

	_VAO->SubData(0, _VerticesSize * sizeof(glm::vec3), &positions[0]);

	if (mask & (unsigned)VertexAttribute::Normal)
		_VAO->SubData(_VerticesSize * sizeof(glm::vec3), _VerticesSize * sizeof(glm::vec3), &normals[0]);
	else {
		RecalculateNormal(vertices, indices);
	}
	if (mask & (unsigned)VertexAttribute::Tangent) {
		_VAO->SubData(_VerticesSize * 2 * sizeof(glm::vec3), _VerticesSize * sizeof(glm::vec3), &tangents[0]);
	}
	else {
		RecalculateTangent(vertices, indices);
	}
	attributeSize = 3 * sizeof(glm::vec3);
	if (mask & (unsigned)VertexAttribute::Color) {
		_VAO->SubData(_VerticesSize * attributeSize, _VerticesSize * sizeof(glm::vec4), &colors[0]);
		attributeSize += sizeof(glm::vec4);
	}
	if (mask & (unsigned)VertexAttribute::TexCoord0) {
		_VAO->SubData(_VerticesSize * attributeSize, _VerticesSize * sizeof(glm::vec2), &texcoords0s[0]);
		attributeSize += sizeof(glm::vec2);
	}
	if (mask & (unsigned)VertexAttribute::TexCoord1) {
		_VAO->SubData(_VerticesSize * attributeSize, _VerticesSize * sizeof(glm::vec2), &texcoords1s[0]);
		attributeSize += sizeof(glm::vec2);
	}
	if (mask & (unsigned)VertexAttribute::TexCoord2) {
		_VAO->SubData(_VerticesSize * attributeSize, _VerticesSize * sizeof(glm::vec2), &texcoords2s[0]);
		attributeSize += sizeof(glm::vec2);
	}
	if (mask & (unsigned)VertexAttribute::TexCoord3) {
		_VAO->SubData(_VerticesSize * attributeSize, _VerticesSize * sizeof(glm::vec2), &texcoords3s[0]);
		attributeSize += sizeof(glm::vec2);
	}
	if (mask & (unsigned)VertexAttribute::TexCoord4) {
		_VAO->SubData(_VerticesSize * attributeSize, _VerticesSize * sizeof(glm::vec2), &texcoords4s[0]);
		attributeSize += sizeof(glm::vec2);
	}
	if (mask & (unsigned)VertexAttribute::TexCoord5) {
		_VAO->SubData(_VerticesSize * attributeSize, _VerticesSize * sizeof(glm::vec2), &texcoords5s[0]);
		attributeSize += sizeof(glm::vec2);
	}
	if (mask & (unsigned)VertexAttribute::TexCoord6) {
		_VAO->SubData(_VerticesSize * attributeSize, _VerticesSize * sizeof(glm::vec2), &texcoords6s[0]);
		attributeSize += sizeof(glm::vec2);
	}
	if (mask & (unsigned)VertexAttribute::TexCoord7) {
		_VAO->SubData(_VerticesSize * attributeSize, _VerticesSize * sizeof(glm::vec2), &texcoords7s[0]);
		attributeSize += sizeof(glm::vec2);
	}
#pragma endregion
#pragma region AttributePointer
	_VAO->EnableAttributeArray(0);
	_VAO->SetAttributePointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), 0);
	_VAO->EnableAttributeArray(1);
	_VAO->SetAttributePointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)(sizeof(glm::vec3) * _VerticesSize));
	_VAO->EnableAttributeArray(2);
	_VAO->SetAttributePointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)(2 * sizeof(glm::vec3) * _VerticesSize));
	attributeSize = 3 * sizeof(glm::vec3);
	if (mask & (unsigned)VertexAttribute::Color) {
		_VAO->EnableAttributeArray(3);
		_VAO->SetAttributePointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(glm::vec4), (void*)(attributeSize * _VerticesSize));
		attributeSize += sizeof(glm::vec4);
	}
	if (mask & (unsigned)VertexAttribute::TexCoord0) {
		_VAO->EnableAttributeArray(4);
		_VAO->SetAttributePointer(4, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), (void*)(attributeSize * _VerticesSize));
		attributeSize += sizeof(glm::vec2);
	}
	if (mask & (unsigned)VertexAttribute::TexCoord1) {
		_VAO->EnableAttributeArray(5);
		_VAO->SetAttributePointer(5, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), (void*)(attributeSize * _VerticesSize));
		attributeSize += sizeof(glm::vec2);
	}
	if (mask & (unsigned)VertexAttribute::TexCoord2) {
		_VAO->EnableAttributeArray(6);
		_VAO->SetAttributePointer(6, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), (void*)(attributeSize * _VerticesSize));
		attributeSize += sizeof(glm::vec2);
	}
	if (mask & (unsigned)VertexAttribute::TexCoord3) {
		_VAO->EnableAttributeArray(7);
		_VAO->SetAttributePointer(7, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), (void*)(attributeSize * _VerticesSize));
		attributeSize += sizeof(glm::vec2);
	}
	if (mask & (unsigned)VertexAttribute::TexCoord4) {
		_VAO->EnableAttributeArray(8);
		_VAO->SetAttributePointer(8, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), (void*)(attributeSize * _VerticesSize));
		attributeSize += sizeof(glm::vec2);
	}
	if (mask & (unsigned)VertexAttribute::TexCoord5) {
		_VAO->EnableAttributeArray(9);
		_VAO->SetAttributePointer(9, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), (void*)(attributeSize * _VerticesSize));
		attributeSize += sizeof(glm::vec2);
	}
	if (mask & (unsigned)VertexAttribute::TexCoord6) {
		_VAO->EnableAttributeArray(10);
		_VAO->SetAttributePointer(10, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), (void*)(attributeSize * _VerticesSize));
		attributeSize += sizeof(glm::vec2);
	}
	if (mask & (unsigned)VertexAttribute::TexCoord7) {
		_VAO->EnableAttributeArray(11);
		_VAO->SetAttributePointer(11, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), (void*)(attributeSize * _VerticesSize));
		attributeSize += sizeof(glm::vec2);
	}
#pragma endregion
	_VAO->EBO()->SetData((GLsizei)_IndicesSize * sizeof(unsigned), &indices.at(0), GL_STATIC_DRAW);
}


size_t UniEngine::Mesh::GetVerticesAmount()
{
	return _IndicesSize;
}

size_t UniEngine::Mesh::Size()
{
	return _IndicesSize;
}

void UniEngine::Mesh::RecalculateNormal(std::vector<Vertex>& vertices, std::vector<unsigned>& indices)
{
	std::vector<std::vector<glm::vec3>> normalLists = std::vector<std::vector<glm::vec3>>();
	auto size = vertices.size();
	for (auto i = 0; i < size; i++) {
		normalLists.push_back(std::vector<glm::vec3>());
	}
	for (size_t i = 0; i < _IndicesSize / 3; i++) {
		auto v1 = vertices.at(indices.at(3 * i)).Position;
		auto v2 = vertices.at(indices.at(3 * i + 1)).Position;
		auto v3 = vertices.at(indices.at(3 * i + 2)).Position;
		auto normal = glm::normalize(glm::cross(v1 - v2, v1 - v3));
		normalLists[indices.at(3 * i)].push_back(normal);
		normalLists[indices.at(3 * i + 1)].push_back(normal);
		normalLists[indices.at(3 * i + 2)].push_back(normal);
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

void UniEngine::Mesh::RecalculateTangent(std::vector<Vertex>& vertices, std::vector<unsigned>& indices)
{
	std::vector<std::vector<glm::vec3>> tangentLists = std::vector<std::vector<glm::vec3>>();
	auto size = vertices.size();
	for (auto i = 0; i < size; i++) {
		tangentLists.push_back(std::vector<glm::vec3>());
	}
	for (size_t i = 0; i < _IndicesSize / 3; i++) {
		auto v1 = vertices.at(indices.at(3 * i)).Position;
		auto v2 = vertices.at(indices.at(3 * i + 1)).Position;
		auto v3 = vertices.at(indices.at(3 * i + 2)).Position;
		auto uv1 = vertices.at(indices.at(3 * i)).TexCoords0;
		auto uv2 = vertices.at(indices.at(3 * i + 1)).TexCoords0;
		auto uv3 = vertices.at(indices.at(3 * i + 2)).TexCoords0;

		auto e21 = v2 - v1;
		auto d21 = uv2 - uv1;
		auto e31 = v3 - v1;
		auto d31 = uv3 - uv1;
		float f = 1.0f / (d21.x * d31.y - d31.x * d21.y);
		auto tangent = f * glm::vec3(
			d31.y * e21.x - d21.y * e31.x,
			d31.y * e21.y - d21.y * e31.y,
			d31.y * e21.z - d21.y * e31.z);
		tangentLists[indices.at(3 * i)].push_back(tangent);
		tangentLists[indices.at(3 * i + 1)].push_back(tangent);
		tangentLists[indices.at(3 * i + 2)].push_back(tangent);
	}
	std::vector<glm::vec3> tangents = std::vector<glm::vec3>();
	for (auto i = 0; i < size; i++) {
		glm::vec3 tangent = glm::vec3(0.0f);
		for (auto j : tangentLists[i]) {
			tangent += j;
		}
		tangents.push_back(glm::normalize(tangent));
	}

	_VAO->SubData(size * 2 * sizeof(glm::vec3), size * sizeof(glm::vec3), &tangents[0]);
}



GLVAO* UniEngine::Mesh::VAO()
{
	return _VAO;
}

void UniEngine::Mesh::Enable()
{
	_VAO->Bind();
}


void* UniEngine::Mesh::GetAttributeArray(VertexAttribute channel)
{
	return nullptr;
}
