#include "StarClusterSystem.h"
void Galaxy::StarClusterPattern::OnGui()
{
	static bool autoApply = true;
	ImGui::Checkbox("Auto apply", &autoApply);
	if (!autoApply && ImGui::Button("Apply")) Apply();
	bool needUpdate = false;
	float ySpread = m_ySpread;
	float xzSpread = m_xzSpread;
	float diskDiameter = m_diskDiameter;
	float diskEccentricity = m_diskEccentricity;
	float coreProportion = m_coreProportion;
	float coreEccentricity = m_coreEccentricity;
	float centerDiameter = m_centerDiameter;
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
	float twist = m_twist;
	glm::vec3 centerPosition = m_centerPosition;
	if (ImGui::DragFloat("Y Spread", &ySpread, 0.001f, 0.0f, 1.0f, "%.3f"))
	{
		m_ySpread = ySpread;
		needUpdate = true;
	}
	if (ImGui::DragFloat("XZ Spread", &xzSpread, 0.001f, 0.0f, 1.0f, "%.3f"))
	{
		m_xzSpread = xzSpread;
		needUpdate = true;
	}

	if (ImGui::DragFloat("Disk size", &diskDiameter, 1.0f, 1.0f, 10000.0f))
	{
		m_diskDiameter = diskDiameter;
		needUpdate = true;
	}
	if (ImGui::DragFloat("Disk eccentricity", &diskEccentricity, 0.01f, 0.0f, 1.0f))
	{
		m_diskEccentricity = diskEccentricity;
		needUpdate = true;
	}
	if (ImGui::DragFloat("Core proportion", &coreProportion, 0.01f, 0.0f, 1.0f))
	{
		m_coreProportion = coreProportion;
		needUpdate = true;
	}
	if (ImGui::DragFloat("Core eccentricity", &coreEccentricity, 0.01f, 0, 1))
	{
		m_coreEccentricity = coreEccentricity;
		needUpdate = true;
	}
	if (ImGui::DragFloat("Center size", &centerDiameter, 1.0f, 0, 9999))
	{
		m_centerDiameter = centerDiameter;
		needUpdate = true;
	}
	if (ImGui::DragFloat("Center eccentricity", &centerEccentricity, 0.01f, 0, 1))
	{
		m_centerEccentricity = centerEccentricity;
		needUpdate = true;
	}
	if (ImGui::DragFloat("Disk speed", &diskSpeed, 0.1f, -100, 100))
	{
		m_diskSpeed = diskSpeed;
		needUpdate = true;
	}
	if (ImGui::DragFloat("Core speed", &coreSpeed, 0.1f, -100, 100))
	{
		m_coreSpeed = coreSpeed;
		needUpdate = true;
	}
	if (ImGui::DragFloat("Center speed", &centerSpeed, 0.1f, -100, 100))
	{
		m_centerSpeed = centerSpeed;
		needUpdate = true;
	}
	if (ImGui::DragFloat("Disk X tilt", &diskTiltX, 1.0f, -180.0f, 180.0f))
	{
		m_diskTiltX = diskTiltX;
		needUpdate = true;
	}
	if (ImGui::DragFloat("Disk Z tilt", &diskTiltZ, 1.0f, -180.0f, 180.0f))
	{
		m_diskTiltZ = diskTiltZ;
		needUpdate = true;
	}
	if (ImGui::DragFloat("Core X tilt", &coreTiltX, 1.0f, -180.0f, 180.0f))
	{
		m_coreTiltX = coreTiltX;
		needUpdate = true;
	}
	if (ImGui::DragFloat("Core Z tilt", &coreTiltZ, 1.0f, -180.0f, 180.0f))
	{
		m_coreTiltZ = coreTiltZ;
		needUpdate = true;
	}
	if (ImGui::DragFloat("Center X tilt", &centerTiltX, 1.0f, -180.0f, 180.0f))
	{
		m_centerTiltX = centerTiltX;
		needUpdate = true;
	}
	if (ImGui::DragFloat("Center Z tilt", &centerTiltZ, 1.0f, -180.0f, 180.0f))
	{
		m_centerTiltZ = centerTiltZ;
		needUpdate = true;
	}
	if (ImGui::DragFloat3("Center position", &centerPosition.x, 0.01f, -1.0f, 1.0f))
	{
		m_centerPosition = centerPosition;
		needUpdate = true;
	}
	if (ImGui::DragFloat("Twist", &twist, 1.0f, -720.0f, 720.0f))
	{
		m_twist = twist;
		needUpdate = true;
	}
	if (needUpdate)
	{
		Apply(true);
	}
}

