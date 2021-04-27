#include "StarClusterSystem.h"

void Galaxy::StarClusterPattern::OnGui()
{
	if (ImGui::Button("Apply")) Apply();
	bool needUpdate = false;
	float ySpread = m_ySpread;
	float xzSpread = m_xzSpread;
	float diskAb = m_diskAb;
	float diskEccentricity = m_diskEccentricity;
	float coreProportion = m_coreProportion;
	float coreEccentricity = m_coreEccentricity;
	float centerAb = m_centerAb;
	float centerEccentricity = m_centerEccentricity;
	float diskSpeed = m_diskSpeed;
	float coreSpeed = m_coreSpeed;
	float centerSpeed = m_centerSpeed;
	float diskTiltX = m_diskTiltX;
	float diskTiltZ = m_diskTiltZ;
	float coreTiltX = m_coreTiltX;
	float coreTiltZ = m_coreTiltZ;
	float centerTiltX = m_centerTiltX;
	float centerTiltZ = m_centerTiltZ;
	float rotation = m_rotation;
	glm::vec3 centerPosition = m_centerPosition;
	if (ImGui::DragFloat("Y Spread", &ySpread, 0.01f, 0, 1))
	{
		m_ySpread = ySpread;
		needUpdate = true;
	}
	if (ImGui::DragFloat("XZ Spread", &xzSpread, 0.01f, 0, 1))
	{
		m_xzSpread = xzSpread;
		needUpdate = true;
	}
	/*
	if (ImGui::DragFloat("Y Spread", &ySpread, 0.01f, 0, 1))
	{
		m_diskAb = ySpread;
		needUpdate = true;
	}
	if (ImGui::DragFloat("Y Spread", &ySpread, 0.01f, 0, 1))
	{
		m_diskEccentricity = ySpread;
		needUpdate = true;
	}
	if (ImGui::DragFloat("Y Spread", &ySpread, 0.01f, 0, 1))
	{
		m_coreProportion = ySpread;
		needUpdate = true;
	}
	if (ImGui::DragFloat("Y Spread", &ySpread, 0.01f, 0, 1))
	{
		m_coreEccentricity = ySpread;
		needUpdate = true;
	}
	if (ImGui::DragFloat("Y Spread", &ySpread, 0.01f, 0, 1))
	{
		m_centerAb = ySpread;
		needUpdate = true;
	}
	if (ImGui::DragFloat("Y Spread", &ySpread, 0.01f, 0, 1))
	{
		m_centerEccentricity = ySpread;
		needUpdate = true;
	}
	if (ImGui::DragFloat("Y Spread", &ySpread, 0.01f, 0, 1))
	{
		m_diskSpeed = ySpread;
		needUpdate = true;
	}
	if (ImGui::DragFloat("Y Spread", &ySpread, 0.01f, 0, 1))
	{
		m_coreSpeed = ySpread;
		needUpdate = true;
	}
	if (ImGui::DragFloat("Y Spread", &ySpread, 0.01f, 0, 1))
	{
		m_centerSpeed = ySpread;
		needUpdate = true;
	}
	if (ImGui::DragFloat("Y Spread", &ySpread, 0.01f, 0, 1))
	{
		m_diskTiltX = ySpread;
		needUpdate = true;
	}
	if (ImGui::DragFloat("Y Spread", &ySpread, 0.01f, 0, 1))
	{
		m_diskTiltZ = ySpread;
		needUpdate = true;
	}
	if (ImGui::DragFloat("Y Spread", &ySpread, 0.01f, 0, 1))
	{
		m_coreTiltX = ySpread;
		needUpdate = true;
	}
	if (ImGui::DragFloat("Y Spread", &ySpread, 0.01f, 0, 1))
	{
		m_coreTiltZ = ySpread;
		needUpdate = true;
	}
	if (ImGui::DragFloat("Y Spread", &ySpread, 0.01f, 0, 1))
	{
		m_centerTiltX = ySpread;
		needUpdate = true;
	}
	if (ImGui::DragFloat("Y Spread", &ySpread, 0.01f, 0, 1))
	{
		m_centerTiltZ = ySpread;
		needUpdate = true;
	}*/
	if(needUpdate)
	{
		Apply();
	}
}

void Galaxy::StarClusterPattern::Apply()
{
	SetAb();
	EntityManager::ForEach<StarClusterIndex, StarOrbit, StarOrbitOffset, StarOrbitProportion>(JobManager::SecondaryWorkers(), 
		[&](int i, Entity entity, StarClusterIndex& starClusterIndex, StarOrbit& starOrbit, StarOrbitOffset& starOrbitOffset, StarOrbitProportion& starOrbitProportion)
		{
			starOrbitOffset = GetOrbitOffset(starOrbitProportion.m_value);
			starOrbit = GetOrbit(starOrbitProportion.m_value);
		}
	);
}

