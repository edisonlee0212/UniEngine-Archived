#include "pch.h"
#include "RingMesh.h"

TreeUtilities::RingMesh::RingMesh(glm::vec3 startPosition, glm::vec3 endPosition, glm::vec3 startAxis, glm::vec3 endAxis, float startRadius, float endRadius)
	: StartPosition(startPosition),
	EndPosition(endPosition),
	StartAxis(startAxis),
	EndAxis(endAxis),
	StartRadius(startRadius),
	EndRadius(endRadius)
{
}

void TreeUtilities::RingMesh::AppendPoints(std::vector<Vertex>& vertices, int resolution)
{
	std::vector<Vertex> startRing;
	std::vector<Vertex> endRing;
	float angleStep = 360.0f / (float)(resolution);
	Vertex archetype;
	for (int i = 0; i < resolution; i++) {
		archetype.Position = GetPoint(angleStep * i, true);
		startRing.push_back(archetype);
	}
	for (int i = 0; i < resolution; i++) {
		archetype.Position = GetPoint(angleStep * i, false);
		endRing.push_back(archetype);
	}
	float textureXstep = 1.0f / resolution * 4;
	for (int i = 0; i < resolution - 1; i++) {
		float x = (i % resolution) * textureXstep;
		startRing[i].TexCoords0 = glm::vec2(x, 0.0f);
		startRing[i + 1].TexCoords0 = glm::vec2(x + textureXstep, 0.0f);
		endRing[i].TexCoords0 = glm::vec2(x, 1.0f);
		endRing[i + 1].TexCoords0 = glm::vec2(x + textureXstep, 1.0f);
		vertices.push_back(startRing[i]);
		vertices.push_back(startRing[i + 1]);
		vertices.push_back(endRing[i]);
		vertices.push_back(endRing[i + 1]);
		vertices.push_back(endRing[i]);
		vertices.push_back(startRing[i + 1]);
	}
	startRing[resolution - 1].TexCoords0 = glm::vec2(1.0f - textureXstep, 0.0f);
	startRing[0].TexCoords0 = glm::vec2(1.0f, 0.0f);
	endRing[resolution - 1].TexCoords0 = glm::vec2(1.0f - textureXstep, 1.0f);
	endRing[0].TexCoords0 = glm::vec2(1.0f, 1.0f);
	vertices.push_back(startRing[resolution - 1]);
	vertices.push_back(startRing[0]);
	vertices.push_back(endRing[resolution - 1]);
	vertices.push_back(endRing[0]);
	vertices.push_back(endRing[resolution - 1]);
	vertices.push_back(startRing[0]);
}

inline glm::vec3 TreeUtilities::RingMesh::GetPoint(float angle, bool isStart)
{
	glm::vec3 position;
	glm::vec3 tmp = glm::vec3(0.0f);
	tmp.x = glm::sin(3.1415926f * angle / 180.0f);
	tmp.y = 0;
	tmp.z = glm::cos(3.1415926f * angle / 180.0f);

	glm::vec3 direction = glm::cross(tmp, isStart ? this->StartAxis : this->EndAxis);

	direction = glm::normalize(direction);
	position = (isStart ? this->StartPosition : this->EndPosition) + direction * (isStart ? this->StartRadius : this->EndRadius);

	return position;
}
