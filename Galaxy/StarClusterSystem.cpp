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
	glm::vec3 centerOffset = m_centerOffset;
	glm::vec3 centerPosition = m_centerPosition;
	if (ImGui::TreeNode("Shape")) {
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
		ImGui::TreePop();
		if (ImGui::DragFloat3("Center offset", &centerOffset.x, 1.0f, -10000.0f, 10000.0f))
		{
			m_centerOffset = centerOffset;
			needUpdate = true;
		}
		if (ImGui::DragFloat3("Center position", &centerPosition.x, 1.0f, -10000.0f, 10000.0f))
		{
			m_centerPosition = centerPosition;
			needUpdate = true;
		}
	}
	if (ImGui::TreeNode("Movement")) {
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
		if (ImGui::DragFloat("Twist", &twist, 1.0f, -720.0f, 720.0f))
		{
			m_twist = twist;
			needUpdate = true;
		}
		ImGui::TreePop();
	}
	bool colorUpdate = false;
	if (ImGui::TreeNode("Rendering"))
	{
		if (ImGui::ColorEdit3("Disk Color", &m_diskColor.x, 0.1)) colorUpdate = true;
		if (ImGui::DragFloat("Disk Color Intensity", &m_diskEmissionIntensity, 0.01f, 1.0f, 10.0f)) colorUpdate = true;
		if (ImGui::ColorEdit3("Core Color", &m_coreColor.x, 0.1)) colorUpdate = true;
		if (ImGui::DragFloat("Core Color Intensity", &m_coreEmissionIntensity, 0.01f, 1.0f, 10.0f)) colorUpdate = true;
		if (ImGui::ColorEdit3("Center Color", &m_centerColor.x, 0.1)) colorUpdate = true;
		if (ImGui::DragFloat("Center Color Intensity", &m_centerEmissionIntensity, 0.01f, 1.0f, 10.0f)) colorUpdate = true;
		ImGui::TreePop();
	}

	if (needUpdate)
	{
		Apply(true);
	}
	else if (colorUpdate)
	{
		Apply(true, true);
	}
}

void Galaxy::StarClusterPattern::Apply(const bool& forceUpdateAllStars, const bool& onlyUpdateColors)
{
	SetAb();
	EntityManager::ForEach<StarInfo, StarClusterIndex, StarOrbit, StarOrbitOffset, StarOrbitProportion, SurfaceColor>(JobManager::SecondaryWorkers(),
		[&](int i, Entity entity, StarInfo& starInfo, StarClusterIndex& starClusterIndex, StarOrbit& starOrbit, StarOrbitOffset& starOrbitOffset, StarOrbitProportion& starOrbitProportion, SurfaceColor& surfaceColor)
		{
			if (!forceUpdateAllStars && starInfo.m_initialized) return;
			if (starClusterIndex.m_value != this->m_starClusterIndex.m_value) return;
			starInfo.m_initialized = true;
			const auto proportion = starOrbitProportion.m_value;
			if (!onlyUpdateColors) {
				starOrbitOffset = GetOrbitOffset(proportion);
				starOrbit = GetOrbit(proportion);
			}
			surfaceColor.m_value = GetColor(proportion);
			surfaceColor.m_intensity = GetIntensity(proportion);
		}
	);
	EntityManager::ForEach<StarOrbit, StarOrbitA, StarOrbitB, StarOrbitSpeedMultiplier, StarTiltX, StarTiltY, StarTiltZ, OrbitCenter>(JobManager::SecondaryWorkers(),
		[&](int i, Entity entity, StarOrbit& starOrbit, StarOrbitA& starOrbitA, StarOrbitB& starOrbitB,
			StarOrbitSpeedMultiplier& starOrbitSpeedMultiplier
			, StarTiltX& starTiltX, StarTiltY& starTiltY, StarTiltZ& starTiltZ, OrbitCenter& starCenter)
		{
			starOrbitA.m_value = starOrbit.m_a;
			starOrbitB.m_value = starOrbit.m_b;
			starOrbitSpeedMultiplier.m_value = starOrbit.m_speedMultiplier;
			starTiltX.m_value = starOrbit.m_tiltX;
			starTiltY.m_value = starOrbit.m_tiltY;
			starTiltZ.m_value = starOrbit.m_tiltZ;
			starCenter.m_value = starOrbit.m_center;
		}
	);
}