void Galaxy::StarClusterSystem::CalculateStarPositionAsync()
{
	auto list = EntityManager::UnsafeGetComponentDataArray<GlobalTransform>(m_starQuery);
	if (m_firstTime || m_currentStatus.wait_for(std::chrono::seconds(0)) == std::future_status::ready)
	{
		m_useFront = !m_useFront;
		m_calcPositionResult = Application::EngineTime() - m_calcPositionTimer;
		m_firstTime = false;

		m_applyPositionTimer = Application::EngineTime();
		EntityManager::ForEach<StarPosition, GlobalTransform, Transform>(
			JobManager::SecondaryWorkers(), m_starQuery,
			[this](int i, Entity entity, StarPosition& position, GlobalTransform& globalTransform, Transform& transform)
			{
				//Code here will be exec in parallel
				globalTransform.m_value = glm::translate(glm::vec3(position.m_value) / 20.0f) * glm::scale(m_size * glm::vec3(1.0f));
				transform.m_value = globalTransform.m_value;
			}, false
			);
		m_applyPositionTimer = Application::EngineTime() - m_applyPositionTimer;

		m_calcPositionTimer = Application::EngineTime();
		m_currentStatus = std::async(std::launch::async, [=]()
			{
				EntityManager::ForEach<StarSeed, StarPosition, StarOrbit, StarOrbitOffset>(
					JobManager::SecondaryWorkers(), m_starQuery,
					[=](int i, Entity entity, StarSeed& seed, StarPosition& position, StarOrbit& orbit, StarOrbitOffset& offset)
					{
						//Code here will be exec in parallel
						position.m_value = orbit.GetPoint(offset.m_value, seed.m_value * 360.0f + m_galaxyTime, true);
					}, false
					);

				if (m_useFront)
				{
					auto& imr = m_starClusterBack.GetPrivateComponent<Particles>();
					imr->m_matrices.resize(m_starQuery.GetEntityAmount());
					EntityManager::ForEach<GlobalTransform>(
						JobManager::SecondaryWorkers(), m_starQuery,
						[&](int i, Entity entity, GlobalTransform& globalTransform)
						{
							imr->m_matrices[i] = globalTransform.m_value;
						}, false
						);
				}
				else
				{
					auto& imr = m_starClusterFront.GetPrivateComponent<Particles>();
					imr->m_matrices.resize(m_starQuery.GetEntityAmount());
					EntityManager::ForEach<GlobalTransform>(
						JobManager::SecondaryWorkers(), m_starQuery,
						[&](int i, Entity entity, GlobalTransform& globalTransform)
						{
							imr->m_matrices[i] = globalTransform.m_value;
						}, false
						);
				}
			}
		);
	}
}

void Galaxy::StarClusterSystem::CalculateStarPositionSync()
{
	m_calcPositionTimer = Application::EngineTime();
	EntityManager::ForEach<StarSeed, StarPosition, StarOrbit, StarOrbitOffset>(
		JobManager::SecondaryWorkers(), m_starQuery,
		[=](int i, Entity entity, StarSeed& seed, StarPosition& position, StarOrbit& orbit, StarOrbitOffset& offset)
		{
			//Code here will be exec in parallel
			position.m_value = orbit.GetPoint(offset.m_value, seed.m_value * 360.0f + m_galaxyTime, true);
		}, false
		);
	m_calcPositionResult = Application::EngineTime() - m_calcPositionTimer;
	
	
}

void Galaxy::StarClusterSystem::ApplyPositionSync()
{
	m_applyPositionTimer = Application::EngineTime();
	EntityManager::ForEach<StarPosition, GlobalTransform, Transform>(
		JobManager::SecondaryWorkers(), m_starQuery,
		[this](int i, Entity entity, StarPosition& position, GlobalTransform& globalTransform, Transform& transform)
		{
			//Code here will be exec in parallel
			globalTransform.m_value = glm::translate(glm::vec3(position.m_value) / 20.0f) * glm::scale(m_size * glm::vec3(1.0f));
			transform.m_value = globalTransform.m_value;
		}, false
		);
	m_applyPositionTimer = Application::EngineTime() - m_applyPositionTimer;

	auto& imr = m_starClusterFront.GetPrivateComponent<Particles>();
	imr->m_matrices.resize(m_starQuery.GetEntityAmount());
	EntityManager::ForEach<GlobalTransform>(
		JobManager::SecondaryWorkers(), m_starQuery,
		[&](int i, Entity entity, GlobalTransform& globalTransform)
		{
			imr->m_matrices[i] = globalTransform.m_value;
		}, false
		);
	m_useFront = true;
}

void Galaxy::StarClusterSystem::SetRenderer()
{
	m_starClusterBack.SetEnabled(!m_useFront);
	m_starClusterFront.SetEnabled(m_useFront);
}

void Galaxy::StarClusterSystem::LateUpdate()
{
	ImGui::Begin("Galaxy Control Panel");
	ImGui::DragFloat("Speed", &m_speed, 1.0f, 0.1f, 30000.0f);
	ImGui::DragFloat("Star Size", &m_size, 0.1f, 0.1f, 10.0f);
	ImGui::InputFloat("Apply", &m_applyPositionTimer);
	ImGui::InputFloat("Copy", &m_copyPositionTimer);
	ImGui::InputFloat("Calc", &m_calcPositionResult);
	ImGui::End();
}

