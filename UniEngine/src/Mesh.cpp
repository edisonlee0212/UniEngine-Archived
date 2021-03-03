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
	m_indicesSize = 0;
	m_bound = Bound();
	m_name = "New mesh";
}

void UniEngine::Mesh::SetVertices(unsigned mask, std::vector<Vertex>& vertices, std::vector<unsigned>& indices, bool store)
{
	m_mask = mask;
	m_indicesSize = indices.size();
	m_verticesSize = vertices.size();
	if (m_verticesSize == 0) {
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
		RecalculateNormal(vertices, indices);
	}
	if (mask & (unsigned)VertexAttribute::Tangent) {
		m_vao->SubData(m_verticesSize * 2 * sizeof(glm::vec3), m_verticesSize * sizeof(glm::vec3), &tangents[0]);
	}
	else {
		RecalculateTangent(vertices, indices);
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
	m_vao->Ebo()->SetData((GLsizei)m_indicesSize * sizeof(unsigned), &indices.at(0), GL_STATIC_DRAW);

	m_localStored = store;
	if (store)
	{
		m_vertices.resize(vertices.size());
		m_indices.resize(indices.size());
		memcpy(m_vertices.data(), vertices.data(), vertices.size() * sizeof(Vertex));
		memcpy(m_indices.data(), indices.data(), indices.size() * sizeof(unsigned));
	}
}


size_t UniEngine::Mesh::GetVerticesAmount()
{
	return m_indicesSize;
}

size_t UniEngine::Mesh::Size()
{
	return m_indicesSize;
}

void UniEngine::Mesh::RecalculateNormal(std::vector<Vertex>& vertices, std::vector<unsigned>& indices)
{
	std::vector<std::vector<glm::vec3>> normalLists = std::vector<std::vector<glm::vec3>>();
	auto size = vertices.size();
	for (auto i = 0; i < size; i++) {
		normalLists.push_back(std::vector<glm::vec3>());
	}
	for (size_t i = 0; i < m_indicesSize / 3; i++) {
		auto v1 = vertices.at(indices.at(3 * i)).m_position;
		auto v2 = vertices.at(indices.at(3 * i + 1)).m_position;
		auto v3 = vertices.at(indices.at(3 * i + 2)).m_position;
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

	m_vao->SubData(size * sizeof(glm::vec3), size * sizeof(glm::vec3), &normals[0]);
}

void UniEngine::Mesh::RecalculateTangent(std::vector<Vertex>& vertices, std::vector<unsigned>& indices)
{
	std::vector<std::vector<glm::vec3>> tangentLists = std::vector<std::vector<glm::vec3>>();
	auto size = vertices.size();
	for (auto i = 0; i < size; i++) {
		tangentLists.push_back(std::vector<glm::vec3>());
	}
	for (size_t i = 0; i < m_indicesSize / 3; i++) {
		auto v1 = vertices.at(indices.at(3 * i)).m_position;
		auto v2 = vertices.at(indices.at(3 * i + 1)).m_position;
		auto v3 = vertices.at(indices.at(3 * i + 2)).m_position;
		auto uv1 = vertices.at(indices.at(3 * i)).m_texCoords0;
		auto uv2 = vertices.at(indices.at(3 * i + 1)).m_texCoords0;
		auto uv3 = vertices.at(indices.at(3 * i + 2)).m_texCoords0;

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

	m_vao->SubData(size * 2 * sizeof(glm::vec3), size * sizeof(glm::vec3), &tangents[0]);
}


std::shared_ptr<GLVAO> UniEngine::Mesh::Vao()
{
	return m_vao;
}

void UniEngine::Mesh::Enable()
{
	m_vao->Bind();
}

std::vector<Vertex>& Mesh::GetVerticesUnsafe()
{
	return m_vertices;
}

std::vector<unsigned>& Mesh::GetIndicesUnsafe()
{
	return m_indices;
}

void Mesh::LoadBin(std::string& fileName)
{
	std::ifstream ifs(fileName, std::ios::binary);
	if (ifs.fail()) {
		Debug::Error("INFO: cannot open file: ");
		return;
	}
	int vertN = 0;
	ifs.read((char*)&vertN, sizeof(int));
	m_verticesSize = vertN;
	char yn;
	ifs.read(&yn, 1); // always xyz
	if (yn != 'y') {
		Debug::Error("INTERNAL ERROR: there should always be vertex xyz data");
		return;
	}
	m_vertices.resize(m_verticesSize);
	bool hasColor = false;
	bool hasNormal = false;
	bool hasTextureCoords = false;
	ifs.read(&yn, 1); // Color
	if (yn == 'y') {
		hasColor = true;
	}
	ifs.read(&yn, 1); // Normal
	if (yn == 'y') {
		hasNormal = true;
	}
	ifs.read(&yn, 1); // TexCoords
	if (yn == 'y') {
		hasTextureCoords = true;
	}
	for(int i = 0; i < m_verticesSize; i++)
	{
		ifs.read((char*)&m_vertices[i], sizeof(glm::vec3));
	}
	if(hasColor)
	{
		for (int i = 0; i < m_verticesSize; i++)
		{
			ifs.read((char*)(&m_vertices[i]) + offsetof(Vertex, m_color), sizeof(glm::vec3));
		}
	}
	if (hasNormal)
	{
		for (int i = 0; i < m_verticesSize; i++)
		{
			ifs.read((char*)(&m_vertices[i]) + offsetof(Vertex, m_normal), sizeof(glm::vec3));
		}
	}
	glm::vec3 temp;
	if (hasTextureCoords)
	{
		for (int i = 0; i < m_verticesSize; i++)
		{
			//ifs.read((char*)(&_Vertices[i]) + offsetof(Vertex, TexCoords0), sizeof(glm::vec2));
			ifs.read((char*)&temp, sizeof(glm::vec2));
		}
	}
	int trisN = 0;
	ifs.read((char*)&trisN, sizeof(int));
	m_indicesSize = trisN;
	m_indicesSize = m_indicesSize * 3;
	m_indices.resize(m_indicesSize);

	for (int i = 0; i < m_indicesSize; i++)
	{
		ifs.read((char*)&m_indices[i], sizeof(unsigned));
	}
	unsigned mask = 1;
	if (hasColor)
	{
		mask += (unsigned)VertexAttribute::Color;
	}
	if (hasNormal)
	{
		mask += (unsigned)VertexAttribute::Normal;
	}
	if (hasTextureCoords)
	{
		//mask += (int)VertexAttribute::TexCoord0;
	}
	SetVertices(mask, m_vertices, m_indices);
	m_localStored = true;
}