void Galaxy::StarClusterSystem::OnGui()
{
	if (ImGui::Begin("Star Cluster System"))
	{
		if (ImGui::Checkbox("Enable SIMD", &m_useSimd)) m_counter = 0;
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
			ImGui::DragFloat("Speed", &m_speed, 1.0f, 0.0f, 40000.0f);
			ImGui::DragFloat("Star Size", &m_size, 0.01f, 0.01f, 10.0f);

		}
		ImGui::Text("Status:");
		ImGui::InputFloat("Apply time", &m_applyPositionTimer, 0, 0, "%.5f", ImGuiInputTextFlags_ReadOnly);
		ImGui::InputFloat("Copy time", &m_copyPositionTimer, 0, 0, "%.5f", ImGuiInputTextFlags_ReadOnly);
		ImGui::InputFloat("Calculation time", &m_calcPositionResult, 0, 0, "%.5f", ImGuiInputTextFlags_ReadOnly);
	}
	ImGui::End();
}

void Galaxy::StarClusterSystem::RenderStars(std::unique_ptr<CameraComponent>& camera, const glm::vec3& cameraPosition, const glm::quat& cameraRotation)
{
	auto& matrices = m_useFront ? m_frontMatrices : m_backMatrices;
	auto& colors = m_useFront ? m_frontColors : m_backColors;
	if (matrices.empty() || colors.empty() || matrices.size() != colors.size()) return;
	if (!camera->IsEnabled()) return;
#pragma region Render
	CameraComponent::m_cameraInfoBlock.UpdateMatrices(camera.get(),
		cameraPosition,
		cameraRotation
	);
	CameraComponent::m_cameraInfoBlock.UploadMatrices(camera.get());
	camera->Bind();
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glDrawBuffer(GL_COLOR_ATTACHMENT0);
	glEnable(GL_DEPTH_TEST);
	const auto mesh = Default::Primitives::Cube;
	mesh->Enable();
	const auto vao = mesh->Vao();

	const size_t count = colors.size();
	m_renderColorBuffer.SetData(static_cast<GLsizei>(count) * sizeof(glm::vec4), colors.data(), GL_DYNAMIC_DRAW);
	vao->EnableAttributeArray(11);
	vao->SetAttributePointer(11, 4, GL_FLOAT, GL_FALSE, sizeof(glm::vec4), (void*)0);
	vao->SetAttributeDivisor(11, 1);

	m_renderTransformBuffer.SetData(static_cast<GLsizei>(count) * sizeof(glm::mat4), matrices.data(), GL_DYNAMIC_DRAW);
	vao->EnableAttributeArray(12);
	vao->SetAttributePointer(12, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)0);
	vao->EnableAttributeArray(13);
	vao->SetAttributePointer(13, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(sizeof(glm::vec4)));
	vao->EnableAttributeArray(14);
	vao->SetAttributePointer(14, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(2 * sizeof(glm::vec4)));
	vao->EnableAttributeArray(15);
	vao->SetAttributePointer(15, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(3 * sizeof(glm::vec4)));
	vao->SetAttributeDivisor(12, 1);
	vao->SetAttributeDivisor(13, 1);
	vao->SetAttributeDivisor(14, 1);
	vao->SetAttributeDivisor(15, 1);

	m_starRenderProgram->Bind();
	const glm::mat4 translation = glm::translate(glm::identity<glm::mat4>(), glm::vec3(0.0f));
	const glm::mat4 scale = glm::scale(glm::identity<glm::mat4>(), glm::vec3(1.0));
	const glm::mat4 model = translation * scale;
	m_starRenderProgram->SetFloat4x4("model", model);

	glDrawElementsInstanced(GL_TRIANGLES, static_cast<GLsizei>(mesh->GetTriangleAmount()) * 3, GL_UNSIGNED_INT, 0, (GLsizei)count);
	vao->DisableAttributeArray(11);
	vao->DisableAttributeArray(12);
	vao->DisableAttributeArray(13);
	vao->DisableAttributeArray(14);
	vao->DisableAttributeArray(15);
#pragma endregion
}

