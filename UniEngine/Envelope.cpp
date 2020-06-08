#include "Envelope.h"

using namespace UniEngine;
SCTree::Envelope::Envelope(glm::vec3 spaceOffset, glm::vec3 spaceSize)
{
	_SpaceOffset = spaceOffset;
	_SpaceSize = spaceSize;
	_PointsGenerated = false;
	_PointPositions = std::vector<glm::vec3>();
	_PointMatrices = std::vector<glm::mat4>();
}

SCTree::Envelope::~Envelope()
{
}

void SCTree::Envelope::GeneratePoints(size_t amount)
{
	Clear();
	int size = 0;
	while (size < amount) {
		glm::vec3 point = _SpaceOffset + glm::vec3(_SpaceSize.x * (float)rand() / (RAND_MAX),
			_SpaceSize.y * (float)rand() / (RAND_MAX),
			_SpaceSize.z * (float)rand() / (RAND_MAX));
		if (IsInEnvelope(point)) {
			AddPoint(point);
			size++;
		}
	}
	_PointsGenerated = true;
}

void SCTree::Envelope::AddPoint(glm::vec3 point, glm::vec3 scale)
{
	glm::mat4 matrix = glm::translate(glm::mat4(1.0f), point);
	matrix = glm::scale(matrix, scale);
	_PointPositions.push_back(point);
	_PointMatrices.push_back(matrix);
}

void SCTree::Envelope::RemovePointSwapBack(int index)
{
	_PointPositions[index] = _PointPositions.back();
	_PointMatrices[index] = _PointMatrices.back();
	_PointPositions.pop_back();
	_PointMatrices.pop_back();
}

void SCTree::Envelope::Clear()
{
	_PointPositions.clear();
	_PointMatrices.clear();
	_PointsGenerated = false;
}

bool SCTree::Envelope::PointsGenerated()
{
	return _PointsGenerated;
}

void SCTree::Envelope::Draw(Camera* camera, Material* pointMaterial)
{
	if (_PointMatrices.size() > 0) {
		RenderManager::DrawMeshInstanced(Default::Primitives::Sphere, pointMaterial, &_PointMatrices[0], _PointMatrices.size(), camera);
	}
}

std::vector<glm::vec3>* SCTree::Envelope::PointPositions()
{
	return &_PointPositions;
}
