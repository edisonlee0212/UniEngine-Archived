#include "PlanetTerrainSystem.h"

void Planet::PlanetTerrainSystem::OnCreate()
{
	_GenerationQueue = std::queue<TerrainChunk*>();
	_PlanetTerrainList = std::vector<PlanetTerrain*>();
}

void Planet::PlanetTerrainSystem::Update()
{
	Position cameraPos = _EntityCollection->GetFixedData<Position>(_TargetCameraEntity);
	
	for (auto planet : _PlanetTerrainList) {
		auto planetInfo = planet->_Info;
		//1. Scan and expand.
		for (auto i = 0; i < planet->_ChunkList.size(); i++) {
			auto chunk = planet->_ChunkList[i];
			if (glm::distance(glm::vec3(chunk->ChunkCenterPosition(planetInfo.Position, planetInfo.Radius, planetInfo.Rotation)), cameraPos.value)
				< (_LodDistance * planetInfo.Radius / glm::pow(2, chunk->DetailLevel + 1))) {
				if (chunk->C0 != nullptr) {
					_GenerationQueue.push(chunk->C0);
					//TODO: Dont forget to reset index.
					Remove(&planet->_RecycledChunkList, chunk->C0->Index);
				}
				else {
					//TODO: Dont forget to reset index.
					_GenerationQueue.push(new TerrainChunk(chunk, 0, chunk->DetailLevel + 1, glm::ivec2(chunk->ChunkCoordinate.x * 2, chunk->ChunkCoordinate.y * 2 + 1), ChunkDirection::UpperLeft, chunk->LocalUp));
				}
				if (chunk->C1 != nullptr) {
					_GenerationQueue.push(chunk->C1);
					Remove(&planet->_RecycledChunkList, chunk->C1->Index);
				}
				else {
					_GenerationQueue.push(new TerrainChunk(chunk, 0, chunk->DetailLevel + 1, glm::ivec2(chunk->ChunkCoordinate.x * 2 + 1, chunk->ChunkCoordinate.y * 2 + 1), ChunkDirection::UpperRight, chunk->LocalUp));
				}
				if (chunk->C2 != nullptr) {
					_GenerationQueue.push(chunk->C2);
					Remove(&planet->_RecycledChunkList, chunk->C2->Index);
				}
				else {
					_GenerationQueue.push(new TerrainChunk(chunk, 0, chunk->DetailLevel + 1, glm::ivec2(chunk->ChunkCoordinate.x * 2, chunk->ChunkCoordinate.y * 2), ChunkDirection::LowerLeft, chunk->LocalUp));
				}
				if (chunk->C3 != nullptr) {
					_GenerationQueue.push(chunk->C3);
					Remove(&planet->_RecycledChunkList, chunk->C3->Index);
				}
				else {
					_GenerationQueue.push(new TerrainChunk(chunk, 0, chunk->DetailLevel + 1, glm::ivec2(chunk->ChunkCoordinate.x * 2 + 1, chunk->ChunkCoordinate.y * 2), ChunkDirection::LowerRight, chunk->LocalUp));
				}
				_RecycleQueue.push(chunk->Index);
			}
			else
			{
				planet->_ChunkList[i]->ToRecycle = true;
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

			}
			if (c2->_Mesh == nullptr) {

			}
			if (c3->_Mesh == nullptr) {

			}
			if (c4->_Mesh == nullptr) {

			}
			auto size = planet->_ChunkList.size();
			c1->Index = size;
			c2->Index = size + 1;
			c3->Index = size + 2;
			c4->Index = size + 3;
			c1->ToRecycle = false;
			c2->ToRecycle = false;
			c3->ToRecycle = false;
			c4->ToRecycle = false;
			planet->_ChunkList.push_back(c1);
			planet->_ChunkList.push_back(c2);
			planet->_ChunkList.push_back(c3);
			planet->_ChunkList.push_back(c4);
			auto recycle = planet->_ChunkList[_RecycleQueue.front()];
			Remove(&planet->_ChunkList, _RecycleQueue.front());
			recycle->Index = planet->_RecycledChunkList.size();
			planet->_RecycledChunkList.push_back(recycle);
			_RecycleQueue.pop();
		}

		//3. Scan and collapse.
		for (auto i = 0; i < planet->_RecycledChunkList.size(); i++) {
			auto chunk = planet->_RecycledChunkList[i];
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
			auto c1 = _GenerationQueue.front();
			_GenerationQueue.pop();
			if (c1->_Mesh == nullptr) {

			}
			auto size = planet->_ChunkList.size();
			c1->Index = size;
			c1->ToRecycle = false;
			planet->_ChunkList.push_back(c1);
			auto recycle = planet->_ChunkList[_RecycleQueue.front()];
			Remove(&planet->_ChunkList, _RecycleQueue.front());
			recycle->Index = planet->_RecycledChunkList.size();
			planet->_RecycledChunkList.push_back(recycle);
			_RecycleQueue.pop();

			recycle = planet->_ChunkList[_RecycleQueue.front()];
			Remove(&planet->_ChunkList, _RecycleQueue.front());
			recycle->Index = planet->_RecycledChunkList.size();
			planet->_RecycledChunkList.push_back(recycle);
			_RecycleQueue.pop();

			recycle = planet->_ChunkList[_RecycleQueue.front()];
			Remove(&planet->_ChunkList, _RecycleQueue.front());
			recycle->Index = planet->_RecycledChunkList.size();
			planet->_RecycledChunkList.push_back(recycle);
			_RecycleQueue.pop();

			recycle = planet->_ChunkList[_RecycleQueue.front()];
			Remove(&planet->_ChunkList, _RecycleQueue.front());
			recycle->Index = planet->_RecycledChunkList.size();
			planet->_RecycledChunkList.push_back(recycle);
			_RecycleQueue.pop();

		}
	}

	

	
}

void Planet::PlanetTerrainSystem::FixedUpdate()
{

}

void Planet::PlanetTerrainSystem::Remove(std::vector<TerrainChunk*>* list, unsigned index)
{
	list->at(index) = list->back();
	list->at(index)->Index = index;
	list->pop_back();
}
