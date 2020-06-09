#include "World.h"
#include "Core.h"
#include "ManagerBase.h"
#include "EntityCollection.h"
#include "TimeSystem.h"
#include "InputSystem.h"
#include "RenderSystem.h"
#include "PhysicsSystem.h"
#include "TransformSystem.h"
#include "SharedComponentSystem.h"
#include "WindowManager.h"
#include "CameraComponent.h"

using namespace UniEngine;


World::World() {
	
	_EntityCollection = new EntityCollection();
	ManagerBase::_EntityCollection = _EntityCollection;
	ManagerBase::_World = this;
	_TimeStep = 0.2f;
	InitImGui();

}

void UniEngine::World::Init()
{
	//Initialization System Group
	CreateSystem<TimeSystem>();
	CreateSystem<InputSystem>();

	//Simulation System Group
	CreateSystem<PhysicsSystem>();
	CreateSystem<TransformSystem>();

	//Presentation System Group
	CreateSystem<RenderSystem>();



	_MainCamera = new Camera(WindowManager::CurrentWindow());
	auto cameraEntity = _EntityCollection->CreateEntity();
	CameraComponent* cameraComponent = new CameraComponent();
	cameraComponent->Value = _MainCamera;
	_EntityCollection->SetSharedComponent<CameraComponent>(cameraEntity, cameraComponent) ;
}



World::~World() {
	for (auto i : _Systems) {
		i->OnDestroy();
		delete i;
	}
}
void World::Update() {

	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	if (Time::FixedDeltaTime() >= _TimeStep) {
		Time::SetFixedDeltaTime(0);
		for (auto i : _Systems) {
			if (i->Enabled()) i->FixedUpdate();
		}
	}
	
	for (auto i : _Systems) {
		if (i->Enabled()) i->Update();
	}

	DrawInfoWindow();

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

EntityCollection* UniEngine::World::GetEntityCollection()
{
	return _EntityCollection;
}

Camera* UniEngine::World::MainCamera()
{
	return _MainCamera;
}

inline void World::InitImGui() {
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();

	ImGui_ImplGlfw_InitForOpenGL(WindowManager::CurrentWindow()->GetGLFWWinwow(), true);
	ImGui_ImplOpenGL3_Init("#version 420 core");
	ImGui::StyleColorsDark();
}

inline void World::DrawInfoWindow() {
	ImGui::Begin("World Info");
	ImGui::SliderFloat("sec/step", &_TimeStep, 0.05f, 1.0f);
	ImGui::Text("%.1f FPS", ImGui::GetIO().Framerate);
	int tris = RenderManager::Triangles();
	std::string trisstr = "";
	if (tris < 999) {
		trisstr += std::to_string(tris);
	}
	else if (tris < 999999) {
		trisstr += std::to_string((int)(tris / 1000)) + "K";
	}
	else {
		trisstr += std::to_string((int)(tris / 1000000)) + "M";
	}
	trisstr += " tris";
	ImGui::Text(trisstr.c_str());

	ImGui::Text("%d drawcall", RenderManager::DrawCall());
	
	ImGui::End();

	ImGui::Begin("Logs");
	int size = Debug::mLogMessages.size();
	std::string logs = "";
	for (int i = size - 1; i > 0; i--) {
		if (i < size - 50) break;
		logs += *Debug::mLogMessages[i];
	}
	ImGui::Text(logs.c_str());
	ImGui::End();
}
