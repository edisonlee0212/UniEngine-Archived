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

	size_t starAmount = 600000;
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
}

void Galaxy::StarClusterSystem::Update()
{
	ImGui::Begin("Galaxy Control Panel");
	ImGui::SliderFloat("Speed", &_Speed, 1.0f, 3000.0f);
	ImGui::SliderFloat("Star Size", &_Size, 0.1f, 2.0f);
	ImGui::End();
	_GalaxyTime += _World->Time()->DeltaTime() * _Speed;
	float time = _GalaxyTime;

	float timer = Application::EngineTime();
	//1. Calculate position (double precision) for each star
	EntityManager::ForEach<StarSeed, StarPosition, StarOrbit, StarOrbitOffset>(_StarQuery,
		[time](int i, Entity entity, StarSeed& seed, StarPosition& position, StarOrbit& orbit, StarOrbitOffset& offset)
		{
			position.Value = orbit.GetPoint(offset.Value, seed.Value * 360.0f + time, true);
		}, false
	);
	//2. Apply position and size to the transform which will later be used for rendering.
	float size = _Size;
	EntityManager::ForEach<StarPosition, GlobalTransform, Transform>(
		_StarQuery,
		[size](int i, Entity entity, StarPosition& position, GlobalTransform& globalTransform, Transform& transform)
		{
			globalTransform.Value = glm::translate(glm::vec3(position.Value) / 20.0f) * glm::scale(size * glm::vec3(1.0f));
			transform.Value = globalTransform.Value;
		}, false
	);

	
	
	//3. Setup transforms for particles component for the entity for actual rendering.
	auto& imr = _StarCluster.GetPrivateComponent<Particles>();
	imr->Matrices.resize(0);
	_StarQuery.ToComponentDataArray(*(std::vector<GlobalTransform>*)(void*)&imr->Matrices);
	//Debug::Log("Calculation Time: " + std::to_string(Application::EngineTime() - timer));
}

void Galaxy::StarClusterSystem::FixedUpdate()
{
}