void Galaxy::StarClusterSystem::CalculateStarPositionAsync()
{
	auto list = EntityManager::UnsafeGetComponentDataArray<GlobalTransform>(m_starQuery);
	if (m_firstTime || m_currentStatus.wait_for(std::chrono::seconds(0)) == std::future_status::ready)
	{
		m_useFront = !m_useFront;
		m_calcPositionResult = Application::EngineTime() - m_calcPositionTimer;
		m_firstTime = false;
		ApplyPosition();
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
				CopyPosition(true);
			}
		);
	}
}

void Galaxy::StarClusterSystem::CalculateStarPositionSync()
{
	//Star calculation happens here:
	if (m_useSimd)
	{
		const auto orbitALists = EntityManager::UnsafeGetComponentDataArray<StarOrbitA>(m_starQuery);
		const auto orbitBLists = EntityManager::UnsafeGetComponentDataArray<StarOrbitB>(m_starQuery);
		const auto orbitSpeedMultiplierLists = EntityManager::UnsafeGetComponentDataArray<StarOrbitSpeedMultiplier>(m_starQuery);
		const auto orbitTiltXLists = EntityManager::UnsafeGetComponentDataArray<StarTiltX>(m_starQuery);
		const auto orbitTiltYLists = EntityManager::UnsafeGetComponentDataArray<StarTiltY>(m_starQuery);
		const auto orbitTiltZLists = EntityManager::UnsafeGetComponentDataArray<StarTiltZ>(m_starQuery);
		const auto orbitCenterLists = EntityManager::UnsafeGetComponentDataArray<OrbitCenter>(m_starQuery);

		const auto proportionLists = EntityManager::UnsafeGetComponentDataArray<StarOrbitProportion>(m_starQuery);
		const auto starOrbitOffsetLists = EntityManager::UnsafeGetComponentDataArray<StarOrbitOffset>(m_starQuery);

		const auto positionLists = EntityManager::UnsafeGetComponentDataArray<StarPosition>(m_starQuery);

		std::vector<std::shared_future<void>> results;
		m_calcPositionTimer = Application::EngineTime();
		const auto threadSize = JobManager::SecondaryWorkers().Size();
		const auto chunkSize = orbitALists.size();
		const auto chunkPerThread = chunkSize / threadSize;
		const auto chunkReminder = chunkSize % threadSize;
		const auto lastChunkIndex = chunkPerThread * threadSize;
		for (int threadIndex = 0; threadIndex < threadSize; threadIndex++)
		{
			results.push_back(JobManager::SecondaryWorkers().Push([=](int id)
				{
					const auto maxChunkIndex = chunkPerThread + (threadIndex < chunkReminder ? 1 : 0);
					std::vector<glm::dvec3> points;
					std::vector<double> angles;
					for (auto allocatedChunkIndex = 0; allocatedChunkIndex < maxChunkIndex; allocatedChunkIndex++) {
						auto chunkIndex = allocatedChunkIndex + chunkPerThread * threadIndex;
						if(threadIndex < chunkReminder && allocatedChunkIndex == maxChunkIndex - 1)
						{
							chunkIndex = lastChunkIndex + threadIndex;
						}
						auto* const orbitAList = orbitALists[chunkIndex].first;
						auto* const orbitBList = orbitBLists[chunkIndex].first;
						auto* const orbitSpeedMultiplierList = orbitSpeedMultiplierLists[chunkIndex].first;
						auto* const orbitTiltXList = orbitTiltXLists[chunkIndex].first;
						auto* const orbitTiltYList = orbitTiltYLists[chunkIndex].first;
						auto* const orbitTiltZList = orbitTiltZLists[chunkIndex].first;
						auto* const orbitCenterList = orbitCenterLists[chunkIndex].first;
						auto* const proportionList = proportionLists[chunkIndex].first;
						auto* const starOrbitOffsetList = starOrbitOffsetLists[chunkIndex].first;
						auto* const positionList = positionLists[chunkIndex].first;
						const auto size = orbitALists[chunkIndex].second;
						points.resize(size);
						angles.resize(size);
						//SIMD Capable
						const bool useSIMD = false;
						if (useSIMD) {
							const auto div = size / 4;
							for (auto i = 0; i < div; i++)
							{
								const auto orbitA4 = _mm256_load_pd((double*)((char*)orbitAList + i * 4 * sizeof(double)));
								const auto orbitB4 = _mm256_load_pd((double*)((char*)orbitBList + i * 4 * sizeof(double)));
								const auto speedMul4 = _mm256_load_pd((double*)((char*)orbitSpeedMultiplierList + i * 4 * sizeof(double)));
								const auto proportion4 = _mm256_load_pd((double*)((char*)proportionList + i * 4 * sizeof(double)));

								const double d360[4] = { 360.0, 360.0, 360.0, 360.0 };
								const double times[4] = { m_galaxyTime, m_galaxyTime, m_galaxyTime, m_galaxyTime };
								const auto d4 = _mm256_load_pd(d360);
								__m256d time4 = _mm256_load_pd(times);
								time4 = _mm256_add_pd(_mm256_mul_pd(proportion4, d4), time4);
								// proportion->m_value * 360.0f + m_galaxyTime;

								_mm256_storeu_pd(
									&angles[i * 4],
									_mm256_mul_pd(_mm256_div_pd(time4, _mm256_sqrt_pd(_mm256_add_pd(orbitA4, orbitB4))), speedMul4)
								);
								//angles[i] = time / glm::sqrt(orbitA->m_value + orbitB->m_value) * speedMul->m_value;
							}

							for (auto i = div * 4; i < size; i++)
							{
								auto* orbitA = (StarOrbitA*)((char*)orbitAList + i * sizeof(StarOrbitA));
								auto* orbitB = (StarOrbitB*)((char*)orbitBList + i * sizeof(StarOrbitB));
								auto* speedMul = (StarOrbitSpeedMultiplier*)((char*)orbitSpeedMultiplierList + i * sizeof(StarOrbitSpeedMultiplier));
								auto* proportion = (StarOrbitProportion*)((char*)proportionList + i * sizeof(StarOrbitProportion));

								const double time = proportion->m_value * 360.0f + m_galaxyTime;
								angles[i] = time / glm::sqrt(orbitA->m_value + orbitB->m_value) * speedMul->m_value;
							}
						}
						else {
							for (auto i = 0; i < size; i++)
							{
								auto* orbitA = (StarOrbitA*)((char*)orbitAList + i * sizeof(StarOrbitA));
								auto* orbitB = (StarOrbitB*)((char*)orbitBList + i * sizeof(StarOrbitB));
								auto* speedMul = (StarOrbitSpeedMultiplier*)((char*)orbitSpeedMultiplierList + i * sizeof(StarOrbitSpeedMultiplier));
								auto* proportion = (StarOrbitProportion*)((char*)proportionList + i * sizeof(StarOrbitProportion));

								const double time = proportion->m_value * 360.0f + m_galaxyTime;
								angles[i] = time / glm::sqrt(orbitA->m_value + orbitB->m_value) * speedMul->m_value;
							}
						}
						for (auto i = 0; i < size; i++)
						{
							auto* orbitA = (StarOrbitA*)((char*)orbitAList + i * sizeof(StarOrbitA));
							auto* orbitB = (StarOrbitB*)((char*)orbitBList + i * sizeof(StarOrbitB));
							points[i].x = glm::sin(glm::radians(angles[i])) * orbitA->m_value;
							points[i].y = 0;
							points[i].z = glm::cos(glm::radians(angles[i])) * orbitB->m_value;
						}
						for (auto i = 0; i < size; i++)
						{
							auto* tiltX = (StarTiltX*)((char*)orbitTiltXList + i * sizeof(StarTiltX));
							auto* tiltY = (StarTiltY*)((char*)orbitTiltYList + i * sizeof(StarTiltY));
							auto* tiltZ = (StarTiltZ*)((char*)orbitTiltZList + i * sizeof(StarTiltZ));

							points[i] = StarOrbit::Rotate(glm::angleAxis(glm::radians(tiltX->m_value), glm::dvec3(1, 0, 0)), points[i]);
							points[i] = StarOrbit::Rotate(glm::angleAxis(glm::radians(tiltY->m_value), glm::dvec3(0, 1, 0)), points[i]);
							points[i] = StarOrbit::Rotate(glm::angleAxis(glm::radians(tiltZ->m_value), glm::dvec3(0, 0, 1)), points[i]);
						}
						//SIMD Capable
						if (useSIMD) {
							const auto div2 = 3 * size / 4;
							for (auto i = 0; i < div2; i++)
							{
								const auto point4 = _mm256_load_pd((double*)((char*)points.data() + i * 4 * sizeof(double)));
								const auto center4 = _mm256_load_pd((double*)((char*)orbitCenterList + i * 4 * sizeof(double)));
								const auto offset4 = _mm256_load_pd((double*)((char*)starOrbitOffsetList + i * 4 * sizeof(double)));
								_mm256_storeu_pd(
									(double*)((char*)positionList + i * 4 * sizeof(double)),
									_mm256_add_pd(point4, _mm256_add_pd(center4, offset4))
								);
							}
							for (auto i = div2 * 4; i < size * 3; i++)
							{
								auto point = *(double*)((char*)points.data() + i * sizeof(double));
								const auto center = *(double*)((char*)orbitCenterList + i * sizeof(double));
								const auto offset = *(double*)((char*)starOrbitOffsetList + i * sizeof(double));
								auto* position = (double*)((char*)positionList + i * sizeof(double));
								point += center;
								point += offset;
								*position = point;
							}
						}
						else {
							for (auto i = 0; i < size; i++)
							{
								auto* center = (OrbitCenter*)((char*)orbitCenterList + i * sizeof(OrbitCenter));
								auto* offset = (StarOrbitOffset*)((char*)starOrbitOffsetList + i * sizeof(StarOrbitOffset));
								auto* position = (StarPosition*)((char*)positionList + i * sizeof(StarPosition));
								points[i] += center->m_value;
								points[i] += offset->m_value;
								position->m_value = points[i];
							}
						}
					}
				}

			).share());
		}
		for (const auto& i : results) i.wait();
		const auto usedTime = Application::EngineTime() - m_calcPositionTimer;
		m_calcPositionResult = m_calcPositionResult * m_counter / (m_counter + 1) + usedTime / (m_counter + 1);
	}
	else {
		m_calcPositionTimer = Application::EngineTime();
		EntityManager::ForEach<StarOrbitProportion, StarPosition, StarOrbit, StarOrbitOffset>(
			JobManager::SecondaryWorkers(), m_starQuery,
			[=](int i, Entity entity, StarOrbitProportion& starProportion, StarPosition& starPosition, StarOrbit& starOrbit, StarOrbitOffset& starOrbitOffset)
			{
				//Code here will be exec in parallel
				starPosition.m_value = starOrbit.GetPoint(starOrbitOffset.m_value, starProportion.m_value * 360.0f + m_galaxyTime, true);
			}, false
			);
		const auto usedTime = Application::EngineTime() - m_calcPositionTimer;
		m_calcPositionResult = m_calcPositionResult * m_counter / (m_counter + 1) + usedTime / (m_counter + 1);
	}
	//Copy data for rendering.
	m_useFront = true;
	ApplyPosition();
	CopyPosition();
}

