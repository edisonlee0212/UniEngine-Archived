#include "StarClusterSystem.h"

void Galaxy::StarClusterSystem::OnCreate()
{
	_StarClusterArchetype = EntityManager::CreateEntityArchetype("Star Cluster",
		GlobalTransform(),
		StarClusterIndex()
	);
	_StarCluster = EntityManager::CreateEntity(_StarClusterArchetype);
	GlobalTransform ltw;
	ltw.SetScale(glm::vec3(1.0f));
	auto imr = std::make_unique<Particles>();
	imr->m_material = std::make_shared<Material>();
	imr->m_castShadow = false;
	imr->m_receiveShadow = false;
	imr->m_mesh = Default::Primitives::Cube;
	imr->m_material->SetProgram(Default::GLPrograms::StandardInstancedProgram);
	imr->m_material->SetTexture(Default::Textures::StandardTexture);
	_StarCluster.SetPrivateComponent(std::move(imr));
	_StarCluster.SetComponentData(ltw);

	auto pattern = new StarClusterPattern();
	_StarQuery = EntityManager::CreateEntityQuery();
	EntityManager::SetEntityQueryAllFilters(_StarQuery, StarSeed());
	_Patterns.push_back(pattern);
	_StarArchetype = EntityManager::CreateEntityArchetype("Star",
		GlobalTransform(),
		StarClusterIndex(),
		StarIndex(),
		StarSeed(), StarOrbit(), StarOrbitOffset(), StarOrbitProportion(), StarPosition(),
		SelectionStatus(), OriginalColor(), SurfaceColor(), DisplayColor()
	);
	pattern->YSpread = 0.05;
	pattern->XZSpread = 0.015;
	pattern->DiskAB = 3000;
	pattern->DiskEccentricity = 0.5;
	pattern->CoreProportion = 0.4;
	pattern->CoreEccentricity = 0.8;
	pattern->CenterAB = 10;
	pattern->CenterEccentricity = 0.5;
	pattern->DiskSpeed = 1;
	pattern->CoreSpeed = 5;
	pattern->CenterSpeed = 10;
	pattern->DiskTiltX = 0;
	pattern->DiskTiltZ = 0;
	pattern->CoreTiltX = 0;
	pattern->CoreTiltZ = 0;
	pattern->CenterTiltX = 0;
	pattern->CenterTiltZ = 0;
	pattern->DiskColor = glm::vec4(0, 0, 1, 1);
	pattern->CoreColor = glm::vec4(1, 1, 0, 1);
	pattern->CenterColor = glm::vec4(1, 1, 1, 1);
	pattern->Rotation = 360;
	pattern->CenterPosition = glm::dvec3(0);
	pattern->SetAB();

	//Generate Stars
	StarClusterIndex cindex;
	StarIndex index;
	cindex.Value = 0;
	StarSeed seed;
	StarOrbit orbit;
	StarOrbitOffset offset;
	StarOrbitProportion proportion;

	JobManager::ResizePrimaryWorkers(2);
	JobManager::ResizeSecondaryWorkers(5);
	
	size_t starAmount = 6000;
	auto stars = EntityManager::CreateEntities(_StarArchetype, starAmount, "Star");
	for (auto i = 0; i < starAmount; i++) {
		auto starEntity = stars[i];
		starEntity.SetStatic(true);
		index.Value = i;
		seed.Value = glm::linearRand(0.0, 1.0);
		proportion.Value = seed.Value;
		offset = pattern->GetOrbitOffset(proportion.Value);
		orbit = pattern->GetOrbit(proportion.Value);
		EntityManager::SetComponentData(starEntity, index);
		EntityManager::SetComponentData(starEntity, seed);
		EntityManager::SetComponentData(starEntity, proportion);
		EntityManager::SetComponentData(starEntity, offset);
		EntityManager::SetComponentData(starEntity, orbit);
		EntityManager::SetComponentData(starEntity, cindex);
	}
	_FirstTime = true;
}

void Galaxy::StarClusterSystem::Update()
{
	ImGui::Begin("Galaxy Control Panel");
	ImGui::DragFloat("Speed", &_Speed, 1.0f, 0.1f, 30000.0f);
	ImGui::DragFloat("Star Size", &_Size, 0.1f, 0.1f, 10.0f);
	ImGui::InputFloat("Apply", &_ApplyPositionTimer);
	ImGui::InputFloat("Copy", &_CopyPositionTimer);
	ImGui::InputFloat("Calc", &_CalcPositionResult);
	ImGui::End();
	_GalaxyTime += m_world->Time()->DeltaTime() * _Speed;
	float time = _GalaxyTime;

	if(_FirstTime || _CurrentStatus.wait_for(std::chrono::seconds(0)) == std::future_status::ready)
	{
		_CalcPositionResult = Application::EngineTime() - _CalcPositionTimer;
		_FirstTime = false;
		_ApplyPositionTimer = Application::EngineTime();
		EntityManager::ForEach<StarPosition, GlobalTransform, Transform>(
			JobManager::PrimaryWorkers(), _StarQuery,
			[this](int i, Entity entity, StarPosition& position, GlobalTransform& globalTransform, Transform& transform)
			{
				//Code here will be exec in parallel
				globalTransform.m_value = glm::translate(glm::vec3(position.Value) / 20.0f) * glm::scale(_Size * glm::vec3(1.0f));
				transform.m_value = globalTransform.m_value;
			}, false
		);
		_ApplyPositionTimer = Application::EngineTime() - _ApplyPositionTimer;

		_CopyPositionTimer = Application::EngineTime();
		auto& imr = _StarCluster.GetPrivateComponent<Particles>();
		imr->m_matrices.resize(_StarQuery.GetEntityAmount());
		EntityManager::ForEach<StarPosition, GlobalTransform, Transform>(
			JobManager::PrimaryWorkers(), _StarQuery,
			[&](int i, Entity entity, StarPosition& position, GlobalTransform& globalTransform, Transform& transform)
			{
				imr->m_matrices[i] = globalTransform.m_value;
			}, false
			);
		_CopyPositionTimer = Application::EngineTime() - _CopyPositionTimer;

		_CalcPositionTimer = Application::EngineTime();
		_CurrentStatus = std::async(std::launch::async, [=]()
			{
				auto task =
					EntityManager::CreateParallelTask<StarSeed, StarPosition, StarOrbit, StarOrbitOffset>(
						[time](int i, Entity entity, StarSeed& seed, StarPosition& position, StarOrbit& orbit, StarOrbitOffset& offset)
						{
							//Code here will be exec in parallel
							position.Value = orbit.GetPoint(offset.Value, seed.Value * 360.0f + time, true);
						}
				);
				//Retrieve std::future for the task
				//Dispatch the task
				task(JobManager::SecondaryWorkers(), _StarQuery, false);
			}
		);
		//Generate a parallel task to calculate position (double precision) for each star
	}
}

void Galaxy::StarClusterSystem::FixedUpdate()
{
}

void Galaxy::StarClusterSystem::OnStartRunning()
{
	_FirstTime = true;
}
