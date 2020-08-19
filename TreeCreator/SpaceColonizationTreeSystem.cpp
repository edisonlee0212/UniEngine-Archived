#include "SpaceColonizationTreeSystem.h"

static const char* EnvelopeTypes[]{ "Default", "Box", "Cylinder", "Coil" };

void SpaceColonizationTreeSystem::DrawGUI()
{
	ImGui::Begin("Space Colonization");

	if (ImGui::CollapsingHeader("Tree Creation controller")) {
		ImGui::TreePush();
		std::string title = "Tree Color";
		ImGui::ColorEdit3(title.c_str(), (float*)&_NewTreeColor.Color);
		title = "Bud Color";
		ImGui::ColorEdit3(title.c_str(), (float*)&_NewTreeColor.BudColor);
		title = "Leaf Color";
		ImGui::ColorEdit3(title.c_str(), (float*)&_NewTreeColor.LeafColor);
		title = "Connection Color";
		ImGui::ColorEdit3(title.c_str(), (float*)&_NewTreeColor.ConnectionColor);


		glm::vec3 position;
		ImGui::InputFloat3("New tree position", (float*)&_NewTreePosition, 2);
		if (ImGui::Button("Create")) {
			CreateTree(_NewTreeColor, _NewTreePosition);
		}
		ImGui::TreePop();
	}

	auto treeEntities = TreeManager::GetTreeSystem()->GetTreeEntities();
	if (ImGui::CollapsingHeader("Envelope controller", ImGuiTreeNodeFlags_DefaultOpen)) {
		ImGui::TreePush();
		int currentType = _SelectedEnvelopeType;
		ImGui::Combo("Envelope Type", &currentType, EnvelopeTypes, IM_ARRAYSIZE(EnvelopeTypes), 3);
		if (currentType != _SelectedEnvelopeType) {
			_Envelope.ResetType((EnvelopeType)currentType);
			_SelectedEnvelopeType = currentType;
		}

		ImGui::InputFloat3("Envelope Position", (float*)&_Envelope._SpaceCenter, 2);
		ImGui::InputFloat3("Envelope Size", (float*)&_Envelope._SpaceSize, 2);

		ImGui::InputInt("Amount", &_PushAttractionPoints);
		if (ImGui::Button("Push Attraction Points")) {
			PushAttractionPoints(_PushAttractionPoints);
		}
		if (ImGui::Button("Clear Attraction Points")) {
			ClearAttractionPoints();
		}
		ImGui::TreePop();
	}
	if (ImGui::CollapsingHeader("Growth controller")) {
		ImGui::TreePush();
		if (ImGui::Button("Start all")) {
			for (auto tree : *treeEntities) {
				TreeGrowIteration iteration = EntityManager::GetComponentData<TreeGrowIteration>(tree);
				iteration.Enable = true;
				EntityManager::SetComponentData(tree, iteration);
			}
		}
		if (ImGui::CollapsingHeader("Tree List", ImGuiTreeNodeFlags_DefaultOpen)) {
			TreeIndex index;
			TreeColor color;
			ImGui::TreePush();
			for (auto tree : *treeEntities) {
				index = EntityManager::GetComponentData<TreeIndex>(tree);
				std::string title = "Tree ";
				title += std::to_string(index.Value);
				bool opened = ImGui::TreeNodeEx(title.c_str(), ImGuiTreeNodeFlags_NoAutoOpenOnLog | ImGuiTreeNodeFlags_FramePadding);
				if (opened) {
					color = EntityManager::GetComponentData<TreeColor>(tree);
					ImGui::Text("Tree Color: [%d, %d, %d]", (int)(color.BudColor.x * 256.0f), (int)(color.BudColor.y * 256.0f), (int)(color.BudColor.z * 256.0f));
					ImGui::Separator();
					TreeGrowIteration iteration = EntityManager::GetComponentData<TreeGrowIteration>(tree);
					int remain = iteration.Value;
					bool setEnabled = iteration.Enable;
					std::string gtitle = "Growing##";
					gtitle += std::to_string(index.Value);
					ImGui::Checkbox(gtitle.c_str(), &setEnabled);
					gtitle = "Iteration##";
					gtitle += std::to_string(index.Value);
					ImGui::InputInt(gtitle.c_str(), &remain);
					if (ImGui::IsItemActivated()) {
						setEnabled = false;
					}
					if (remain != iteration.Value || setEnabled != iteration.Enable) {
						iteration.Enable = setEnabled;
						iteration.Value = remain;
						EntityManager::SetComponentData(tree, iteration);
					}
					ImGui::TreePop();
				}
			}
			ImGui::TreePop();
		}
		ImGui::TreePop();
	}
	ImGui::End();
}