void Galaxy::StarClusterSystem::ApplyPosition()
{
	m_applyPositionTimer = Application::EngineTime();
	EntityManager::ForEach<StarPosition, GlobalTransform, Transform, SurfaceColor, DisplayColor>(
		JobManager::SecondaryWorkers(), m_starQuery,
		[this](int i, Entity entity, StarPosition& position, GlobalTransform& globalTransform, Transform& transform,
			SurfaceColor& surfaceColor,
			DisplayColor& displayColor)
		{
			//Code here will be exec in parallel
			globalTransform.m_value = glm::translate(glm::vec3(position.m_value) / 20.0f) * glm::scale(m_size * glm::vec3(1.0f));
			transform.m_value = globalTransform.m_value;
			displayColor.m_value = surfaceColor.m_value;
			displayColor.m_intensity = surfaceColor.m_intensity;
		}, false
		);
	m_applyPositionTimer = Application::EngineTime() - m_applyPositionTimer;
}

void Galaxy::StarClusterSystem::CopyPosition(const bool& reverse)
{
	bool check = reverse ? !m_useFront : m_useFront;
	auto& matrices = check ? m_frontMatrices : m_backMatrices;
	auto& colors = check ? m_frontColors : m_backColors;
	const auto starAmount = m_starQuery.GetEntityAmount();
	matrices.resize(starAmount);
	colors.resize(starAmount);
	EntityManager::ForEach<GlobalTransform, DisplayColor>(
		JobManager::SecondaryWorkers(), m_starQuery,
		[&](int i, Entity entity, GlobalTransform& globalTransform, DisplayColor& displayColor)
		{
			matrices[i] = globalTransform.m_value;
			colors[i] = glm::vec4(displayColor.m_value * displayColor.m_intensity, 1.0f);
		}, false
		);
}

