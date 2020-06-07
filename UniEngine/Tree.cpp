#include "Tree.h"

SCTree::Tree::Tree(glm::vec3 position, Material* pointMaterial, Material* meshMaterial, Material* organMaterial)
	: _Position(position),
	_PointMaterial(pointMaterial),
	_MeshMaterial(meshMaterial),
	_OrganMaterial(organMaterial),
	_GrowingBranches(std::vector<Branch*>()),
	_NeedsToGrow(false),
	_Root(new Branch(position, nullptr, true, 1)),
	_MaxGrowIteration(_Root->growIteration),
	_MeshGenerated(false),
	_OrganGenerated(false)
{
}

void SCTree::Tree::Draw(Camera* camera, bool drawOrgan)
{
	if (_PointMatrices.size() > 0) {
		if (_MeshGenerated) {
			glm::mat4 matrix = glm::translate(glm::mat4(1.0f), _Position);
			matrix = glm::scale(matrix, glm::vec3(1.0f));
			RenderManager::DrawMesh(_Mesh, matrix, _MeshMaterial, camera);
			if (drawOrgan && _OrganGenerated) {
				RenderManager::DrawMeshInstanced(Default::Primitives::Quad, _OrganMaterial, &_LeafList[0], _LeafList.size(), camera);
			}
		}
		else RenderManager::DrawMeshInstanced(Default::Primitives::Cube, _PointMaterial, &_PointMatrices[0], _PointMatrices.size(), camera);
	}
}

SCTree::Tree::~Tree()
{
	delete _Root;
}

void SCTree::Tree::GrowTrunk(float growDist, float attractionDist, Envelope* envelope, glm::vec3 tropism)
{
	bool found = false;
	int timeOut = 1000;
	Branch* currentBranch = _Root;
	auto pointsList = envelope->PointPositions();
	auto size = pointsList->size();
	while (!found && timeOut > 0) {
		for (int i = 0; i < size; i++) {
			auto point = pointsList->at(i);
			float dist = glm::distance(currentBranch->position, point);
			if (dist < attractionDist) {
				found = true;
				currentBranch->growDir = glm::vec3(0.0f);
				_GrowingBranches.push_back(currentBranch);
				break;
			}
			currentBranch->growDir += point - currentBranch->position;
		}
		if (!found) {
			auto newBranch = currentBranch->Grow(growDist, true, tropism);
			currentBranch = newBranch;
		}
		timeOut--;
	}
	if (timeOut < 0) {
		Debug::Log("Error generating the trunk");
	}
	_NeedsToGrow = true;
}