void Galaxy::StarClusterPattern::Apply(const bool& forceUpdateAllStars)
{
	SetAb();
	EntityManager::ForEach<StarInfo, StarClusterIndex, StarOrbit, StarOrbitOffset, StarOrbitProportion>(JobManager::SecondaryWorkers(),
		[&](int i, Entity entity, StarInfo& starInfo, StarClusterIndex& starClusterIndex, StarOrbit& starOrbit, StarOrbitOffset& starOrbitOffset, StarOrbitProportion& starOrbitProportion)
		{
			if (!forceUpdateAllStars && starInfo.m_initialized) return;
			starInfo.m_initialized = true;
			starOrbitOffset = GetOrbitOffset(starOrbitProportion.m_value);
			starOrbit = GetOrbit(starOrbitProportion.m_value);
		}
	);
}

void Galaxy::StarClusterSystem::OnGui()
{
	if (ImGui::Begin("Star Cluster System"))
	{
		static int amount = 10000;
		ImGui::DragInt("Amount", &amount, 1, 1, 100000);
		if (ImGui::CollapsingHeader("Star clusters", ImGuiTreeNodeFlags_DefaultOpen)) {
			int i = 0;
			for (auto& pattern : m_starClusterPatterns) {
				i++;
				if (ImGui::TreeNodeEx((std::to_string(i) + ": " + pattern.m_name).c_str(), ImGuiTreeNodeFlags_DefaultOpen)) {
					if (ImGui::TreeNodeEx("Properties", ImGuiTreeNodeFlags_DefaultOpen)) {
						pattern.OnGui();
						ImGui::TreePop();
					}
					if (ImGui::Button("Add stars"))
					{
						PushStars(pattern, amount);
					}
					ImGui::TreePop();
				}
			}
		}
		if (ImGui::CollapsingHeader("Star removal", ImGuiTreeNodeFlags_DefaultOpen)) {
			if (ImGui::Button("Remove stars")) RandomlyRemoveStars(amount);
			if (ImGui::Button("Remove all stars")) ClearAllStars();
		}
		if (ImGui::CollapsingHeader("Run time control", ImGuiTreeNodeFlags_DefaultOpen)) {
			ImGui::DragFloat("Speed", &m_speed, 1.0f, 0.1f, 30000.0f);
			ImGui::DragFloat("Star Size", &m_size, 0.1f, 0.1f, 10.0f);

		}
		ImGui::Text("Status:");
		ImGui::InputFloat("Apply time", &m_applyPositionTimer, 0, 0, "%.3f", ImGuiInputTextFlags_ReadOnly);
		ImGui::InputFloat("Copy time", &m_copyPositionTimer, 0, 0, "%.3f", ImGuiInputTextFlags_ReadOnly);
		ImGui::InputFloat("Calculation time", &m_calcPositionResult, 0, 0, "%.3f", ImGuiInputTextFlags_ReadOnly);
	}
	ImGui::End();
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
				EntityManager::ForEach<StarOrbitProportion, StarPosition, StarOrbit, StarOrbitOffset>(
					JobManager::SecondaryWorkers(), m_starQuery,
					[=](int i, Entity entity, StarOrbitProportion& starProportion, StarPosition& starPosition, StarOrbit& starOrbit, StarOrbitOffset& starOrbitOffset)
					{
						//Code here will be exec in parallel
						starPosition.m_value = starOrbit.GetPoint(starOrbitOffset.m_value, starProportion.m_value * 360.0f + m_galaxyTime, true);
					}, false
					);

				if (m_useFront)
				{
					auto& imr = m_rendererBack.GetPrivateComponent<Particles>();
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
					auto& imr = m_rendererFront.GetPrivateComponent<Particles>();
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
	EntityManager::ForEach<StarOrbitProportion, StarPosition, StarOrbit, StarOrbitOffset>(
		JobManager::SecondaryWorkers(), m_starQuery,
		[=](int i, Entity entity, StarOrbitProportion& statProportion, StarPosition& starPosition, StarOrbit& starOrbit, StarOrbitOffset& starOrbitOffset)
		{
			//Code here will be exec in parallel
			starPosition.m_value = starOrbit.GetPoint(starOrbitOffset.m_value, statProportion.m_value * 360.0f + m_galaxyTime, true);
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

	auto& imr = m_rendererFront.GetPrivateComponent<Particles>();
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

void Galaxy::StarClusterSystem::SetRenderer() const
{
	m_rendererBack.SetEnabled(!m_useFront);
	m_rendererFront.SetEnabled(m_useFront);
}

void Galaxy::StarClusterSystem::LateUpdate()
{
	OnGui();
}

void Galaxy::StarClusterSystem::OnCreate()
{
	EditorManager::GetInstance().m_selectedHierarchyDisplayMode = 0;
	m_rendererFront = EntityManager::CreateEntity("Renderer 1");
	GlobalTransform ltw;
	ltw.SetScale(glm::vec3(1.0f));
	auto imr = std::make_unique<Particles>();
	imr->m_material = std::make_shared<Material>();
	imr->m_castShadow = false;
	imr->m_receiveShadow = false;
	imr->m_mesh = Default::Primitives::Cube;
	imr->m_material->SetProgram(Default::GLPrograms::StandardInstancedProgram);
	imr->m_material->SetTexture(Default::Textures::StandardTexture);
	m_rendererFront.SetPrivateComponent(std::move(imr));
	m_rendererFront.SetComponentData(ltw);

	m_rendererBack = EntityManager::CreateEntity("Renderer 2");
	ltw.SetScale(glm::vec3(1.0f));
	imr = std::make_unique<Particles>();
	imr->m_material = std::make_shared<Material>();
	imr->m_castShadow = false;
	imr->m_receiveShadow = false;
	imr->m_mesh = Default::Primitives::Cube;
	imr->m_material->SetProgram(Default::GLPrograms::StandardInstancedProgram);
	imr->m_material->SetTexture(Default::Textures::StandardTexture);
	m_rendererBack.SetPrivateComponent(std::move(imr));
	m_rendererBack.SetComponentData(ltw);

	m_starClusterPatterns.resize(1);
	auto& pattern = m_starClusterPatterns[0];

	m_starQuery = EntityManager::CreateEntityQuery();
	EntityManager::SetEntityQueryAllFilters(m_starQuery, StarInfo());

	m_starArchetype = EntityManager::CreateEntityArchetype("Star",
		GlobalTransform(),
		StarClusterIndex(),
		StarInfo(), StarOrbit(), StarOrbitOffset(), StarOrbitProportion(), StarPosition(),
		SelectionStatus(), OriginalColor(), SurfaceColor(), DisplayColor()
	);
	pattern.m_ySpread = 0.05;
	pattern.m_xzSpread = 0.015;
	pattern.m_diskDiameter = 3000;
	pattern.m_diskEccentricity = 0.5;
	pattern.m_coreProportion = 0.4;
	pattern.m_coreEccentricity = 0.8;
	pattern.m_centerDiameter = 10;
	pattern.m_centerEccentricity = 0.5;
	pattern.m_diskSpeed = 1;
	pattern.m_coreSpeed = 5;
	pattern.m_centerSpeed = 10;
	pattern.m_diskTiltX = 0;
	pattern.m_diskTiltZ = 0;
	pattern.m_coreTiltX = 0;
	pattern.m_coreTiltZ = 0;
	pattern.m_centerTiltX = 0;
	pattern.m_centerTiltZ = 0;
	pattern.m_diskColor = glm::vec4(0, 0, 1, 1);
	pattern.m_coreColor = glm::vec4(1, 1, 0, 1);
	pattern.m_centerColor = glm::vec4(1, 1, 1, 1);
	pattern.m_twist = 360;
	pattern.m_centerPosition = glm::dvec3(0);
	pattern.SetAb();


	JobManager::ResizePrimaryWorkers(1);
	JobManager::ResizeSecondaryWorkers(16);


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

void Galaxy::StarClusterSystem::PushStars(StarClusterPattern& pattern, const size_t& amount) const
{
	auto stars = EntityManager::CreateEntities(m_starArchetype, amount, "Star");
	for (auto i = 0; i < amount; i++) {
		auto starEntity = stars[i];
		starEntity.SetStatic(true);
		StarOrbitProportion proportion;
		proportion.m_value = glm::linearRand(0.0, 1.0);
		StarInfo starInfo;
		EntityManager::SetComponentData(starEntity, starInfo);
		EntityManager::SetComponentData(starEntity, proportion);
		EntityManager::SetComponentData(starEntity, pattern.m_starClusterIndex);
	}
	pattern.Apply();
}

void Galaxy::StarClusterSystem::RandomlyRemoveStars(const size_t& amount) const
{
	std::vector<Entity> stars;
	m_starQuery.ToEntityArray(stars);
	size_t residue = amount;
	for (const auto& i : stars) {
		if (residue > 0) residue--;
		else break;
		EntityManager::DeleteEntity(i);
	}
}

void Galaxy::StarClusterSystem::ClearAllStars() const
{
	std::vector<Entity> stars;
	m_starQuery.ToEntityArray(stars);
	for (const auto& i : stars) EntityManager::DeleteEntity(i);
}

void Galaxy::StarClusterSystem::FixedUpdate()
{
}

void Galaxy::StarClusterSystem::OnStartRunning()
{
	m_firstTime = true;
}