void Galaxy::StarClusterSystem::LateUpdate()
{
	OnGui();
}

void Galaxy::StarClusterSystem::OnCreate()
{
	const auto vertShaderCode = std::string("#version 460 core\n")
		+ *Default::ShaderIncludes::Uniform +
		+"\n"
		+ FileIO::LoadFileAsString(FileIO::GetResourcePath() + "Shaders/Vertex/ColoredGizmos.vert");
	const auto fragShaderCode = std::string("#version 460 core\n")
		+ *Default::ShaderIncludes::Uniform
		+ "\n"
		+ FileIO::LoadFileAsString(FileIO::GetResourcePath() + "Shaders/Fragment/ColoredGizmos.frag");

	auto standardVert = std::make_shared<GLShader>(ShaderType::Vertex);
	standardVert->Compile(vertShaderCode);
	auto standardFrag = std::make_shared<GLShader>(ShaderType::Fragment);
	standardFrag->Compile(fragShaderCode);
	m_starRenderProgram = std::make_unique<GLProgram>(standardVert, standardFrag);

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

	m_starClusterPatterns.resize(2);
	auto& starClusterPattern1 = m_starClusterPatterns[0];
	auto& starClusterPattern2 = m_starClusterPatterns[1];
	starClusterPattern1.m_starClusterIndex.m_value = 0;
	starClusterPattern2.m_starClusterIndex.m_value = 1;
	m_starQuery = EntityManager::CreateEntityQuery();
	EntityManager::SetEntityQueryAllFilters(m_starQuery, StarInfo());

	m_starArchetype = EntityManager::CreateEntityArchetype("Star",
		GlobalTransform(),
		StarClusterIndex(),
		StarInfo(), StarOrbit(), StarOrbitOffset(), StarOrbitProportion(), StarPosition(),
		SelectionStatus(), OriginalColor(), SurfaceColor(), DisplayColor(),
		//SIMD
		StarOrbitA(), StarOrbitB(), StarOrbitSpeedMultiplier(),
		StarTiltX(), StarTiltY(), StarTiltZ(),
		OrbitCenter()
	);
	JobManager::ResizePrimaryWorkers(1);
	JobManager::ResizeSecondaryWorkers(16);
	m_firstTime = true;
	Enable();
}