inline void SpaceColonizationTreeSystem::AddAttractionPoint(Translation translation)
{
	auto pointEntity = EntityManager::CreateEntity(_AttractionPointArchetype);
	EntityManager::SetComponentData(
		pointEntity,
		translation);

	EntityManager::SetComponentData(
		pointEntity,
		AttractionPointIndex(_AttractionPointMaxIndex)
	);
	Scale s;
	s.Value = glm::vec3(0.1f);
	EntityManager::SetComponentData(
		pointEntity,
		s
	);
	_AttractionPointMaxIndex++;
}

void SpaceColonizationTreeSystem::GrowAllTrees(float attractionDistance, float removeDistance, float growDistance)
{
	if (_AttractionPointQuery.GetEntityAmount() == 0) {
		//No more attraction points, return.
		Debug::Log("SpaceColonizationTreeSystem: Run out of attraction points!");
		_AllTreesToGrowIteration = 0;
		return;
	}
	unsigned newBudAmount = 0;
	//Retreve all buds;
	auto budEntityList = TreeManager::GetBudSystem()->GetBudEntities();
	auto ltwList = std::vector<LocalToWorld>();
	_BudQuery.ToComponentDataArray(&ltwList);
	EntityManager::ForEach<AttractionPointCurrentStatus>(_AttractionPointQuery, [](int i, Entity entity, AttractionPointCurrentStatus* status)
		{
			status->remove = false;
			status->budEntityIndex = 0;
			status->distance = 999999;
			status->growDirDelta = glm::vec3(0.0f);
		});
	//Assign points to buds;
	for (int i = 0; i < budEntityList->size(); i++) {
		auto budEntity = budEntityList->at(i);
		if (!budEntity.Enabled()) continue;
		BudInfo budType = EntityManager::GetComponentData<BudInfo>(budEntity);
		if (budType.Value == BudTypes::LATERAL_BUD && !budType.Searching) {
			continue;
		}
		unsigned budEntityIndex = budEntity.Index;
		glm::vec3 budPos = ltwList[i].Value[3];
		EntityManager::ForEach<Translation, AttractionPointCurrentStatus>(_AttractionPointQuery, [budEntityIndex, budPos, attractionDistance, removeDistance](int i, Entity entity, Translation* translation, AttractionPointCurrentStatus* status)
			{
				float distance = glm::distance(translation->Value, budPos);
				if (distance < attractionDistance && distance < status->distance) {
					status->remove = distance < removeDistance;
					status->budEntityIndex = budEntityIndex;
					status->distance = distance;
					status->growDirDelta = translation->Value - budPos;
				}
			});
	}
#pragma region Remove points
	std::vector<Entity> points;
	std::mutex ml;
	EntityManager::ForEach<AttractionPointCurrentStatus>(_AttractionPointQuery, [&points, &ml](int i, Entity entity, AttractionPointCurrentStatus* status) {
		if (status->remove) {
			std::lock_guard<std::mutex> lock(ml);
			points.push_back(entity);
		}
		});
	for (auto i : points) {
		EntityManager::DeleteEntity(i);
	}
#pragma endregion
	//Create new buds
	for (int i = 0; i < budEntityList->size(); i++) {
		auto budEntity = budEntityList->at(i);
		if (!budEntity.Enabled()) continue;
		BudInfo budType = EntityManager::GetComponentData<BudInfo>(budEntity);
		if (budType.Value == BudTypes::LATERAL_BUD && !budType.Searching) {
			continue;
		}
		unsigned budEntityIndex = budEntity.Index;
		std::mutex ml;
		unsigned amount = 0;
		glm::vec3 growDir = glm::vec3(0.0f);
		EntityManager::ForEach<AttractionPointCurrentStatus>(_AttractionPointQuery, [budEntityIndex, &ml, &amount, &growDir](int i, Entity entity, AttractionPointCurrentStatus* status)
			{
				if (status->budEntityIndex == budEntityIndex) {
					std::lock_guard<std::mutex> lock(ml);
					amount++;
					growDir += status->growDirDelta;
				}
			});
		if (amount == 0) {
			if (budType.Value == BudTypes::APICAL_BUD && budType.Searching) {
				glm::vec3 budPos = ltwList[i].Value[3];
				float minDistance = 999999;
				EntityManager::ForEach<Translation>(_AttractionPointQuery, [&amount, &ml, &growDir, budPos, &minDistance](int i, Entity entity, Translation* translation)
					{
						float distance = glm::distance(translation->Value, budPos);
						if (distance < minDistance) {
							std::lock_guard<std::mutex> lock(ml);
							minDistance = distance;
							growDir += translation->Value - budPos;
							amount++;
						}
					});

			}
			else if (budType.Value == BudTypes::LATERAL_BUD) {
				budType.Searching = false;
				EntityManager::SetComponentData(budEntityList->at(i), budType);
			}
		}
		else {
			if (budType.Value == BudTypes::APICAL_BUD) {
				//Stop overall search for apical bud if it already found the target.
				budType.Searching = false;
			}
			else {
				//Continue searching if we still have points around.
				budType.Searching = true;
			}
		}
		if (amount != 0) {
#pragma region Create New bud
			Entity currentBud = budEntityList->at(i);
			growDir = glm::normalize(growDir);
			Translation t;
			Rotation r;
			r.Value = glm::quat(0, 0, 0, 0);
			Scale s;
			LocalPosition lp;
			lp.Value = growDir * growDistance;
			t.Value = lp.Value + EntityManager::GetComponentData<Translation>(currentBud).Value;
			s.Value = glm::vec3(1.0f);
			//TODO: Check newbud is valid.
			auto childList = EntityManager::GetChildren(currentBud);
			bool tooClose = false;
			for (auto i : childList) {
				if (glm::distance(t.Value, EntityManager::GetComponentData<Translation>(i).Value) < 0.05f) {
					tooClose = true;
				}
			}
			if (!tooClose) {
				newBudAmount++;
				auto newBud = TreeManager::CreateBud(EntityManager::GetComponentData<TreeIndex>(currentBud), currentBud);
				EntityManager::SetComponentData(newBud, lp);
				EntityManager::SetComponentData(newBud, t);
				EntityManager::SetComponentData(newBud, r);
				EntityManager::SetComponentData(newBud, s);
				if (budType.Value == BudTypes::APICAL_BUD) {
					EntityManager::SetComponentData(newBud, budType);
					budType.Value = BudTypes::LATERAL_BUD;
					budType.Searching = true;
					EntityManager::SetComponentData(currentBud, budType);
				}
				else {
					EntityManager::SetComponentData(currentBud, budType);
					budType.Searching = true;
					EntityManager::SetComponentData(newBud, budType);
				}
			}
#pragma endregion
		}
	}

	if (newBudAmount == 0) {
		//No more attraction points, return.
		Debug::Log("SpaceColonizationTreeSystem: No new buds generated in this iteration, finish growing.");
		_AllTreesToGrowIteration = 0;
	}

}

