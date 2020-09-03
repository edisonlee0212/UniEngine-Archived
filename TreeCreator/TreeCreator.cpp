// SponzaTest.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "UniEngine.h"
#include "CameraControlSystem.h"
#include "SpaceColonizationTreeSystem.h"
#include "PlantSimulationSystem.h"
#include "TreeManager.h"
#include "EntityEditorSystem.h"

#include "EntityEditorSystem.h"

using namespace UniEngine;
using namespace TreeUtilities;
void InitGround();
void InitSpaceColonizationTreeSystem();
void InitPlantSimulationSystem();



int main()
{

	LightingManager::SetAmbientLight(0.2f);
	Application::Init();

	Application::SetTimeStep(0.016f);
#pragma region Preparations
	World* world = Application::GetWorld();
	WorldTime* time = world->Time();
	EntityEditorSystem* editorSystem = world->CreateSystem<EntityEditorSystem>(SystemGroup::PresentationSystemGroup);

	EntityArchetype archetype = EntityManager::CreateEntityArchetype("General", Translation(), Rotation(), Scale(), LocalToWorld());
	CameraControlSystem* ccs = world->CreateSystem<CameraControlSystem>(SystemGroup::SimulationSystemGroup);
	ccs->Enable();
	ccs->SetPosition(glm::vec3(0, 3, 6));
	ccs->SetVelocity(10.0f);
	InitGround();
#pragma endregion
	TreeManager::Init();
	
	TreeManager::GetLightEstimator()->ResetCenterDistance(20);
	TreeManager::GetLightEstimator()->ResetSnapShotWidth(10);
	//From top
	TreeManager::GetLightEstimator()->PushSnapShot(glm::vec3(0, -1, 0), 1.0f);
	
	//45
	float tilt = 0.2f;
	TreeManager::GetLightEstimator()->PushSnapShot(glm::vec3(0, -1, tilt), 0.9f);
	TreeManager::GetLightEstimator()->PushSnapShot(glm::vec3(0, -1, -tilt), 0.9f);
	TreeManager::GetLightEstimator()->PushSnapShot(glm::vec3(tilt, -1, 0), 0.9f);
	TreeManager::GetLightEstimator()->PushSnapShot(glm::vec3(-tilt, -1, 0), 0.9f);
	
	tilt = 1.0f;
	TreeManager::GetLightEstimator()->PushSnapShot(glm::vec3(0, -1, tilt), 0.5f);
	TreeManager::GetLightEstimator()->PushSnapShot(glm::vec3(0, -1, -tilt), 0.5f);
	TreeManager::GetLightEstimator()->PushSnapShot(glm::vec3(tilt, -1, 0), 0.5f);
	TreeManager::GetLightEstimator()->PushSnapShot(glm::vec3(-tilt, -1, 0), 0.5f);
	
	tilt = 10.0f;
	TreeManager::GetLightEstimator()->PushSnapShot(glm::vec3(0, -1, tilt), 0.1f);
	TreeManager::GetLightEstimator()->PushSnapShot(glm::vec3(0, -1, -tilt), 0.1f);
	TreeManager::GetLightEstimator()->PushSnapShot(glm::vec3(tilt, -1, 0), 0.1f);
	TreeManager::GetLightEstimator()->PushSnapShot(glm::vec3(-tilt, -1, 0), 0.1f);
	InitPlantSimulationSystem();
	Application::Run();
	Application::End();
	return 0; 
}
void InitPlantSimulationSystem() {
	auto psSys = Application::GetWorld()->CreateSystem<PlantSimulationSystem>(SystemGroup::SimulationSystemGroup);
	TreeColor treeColor;
	treeColor.Color = glm::vec4(1, 1, 1, 1);
	treeColor.BudColor = glm::vec4(1, 0, 0, 1);
	treeColor.ConnectionColor = glm::vec4(0.6f, 0.3f, 0, 1);
	treeColor.LeafColor = glm::vec4(0, 1, 0, 1);
	TreeParameters tps = TreeParameters();
#pragma region Parameters
	tps.VarianceApicalAngle = 0.42990970562500003;
	tps.LateralBudNumber = 2;
	tps.MeanBranchingAngle = 27.198200000000000;
	tps.VarianceBranchingAngle = 0.037388089600000000;
	tps.MeanRollAngle = 113.11000000000000;
	tps.VarianceRollAngle = 13.090141080900001;

	tps.ApicalBudExtintionRate = 0.99903945880000000;
	tps.LateralBudEntintionRate = 0.0062681600000000001;
	tps.ApicalBudLightingFactor = 0.099225700000000000;
	tps.LateralBudLightingFactor = 1.0005922199999999;
	tps.ApicalDominanceBase = 5.0524730000000000;
	tps.ApicalDominanceDistanceFactor = 0.37777800000000000;
	tps.ApicalDominanceAgeFactor = 0.44704700000000003;
	tps.GrowthRate = 1.3069500000000001;
	tps.InternodeLengthBase = 0.92382719999999996;
	tps.InternodeLengthAgeFactor = 0.95584000000000002;

	tps.ApicalControl = 0.93576000000000004;
	tps.ApicalControlAgeDescFactor = 0.91815700000000000;
	tps.ApicalControlLevelFactor = 1.0000000000000000;
	tps.Phototropism = 0.22445109999999999;
	tps.GravitropismBase = 0.039603199999999998;
	tps.PruningFactor = 0.43430900000000000;
	tps.LowBranchPruningFactor = 0.63922599999999996;
	tps.GravityBendingStrength = 0.2f;
	tps.Age = 14;
	tps.GravityFactor = 0.050594199999999999;
	tps.MaxBudAge = 8;
	tps.EndNodeThickness = 0.5f;
	tps.ThicknessControlFactor = 0.75f;
	tps.GravityBackPropageteFixedCoefficient = 0.5f;
#pragma endregion
	Entity tree1 = psSys->CreateTree(tps, treeColor, glm::vec3(-3, 0, 0), true);
	Entity tree2 = psSys->CreateExampleTree(treeColor, glm::vec3(3, 0, 0), 1);
}
void InitSpaceColonizationTreeSystem()
{
	auto sctSys = Application::GetWorld()->CreateSystem<SpaceColonizationTreeSystem>(SystemGroup::SimulationSystemGroup);
	sctSys->ResetEnvelopeType(EnvelopeType::Box);
	sctSys->ResetEnvelope(160, 20, 60);
	sctSys->PushAttractionPoints(10000);

	TreeColor treeColor;
	treeColor.Color = glm::vec4(1, 1, 1, 1);
	treeColor.BudColor = glm::vec4(1, 0, 0, 1);
	treeColor.ConnectionColor = glm::vec4(0.6f, 0.3f, 0, 1);
	treeColor.LeafColor = glm::vec4(0, 1, 0, 1);
	Entity tree1 = sctSys->CreateTree(treeColor, glm::vec3(30, 0, -30));

	treeColor.BudColor = glm::vec4(0, 1, 0, 1);
	treeColor.ConnectionColor = glm::vec4(0.6f, 0.3f, 0, 1);
	Entity tree2 = sctSys->CreateTree(treeColor, glm::vec3(30, 0, 30));

	treeColor.BudColor = glm::vec4(0, 0, 1, 1);
	treeColor.ConnectionColor = glm::vec4(0.6f, 0.3f, 0, 1);
	Entity tree3 = sctSys->CreateTree(treeColor, glm::vec3(-30, 0, -30));

	treeColor.BudColor = glm::vec4(0, 1, 1, 1);
	treeColor.ConnectionColor = glm::vec4(0.6f, 0.3f, 0, 1);
	Entity tree4 = sctSys->CreateTree(treeColor, glm::vec3(-30, 0, 30));

	sctSys->PushGrowAllTreesIterations(100);
}
void InitGround() {
	EntityArchetype archetype = EntityManager::CreateEntityArchetype("General", Translation(), Rotation(), Scale(), LocalToWorld());
	auto entity = EntityManager::CreateEntity(archetype);
	Translation translation = Translation();
	translation.Value = glm::vec3(0.0f, 0.0f, 0.0f);
	Scale scale = Scale();
	scale.Value = glm::vec3(10.0f);
	EntityManager::SetComponentData<Translation>(entity, translation);
	EntityManager::SetComponentData<Scale>(entity, scale);


	auto mat = new Material();
	mat->Programs()->push_back(Default::GLPrograms::StandardProgram);
	auto texture = new Texture2D(TextureType::DIFFUSE);
	texture->LoadTexture(FileIO::GetPath("Textures/white.png"), "");
	mat->Textures2Ds()->push_back(texture);
	mat->SetMaterialProperty("material.shininess", 32.0f);
	MeshMaterialComponent* meshMaterial = new MeshMaterialComponent();
	meshMaterial->_Mesh = Default::Primitives::Quad;
	meshMaterial->_Material = mat;
	EntityManager::SetSharedComponent<MeshMaterialComponent>(entity, meshMaterial);

}


