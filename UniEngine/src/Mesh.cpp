#include "pch.h"
#include "Mesh.h"
using namespace UniEngine;

void Mesh::OnGui()
{
	ImGui::Text(("Name: " + m_name).c_str());
	if (ImGui::BeginPopupContextItem(m_name.c_str()))
	{
		if (ImGui::BeginMenu("Rename"))
		{
			static char newName[256];
			ImGui::InputText("New name", newName, 256);
			if (ImGui::Button("Confirm")) m_name = std::string(newName);
			ImGui::EndMenu();
		}
		ImGui::EndPopup();
	}
}

glm::vec3 UniEngine::Mesh::GetCenter() const
{
	return m_bound.Center();
}
Bound UniEngine::Mesh::GetBound() const
{
	return m_bound;
}

UniEngine::Mesh::Mesh()
{
	m_vao = std::make_shared<GLVAO>();
	m_triangleSize = 0;
	m_bound = Bound();
	m_name = "New mesh";
}

void UniEngine::Mesh::SetVertices(const unsigned& mask, std::vector<Vertex>& vertices, std::vector<unsigned>& indices, const bool& store)
{
	if(indices.size() % 3 != 0)
	{
		Debug::Error("Triangle size wrong!");
		return;
	} 
	std::vector<glm::uvec3> triangles;
	triangles.resize(indices.size() / 3);
	memcpy(triangles.data(), indices.data(), indices.size() * sizeof(unsigned));
	SetVertices(mask, vertices, triangles, store);
}

