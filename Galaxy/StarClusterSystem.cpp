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
	imr->Material = std::make_shared<Material>();
	imr->CastShadow = false;
	imr->ReceiveShadow = false;
	imr->Mesh = Default::Primitives::Sphere;
	imr->Material->SetProgram(Default::GLPrograms::StandardInstancedProgram);
	imr->Material->SetTexture(Default::Textures::StandardTexture);
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

	size_t starAmount = 60000;
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
	ImGui::SliderFloat("Speed", &_Speed, 1.0f, 3000.0f);
	ImGui::SliderFloat("Star Size", &_Size, 0.1f, 2.0f);
	ImGui::SliderFloat("Apply", &_ApplyPositionTimer, 1.0f, 3000.0f);
	ImGui::SliderFloat("Copy", &_CopyPositionTimer, 0.1f, 2.0f);
	ImGui::SliderFloat("Calc", &_CalcPositionResult, 1.0f, 3000.0f);
	ImGui::End();
	_GalaxyTime += _World->Time()->DeltaTime() * _Speed;
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
				globalTransform.Value = glm::translate(glm::vec3(position.Value) / 20.0f) * glm::scale(_Size * glm::vec3(1.0f));
				transform.Value = globalTransform.Value;
			}, false
		);
		_ApplyPositionTimer = Application::EngineTime() - _ApplyPositionTimer;

		_CopyPositionTimer = Application::EngineTime();
		auto& imr = _StarCluster.GetPrivateComponent<Particles>();
		imr->Matrices.resize(0);
		_StarQuery.ToComponentDataArray(*(std::vector<GlobalTransform>*)(void*) & imr->Matrices);
		_CopyPositionTimer = Application::EngineTime() - _CopyPositionTimer;

		_CalcPositionTimer = Application::EngineTime();
		_CurrentStatus = std::async(std::launch::async, [=]()
			{
				auto task =
					EntityManager::CreateParallelTask<StarSeed, StarPosition, StarOrbit, StarOrbitOffset>(
						[time](int i, Entity entity, StarSeed& seed, StarPosition& position, StarOrbit& orbit, StarOrbitOffset& offset)
						{
							while (1){}
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
