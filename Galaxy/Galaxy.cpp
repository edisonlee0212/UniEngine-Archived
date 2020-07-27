// Galaxy.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "UniEngine.h"
#include "CameraControlSystem.h"



using namespace UniEngine;

struct StarTag : ComponentBase
{
};

int main()
{
	Engine* engine = new Engine();
	LightingManager::SetDirectionalLightResolution(2048);
	LightingManager::SetStableFit(true);
	LightingManager::SetSeamFixRatio(0.05f);
	LightingManager::SetMaxShadowDistance(500);
	LightingManager::SetVSMMaxVariance(0.001f);
	LightingManager::SetEVSMExponent(80.0f);
	LightingManager::SetSplitRatio(0.15f, 0.3f, 0.5f, 1.0f);
	LightingManager::SetAmbientLight(0.5f);
	auto window = WindowManager::CreateGLFWwindow(1600, 900, "Main", NULL);
	engine->Start(window, 1600, 900);
	/*
	#pragma region Lights
		MeshMaterialComponent* cylinder = new MeshMaterialComponent();
		cylinder->_Mesh = Default::Primitives::Cylinder;
		cylinder->_Material = Default::Materials::StandardMaterial;
		Scale scale;
		scale.value = glm::vec3(0.5f);



		MeshMaterialComponent* dlmmc = new MeshMaterialComponent();
		cylinder->_Mesh = Default::Primitives::Cylinder;
		cylinder->_Material = Default::Materials::StandardMaterial;
		scale.value = glm::vec3(0.5f);

		DirectionalLightComponent* dlc = new DirectionalLightComponent();

		Entity dle = EntityManager::CreateEntity(archetype);
		EntityManager::SetSharedComponent<DirectionalLightComponent>(dle, dlc);
		EntityManager::SetComponentData<Scale>(dle, scale);

		DirectionalLightComponent* dlc2 = new DirectionalLightComponent();
		Entity dle2 = EntityManager::CreateEntity(archetype);
		EntityManager::SetSharedComponent<DirectionalLightComponent>(dle2, dlc2);
		EntityManager::SetComponentData<Scale>(dle2, scale);


		MeshMaterialComponent* plmmc = new MeshMaterialComponent();
		plmmc->_Mesh = Default::Primitives::Sphere;
		plmmc->_Material = Default::Materials::StandardMaterial;
		scale.value = glm::vec3(0.5f);

		PointLightComponent* plc = new PointLightComponent();
		plc->constant = 1.0f;
		plc->linear = 0.09f;
		plc->quadratic = 0.032f;
		plc->farPlane = 200.0f;
		plc->diffuse = glm::vec3(3.0f);
		plc->specular = glm::vec3(5.0f);
		Entity ple = EntityManager::CreateEntity(archetype);
		EntityManager::SetSharedComponent<PointLightComponent>(ple, plc);
		EntityManager::SetComponentData<Scale>(ple, scale);
		EntityManager::SetSharedComponent<MeshMaterialComponent>(ple, plmmc);

	#pragma endregion
	*/
#pragma region Preparations
	World* world = engine->GetWorld();
	WorldTime* time = world->Time();
	bool enableSCTreeSystem = false;

	Camera* mainCamera = new Camera(WindowManager::CurrentWindow(), 0.1f, 500.0f);

	EntityArchetype archetype = EntityManager::CreateEntityArchetype<Position, Rotation, Scale, LocalToWorld>(Position(), Rotation(), Scale(), LocalToWorld());

	auto cameraEntity = EntityManager::CreateEntity(archetype);
	CameraComponent* cameraComponent = new CameraComponent();
	cameraComponent->Value = mainCamera;
	EntityManager::SetSharedComponent<CameraComponent>(cameraEntity, cameraComponent);

	engine->SetMainCamera(cameraEntity);

	CameraControlSystem* ccs = world->CreateSystem<CameraControlSystem>(SystemGroup::SimulationSystemGroup);
	ccs->SetSensitivity(0.1f);
	ccs->SetVelocity(20.0f);
	ccs->Enable();
	ccs->SetTargetCamera(cameraEntity);
	ccs->EnableWindowControl(true);
	ccs->SetPosition(glm::vec3(-40, 25, 3));

	auto starMat = new Material();
	starMat->Programs()->push_back(Default::GLPrograms::StandardInstancedProgram);
	auto starTex = new Texture2D(TextureType::DIFFUSE);
	starTex->LoadTexture(FileIO::GetPath("Textures/green.png"), "");
	starMat->Textures2Ds()->push_back(starTex);

	//Generate an entity archetype for cube
	EntityArchetype starArchetype = 
		EntityManager::CreateEntityArchetype<StarTag, Position, Rotation, Scale, LocalToWorld>(StarTag(), Position(), Rotation(), Scale(), LocalToWorld());

	//Create 200 * 200 = 40000 Cubes
	int width = 200;
	for (int i = 0; i < width * width; i++) {
		auto entity = EntityManager::CreateEntity(starArchetype);
	}

	//Create entityquery for operations
	EntityQuery eq = EntityManager::CreateEntityQuery();
	EntityManager::SetEntityQueryAllFilters<StarTag>(eq, StarTag());

	//Multiple Components Query is allowed
	//EntityManager::SetEntityQueryAllFilters<StarTag, LocalToWorld>(eq, StarTag(), LocalToWorld());
#pragma endregion

#pragma region EngineLoop
	bool loopable = true;
	//Create an array to hold matrices data for cubes.
	std::vector<LocalToWorld> matrices = std::vector<LocalToWorld>();
	float timer = 0.0f;
	float speed = 1.0f;
	while (loopable) {
		loopable = engine->LoopStart();
		timer += engine->GetWorld()->Time()->DeltaTime() * speed;
		if (timer > 2.0f) timer = 0.0f;

		//Cube operation, we set their positions and scales according to time and index
		//I used lamda function here.
		EntityManager::ForEach<Position, Scale>(eq, [width, timer](int i, Position* p, Scale* s) {
			p->value = glm::vec3((i % width) * 1.0f - width * 0.5, glm::sin(3.1415926f * timer + 0.5f * (i % width) + 0.5f * (i / width)), (i / width) * 1.0f - width * 0.5);
			s->value = glm::vec3(0.2f);
			});

		//Get the matrices data.
		matrices.clear();
		EntityManager::GetComponentDataArray(eq, &matrices);
		RenderManager::DrawMeshInstanced(Default::Primitives::Cube, starMat, glm::mat4(1.0f), (glm::mat4*)matrices.data(), matrices.size(), mainCamera);
		
		//Render speed control window
		ImGui::Begin("Speed Control");
		ImGui::SliderFloat("Factor", &speed, 0.0f, 8.0f);
		ImGui::End();
		//Finish engine loop.
		loopable = engine->Loop();
		loopable = engine->LoopEnd();


	}
	engine->End();
#pragma endregion
	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