void Mesh::SetVertices(const unsigned& mask, std::vector<Vertex>& vertices, std::vector<glm::uvec3>& triangles, const bool& store)
{
	m_mask = mask;
	m_triangleSize = triangles.size();
	m_verticesSize = vertices.size();
	if (m_verticesSize == 0) {
		Debug::Log("Mesh: SetVertices empty!");
		return;
	}
	if (!(mask & (unsigned)VertexAttribute::Position)) {
		Debug::Error("No Position Data!");
		return;
	}
	auto positions = std::vector<glm::vec3>();
	auto normals = std::vector<glm::vec3>();
	auto tangents = std::vector<glm::vec3>();
	auto colors = std::vector<glm::vec4>();
	auto texcoords0s = std::vector<glm::vec2>();
	auto texcoords1s = std::vector<glm::vec2>();
	auto texcoords2s = std::vector<glm::vec2>();
	auto texcoords3s = std::vector<glm::vec2>();
	auto texcoords4s = std::vector<glm::vec2>();
	auto texcoords5s = std::vector<glm::vec2>();
	auto texcoords6s = std::vector<glm::vec2>();
	auto texcoords7s = std::vector<glm::vec2>();
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
	m_vao->SetData((GLsizei)(m_verticesSize * attributeSize), nullptr, GL_STATIC_DRAW);
#pragma endregion
#pragma region Copy
	glm::vec3 minBound = vertices.at(0).m_position;
	glm::vec3 maxBound = vertices.at(0).m_position;
	for (size_t i = 0; i < m_verticesSize; i++) {
		auto position = vertices.at(i).m_position;
		minBound = glm::vec3(glm::min(minBound.x, position.x), glm::min(minBound.y, position.y), glm::min(minBound.z, position.z));
		maxBound = glm::vec3(glm::max(maxBound.x, position.x), glm::max(maxBound.y, position.y), glm::max(maxBound.z, position.z));
		positions.push_back(vertices.at(i).m_position);
		if (mask & (unsigned)VertexAttribute::Normal) {
			normals.push_back(vertices.at(i).m_normal);
		}
		if (mask & (unsigned)VertexAttribute::Tangent) {
			tangents.push_back(vertices.at(i).m_tangent);
		}
		if (mask & (unsigned)VertexAttribute::Color) {
			colors.push_back(vertices.at(i).m_color);
		}
		if (mask & (unsigned)VertexAttribute::TexCoord0) {
			texcoords0s.push_back(vertices.at(i).m_texCoords0);
		}
		if (mask & (unsigned)VertexAttribute::TexCoord1) {
			texcoords1s.push_back(vertices.at(i).m_texCoords1);
		}
		if (mask & (unsigned)VertexAttribute::TexCoord2) {
			texcoords2s.push_back(vertices.at(i).m_texCoords2);
		}
		if (mask & (unsigned)VertexAttribute::TexCoord3) {
			texcoords3s.push_back(vertices.at(i).m_texCoords3);
		}
		if (mask & (unsigned)VertexAttribute::TexCoord4) {
			texcoords4s.push_back(vertices.at(i).m_texCoords4);
		}
		if (mask & (unsigned)VertexAttribute::TexCoord5) {
			texcoords5s.push_back(vertices.at(i).m_texCoords5);
		}
		if (mask & (unsigned)VertexAttribute::TexCoord6) {
			texcoords6s.push_back(vertices.at(i).m_texCoords6);
		}
		if (mask & (unsigned)VertexAttribute::TexCoord7) {
			texcoords7s.push_back(vertices.at(i).m_texCoords7);
		}
	}
	m_bound.m_max = maxBound;
	m_bound.m_min = minBound;
#pragma endregion
#pragma region ToGPU

	m_vao->SubData(0, m_verticesSize * sizeof(glm::vec3), &positions[0]);

	if (mask & (unsigned)VertexAttribute::Normal)
		m_vao->SubData(m_verticesSize * sizeof(glm::vec3), m_verticesSize * sizeof(glm::vec3), &normals[0]);
	else {
		RecalculateNormal(vertices, triangles);
	}
	if (mask & (unsigned)VertexAttribute::Tangent) {
		m_vao->SubData(m_verticesSize * 2 * sizeof(glm::vec3), m_verticesSize * sizeof(glm::vec3), &tangents[0]);
	}
	else {
		RecalculateTangent(vertices, triangles);
	}
	attributeSize = 3 * sizeof(glm::vec3);
	if (mask & (unsigned)VertexAttribute::Color) {
		m_vao->SubData(m_verticesSize * attributeSize, m_verticesSize * sizeof(glm::vec4), &colors[0]);
		attributeSize += sizeof(glm::vec4);
	}
	if (mask & (unsigned)VertexAttribute::TexCoord0) {
		m_vao->SubData(m_verticesSize * attributeSize, m_verticesSize * sizeof(glm::vec2), &texcoords0s[0]);
		attributeSize += sizeof(glm::vec2);
	}
	if (mask & (unsigned)VertexAttribute::TexCoord1) {
		m_vao->SubData(m_verticesSize * attributeSize, m_verticesSize * sizeof(glm::vec2), &texcoords1s[0]);
		attributeSize += sizeof(glm::vec2);
	}
	if (mask & (unsigned)VertexAttribute::TexCoord2) {
		m_vao->SubData(m_verticesSize * attributeSize, m_verticesSize * sizeof(glm::vec2), &texcoords2s[0]);
		attributeSize += sizeof(glm::vec2);
	}
	if (mask & (unsigned)VertexAttribute::TexCoord3) {
		m_vao->SubData(m_verticesSize * attributeSize, m_verticesSize * sizeof(glm::vec2), &texcoords3s[0]);
		attributeSize += sizeof(glm::vec2);
	}
	if (mask & (unsigned)VertexAttribute::TexCoord4) {
		m_vao->SubData(m_verticesSize * attributeSize, m_verticesSize * sizeof(glm::vec2), &texcoords4s[0]);
		attributeSize += sizeof(glm::vec2);
	}
	if (mask & (unsigned)VertexAttribute::TexCoord5) {
		m_vao->SubData(m_verticesSize * attributeSize, m_verticesSize * sizeof(glm::vec2), &texcoords5s[0]);
		attributeSize += sizeof(glm::vec2);
	}
	if (mask & (unsigned)VertexAttribute::TexCoord6) {
		m_vao->SubData(m_verticesSize * attributeSize, m_verticesSize * sizeof(glm::vec2), &texcoords6s[0]);
		attributeSize += sizeof(glm::vec2);
	}
	if (mask & (unsigned)VertexAttribute::TexCoord7) {
		m_vao->SubData(m_verticesSize * attributeSize, m_verticesSize * sizeof(glm::vec2), &texcoords7s[0]);
		attributeSize += sizeof(glm::vec2);
	}
#pragma endregion
#pragma region AttributePointer
	m_vao->EnableAttributeArray(0);
	m_vao->SetAttributePointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), 0);
	m_vao->EnableAttributeArray(1);
	m_vao->SetAttributePointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)(sizeof(glm::vec3) * m_verticesSize));
	m_vao->EnableAttributeArray(2);
	m_vao->SetAttributePointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)(2 * sizeof(glm::vec3) * m_verticesSize));
	attributeSize = 3 * sizeof(glm::vec3);
	if (mask & (unsigned)VertexAttribute::Color) {
		m_vao->EnableAttributeArray(3);
		m_vao->SetAttributePointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(glm::vec4), (void*)(attributeSize * m_verticesSize));
		attributeSize += sizeof(glm::vec4);
	}
	if (mask & (unsigned)VertexAttribute::TexCoord0) {
		m_vao->EnableAttributeArray(4);
		m_vao->SetAttributePointer(4, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), (void*)(attributeSize * m_verticesSize));
		attributeSize += sizeof(glm::vec2);
	}
	if (mask & (unsigned)VertexAttribute::TexCoord1) {
		m_vao->EnableAttributeArray(5);
		m_vao->SetAttributePointer(5, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), (void*)(attributeSize * m_verticesSize));
		attributeSize += sizeof(glm::vec2);
	}
	if (mask & (unsigned)VertexAttribute::TexCoord2) {
		m_vao->EnableAttributeArray(6);
		m_vao->SetAttributePointer(6, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), (void*)(attributeSize * m_verticesSize));
		attributeSize += sizeof(glm::vec2);
	}
	if (mask & (unsigned)VertexAttribute::TexCoord3) {
		m_vao->EnableAttributeArray(7);
		m_vao->SetAttributePointer(7, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), (void*)(attributeSize * m_verticesSize));
		attributeSize += sizeof(glm::vec2);
	}
	if (mask & (unsigned)VertexAttribute::TexCoord4) {
		m_vao->EnableAttributeArray(8);
		m_vao->SetAttributePointer(8, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), (void*)(attributeSize * m_verticesSize));
		attributeSize += sizeof(glm::vec2);
	}
	if (mask & (unsigned)VertexAttribute::TexCoord5) {
		m_vao->EnableAttributeArray(9);
		m_vao->SetAttributePointer(9, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), (void*)(attributeSize * m_verticesSize));
		attributeSize += sizeof(glm::vec2);
	}
	if (mask & (unsigned)VertexAttribute::TexCoord6) {
		m_vao->EnableAttributeArray(10);
		m_vao->SetAttributePointer(10, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), (void*)(attributeSize * m_verticesSize));
		attributeSize += sizeof(glm::vec2);
	}
	if (mask & (unsigned)VertexAttribute::TexCoord7) {
		m_vao->EnableAttributeArray(11);
		m_vao->SetAttributePointer(11, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), (void*)(attributeSize * m_verticesSize));
		attributeSize += sizeof(glm::vec2);
	}
