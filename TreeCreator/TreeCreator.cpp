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
	LightingManager::SetAmbientLight(1.0f);
	Application::Init();

	Application::SetTimeStep(0.016f);
#pragma region Preparations
	World* world = Application::GetWorld();
	WorldTime* time = world->Time();
	EntityEditorSystem* editorSystem = world->CreateSystem<EntityEditorSystem>(SystemGroup::PresentationSystemGroup);

	EntityArchetype archetype = EntityManager::CreateEntityArchetype("General", Translation(), Rotation(), Scale(), LocalToWorld());
	CameraControlSystem* ccs = world->CreateSystem<CameraControlSystem>(SystemGroup::SimulationSystemGroup);
	ccs->Enable();
	ccs->SetPosition(glm::vec3(0, 30, 60));
	InitGround();
#pragma endregion
	TreeManager::Init();
	//InitSpaceColonizationTreeSystem();
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
	Entity tree1 = psSys->CreateExampleTree(treeColor, glm::vec3(0, 0, 0), 3);

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
	scale.Value = glm::vec3(100.0f);
	EntityManager::SetComponentData<Translation>(entity, translation);
	EntityManager::SetComponentData<Scale>(entity, scale);


	auto mat = new Material();
	mat->Programs()->push_back(Default::GLPrograms::StandardProgram);
	auto texture = new Texture2D(TextureType::DIFFUSE);
	texture->LoadTexture(FileIO::GetPath("Textures/treesurface.jpg"), "");
	mat->Textures2Ds()->push_back(texture);
	mat->SetMaterialProperty("material.shininess", 32.0f);
	MeshMaterialComponent* meshMaterial = new MeshMaterialComponent();
	meshMaterial->_Mesh = Default::Primitives::Quad;
	meshMaterial->_Material = mat;
	EntityManager::SetSharedComponent<MeshMaterialComponent>(entity, meshMaterial);

}


