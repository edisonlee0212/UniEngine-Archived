#include "StarClusterSystem.h"

void Galaxy::StarClusterSystem::OnCreate()
{
	_StarClusterArchetype = EntityManager::CreateEntityArchetype("Star Cluster",
		Translation(), Rotation(), Scale(), LocalToWorld(),
		StarClusterIndex()
	);
	_StarCluster = EntityManager::CreateEntity(_StarClusterArchetype);
	Scale s;
	s.Value = glm::vec3(1.0f);
	auto imr = std::make_unique<ParticleSystem>();
	imr->Material = std::make_shared<Material>();
	imr->CastShadow = false;
	imr->ReceiveShadow = false;
	imr->Mesh = Default::Primitives::Sphere;
	imr->Material->SetProgram(Default::GLPrograms::DeferredPrepassInstanced);
	imr->Material->SetTexture(Default::Textures::StandardTexture, TextureType::DIFFUSE);
	_StarCluster.SetPrivateComponent(std::move(imr));
	_StarCluster.SetComponentData(s);

	auto pattern = new StarClusterPattern();
	_StarQuery = EntityManager::CreateEntityQuery();
	EntityManager::SetEntityQueryAllFilters(_StarQuery, StarSeed());
	_Patterns.push_back(pattern);
	_StarArchetype = EntityManager::CreateEntityArchetype("Star",
		Translation(), Rotation(), Scale(), LocalToWorld(),
		StarClusterIndex(),
		StarIndex(),
		StarSeed(), StarOrbit(), StarOrbitOffset(), StarOrbitProportion(), StarPosition(),
		SelectionStatus(), OriginalColor(), SurfaceColor(), DisplayColor()
	);

	//TODO: Set star pattern.
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

	for (auto i = 0; i < 60000; i++) {
		auto starEntity = EntityManager::CreateEntity(_StarArchetype);
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
	EntityManager::ForEach<StarSeed, StarPosition, StarOrbit, StarOrbitOffset>(_StarQuery, [time](int i, Entity entity, StarSeed* seed, StarPosition* position, StarOrbit* orbit, StarOrbitOffset* offset) {
		position->Value = orbit->GetPoint(offset->Value, seed->Value * 360.0 + time, true);
		}, false);
	float size = _Size;
	EntityManager::ForEach<Translation, Scale, StarPosition>(_StarQuery, [size](int i, Entity entity, Translation* translation, Scale* scale, StarPosition* position) {
		translation->Value = position->Value / 20.0;
		scale->Value = size * glm::vec3(1.0f);
		}, false);
	std::vector<Entity> entities = std::vector<Entity>();
	_StarQuery.ToEntityArray(entities);
	//Render from last update.
	std::vector<LocalToWorld> matrices = std::vector<LocalToWorld>();
	_StarQuery.ToComponentDataArray(matrices);

	auto imr = _StarCluster.GetPrivateComponent<ParticleSystem>();
	imr->get()->Matrices.resize(matrices.size());
	memcpy(imr->get()->Matrices.data(), matrices.data(), sizeof(glm::mat4) * matrices.size());
}

void Galaxy::StarClusterSystem::FixedUpdate()
{
}
