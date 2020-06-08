#include "SCTreeSystem.h"
#include "CubeEnvelope.h"
#include "MeshMaterialComponent.h"
#include "FixedData.h"
#include "SurfaceOfRevolutionEnvelope.h"
#include "CoilEnvelope.h"
#include "CylinderEnvelope.h"
using namespace SCTree;
void SCTree::SCTreeSystem::OnCreate()
{
	_EnvelopePointMaterial = new Material();

	_TreePointMaterial = new Material();

	_TreeMeshMaterial = new Material();

	_TreeLeafMaterial = new Material();


	_GrowDist = 0.3f;
	_AttractDitsMult = 2.5f;
	_RemoveDistMult = 0.5f;
	_PointsCount = 4000;

	_DrawOrgan = true;
	Enable();
}

void SCTree::SCTreeSystem::BuildEnvelope() {
	RemoveEnvelope();
	switch (_SelectedEnvelopeType)
	{
	case 0:
		_Envelope = new SurfaceOfRevolutionEnvelope(glm::vec3(-2.0f, 2.0f, -2.0f), glm::vec3(6.0f, 6.0f, 6.0f));
		break;
	case 1:
		_Envelope = new CubeEnvelope(glm::vec3(-2.0f, 2.0f, -2.0f), glm::vec3(6.0f, 6.0f, 6.0f));
		break;
	case 2:
		_Envelope = new CylinderEnvelope(glm::vec3(-2.0f, 2.0f, -2.0f), glm::vec3(6.0f, 6.0f, 6.0f));
		break;
	case 3:
		_Envelope = new CoilEnvelope(glm::vec3(-2.0f, 2.0f, -2.0f), glm::vec3(6.0f, 6.0f, 6.0f));
		break;
	default:
		_Envelope = new CubeEnvelope(glm::vec3(0.0f, 6.0f, 0.0f), glm::vec3(4.0f, 4.0f, 4.0f));
		break;
	}
	Debug::Log("Generating attraction points...");
	_Envelope->GeneratePoints(_PointsCount);
	Debug::Log("Attraction points generation complete. [Amount: " + std::to_string(_PointsCount) + "]");
}


void SCTree::SCTreeSystem::BuildTree() {
	if (_Envelope == nullptr || !_Envelope->PointsGenerated()) BuildEnvelope();
	RemoveTree();
	_Iteration = 0;
	_Tree = new Tree(glm::vec3(0.0f), Default::Materials::StandardMaterial, Default::Materials::StandardMaterial, Default::Materials::StandardMaterial);
	_AttractDist = _GrowDist * _AttractDitsMult;
	_RemoveDist = _GrowDist * _RemoveDistMult;
	Debug::Log("Trunk growing...");
	_Tree->GrowTrunk(_GrowDist, _AttractDist, _Envelope, glm::vec3(0.0f));
	Debug::Log("Trunk grow complete.");
}

void SCTree::SCTreeSystem::RemoveTree() {
	if (_Tree != nullptr) delete _Tree;
	_Tree = nullptr;
}

void SCTree::SCTreeSystem::RemoveEnvelope() {
	if (_Envelope != nullptr) delete _Envelope;
	_Envelope = nullptr;
}

void SCTree::SCTreeSystem::OnDestroy() {
	Disable();
	delete _EnvelopePointMaterial;
	delete _EnvelopeTexture;
	delete _TreePointMaterial;
	delete _TreePointTexture;
	RemoveEnvelope();
	RemoveTree();
}

static const char* EnvelopeTypes[]{ "SurfaceOfRevo", "Cube", "Cylinder", "Coil" };

void SCTree::SCTreeSystem::Update() {
	EnvelopeGUIMenu();
	TreeGUIMenu();
	if (_Envelope != nullptr && _Tree->_NeedsToGrow) _Envelope->Draw(_World->MainCamera(), Default::Materials::StandardInstancedMaterial);
	if (_Tree != nullptr && _Tree->_NeedsToGrow) _Tree->Draw(_World->MainCamera(), Default::Materials::StandardInstancedMaterial);
}

void SCTree::SCTreeSystem::FixedUpdate() {
	if (_Envelope != nullptr && _Tree != nullptr) {
		if (_Tree->_NeedsToGrow) {
			_Iteration++;
			_Tree->Grow(_GrowDist, _AttractDist, _RemoveDist, _Envelope, glm::vec3(0.0f), 0.015f, 0.05f, 0.02f, 0.02f);
		}
		else {
			Entity* entity = _EntityCollection->CreateEntity();
			MeshMaterialComponent* mmc = new MeshMaterialComponent();
			mmc->_Material = Default::Materials::StandardMaterial;
			mmc->_Mesh = _Tree->_Mesh;
			_EntityCollection->SetSharedComponent<MeshMaterialComponent>(entity, mmc);
			Position pos;
			pos.value = _Tree->_Position;
			Scale scale;
			scale.value = glm::vec3(1.0f);
			_EntityCollection->SetFixedData<Position>(entity, pos);
			_EntityCollection->SetFixedData<Scale>(entity, scale);
			RemoveTree();
			RemoveEnvelope();
		}
	}
}

inline void  SCTree::SCTreeSystem::EnvelopeGUIMenu() {
	ImGui::Begin("Envelope Controller");
	ImGui::Combo("Envelope Type", &_SelectedEnvelopeType, EnvelopeTypes, IM_ARRAYSIZE(EnvelopeTypes), 3);
	if (ImGui::Button("Create Aattraction Points")) BuildEnvelope();
	ImGui::SliderInt("Point Amount", &_PointsCount, 100, 16000);
	//ImGui::SliderFloat("Envelope Radius", &_EnvelopeRadius, 1.0f, 5.0f);
	//ImGui::SliderFloat("Minmum Height", &_MinHeight, 0.1f, _MaxHeight);
	//ImGui::SliderFloat("Maximum Height", &_MaxHeight, _MinHeight, 10.0f);
	if (ImGui::Button("Clear Aattraction Points")) RemoveEnvelope();
	ImGui::End();
}

inline void  SCTree::SCTreeSystem::TreeGUIMenu() {
	ImGui::Begin("Tree Controller");
	std::string text = std::string(_DrawOrgan ? "Hide" : "Draw") + " Leaves";
	if (ImGui::Button(text.c_str())) _DrawOrgan = !_DrawOrgan;
	ImGui::SliderFloat("Grow Distance", &_GrowDist, 0.2f, 0.5f);
	ImGui::SliderFloat("Attract Distance Multiplier", &_AttractDitsMult, 1.0f, 5.0f);
	ImGui::SliderFloat("Remove Distance Multiplier", &_RemoveDistMult, 0.1f, 0.9f);
	if (ImGui::Button("Build Tree")) BuildTree();
	if (ImGui::Button("Delete Tree")) RemoveTree();
	ImGui::Text("Iteration = %d", _Iteration);
	ImGui::End();
}