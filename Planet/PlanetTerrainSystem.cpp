#include "PlanetTerrainSystem.h"
#include <gtc/noise.hpp>
void Planet::PlanetTerrainSystem::GenerateTerrain(std::shared_ptr<PlanetTerrain>& planetTerrain, std::shared_ptr<TerrainChunk>& targetChunk) const
{
	if (targetChunk->_Mesh != nullptr) {
		Debug::Error("Mesh Exist!");
	}
	auto mesh = std::make_unique<Mesh>();
	std::vector<Vertex>& vertices = planetTerrain->_SharedVertices;
	auto size = vertices.size();
	auto resolution = planetTerrain->_Info.Resolution;
	for (auto index = 0; index < size; index++) {
		int actualDetailLevel = (int)glm::pow(2, targetChunk->DetailLevel);
		int x = index % resolution;
		int y = index / resolution;
		glm::dvec2 percent = glm::dvec2(x, y) / (double)(resolution - 1) / (double)actualDetailLevel;
		glm::dvec2 globalPercent = 45.0 * glm::dvec2((percent.x + (double)targetChunk->ChunkCoordinate.x / actualDetailLevel - 0.5) * 2.0, (percent.y + (double)targetChunk->ChunkCoordinate.y / actualDetailLevel - 0.5) * 2.0);
		glm::dvec2 actualPercent = glm::dvec2(glm::tan(glm::radians(globalPercent.x)), glm::tan(glm::radians(globalPercent.y)));
		glm::dvec3 pointOnUnitCube = targetChunk->LocalUp + actualPercent.x * targetChunk->AxisA + actualPercent.y * targetChunk->AxisB;
		pointOnUnitCube = glm::normalize(pointOnUnitCube);
		double elevation = 0;
		elevation = glm::simplex(pointOnUnitCube) * 0.05;
		double previousResult = 0;
		/*
		for (int j = 0; j < shapeConstructionStages.Length; j++)
		{
			previousResult = shapeConstructionStages[j].Process(pointOnUnitCube, ref noise, previousResult, elevation);
			elevation += previousResult;
		}*/
		vertices.at(index).Position = glm::vec3(pointOnUnitCube * planetTerrain->_Info.Radius * (1.0 + elevation));
	}
	mesh->SetVertices(1 | (unsigned)VertexAttribute::TexCoord0, planetTerrain->_SharedVertices, planetTerrain->_SharedTriangles);
	targetChunk->_Mesh = std::move(mesh);
}

void Planet::PlanetTerrainSystem::SetMaxMeshAmount(unsigned amount)
{
	_MaxRecycledMeshAmount = amount;
}

void Planet::PlanetTerrainSystem::CreatePlanet(PlanetInfo info)
{
	auto terrain = std::make_shared<PlanetTerrain>(info, _DefaultSurfaceMaterial, _GenerationQueue);
	_PlanetTerrainList.push_back(terrain);
	while (!_GenerationQueue.empty()) {
		auto chunk = _GenerationQueue.front();
		_GenerationQueue.pop();
		if (chunk->_Mesh == nullptr) {
			GenerateTerrain(terrain, chunk);
		}
		auto size = terrain->_ChunkList.size();
		chunk->Index = size;
		chunk->TooFar = false;
		terrain->_ChunkList.push_back(chunk);
	}
}

void Planet::PlanetTerrainSystem::OnCreate()
{
	_GenerationQueue = std::queue<std::shared_ptr<TerrainChunk>>();
	_PlanetTerrainList = std::vector<std::shared_ptr<PlanetTerrain>>();
	_MaxRecycledMeshAmount = 50;
	_DefaultSurfaceMaterial = std::make_shared<Material>();
	_DefaultSurfaceMaterial->SetProgram(Default::GLPrograms::StandardProgram);
	_DefaultSurfaceMaterial->SetTexture(Default::Textures::UV, TextureType::DIFFUSE);
}

