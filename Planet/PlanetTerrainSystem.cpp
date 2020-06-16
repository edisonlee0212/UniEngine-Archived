#include "PlanetTerrainSystem.h"

void Planet::PlanetTerrainSystem::GenerateTerrain(PlanetTerrain* planetTerrain, TerrainChunk* targetChunk)
{
	if (targetChunk->_Mesh != nullptr) {
		Debug::Error("Mesh Exist!");
	}
	Mesh* mesh = new Mesh();
	std::vector<Vertex>* vertices = &planetTerrain->_SharedVertices;
	auto size = vertices->size();
	auto resolution = planetTerrain->_Info.Resolution;
	for (auto index = 0; index < size; index++) {
		int actualDetailLevel = (int)glm::pow(2, targetChunk->DetailLevel);
		int x = index % resolution;
		int y = index / resolution;
		glm::dvec2 percent = glm::dvec2(x, y) / (double)(resolution - 1) / (double)actualDetailLevel;
		glm::dvec3 pointOnUnitCube = targetChunk->LocalUp + (percent.x + (double)targetChunk->ChunkCoordinate.x / actualDetailLevel - 0.5) * 2 * targetChunk->AxisA + (percent.y + (double)targetChunk->ChunkCoordinate.y / actualDetailLevel - 0.5) * 2 * targetChunk->AxisB;
		pointOnUnitCube = glm::normalize(pointOnUnitCube);
		double elevation = 0;
		double previousResult = 0;
		/*
		for (int j = 0; j < shapeConstructionStages.Length; j++)
		{
			previousResult = shapeConstructionStages[j].Process(pointOnUnitCube, ref noise, previousResult, elevation);
			elevation += previousResult;
		}*/
		vertices->at(index).Position = glm::vec3(pointOnUnitCube * planetTerrain->_Info.Radius * (1.0 + elevation));
	}
	mesh->SetVertices(1, vertices, &planetTerrain->_SharedTriangles);
	targetChunk->_Mesh = mesh;
}

void Planet::PlanetTerrainSystem::SetCameraEntity(Entity* targetEntity)
{
	_TargetCameraEntity = targetEntity;
}

void Planet::PlanetTerrainSystem::CreatePlanet(PlanetInfo info)
{
	PlanetTerrain* terrain = new PlanetTerrain(info, Default::Materials::StandardMaterial, &_GenerationQueue);
	_PlanetTerrainList.push_back(terrain);
	while (!_GenerationQueue.empty()) {
		auto chunk = _GenerationQueue.front();
		_GenerationQueue.pop();
		if (chunk->_Mesh == nullptr) {
			GenerateTerrain(terrain, chunk);
		}
		auto size = terrain->_ChunkList.size();
		chunk->Index = size;
		chunk->ToRecycle = false;
		terrain->_ChunkList.push_back(chunk);
	}
}

void Planet::PlanetTerrainSystem::OnCreate()
{
	_GenerationQueue = std::queue<TerrainChunk*>();
	_PlanetTerrainList = std::vector<PlanetTerrain*>();
}

void Planet::PlanetTerrainSystem::Update()
{
	auto camera = _EntityCollection->GetSharedComponent<CameraComponent>(_TargetCameraEntity)->Value;
	for (auto i = 0; i < _PlanetTerrainList.size(); i++) {
		auto planetChunks = _PlanetTerrainList[i]->_ChunkList;
		auto planetInfo = _PlanetTerrainList[i]->_Info;
		glm::mat4 matrix = glm::scale(glm::translate(glm::mat4_cast(planetInfo.Rotation), glm::vec3(planetInfo.Position)), glm::vec3(1.0f));
		for (auto j = 0; j < planetChunks.size(); j++) {
			RenderManager::DrawMesh(planetChunks[j]->_Mesh, Default::Materials::StandardMaterial, matrix, camera);
		}
	}
}