void Galaxy::StarClusterSystem::Update()
{
	m_galaxyTime += m_world->Time()->DeltaTime() * m_speed;

	//This method calculate the position for each star. Remove this line if you use your own implementation.
	CalculateStarPositionSync();

	//Do not touch below functions.
	RenderManager::DrawGizmoMeshInstancedColored(Default::Primitives::Cube.get(), RenderManager::GetMainCamera(), m_useFront ? m_frontColors.data() : m_backColors.data(), m_useFront ? m_frontMatrices.data() : m_backMatrices.data(), m_useFront ? m_frontColors.size() : m_backColors.size(), glm::scale(glm::vec3(m_size)));

	m_counter++;
}

void Galaxy::StarClusterSystem::PushStars(StarClusterPattern& pattern, const size_t& amount)
{
	m_counter = 0;
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

void Galaxy::StarClusterSystem::RandomlyRemoveStars(const size_t& amount)
{
	m_counter = 0;
	std::vector<Entity> stars;
	m_starQuery.ToEntityArray(stars);
	size_t residue = amount;
	for (const auto& i : stars) {
		if (residue > 0) residue--;
		else break;
		EntityManager::DeleteEntity(i);
	}
}

void Galaxy::StarClusterSystem::ClearAllStars()
{
	m_counter = 0;
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