void Planet::PlanetTerrainSystem::Update()
{
	for (auto i = 0; i < _PlanetTerrainList.size(); i++) {
		auto planetChunks = _PlanetTerrainList[i]->_ChunkList;
		auto planetInfo = _PlanetTerrainList[i]->_Info;
		glm::mat4 matrix = glm::scale(glm::translate(glm::mat4_cast(planetInfo.Rotation), glm::vec3(planetInfo.Position)), glm::vec3(1.0f));
		for (auto j = 0; j < planetChunks.size(); j++) {
			//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			RenderManager::DrawMesh(planetChunks[j]->_Mesh.get(), _DefaultSurfaceMaterial.get(), matrix, RenderManager::GetMainCamera(), true);
			//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		}
	}

	auto cameraLtw = RenderManager::GetMainCamera()->GetOwner().GetComponentData<LocalToWorld>();
	for (auto i = 0; i < _PlanetTerrainList.size(); i++) {
		auto planetTerrain = _PlanetTerrainList[i];
		auto planetInfo = planetTerrain->_Info;
		//1. Scan and expand.
		for (auto j = 0; j < planetTerrain->_ChunkList.size(); j++) {
			auto chunk = planetTerrain->_ChunkList[j];
			if (glm::distance(glm::vec3(chunk->ChunkCenterPosition(planetInfo.Position, planetInfo.Radius, planetInfo.Rotation)), cameraLtw.GetPosition())
				< (planetInfo.LodDistance * planetInfo.Radius / glm::pow(2, chunk->DetailLevel + 1))) {
				if (chunk->DetailLevel < planetInfo.MaxLodLevel) {
					if (chunk->C0 != nullptr) {
						_GenerationQueue.push(chunk->C0);
						Remove(planetTerrain->_RecycledChunkList, chunk->C0->Index);
					}
					else {
						chunk->C0 = std::make_shared<TerrainChunk>(chunk, 0, chunk->DetailLevel + 1, glm::ivec2(chunk->ChunkCoordinate.x * 2, chunk->ChunkCoordinate.y * 2 + 1), ChunkDirection::UpperLeft, chunk->LocalUp);
						_GenerationQueue.push(chunk->C0);

					}
					if (chunk->C1 != nullptr) {
						_GenerationQueue.push(chunk->C1);
						Remove(planetTerrain->_RecycledChunkList, chunk->C1->Index);
					}
					else {
						chunk->C1 = std::make_shared<TerrainChunk>(chunk, 0, chunk->DetailLevel + 1, glm::ivec2(chunk->ChunkCoordinate.x * 2 + 1, chunk->ChunkCoordinate.y * 2 + 1), ChunkDirection::UpperRight, chunk->LocalUp);
						_GenerationQueue.push(chunk->C1);
					}
					if (chunk->C2 != nullptr) {
						_GenerationQueue.push(chunk->C2);
						Remove(planetTerrain->_RecycledChunkList, chunk->C2->Index);
					}
					else {
						chunk->C2 = std::make_shared<TerrainChunk>(chunk, 0, chunk->DetailLevel + 1, glm::ivec2(chunk->ChunkCoordinate.x * 2, chunk->ChunkCoordinate.y * 2), ChunkDirection::LowerLeft, chunk->LocalUp);
						_GenerationQueue.push(chunk->C2);
					}
					if (chunk->C3 != nullptr) {
						_GenerationQueue.push(chunk->C3);
						Remove(planetTerrain->_RecycledChunkList, chunk->C3->Index);
					}
					else {
						chunk->C3 = std::make_shared<TerrainChunk>(chunk, 0, chunk->DetailLevel + 1, glm::ivec2(chunk->ChunkCoordinate.x * 2 + 1, chunk->ChunkCoordinate.y * 2), ChunkDirection::LowerRight, chunk->LocalUp);
						_GenerationQueue.push(chunk->C3);
					}
					Remove(planetTerrain->_ChunkList, j);
					planetTerrain->_WaitingList.push_back(chunk);
					chunk->ToRecycle = true;
				}
			}
			else if (glm::distance(glm::vec3(chunk->ChunkCenterPosition(planetInfo.Position, planetInfo.Radius, planetInfo.Rotation)), cameraLtw.GetPosition())
				> (planetInfo.LodDistance * planetInfo.Radius / glm::pow(2, chunk->DetailLevel)))
			{
				if (chunk->Parent != nullptr) {
					chunk->TooFar = true;
				}
			}
		}

		//2. Generate meshes.
		while (!_GenerationQueue.empty()) {
			auto c1 = _GenerationQueue.front();
			_GenerationQueue.pop();
			auto c2 = _GenerationQueue.front();
			_GenerationQueue.pop();
			auto c3 = _GenerationQueue.front();
			_GenerationQueue.pop();
			auto c4 = _GenerationQueue.front();
			_GenerationQueue.pop();
			if (c1->_Mesh == nullptr) {
				GenerateTerrain(planetTerrain, c1);
			}
			if (c2->_Mesh == nullptr) {
				GenerateTerrain(planetTerrain, c2);
			}
			if (c3->_Mesh == nullptr) {
				GenerateTerrain(planetTerrain, c3);
			}
			if (c4->_Mesh == nullptr) {
				GenerateTerrain(planetTerrain, c4);
			}
			auto size = planetTerrain->_ChunkList.size();
			c1->Index = size;
			c2->Index = size + 1;
			c3->Index = size + 2;
			c4->Index = size + 3;
			c1->TooFar = false;
			c2->TooFar = false;
			c3->TooFar = false;
			c4->TooFar = false;
			c1->ToRecycle = false;
			c2->ToRecycle = false;
			c3->ToRecycle = false;
			c4->ToRecycle = false;
			planetTerrain->_ChunkList.push_back(c1);
			planetTerrain->_ChunkList.push_back(c2);
			planetTerrain->_ChunkList.push_back(c3);
			planetTerrain->_ChunkList.push_back(c4);
		}

		for (auto j : planetTerrain->_WaitingList) {
			j->Index = planetTerrain->_RecycledChunkList.size();
			planetTerrain->_RecycledChunkList.push_back(j);
		}

		planetTerrain->_WaitingList.clear();

		//3. Scan and collapse.
		for (auto j = 0; j < planetTerrain->_RecycledChunkList.size(); j++) {
			auto chunk = planetTerrain->_RecycledChunkList[j];
			if (chunk->C0 == nullptr || chunk->C1 == nullptr || chunk->C2 == nullptr || chunk->C3 == nullptr) continue;
			if (chunk->C0->ToRecycle || chunk->C1->ToRecycle || chunk->C2->ToRecycle || chunk->C3->ToRecycle) continue;
			if (chunk->C0->TooFar && chunk->C1->TooFar && chunk->C2->TooFar && chunk->C3->TooFar) {
				Remove(planetTerrain->_RecycledChunkList, j);
				_GenerationQueue.push(chunk);
				Remove(planetTerrain->_ChunkList, chunk->C0->Index);
				planetTerrain->_WaitingList.push_back(chunk->C0);
				chunk->C0->ToRecycle = true;
				Remove(planetTerrain->_ChunkList, chunk->C1->Index);
				planetTerrain->_WaitingList.push_back(chunk->C1);
				chunk->C1->ToRecycle = true;
				Remove(planetTerrain->_ChunkList, chunk->C2->Index);
				planetTerrain->_WaitingList.push_back(chunk->C2);
				chunk->C2->ToRecycle = true;
				Remove(planetTerrain->_ChunkList, chunk->C3->Index);
				planetTerrain->_WaitingList.push_back(chunk->C3);
				chunk->C3->ToRecycle = true;
			}
		}

		//4. Recycle chunk.

		while (!_GenerationQueue.empty()) {
			auto chunk = _GenerationQueue.front();
			_GenerationQueue.pop();
			if (chunk->_Mesh == nullptr) {
				GenerateTerrain(planetTerrain, chunk);
			}
			chunk->Index = planetTerrain->_ChunkList.size();
			chunk->TooFar = false;
			chunk->ToRecycle = false;
			planetTerrain->_ChunkList.push_back(chunk);
		}

		for (auto j : planetTerrain->_WaitingList) {
			j->Index = planetTerrain->_RecycledChunkList.size();
			planetTerrain->_RecycledChunkList.push_back(j);
		}
		planetTerrain->_WaitingList.clear();

		//Release mesh from GPU memory.
		for (auto j = _MaxRecycledMeshAmount; j < planetTerrain->_RecycledChunkList.size(); j++) {
			planetTerrain->_RecycledChunkList[i]->_Mesh.reset();
		}
	}

}

void Planet::PlanetTerrainSystem::FixedUpdate()
{
}

void Planet::PlanetTerrainSystem::Remove(std::vector<std::shared_ptr<TerrainChunk>>& list, unsigned index)
{
	list.at(index) = list.back();
	list.at(index)->Index = index;
	list.pop_back();
}