void Planet::PlanetTerrainSystem::FixedUpdate()
{
	Position cameraPos = _EntityCollection->GetFixedData<Position>(_TargetCameraEntity);

	for (auto i = 0; i < _PlanetTerrainList.size(); i++) {
		auto planetTerrain = _PlanetTerrainList[i];
		auto planetInfo = planetTerrain->_Info;
		//1. Scan and expand.
		for (auto j = 0; j < planetTerrain->_ChunkList.size(); j++) {
			auto chunk = planetTerrain->_ChunkList[j];
			if (glm::distance(glm::vec3(chunk->ChunkCenterPosition(planetInfo.Position, planetInfo.Radius, planetInfo.Rotation)), cameraPos.value)
				< (planetInfo.LodDistance * planetInfo.Radius / glm::pow(2, chunk->DetailLevel + 1))) {
				if (chunk->C0 != nullptr) {
					_GenerationQueue.push(chunk->C0);
					//TODO: Dont forget to reset index.
					Remove(&planetTerrain->_RecycledChunkList, chunk->C0->Index);
				}
				else {
					//TODO: Dont forget to reset index.
					_GenerationQueue.push(new TerrainChunk(chunk, 0, chunk->DetailLevel + 1, glm::ivec2(chunk->ChunkCoordinate.x * 2, chunk->ChunkCoordinate.y * 2 + 1), ChunkDirection::UpperLeft, chunk->LocalUp));
					
				}
				if (chunk->C1 != nullptr) {
					_GenerationQueue.push(chunk->C1);
					Remove(&planetTerrain->_RecycledChunkList, chunk->C1->Index);
				}
				else {
					_GenerationQueue.push(new TerrainChunk(chunk, 0, chunk->DetailLevel + 1, glm::ivec2(chunk->ChunkCoordinate.x * 2 + 1, chunk->ChunkCoordinate.y * 2 + 1), ChunkDirection::UpperRight, chunk->LocalUp));
				}
				if (chunk->C2 != nullptr) {
					_GenerationQueue.push(chunk->C2);
					Remove(&planetTerrain->_RecycledChunkList, chunk->C2->Index);
				}
				else {
					_GenerationQueue.push(new TerrainChunk(chunk, 0, chunk->DetailLevel + 1, glm::ivec2(chunk->ChunkCoordinate.x * 2, chunk->ChunkCoordinate.y * 2), ChunkDirection::LowerLeft, chunk->LocalUp));
				}
				if (chunk->C3 != nullptr) {
					_GenerationQueue.push(chunk->C3);
					Remove(&planetTerrain->_RecycledChunkList, chunk->C3->Index);
				}
				else {
					_GenerationQueue.push(new TerrainChunk(chunk, 0, chunk->DetailLevel + 1, glm::ivec2(chunk->ChunkCoordinate.x * 2 + 1, chunk->ChunkCoordinate.y * 2), ChunkDirection::LowerRight, chunk->LocalUp));
				}
				_RecycleQueue.push(chunk->Index);
			}
			else
			{
				planetTerrain->_ChunkList[j]->ToRecycle = true;
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
			c1->ToRecycle = false;
			c2->ToRecycle = false;
			c3->ToRecycle = false;
			c4->ToRecycle = false;
			planetTerrain->_ChunkList.push_back(c1);
			planetTerrain->_ChunkList.push_back(c2);
			planetTerrain->_ChunkList.push_back(c3);
			planetTerrain->_ChunkList.push_back(c4);
			auto recycle = planetTerrain->_ChunkList[_RecycleQueue.front()];
			Remove(&planetTerrain->_ChunkList, _RecycleQueue.front());
			recycle->Index = planetTerrain->_RecycledChunkList.size();
			planetTerrain->_RecycledChunkList.push_back(recycle);
			_RecycleQueue.pop();
		}

		//3. Scan and collapse.
		for (auto i = 0; i < planetTerrain->_RecycledChunkList.size(); i++) {
			auto chunk = planetTerrain->_RecycledChunkList[i];
			if (chunk->C0 == nullptr || chunk->C1 == nullptr || chunk->C2 == nullptr || chunk->C3 == nullptr) continue;
			if (chunk->C0->ToRecycle && chunk->C1->ToRecycle && chunk->C2->ToRecycle && chunk->C3->ToRecycle) {
				_GenerationQueue.push(chunk);
				_RecycleQueue.push(chunk->C0->Index);
				_RecycleQueue.push(chunk->C1->Index);
				_RecycleQueue.push(chunk->C2->Index);
				_RecycleQueue.push(chunk->C3->Index);
			}
		}

		//4. Recycle chunk.

		while (!_GenerationQueue.empty()) {
			auto chunk = _GenerationQueue.front();
			_GenerationQueue.pop();
			if (chunk->_Mesh == nullptr) {
				GenerateTerrain(planetTerrain, chunk);
			}
			auto size = planetTerrain->_ChunkList.size();
			chunk->Index = size;
			chunk->ToRecycle = false;
			planetTerrain->_ChunkList.push_back(chunk);

			auto recycle = planetTerrain->_ChunkList[_RecycleQueue.front()];
			Remove(&planetTerrain->_ChunkList, _RecycleQueue.front());
			recycle->Index = planetTerrain->_RecycledChunkList.size();
			planetTerrain->_RecycledChunkList.push_back(recycle);
			_RecycleQueue.pop();

			recycle = planetTerrain->_ChunkList[_RecycleQueue.front()];
			Remove(&planetTerrain->_ChunkList, _RecycleQueue.front());
			recycle->Index = planetTerrain->_RecycledChunkList.size();
			planetTerrain->_RecycledChunkList.push_back(recycle);
			_RecycleQueue.pop();

			recycle = planetTerrain->_ChunkList[_RecycleQueue.front()];
			Remove(&planetTerrain->_ChunkList, _RecycleQueue.front());
			recycle->Index = planetTerrain->_RecycledChunkList.size();
			planetTerrain->_RecycledChunkList.push_back(recycle);
			_RecycleQueue.pop();

			recycle = planetTerrain->_ChunkList[_RecycleQueue.front()];
			Remove(&planetTerrain->_ChunkList, _RecycleQueue.front());
			recycle->Index = planetTerrain->_RecycledChunkList.size();
			planetTerrain->_RecycledChunkList.push_back(recycle);
			_RecycleQueue.pop();

		}
	}
}

void Planet::PlanetTerrainSystem::Remove(std::vector<TerrainChunk*>* list, unsigned index)
{
	list->at(index) = list->back();
	list->at(index)->Index = index;
	list->pop_back();
}