void SpaceColonizationTreeSystem::GrowTree(Entity treeEntity, float attractionDistance, float removeDistance, float growDistance)
{
	TreeGrowIteration treeIteration = EntityManager::GetComponentData<TreeGrowIteration>(treeEntity);
	if (treeIteration.Value == 0 || !treeIteration.Enable) {
		return;
	}

	if (_AttractionPointQuery.GetEntityAmount() == 0) {
		//No more attraction points, return.
		Debug::Log("SpaceColonizationTreeSystem: Run out of attraction points!");
		TreeGrowIteration iteration = TreeGrowIteration();
		iteration.Value = 0;
		EntityManager::SetComponentData(treeEntity, iteration);
		return;
	}
	TreeIndex treeIndex = EntityManager::GetComponentData<TreeIndex>(treeEntity);
	unsigned newBudAmount = 0;
	//Retreve all buds;
	auto budEntityList = std::vector<Entity>();
	_BudQuery.ToEntityArray(treeIndex, &budEntityList);
	auto ltwList = std::vector<LocalToWorld>();
	_BudQuery.ToComponentDataArray(treeIndex, &ltwList);
	EntityManager::ForEach<AttractionPointCurrentStatus>(_AttractionPointQuery, [](int i, Entity entity, AttractionPointCurrentStatus* status)
		{
			status->remove = false;
			status->budEntityIndex = 0;
			status->distance = 999999;
			status->growDirDelta = glm::vec3(0.0f);
		});
	//Assign points to buds;
	for (int i = 0; i < budEntityList.size(); i++) {
		auto budEntity = budEntityList.at(i);
		if (!budEntity.Enabled()) continue;
		BudInfo budType = EntityManager::GetComponentData<BudInfo>(budEntity);
		if (budType.Value == BudTypes::LATERAL_BUD && !budType.Searching) {
			continue;
		}
		unsigned budEntityIndex = budEntity.Index;
		glm::vec3 budPos = ltwList[i].Value[3];
		EntityManager::ForEach<Translation, AttractionPointCurrentStatus>(_AttractionPointQuery, [budEntityIndex, budPos, attractionDistance, removeDistance](int i, Entity entity, Translation* translation, AttractionPointCurrentStatus* status)
			{
				float distance = glm::distance(translation->Value, budPos);
				if (distance < attractionDistance && distance < status->distance) {
					status->remove = distance < removeDistance;
					status->budEntityIndex = budEntityIndex;
					status->distance = distance;
					status->growDirDelta = translation->Value - budPos;
				}
			});
	}
#pragma region Remove points
	std::vector<Entity> points;
	std::mutex ml;
	EntityManager::ForEach<AttractionPointCurrentStatus>(_AttractionPointQuery, [&points, &ml](int i, Entity entity, AttractionPointCurrentStatus* status) {
		if (status->remove) {
			std::lock_guard<std::mutex> lock(ml);
			points.push_back(entity);
		}
		});
	for (auto i : points) {
		EntityManager::DeleteEntity(i);
	}
#pragma endregion
	//Create new buds
	for (int i = 0; i < budEntityList.size(); i++) {
		auto budEntity = budEntityList.at(i);
		if (!budEntity.Enabled()) continue;
		BudInfo budType = EntityManager::GetComponentData<BudInfo>(budEntity);
		if (budType.Value == BudTypes::LATERAL_BUD && !budType.Searching) {
			continue;
		}
		unsigned budEntityIndex = budEntity.Index;
		std::mutex ml;
		unsigned amount = 0;
		glm::vec3 growDir = glm::vec3(0.0f);
		EntityManager::ForEach<AttractionPointCurrentStatus>(_AttractionPointQuery, [budEntityIndex, &ml, &amount, &growDir](int i, Entity entity, AttractionPointCurrentStatus* status)
			{
				if (status->budEntityIndex == budEntityIndex) {
					std::lock_guard<std::mutex> lock(ml);
					amount++;
					growDir += status->growDirDelta;
				}
			});
		if (amount == 0) {
			if (budType.Value == BudTypes::APICAL_BUD && budType.Searching) {
				glm::vec3 budPos = ltwList[i].Value[3];
				float minDistance = 999999;
				EntityManager::ForEach<Translation>(_AttractionPointQuery, [&amount, &ml, &growDir, budPos, &minDistance](int i, Entity entity, Translation* translation)
					{
						float distance = glm::distance(translation->Value, budPos);
						if (distance < minDistance) {
							std::lock_guard<std::mutex> lock(ml);
							minDistance = distance;
							growDir += translation->Value - budPos;
							amount++;
						}
					});

			}
			else if (budType.Value == BudTypes::LATERAL_BUD) {
				budType.Searching = false;
				EntityManager::SetComponentData(budEntityList.at(i), budType);
			}
		}
		else {
			if (budType.Value == BudTypes::APICAL_BUD) {
				//Stop overall search for apical bud if it already found the target.
				budType.Searching = false;
			}
			else {
				//Continue searching if we still have points around.
				budType.Searching = true;
			}
		}
		if (amount != 0) {
#pragma region Create New bud
			Entity currentBud = budEntityList.at(i);
			growDir = glm::normalize(growDir);
			Translation t;
			Rotation r;
			r.Value = glm::quat(0, 0, 0, 0);
			Scale s;
			LocalPosition lp;
			lp.Value = growDir * growDistance;
			t.Value = lp.Value + EntityManager::GetComponentData<Translation>(currentBud).Value;
			s.Value = glm::vec3(1.0f);
			//TODO: Check newbud is valid.
			auto childList = EntityManager::GetChildren(currentBud);
			bool tooClose = false;
			for (auto i : childList) {
				if (glm::distance(t.Value, EntityManager::GetComponentData<Translation>(i).Value) < 0.05f) {
					tooClose = true;
				}
			}
			if (!tooClose) {
				newBudAmount++;
				auto newBud = TreeManager::CreateBud(EntityManager::GetComponentData<TreeIndex>(currentBud), currentBud);
				EntityManager::SetComponentData(newBud, lp);
				EntityManager::SetComponentData(newBud, t);
				EntityManager::SetComponentData(newBud, r);
				EntityManager::SetComponentData(newBud, s);
				if (budType.Value == BudTypes::APICAL_BUD) {
					EntityManager::SetComponentData(newBud, budType);
					budType.Value = BudTypes::LATERAL_BUD;
					budType.Searching = true;
					EntityManager::SetComponentData(currentBud, budType);
				}
				else {
					EntityManager::SetComponentData(currentBud, budType);
					budType.Searching = true;
					EntityManager::SetComponentData(newBud, budType);
				}
			}
#pragma endregion
		}
	}

	if (newBudAmount == 0) {
		//No more attraction points, return.
		Debug::Log("SpaceColonizationTreeSystem: No new buds generated in this iteration, finish growing.");
		TreeGrowIteration iteration = TreeGrowIteration();
		iteration.Value = 0;
		EntityManager::SetComponentData(treeEntity, iteration);
	}

	treeIteration.Value--;
	EntityManager::SetComponentData(treeEntity, treeIteration);
}