#pragma endregion
	m_vao->Ebo()->SetData((GLsizei)m_triangleSize * sizeof(glm::uvec3), triangles.data(), GL_STATIC_DRAW);

	m_localStored = store;
	if (store)
	{
		m_vertices.clear();
		m_indices.clear();
		m_vertices.insert(m_vertices.begin(), vertices.begin(), vertices.end());
		m_indices.insert(m_indices.begin(), triangles.begin(), triangles.end());
	}
}


size_t UniEngine::Mesh::GetVerticesAmount() const
{
	return m_triangleSize;
}

size_t UniEngine::Mesh::GetTriangleAmount() const
{
	return m_triangleSize;
}

void UniEngine::Mesh::RecalculateNormal(std::vector<Vertex>& vertices, std::vector<glm::uvec3>& indices) const
{
	std::vector<std::vector<glm::vec3>> normalLists = std::vector<std::vector<glm::vec3>>();
	auto size = vertices.size();
	for (auto i = 0; i < size; i++) {
		normalLists.push_back(std::vector<glm::vec3>());
	}
	for (size_t i = 0; i < m_triangleSize; i++) {
		const auto i1 = indices[i].x;
		const auto i2 = indices[i].y;
		const auto i3 = indices[i].z;
		auto v1 = vertices[i1].m_position;
		auto v2 = vertices[i2].m_position;
		auto v3 = vertices[i3].m_position;
		auto normal = glm::normalize(glm::cross(v1 - v2, v1 - v3));
		normalLists[i1].push_back(normal);
		normalLists[i2].push_back(normal);
		normalLists[i3].push_back(normal);
	}
	std::vector<glm::vec3> normals = std::vector<glm::vec3>();
	for (auto i = 0; i < size; i++) {
		auto normal = glm::vec3(0.0f);
		for (auto j : normalLists[i]) {
			normal += j;
		}
		normals.push_back(glm::normalize(normal));
		vertices[i].m_normal = normal;
	}

	m_vao->SubData(size * sizeof(glm::vec3), size * sizeof(glm::vec3), &normals[0]);
}