void SCTree::Tree::Grow(float growDist, float attractionDist, float removeDist, Envelope* envelope, glm::vec3 tropism, float distDec, float minDist, float decimationDistChild, float decimationDistParent)
{
	auto pointsList = envelope->PointPositions();
	auto size = _GrowingBranches.size();
	int pointSize = pointsList->size();

	for (int i = 0; i < pointSize; i++) {
		auto point = pointsList->at(i);
		float minDists[OMP_THREAD_AMOUNT];
		int minIndices[OMP_THREAD_AMOUNT];
		for (int j = 0; j < OMP_THREAD_AMOUNT; j++) {
			minDists[j] = 9999999;
			minIndices[j] = -1;
		}
		omp_set_num_threads(OMP_THREAD_AMOUNT);
#pragma omp parallel for shared(pointsList, minDists, minIndices)
		for (int j = 0; j < size; j++) {
			float dist = glm::distance(point, _GrowingBranches[j]->position);
			if (dist < minDists[omp_get_thread_num()]) {
				minDists[omp_get_thread_num()] = dist;
				minIndices[omp_get_thread_num()] = j;
			}
		}
		float minDistance = 9999999;
		int minIndex = -1;
		for (int j = 0; j < OMP_THREAD_AMOUNT; j++) {
			if (minDistance > minDists[j]) {
				minDistance = minDists[j];
				minIndex = minIndices[j];
			}
		}
		if (minDistance <= attractionDist && minIndex >= 0) {
			_GrowingBranches[minIndex]->growDir += glm::normalize(point - _GrowingBranches[minIndex]->position);
		}
	}

	bool addedNewBranch = false;

	std::vector<Branch*> resultsList[OMP_THREAD_AMOUNT];
	omp_set_num_threads(OMP_THREAD_AMOUNT);
#pragma omp parallel for shared(resultsList)
	for (int i = 0; i < size; i++) {
		Branch* newBranch = _GrowingBranches[i]->Grow(growDist, false, tropism, distDec, minDist, decimationDistChild, decimationDistParent);
		if (newBranch == nullptr) _GrowingBranches[i] = nullptr;
		else resultsList[omp_get_thread_num()].push_back(newBranch);
	}
	for (size_t i = 0; i < size; i++) {
		if (_GrowingBranches[i] == nullptr) {
			_GrowingBranches.erase(_GrowingBranches.begin() + i);
			i--;
			size--;
		}
	}

	for (size_t i = 0; i < OMP_THREAD_AMOUNT; i++) {
		int resultSize = resultsList[i].size();
		for (size_t j = 0; j < resultSize; j++) {
			auto newBranch = resultsList[i][j];
			_GrowingBranches.push_back(newBranch);
			if (newBranch->growIteration > _MaxGrowIteration) _MaxGrowIteration = newBranch->growIteration;
			addedNewBranch = true;
		}
	}




	size = pointsList->size();
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < _GrowingBranches.size(); j++) {
			if (glm::distance(pointsList->at(i), _GrowingBranches[j]->position) <= removeDist) {
				envelope->RemovePointSwapBack(i);
				size--;
				i--;
				break;
			}
		}
	}

	if (!addedNewBranch) {
		_NeedsToGrow = false;
		Debug::Log("Grow complete.");

		envelope->Clear();

		NodeRelocation();
		Debug::Log("Node Relocation complete.");

		CalculateRadius();
		Debug::Log("Radius Calculation complete.");

		NodeSubdivision();
		Debug::Log("Node Subdivision complete.");

		CollectPoints();
		Debug::Log("Points Collection complete.");

		CalculateMesh(16, 16384);
		Debug::Log("Mesh Generation complete.");

		GenerateOrgan();
		Debug::Log("Organ Generation complete.");
		return;
	}

	CalculateRadius();
	CollectPoints();
}

void SCTree::Tree::CalculateMesh(int resolution, int triangleLimit)
{
	int maxVerticesAmount = triangleLimit * 3;
	_MeshGenerated = false;

	std::vector<Vertex> vertices = std::vector<Vertex>();
	std::vector<unsigned int> indices = std::vector<unsigned int>();
	_Root->CalculateMesh(_Position, &vertices, resolution);
	size_t size = vertices.size();
	for (int i = 0; i < size; i++) {
		indices.push_back(i);
	}
	

	if (_Mesh != nullptr) delete _Mesh;
	_Mesh = new Mesh();

	_Mesh->SetVertices(33, &vertices, &indices);

	_MeshGenerated = true;
}

inline void SCTree::Tree::CalculateRadius() {
	_Root->CalculateRadius(_MaxGrowIteration, 3.0f);
}

inline void SCTree::Tree::CollectPoints() {
	_PointMatrices.clear();
	_Root->CollectPoint(&_PointMatrices);
}

inline void SCTree::Tree::NodeRelocation() {
	Debug::Log("Node Relocation...");
	_Root->Relocation();
}

inline void SCTree::Tree::NodeSubdivision() {
	Debug::Log("Node Subdivision...");
	_Root->Subdivision(_Position, glm::vec3(0.0f, 1.0f, 0.0f), 1);
}

inline void SCTree::Tree::GenerateOrgan() {
	Debug::Log("Generating Organ...");
	_Root->GenerateOrgan(&_LeafList, _MaxGrowIteration);
	_OrganGenerated = true;
}