void SpaceColonizationTreeSystem::OnCreate()
{
	if (!TreeManager::IsReady()) {
		Debug::Error("SpaceColonizationTreeSystem: TreeManager not initialized!");
	}

	_BudSystem = TreeManager::GetBudSystem();
	_LeafQuery = TreeManager::GetLeafQuery();
	_BudQuery = TreeManager::GetBudQuery();
	_TreeQuery = TreeManager::GetTreeQuery();

	_AttractionPointArchetype = EntityManager::CreateEntityArchetype(
		"Attraction Point",
		Translation(), Scale(), LocalToWorld(),
		AttractionPointIndex(), AttractionPointCurrentStatus());
	_AttractionPointQuery = EntityManager::CreateEntityQuery();
	EntityManager::SetEntityQueryAllFilters(_AttractionPointQuery, AttractionPointIndex());
	_AttractionPointMaxIndex = 0;

	_AttractionPointMaterial = new Material();
	_AttractionPointMaterial->Programs()->push_back(Default::GLPrograms::StandardInstancedProgram);
	auto pointTex = new Texture2D(TextureType::DIFFUSE);
	pointTex->LoadTexture(FileIO::GetPath("Textures/green.png"), "");
	_AttractionPointMaterial->Textures2Ds()->push_back(pointTex);

	_Envelope._SpaceCenter = glm::vec3(0, 50, 0);
	_Envelope._SpaceSize = glm::vec3(180, 60, 180);
	_Envelope._Type = EnvelopeType::Box;

	_AllTreesToGrowIteration = 0;
	_PushAttractionPoints = 0;
	_SelectedEnvelopeType = 1;
	_NewTreeMenuOpen = false;
	_NewTreeColor = TreeColor();
	_NewTreeColor.Color = glm::vec4(1);
	_NewTreeColor.BudColor = glm::vec4(1);
	_NewTreeColor.ConnectionColor = glm::vec4(0.6f, 0.3f, 0, 1);
	_NewTreeColor.LeafColor = glm::vec4(0, 1, 0, 1);
	_NewTreePosition = glm::vec3(0);
	Enable();
}