void UniEngine::Mesh::RecalculateTangent(std::vector<Vertex>& vertices, std::vector<glm::uvec3>& indices) const
{
	std::vector<std::vector<glm::vec3>> tangentLists = std::vector<std::vector<glm::vec3>>();
	auto size = vertices.size();
	for (auto i = 0; i < size; i++) {
		tangentLists.push_back(std::vector<glm::vec3>());
	}
	for (size_t i = 0; i < m_triangleSize; i++) {
		const auto i1 = indices[i].x;
		const auto i2 = indices[i].y;
		const auto i3 = indices[i].z;
		auto& v1 = vertices[i1];
		auto& v2 = vertices[i2];
		auto& v3 = vertices[i3];
		auto p1 = v1.m_position;
		auto p2 = v2.m_position;
		auto p3 = v3.m_position;
		auto uv1 = v1.m_texCoords0;
		auto uv2 = v2.m_texCoords0;
		auto uv3 = v3.m_texCoords0;

		auto e21 = p2 - p1;
		auto d21 = uv2 - uv1;
		auto e31 = p3 - p1;
		auto d31 = uv3 - uv1;
		float f = 1.0f / (d21.x * d31.y - d31.x * d21.y);
		auto tangent = f * glm::vec3(
			d31.y * e21.x - d21.y * e31.x,
			d31.y * e21.y - d21.y * e31.y,
			d31.y * e21.z - d21.y * e31.z);
		tangentLists[i1].push_back(tangent);
		tangentLists[i2].push_back(tangent);
		tangentLists[i3].push_back(tangent);
	}
	std::vector<glm::vec3> tangents = std::vector<glm::vec3>();
	for (auto i = 0; i < size; i++) {
		auto tangent = glm::vec3(0.0f);
		for (auto j : tangentLists[i]) {
			tangent += j;
		}
		tangents.push_back(glm::normalize(tangent));
		vertices[i].m_tangent = tangent;
	}

	m_vao->SubData(size * 2 * sizeof(glm::vec3), size * sizeof(glm::vec3), &tangents[0]);
}


std::shared_ptr<GLVAO> UniEngine::Mesh::Vao() const
{
	return m_vao;
}

void UniEngine::Mesh::Enable() const
{
	m_vao->Bind();
}

std::vector<Vertex>& Mesh::GetVerticesUnsafe()
{
	return m_vertices;
}

std::vector<glm::uvec3>& Mesh::GetIndicesUnsafe()
{
	return m_indices;
}

