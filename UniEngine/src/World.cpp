#include "pch.h"
#include "World.h"
#include "UniEngine.h"
using namespace UniEngine;


void World::Purge()
{
	m_worldEntityStorage.m_entityPrivateComponentStorage = PrivateComponentStorage();
	m_worldEntityStorage.m_entities.clear();
	m_worldEntityStorage.m_entityInfos.clear();
	m_worldEntityStorage.m_parentHierarchyVersion = 0;
	for(int index = 1; index < m_worldEntityStorage.m_entityComponentStorage.size(); index++)
	{
		auto& i = m_worldEntityStorage.m_entityComponentStorage[index];
		for (auto& chunk : i.m_chunkArray->Chunks) free(chunk.m_data);
		i.m_chunkArray->Chunks.clear();
		i.m_chunkArray->Entities.clear();
		i.m_archetypeInfo->m_entityAliveCount = 0;
		i.m_archetypeInfo->m_entityCount = 0;
	}
	
	m_worldEntityStorage.m_entities.emplace_back();
	m_worldEntityStorage.m_entityInfos.emplace_back();
}

void World::RegisterFixedUpdateFunction(const std::function<void()>& func)
{
	m_externalFixedUpdateFunctions.push_back(func);
}

Bound UniEngine::World::GetBound() const
{
	return m_worldBound;
}

void UniEngine::World::SetBound(const Bound& value)
{
	m_worldBound = value;
}

UniEngine::Bound::Bound()
{
	m_min = glm::vec3(FLT_MIN);
	m_max = glm::vec3(FLT_MAX);
}

glm::vec3 Bound::Size() const
{
	return (m_max - m_min) / 2.0f;
}

glm::vec3 Bound::Center() const
{
	return (m_max + m_min) / 2.0f;
}

bool Bound::InBound(const glm::vec3& position) const
{
	glm::vec3 center = (m_min + m_max) / 2.0f;
	glm::vec3 size = (m_max - m_min) / 2.0f;
	if (glm::abs(position.x - center.x) > size.x) return false;
	if (glm::abs(position.y - center.y) > size.y) return false;
	if (glm::abs(position.z - center.z) > size.z) return false;
	return true;
}

void Bound::ApplyTransform(const glm::mat4& transform)
{
	std::vector<glm::vec3> corners;
	PopulateCorners(corners);
	m_min = glm::vec3(FLT_MAX);
	m_max = glm::vec3(FLT_MIN);

	// Transform all of the corners, and keep track of the greatest and least
	// values we see on each coordinate axis.
	for (int i = 0; i < 8; i++)
	{
		glm::vec3 transformed = transform * glm::vec4(corners[i], 1.0f);
		m_min = glm::min(m_min, transformed);
		m_max = glm::max(m_max, transformed);
	}
}

void Bound::PopulateCorners(std::vector<glm::vec3>& corners) const
{
	corners.resize(8);
	corners[0] = m_min;
	corners[1] = glm::vec3(m_min.x, m_min.y, m_max.z);
	corners[2] = glm::vec3(m_min.x, m_max.y, m_min.z);
	corners[3] = glm::vec3(m_max.x, m_min.y, m_min.z);
	corners[4] = glm::vec3(m_min.x, m_max.y, m_max.z);
	corners[5] = glm::vec3(m_max.x, m_min.y, m_max.z);
	corners[6] = glm::vec3(m_max.x, m_max.y, m_min.z);
	corners[7] = m_max;
}


void UniEngine::World::SetFrameStartTime(double time) const
{
	m_time->_FrameStartTime = time;
}

void UniEngine::World::SetTimeStep(float timeStep) const
{
	m_time->_TimeStep = timeStep;
}

size_t UniEngine::World::GetIndex() const
{
	return m_index;
}

UniEngine::World::World(size_t index) {
	m_index = index;
	m_time = new WorldTime();
	m_worldEntityStorage = WorldEntityStorage();
	m_worldEntityStorage.m_entities.emplace_back();
	m_worldEntityStorage.m_entityInfos.emplace_back();
	m_worldEntityStorage.m_entityComponentStorage.emplace_back(nullptr, nullptr);
	m_worldEntityStorage.m_entityQueries.emplace_back();
	m_worldEntityStorage.m_entityQueryInfos.emplace_back();
}

void World::ResetTime() const
{
	m_time->_DeltaTime = 0;
	m_time->_LastFrameTime = 0;
	m_time->_FixedDeltaTime = 0;
}


UniEngine::World::~World() {
	for (auto i : m_preparationSystems) {
		i->OnDestroy();
		delete i;
	}
	for (auto i : m_simulationSystems) {
		i->OnDestroy();
		delete i;
	}
	for (auto i : m_presentationSystems) {
		i->OnDestroy();
		delete i;
	}
	delete m_time;
	if(EntityManager::GetInstance().m_currentAttachedWorldEntityStorage == &m_worldEntityStorage)
	{
		EntityManager::Detach();
	}
}

void World::PreUpdate()
{
	m_needFixedUpdate = false;
	if (m_time->_FixedDeltaTime >= m_time->_TimeStep) {
		m_needFixedUpdate = true;
	}
	
	if (m_needFixedUpdate) {
		for (const auto& i : m_externalFixedUpdateFunctions) i();
		for (auto i : m_preparationSystems) {
			if (i->Enabled()) i->FixedUpdate();
		}
		for (auto i : m_simulationSystems) {
			if (i->Enabled()) i->FixedUpdate();
		}
		if (PhysicsSimulationManager::Enabled) PhysicsSimulationManager::Simulate(m_time->_FixedDeltaTime);
		for (auto i : m_presentationSystems) {
			if (i->Enabled()) i->FixedUpdate();
		}
	}
	
	for (auto i : m_preparationSystems) {
		if (i->Enabled()) i->PreUpdate();
	}
	
	for (auto i : m_simulationSystems) {
		if (i->Enabled()) i->PreUpdate();
	}
	
	for (auto i : m_presentationSystems) {
		if (i->Enabled()) i->PreUpdate();
	}
}

void UniEngine::World::Update() {
	
	for (auto i : m_preparationSystems) {
		if (i->Enabled()) i->Update();
	}
	for (auto i : m_simulationSystems) {
		if (i->Enabled()) i->Update();
	}
	for (auto i : m_presentationSystems) {
		if (i->Enabled()) i->Update();
	}
}

void World::LateUpdate()
{
	for (auto i : m_preparationSystems) {
		if (i->Enabled()) i->LateUpdate();
	}

	for (auto i : m_simulationSystems) {
		if (i->Enabled()) i->LateUpdate();
	}

	for (auto i : m_presentationSystems) {
		if (i->Enabled()) i->LateUpdate();
	}
	if (m_needFixedUpdate)
	{
		m_time->_FixedDeltaTime = 0;
	}
}

WorldTime* UniEngine::World::Time() const
{
	return m_time;
}