void SpaceColonizationTreeSystem::OnDestroy()
{
	delete _AttractionPointMaterial;
}

void SpaceColonizationTreeSystem::Update()
{
	auto pointLTWList = std::vector<LocalToWorld>();
	_AttractionPointQuery.ToComponentDataArray(&pointLTWList);
	if (pointLTWList.size() != 0)RenderManager::DrawGizmoPointInstanced(glm::vec4(1, 0, 0, 1), (glm::mat4*)pointLTWList.data(), pointLTWList.size(), Application::GetMainCameraComponent()->Value);
	DrawGUI();
}

void SpaceColonizationTreeSystem::FixedUpdate()
{
	if (_IterationFinishMark) {
		_BudSystem->RefreshConnections();
		TreeManager::GenerateLeavesForAllTrees(LeafInfo());
		_IterationFinishMark = false;
	}
	if (_AllTreesToGrowIteration > 0) {
		_AllTreesToGrowIteration--;
		GrowAllTrees();
		if (_AllTreesToGrowIteration == 0) _IterationFinishMark = true;
	}

	auto treeEntities = TreeManager::GetTreeSystem()->GetTreeEntities();
	for (auto tree : *treeEntities) {
		GrowTree(tree);
	}
}

void SpaceColonizationTreeSystem::ResetEnvelope(float radius, float minHeight, float maxHeight)
{
	_Envelope.Reset(glm::vec3(0.0f, minHeight + (maxHeight - minHeight) / 2.0f, 0.0f), glm::vec3(radius, maxHeight - minHeight, radius));
}