void Galaxy::StarClusterSystem::OnCreate()
{
	m_starClusterArchetype = EntityManager::CreateEntityArchetype("Star Cluster",
		GlobalTransform(),
		StarClusterIndex()
	);
	m_starClusterFront = EntityManager::CreateEntity(m_starClusterArchetype);
	GlobalTransform ltw;
	ltw.SetScale(glm::vec3(1.0f));
	auto imr = std::make_unique<Particles>();
	imr->m_material = std::make_shared<Material>();
	imr->m_castShadow = false;
	imr->m_receiveShadow = false;
	imr->m_mesh = Default::Primitives::Cube;
	imr->m_material->SetProgram(Default::GLPrograms::StandardInstancedProgram);
	imr->m_material->SetTexture(Default::Textures::StandardTexture);
	m_starClusterFront.SetPrivateComponent(std::move(imr));
	m_starClusterFront.SetComponentData(ltw);

	m_starClusterBack = EntityManager::CreateEntity(m_starClusterArchetype);
	ltw.SetScale(glm::vec3(1.0f));
	imr = std::make_unique<Particles>();
	imr->m_material = std::make_shared<Material>();
	imr->m_castShadow = false;
	imr->m_receiveShadow = false;
	imr->m_mesh = Default::Primitives::Cube;
	imr->m_material->SetProgram(Default::GLPrograms::StandardInstancedProgram);
	imr->m_material->SetTexture(Default::Textures::StandardTexture);
	m_starClusterBack.SetPrivateComponent(std::move(imr));
	m_starClusterBack.SetComponentData(ltw);

	m_starClusterEntity = EntityManager::CreateEntity("Star cluster");
	StarClusterIndex starClusterindex;
	EntityManager::AddComponentData(m_starClusterEntity, starClusterindex);
	m_starClusterEntity.SetPrivateComponent(std::make_unique<StarClusterPattern>());
	auto& pattern = m_starClusterEntity.GetPrivateComponent<StarClusterPattern>();
	
	m_starQuery = EntityManager::CreateEntityQuery();
	EntityManager::SetEntityQueryAllFilters(m_starQuery, StarSeed());
	
	m_starArchetype = EntityManager::CreateEntityArchetype("Star",
		GlobalTransform(),
		StarClusterIndex(),
		StarIndex(),
		StarSeed(), StarOrbit(), StarOrbitOffset(), StarOrbitProportion(), StarPosition(),
		SelectionStatus(), OriginalColor(), SurfaceColor(), DisplayColor()
	);
	pattern->m_ySpread = 0.05;
	pattern->m_xzSpread = 0.015;
	pattern->m_diskAb = 3000;
	pattern->m_diskEccentricity = 0.5;
	pattern->m_coreProportion = 0.4;
	pattern->m_coreEccentricity = 0.8;
	pattern->m_centerAb = 10;
	pattern->m_centerEccentricity = 0.5;
	pattern->m_diskSpeed = 1;
	pattern->m_coreSpeed = 5;
	pattern->m_centerSpeed = 10;
	pattern->m_diskTiltX = 0;
	pattern->m_diskTiltZ = 0;
	pattern->m_coreTiltX = 0;
	pattern->m_coreTiltZ = 0;
	pattern->m_centerTiltX = 0;
	pattern->m_centerTiltZ = 0;
	pattern->m_diskColor = glm::vec4(0, 0, 1, 1);
	pattern->m_coreColor = glm::vec4(1, 1, 0, 1);
	pattern->m_centerColor = glm::vec4(1, 1, 1, 1);
	pattern->m_rotation = 360;
	pattern->m_centerPosition = glm::dvec3(0);
	pattern->SetAb();

	//Generate Stars
	StarIndex index;
	StarSeed seed;
	StarOrbitProportion proportion;

	JobManager::ResizePrimaryWorkers(1);
	JobManager::ResizeSecondaryWorkers(16);

	size_t starAmount = 10000;
	auto stars = EntityManager::CreateEntities(m_starArchetype, starAmount, "Star");
	for (auto i = 0; i < starAmount; i++) {
		auto starEntity = stars[i];
		starEntity.SetStatic(true);
		index.m_value = i;
		seed.m_value = glm::linearRand(0.0, 1.0);
		proportion.m_value = seed.m_value;
		EntityManager::SetComponentData(starEntity, index);
		EntityManager::SetComponentData(starEntity, seed);
		EntityManager::SetComponentData(starEntity, proportion);
		EntityManager::SetComponentData(starEntity, starClusterindex);
	}

	pattern->Apply();
	m_firstTime = true;
}

void Galaxy::StarClusterSystem::Update()
{
	m_galaxyTime += m_world->Time()->DeltaTime() * m_speed;
	
	//This method calculate the position for each star. Remove this line if you use your own implementation.
	CalculateStarPositionSync();

	//Do not touch below functions.
	ApplyPositionSync();
	SetRenderer();
}

void Galaxy::StarClusterSystem::FixedUpdate()
{
}

void Galaxy::StarClusterSystem::OnStartRunning()
{
	m_firstTime = true;
}
