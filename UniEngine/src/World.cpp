#include "pch.h"
#include "World.h"
#include "UniEngine.h"
using namespace UniEngine;


void World::Purge()
{
	_WorldEntityStorage.Entities.clear();
	_WorldEntityStorage.ParentRoots.clear();
	_WorldEntityStorage.EntityInfos.clear();
	for(auto& i : _WorldEntityStorage.EntityComponentStorage)
	{
		for (auto& chunk : i.ChunkArray->Chunks) free(chunk.Data);
		i.ChunkArray->Chunks.clear();
		i.ChunkArray->Entities.clear();
		i.ArchetypeInfo->EntityAliveCount = 0;
		i.ArchetypeInfo->EntityCount = 0;
	}
	_WorldEntityStorage.EntitySharedComponentStorage = SharedComponentStorage();
	_WorldEntityStorage.EntityPrivateComponentStorage = PrivateComponentStorage();
	
	_WorldEntityStorage.Entities.emplace_back();
	_WorldEntityStorage.EntityInfos.emplace_back();
}

void World::RegisterFixedUpdateFunction(const std::function<void()>& func)
{
	_ExternalFixedUpdateFunctions.push_back(func);
}

Bound UniEngine::World::GetBound() const
{
	return _WorldBound;
}

void UniEngine::World::SetBound(Bound value)
{
	_WorldBound = value;
}

UniEngine::Bound::Bound()
{
	Min = glm::vec3(FLT_MIN);
	Max = glm::vec3(FLT_MAX);
}

glm::vec3 Bound::Size() const
{
	return (Max - Min) / 2.0f;
}

glm::vec3 Bound::Center() const
{
	return (Max + Min) / 2.0f;
}

bool Bound::InBound(glm::vec3 position) const
{
	glm::vec3 center = (Min + Max) / 2.0f;
	glm::vec3 size = (Max - Min) / 2.0f;
	if (glm::abs(position.x - center.x) > size.x) return false;
	if (glm::abs(position.y - center.y) > size.y) return false;
	if (glm::abs(position.z - center.z) > size.z) return false;
	return true;
}

void Bound::ApplyTransform(glm::mat4 transform)
{
	std::vector<glm::vec3> corners;
	PopulateCorners(corners);
	Min = glm::vec3(FLT_MAX);
	Max = glm::vec3(FLT_MIN);

	// Transform all of the corners, and keep track of the greatest and least
	// values we see on each coordinate axis.
	for (int i = 0; i < 8; i++)
	{
		glm::vec3 transformed = transform * glm::vec4(corners[i], 1.0f);
		Min = glm::min(Min, transformed);
		Max = glm::max(Max, transformed);
	}
}

void Bound::PopulateCorners(std::vector<glm::vec3>& corners) const
{
	corners.resize(8);
	corners[0] = Min;
	corners[1] = glm::vec3(Min.x, Min.y, Max.z);
	corners[2] = glm::vec3(Min.x, Max.y, Min.z);
	corners[3] = glm::vec3(Max.x, Min.y, Min.z);
	corners[4] = glm::vec3(Min.x, Max.y, Max.z);
	corners[5] = glm::vec3(Max.x, Min.y, Max.z);
	corners[6] = glm::vec3(Max.x, Max.y, Min.z);
	corners[7] = Max;
}


void UniEngine::World::SetFrameStartTime(double time) const
{
	_Time->_FrameStartTime = time;
}

void UniEngine::World::SetTimeStep(float timeStep) const
{
	_Time->_TimeStep = timeStep;
}

size_t UniEngine::World::GetIndex() const
{
	return _Index;
}

UniEngine::World::World(size_t index) {
	_Index = index;
	_Time = new WorldTime();
	Purge();
}

void World::ResetTime() const
{
	_Time->_DeltaTime = 0;
	_Time->_LastFrameTime = 0;
	_Time->_FixedDeltaTime = 0;
}


UniEngine::World::~World() {
	for (auto i : _PreparationSystems) {
		i->OnDestroy();
		delete i;
	}
	for (auto i : _SimulationSystems) {
		i->OnDestroy();
		delete i;
	}
	for (auto i : _PresentationSystems) {
		i->OnDestroy();
		delete i;
	}
	delete _Time;
	if(EntityManager::_CurrentAttachedWorldEntityStorage == &_WorldEntityStorage)
	{
		EntityManager::Detach();
	}
}

void World::PreUpdate()
{
	_NeedFixedUpdate = false;
	if (_Time->_FixedDeltaTime >= _Time->_TimeStep) {
		_NeedFixedUpdate = true;
	}
	
	if (_NeedFixedUpdate) {
		for (const auto& i : _ExternalFixedUpdateFunctions) i();
		for (auto i : _PreparationSystems) {
			if (i->Enabled()) i->FixedUpdate();
		}
		for (auto i : _SimulationSystems) {
			if (i->Enabled()) i->FixedUpdate();
		}
		if (PhysicsSimulationManager::Enabled) PhysicsSimulationManager::Simulate(_Time->_FixedDeltaTime);
		for (auto i : _PresentationSystems) {
			if (i->Enabled()) i->FixedUpdate();
		}
	}
	
	for (auto i : _PreparationSystems) {
		if (i->Enabled()) i->PreUpdate();
	}
	
	for (auto i : _SimulationSystems) {
		if (i->Enabled()) i->PreUpdate();
	}
	
	for (auto i : _PresentationSystems) {
		if (i->Enabled()) i->PreUpdate();
	}
}

void UniEngine::World::Update() {
	
	for (auto i : _PreparationSystems) {
		if (i->Enabled()) i->Update();
	}
	for (auto i : _SimulationSystems) {
		if (i->Enabled()) i->Update();
	}
	for (auto i : _PresentationSystems) {
		if (i->Enabled()) i->Update();
	}
}

void World::LateUpdate()
{
	for (auto i : _PreparationSystems) {
		if (i->Enabled()) i->LateUpdate();
	}

	for (auto i : _SimulationSystems) {
		if (i->Enabled()) i->LateUpdate();
	}

	for (auto i : _PresentationSystems) {
		if (i->Enabled()) i->LateUpdate();
	}
	if (_NeedFixedUpdate)
	{
		_Time->_FixedDeltaTime = 0;
	}
}

WorldTime* UniEngine::World::Time() const
{
	return _Time;
}