void SpaceColonizationTreeSystem::ResetEnvelope(glm::vec3 spaceOffset, glm::vec3 spaceSize)
{
	_Envelope.Reset(spaceOffset, spaceSize);
}

void SpaceColonizationTreeSystem::ResetEnvelopeType(EnvelopeType type)
{
	_Envelope.ResetType(type);
}

void SpaceColonizationTreeSystem::PushAttractionPoints(size_t value)
{
	Translation translation;
	for (int i = 0; i < value; i++) {
		translation.Value = _Envelope.GetPoint();
		AddAttractionPoint(translation);
	}
}

void SpaceColonizationTreeSystem::PushGrowAllTreesIterations(size_t iteration)
{
	EntityManager::ForEach<BudInfo>(_BudQuery, [](int i, Entity entity, BudInfo* type) {
		if (type->Value == BudTypes::LATERAL_BUD) type->Searching = true;
		});
	_AllTreesToGrowIteration += iteration;
	_IterationFinishMark = false;
}

void SpaceColonizationTreeSystem::PushGrowIterationToTree(Entity treeEntity, size_t iteration)
{
}

Entity SpaceColonizationTreeSystem::CreateTree(TreeColor color, glm::vec3 position, bool enabled)
{
	BudInfo type;
	type.Value = BudTypes::APICAL_BUD;
	type.Searching = true;
	auto treeEntity = TreeManager::CreateTree();
	Translation t;
	t.Value = position;
	Scale s;
	s.Value = glm::vec3(1.0f);
	EntityManager::SetComponentData(treeEntity, t);
	EntityManager::SetComponentData(treeEntity, s);
	EntityManager::SetComponentData(treeEntity, color);
	TreeGrowIteration iteration;
	iteration.Value = 0;
	iteration.Enable = enabled;
	EntityManager::SetComponentData(treeEntity, iteration);
	auto rootBud = TreeManager::CreateBud(EntityManager::GetComponentData<TreeIndex>(treeEntity), treeEntity);
	EntityManager::SetComponentData(rootBud, t);
	EntityManager::SetComponentData(rootBud, s);
	EntityManager::SetComponentData(rootBud, type);
	return treeEntity;
}

void SpaceColonizationTreeSystem::ClearAttractionPoints()
{
	std::vector<Entity> points;
	std::mutex ml;
	EntityManager::ForEach<AttractionPointCurrentStatus>(_AttractionPointQuery, [&points, &ml](int i, Entity entity, AttractionPointCurrentStatus* status) {
		std::lock_guard<std::mutex> lock(ml);
		points.push_back(entity);
		});
	for (auto i : points) {
		EntityManager::DeleteEntity(i);
	}
}

unsigned SpaceColonizationTreeSystem::AllTreesToGrowIteration()
{
	return _AllTreesToGrowIteration;
}
