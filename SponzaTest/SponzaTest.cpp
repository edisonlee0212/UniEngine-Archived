// SponzaTest.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "UniEngine.h"
#include "CameraControlSystem.h"
#include "Bloom.h"
#include "SSAO.h"
#include "PostProcessing.h"
using namespace UniEngine;
void LightSettingMenu();
void InitGround();


float lightAngle6 = 0;

enum TestScene {
	BACKPACK,
	SPONZA_TEST,
	PCSS,
};
int main()
{
	FileIO::SetResourcePath("../Resources/");
#pragma region Lighting and Shadow settings
	RenderManager::SetShadowMapResolution(8192);
	RenderManager::m_stableFit = false;
	RenderManager::SetSeamFixRatio(0.05f);
	RenderManager::SetMaxShadowDistance(100);
	RenderManager::SetSplitRatio(0.15f, 0.3f, 0.5f, 1.0f);
#pragma endregion
	Application::Init();
#pragma region Preparations
	auto& world = Application::GetCurrentWorld();
	WorldTime* time = world->Time();
	bool enableSCTreeSystem = false;
	EntityArchetype archetype = EntityManager::CreateEntityArchetype("General", GlobalTransform(), Transform());
	
	CameraControlSystem* ccs = world->CreateSystem<CameraControlSystem>(SystemGroup::SimulationSystemGroup);
	ccs->SetSensitivity(0.1f);
	ccs->SetVelocity(20.0f);
	ccs->Enable();
	Transform transform;
	transform.SetPosition(glm::vec3(0, 5, 10));
	transform.SetEulerRotation(glm::radians(glm::vec3(-14.0f, 0.0f, 0.0f)));
	RenderManager::GetMainCamera()->GetOwner().SetComponentData(transform);
	transform.SetEulerRotation(glm::radians(glm::vec3(0.0f, 0.0f, 0.0f)));
	auto postProcessing = std::make_unique<PostProcessing>();
	postProcessing->PushLayer(std::make_unique<Bloom>());
	postProcessing->PushLayer(std::make_unique<SSAO>());
	EntityManager::SetPrivateComponent(RenderManager::GetMainCamera()->GetOwner(), std::move(postProcessing));
	Entity newCam = EntityManager::CreateEntity(archetype, "Camera");
	newCam.SetPrivateComponent(std::make_unique<CameraComponent>());
	newCam.SetComponentData(transform);
	newCam.GetPrivateComponent<CameraComponent>()->ResizeResolution(300, 300);
#pragma endregion
	auto sharedMat = std::make_shared<Material>();
	sharedMat->SetProgram(Default::GLPrograms::StandardProgram);
	sharedMat->SetTexture(Default::Textures::StandardTexture);
	
	auto cylinder = std::make_unique<MeshRenderer>();
	cylinder->m_mesh = Default::Primitives::Cylinder;
	cylinder->m_material = sharedMat;
	TestScene testScene = BACKPACK;
#pragma region PCSS test
	if (testScene == BACKPACK) {
		auto backpackModel = ResourceManager::LoadModel(
			true, FileIO::GetResourcePath("Models/backpack/backpack.obj"), Default::GLPrograms::StandardProgram, false,
			aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace | aiProcess_OptimizeMeshes
		);
		backpackModel->m_name = "Backpack";
		Entity backpackEntity = ResourceManager::ToEntity(archetype, backpackModel);
		backpackEntity.SetName("Backpack");
		transform.SetPosition(glm::vec3(0, 2, 0));
		transform.SetScale(glm::vec3(1.0f));
		EntityManager::SetComponentData(backpackEntity, transform);
	}
	else if (testScene == SPONZA_TEST) {
		//1. Load models using Assimp including textures and meshes and transforms.
		auto sponzaModel = ResourceManager::LoadModel(true, FileIO::GetResourcePath("Models/Sponza/sponza.obj"), Default::GLPrograms::StandardProgram, false,
			aiProcess_Triangulate | aiProcess_CalcTangentSpace | aiProcess_OptimizeMeshes);
		sponzaModel->m_name = "Sponza Scene";
		Entity sponzaEntity = ResourceManager::ToEntity(archetype, sponzaModel);
		sponzaEntity.SetName("Sponza");
		//2. Set overall transform of the entites. We set the root entity's transform and it will
		//	 automatically apply to the entire model by the parent hierarchy transform calculation. See TransformManager & ParentSystem
		transform.SetPosition(glm::vec3(1, 1, 1));
		transform.SetScale(glm::vec3(0.05f));
		EntityManager::SetComponentData(sponzaEntity, transform);
	}
	else if (testScene == PCSS) {
		auto cmmc = std::make_unique<MeshRenderer>();
		cmmc->m_mesh = Default::Primitives::Cube;
		cmmc->m_material = sharedMat;

		Entity model1 = EntityManager::CreateEntity(archetype);
		transform.SetPosition(glm::vec3(-6.0f, 7.0f, 0.0f));


		transform.SetScale(glm::vec3(4.0f, 8.0f, 4.0f));
		EntityManager::SetComponentData(model1, transform);
		EntityManager::SetPrivateComponent<MeshRenderer>(model1, std::move(cylinder));

		auto mmmc = std::make_unique<MeshRenderer>();
		mmmc->m_mesh = Default::Primitives::Sphere;
		mmmc->m_material = sharedMat;

		Entity model2 = EntityManager::CreateEntity(archetype);
		transform.SetPosition(glm::vec3(6.0f, 7.0f, 0.0f));

		transform.SetScale(glm::vec3(5.0f, 5.0f, 5.0f));
		EntityManager::SetComponentData(model2, transform);
		EntityManager::SetPrivateComponent<MeshRenderer>(model2, std::move(mmmc));
	}
#pragma endregion
#pragma region Lights
	transform.SetEulerRotation(glm::radians(glm::vec3(70, 0, 0)));
	
	auto dlc = std::make_unique<DirectionalLight>();
	dlc->m_diffuseBrightness = 1.0f;
	dlc->m_lightSize = 1.0f;
	Entity dle = EntityManager::CreateEntity("Directional Light");
	EntityManager::SetPrivateComponent(dle, std::move(dlc));
	EntityManager::SetComponentData(dle, transform);


	auto dlc2 = std::make_unique<DirectionalLight>();
	dlc2->m_lightSize = 1.0f;
	Entity dle2 = EntityManager::CreateEntity("Directional Light 2");
	EntityManager::SetPrivateComponent(dle2, std::move(dlc2));
	transform.SetEulerRotation(glm::radians(glm::vec3(30, 60, 0)));
	EntityManager::SetComponentData(dle2, transform);


	auto plmmc = std::make_unique<MeshRenderer>();
	plmmc->m_mesh = Default::Primitives::Sphere;
	plmmc->m_material = sharedMat;
	transform.SetScale(glm::vec3(0.5f));

	auto plc = std::make_unique<PointLight>();
	plc->m_constant = 1.0f;
	plc->m_linear = 0.09f;
	plc->m_quadratic = 0.032f;
	plc->m_farPlane = 200.0f;
	plc->m_diffuse = glm::vec3(3.0f);
	Entity ple = EntityManager::CreateEntity("Point Light");
	transform.SetPosition(glm::vec3(0, 20, 0));
	EntityManager::SetPrivateComponent(ple, std::move(plc));
	EntityManager::SetComponentData(ple, transform);
	EntityManager::SetPrivateComponent<MeshRenderer>(ple, std::move(plmmc));

#pragma endregion
	InitGround();
#pragma region EngineLoop
	bool loopable = true;
	//Start engine. Here since we need to inject procedures to the main engine loop we need to manually loop by our self.
	//Another way to run engine is to simply execute:
	Application::Run();
	
	Application::End();
#pragma endregion
	return 0;
}

void LightSettingMenu() {
	ImGui::Begin("Light Angle Controller");
	ImGui::SliderFloat("Point Light", &lightAngle6, 0.0f, 180.0f);
	ImGui::End();
}

void InitGround() {
	EntityArchetype archetype = EntityManager::CreateEntityArchetype("General", Transform(), GlobalTransform());
	auto entity = EntityManager::CreateEntity(archetype);
	entity.SetName("Ground");
	Transform transform;
	transform.SetPosition(glm::vec3(0.0f, 0.0f, 0.0f));
	transform.SetScale(glm::vec3(10.0f));
	EntityManager::SetComponentData(entity, transform);
	/*
	auto entity1 = EntityManager::CreateEntity(archetype);
	translation.value = glm::vec3(-100.0f, 0.0f, 0.0f);
	scale.value = glm::vec3(100.0f, 1.0f, 20.0f);
	Rotation rotation;
	rotation.value = glm::quatLookAt(glm::vec3(0, 1, 0), glm::vec3(1, 0, 0));
	EntityManager::SetComponentData<Translation>(entity1, translation);
	EntityManager::SetComponentData<Scale>(entity1, scale);
	EntityManager::SetComponentData<Rotation>(entity1, rotation);

	auto entity2 = EntityManager::CreateEntity(archetype);
	translation.value = glm::vec3(100.0f, 0.0f, 0.0f);
	scale.value = glm::vec3(100.0f, 1.0f, 20.0f);
	rotation.value = glm::quatLookAt(glm::vec3(0, 1, 0), glm::vec3(-1, 0, 0));

	EntityManager::SetComponentData<Translation>(entity2, translation);
	EntityManager::SetComponentData<Scale>(entity2, scale);
	EntityManager::SetComponentData<Rotation>(entity2, rotation);


	auto entity3 = EntityManager::CreateEntity(archetype);
	translation.value = glm::vec3(0.0f, 0.0f, -100.0f);
	scale.value = glm::vec3(100.0f, 1.0f, 20.0f);
	rotation.value = glm::quatLookAt(glm::vec3(0, 1, 0), glm::vec3(0, 0, 1));

	EntityManager::SetComponentData<Translation>(entity3, translation);
	EntityManager::SetComponentData<Scale>(entity3, scale);
	EntityManager::SetComponentData<Rotation>(entity3, rotation);

	auto entity4 = EntityManager::CreateEntity(archetype);
	translation.value = glm::vec3(0.0f, 0.0f, 100.0f);
	scale.value = glm::vec3(100.0f, 1.0f, 20.0f);
	rotation.value = glm::quatLookAt(glm::vec3(0, 1, 0), glm::vec3(0, 0, -1));

	EntityManager::SetComponentData<Translation>(entity4, translation);
	EntityManager::SetComponentData<Scale>(entity4, scale);
	EntityManager::SetComponentData<Rotation>(entity4, rotation);

	*/
	auto mat = std::make_shared<Material>();
	mat->SetProgram(Default::GLPrograms::StandardProgram);
	
	auto texture = ResourceManager::LoadTexture(false, FileIO::GetResourcePath("Textures/floor.png"));
	mat->SetTexture(texture);
	/*
	auto textureD = ResourceManager::LoadTexture(FileIO::GetResourcePath("Textures/bricks2.jpg"));
	mat->SetTexture(textureD, TextureType::DIFFUSE);
	auto textureN = ResourceManager::LoadTexture(FileIO::GetResourcePath("Textures/bricks2_normal.jpg"));
	mat->SetTexture(textureN, TextureType::NORMAL);
	auto textureH = ResourceManager::LoadTexture(FileIO::GetResourcePath("Textures/bricks2_disp.jpg"));
	mat->SetTexture(textureH, TextureType::DISPLACEMENT);
	*/
	
	mat->m_shininess = 32.0f;
	auto meshMaterial = std::make_unique<MeshRenderer>();
	meshMaterial->m_mesh = Default::Primitives::Quad;
	meshMaterial->m_material = mat;
	EntityManager::SetPrivateComponent<MeshRenderer>(entity, std::move(meshMaterial));
	auto rigidBody = std::make_unique<RigidBody>();
	rigidBody->SetShapeType(ShapeType::Box);
	rigidBody->SetShapeParam(glm::vec3(50, 1, 50));
	rigidBody->SetStatic(true);
	entity.SetPrivateComponent(std::move(rigidBody));
	//EntityManager::SetSharedComponent<MeshRenderer>(entity1, std::shared_ptr<MeshRenderer>(meshMaterial));
	//EntityManager::SetSharedComponent<MeshRenderer>(entity2, std::shared_ptr<MeshRenderer>(meshMaterial));
	//EntityManager::SetSharedComponent<MeshRenderer>(entity3, std::shared_ptr<MeshRenderer>(meshMaterial));
	//EntityManager::SetSharedComponent<MeshRenderer>(entity4, std::shared_ptr<MeshRenderer>(meshMaterial));
}
