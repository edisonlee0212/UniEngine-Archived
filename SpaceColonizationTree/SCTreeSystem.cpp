#include "SCTreeSystem.h"
#include "CubeEnvelope.h"
#include "SurfaceOfRevolutionEnvelope.h"
#include "CoilEnvelope.h"
#include "CylinderEnvelope.h"
using namespace SpaceColonizationTree;
void SpaceColonizationTree::SCTreeSystem::OnCreate()
{
	_EnvelopePointMaterial = new Material();
	_EnvelopePointMaterial->Programs()->push_back(Default::GLPrograms::StandardInstancedProgram);
	_EnvelopeTexture = new Texture2D(TextureType::DIFFUSE);
	_EnvelopeTexture->LoadTexture(FileIO::GetPath("Textures/red.png"), "");
	_EnvelopePointMaterial->Textures2Ds()->push_back(_EnvelopeTexture);

	_TreePointMaterial = new Material();
	_TreePointMaterial->Programs()->push_back(Default::GLPrograms::StandardInstancedProgram);
	_TreePointTexture = new Texture2D(TextureType::DIFFUSE);
	_TreePointTexture->LoadTexture(FileIO::GetPath("Textures/green.png"), "");
	_TreePointMaterial->Textures2Ds()->push_back(_TreePointTexture);

	_TreeMeshMaterial = new Material();
	_TreeMeshMaterial->Programs()->push_back(Default::GLPrograms::StandardProgram);
	_TreeMeshTexture = new Texture2D(TextureType::DIFFUSE);
	_TreeMeshTexture->LoadTexture(FileIO::GetPath("Textures/tree.png"), "");
	_TreeMeshMaterial->Textures2Ds()->push_back(_TreeMeshTexture);

	_TreeLeafMaterial = new Material();
	_TreeLeafMaterial->SetMaterialProperty("material.shininess", 0.0f);
	_TreeLeafMaterial->Programs()->push_back(Default::GLPrograms::StandardInstancedProgram);
	_TreeLeafTexture = new Texture2D(TextureType::DIFFUSE);
	_TreeLeafTexture->LoadTexture(FileIO::GetPath("Textures/green.png"), "");
	_TreeLeafMaterial->Textures2Ds()->push_back(_TreeLeafTexture);

	_GrowDist = 0.3f;
	_AttractDitsMult = 2.5f;
	_RemoveDistMult = 0.5f;
	_PointsCount = 1000;
	_EnvelopeRadius = 6.0f;
	_MinHeight = 2.0f;
	_MaxHeight = 8.0f;
	_TreeSize = 1.0f;
	_DrawOrgan = false;
	_TreeEntity.Version = 0;
	Enable();
}

void SpaceColonizationTree::SCTreeSystem::BuildEnvelope() {
	RemoveTree();
	RemoveEnvelope();
	switch (_SelectedEnvelopeType)
	{
	case 0:
		_Envelope = new SurfaceOfRevolutionEnvelope(glm::vec3(-_EnvelopeRadius / 2.0f, _MinHeight, -_EnvelopeRadius / 2.0f), glm::vec3(_EnvelopeRadius, _MaxHeight - _MinHeight, _EnvelopeRadius));
		break;
	case 1:
		_Envelope = new CubeEnvelope(glm::vec3(-_EnvelopeRadius / 2.0f, _MinHeight, -_EnvelopeRadius / 2.0f), glm::vec3(_EnvelopeRadius, _MaxHeight - _MinHeight, _EnvelopeRadius));
		break;
	case 2:
		_Envelope = new CylinderEnvelope(glm::vec3(-_EnvelopeRadius / 2.0f, _MinHeight, -_EnvelopeRadius / 2.0f), glm::vec3(_EnvelopeRadius, _MaxHeight - _MinHeight, _EnvelopeRadius));
		break;
	case 3:
		_Envelope = new CoilEnvelope(glm::vec3(-_EnvelopeRadius / 2.0f, _MinHeight, -_EnvelopeRadius / 2.0f), glm::vec3(_EnvelopeRadius, _MaxHeight - _MinHeight, _EnvelopeRadius));
		break;
	default:
		_Envelope = new CubeEnvelope(glm::vec3(-_EnvelopeRadius / 2.0f, _MinHeight, -_EnvelopeRadius / 2.0f), glm::vec3(_EnvelopeRadius, _MaxHeight - _MinHeight, _EnvelopeRadius));
		break;
	}
	Debug::Log("Generating attraction points...");
	_Envelope->GeneratePoints(_PointsCount);
	Debug::Log("Attraction points generation complete. [Amount: " + std::to_string(_PointsCount) + "]");
}


void SpaceColonizationTree::SCTreeSystem::BuildTree() {
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

void SpaceColonizationTree::SCTreeSystem::RemoveTree() {
	if (_Tree != nullptr) {
		delete _Tree;
		_Tree = nullptr;
	}
	if (_TreeEntity.Version != 0) {
		EntityManager::DeleteEntity(_TreeEntity);
		_TreeEntity.Version = 0;
	}
	if (_TreeLeaves != nullptr) {
		delete _TreeLeaves;
		_TreeLeaves = nullptr;
	}
	if (_TreeMesh != nullptr) {
		delete _TreeMesh;
		_TreeMesh = nullptr;
	}

}

void SpaceColonizationTree::SCTreeSystem::RemoveEnvelope() {
	if (_Envelope != nullptr) delete _Envelope;
	_Envelope = nullptr;
}

void SpaceColonizationTree::SCTreeSystem::OnDestroy() {
	Disable();
	delete _EnvelopePointMaterial;
	delete _EnvelopeTexture;
	delete _TreePointMaterial;
	delete _TreePointTexture;
	RemoveEnvelope();
	RemoveTree();
}

static const char* EnvelopeTypes[]{ "SurfaceOfRevo", "Cube", "Cylinder", "Coil" };

void SpaceColonizationTree::SCTreeSystem::Update() {
	EnvelopeGUIMenu();
	TreeGUIMenu();
	Camera* mainCamera = dynamic_cast<CameraComponent*>(EntityManager::QuerySharedComponents<CameraComponent>()->at(0)->first)->Value;
	if (_Envelope != nullptr) _Envelope->Draw(mainCamera, _EnvelopePointMaterial, glm::vec3(_TreeSize));
	if (_Tree != nullptr && _Tree->_NeedsToGrow) _Tree->Draw(mainCamera, _TreePointMaterial, glm::vec3(_TreeSize));
	if (_TreeEntity.Version != 0) {
		Scale scale;
		scale.value = glm::vec3(_TreeSize);
		EntityManager::SetComponentData<Scale>(_TreeEntity, scale);
	}
}

void SpaceColonizationTree::SCTreeSystem::FixedUpdate() {
	if (_Envelope != nullptr && _Tree != nullptr) {
		if (_Tree->_NeedsToGrow) {
			_Iteration++;
			_Tree->Grow(_GrowDist, _AttractDist, _RemoveDist, _Envelope, glm::vec3(0.0f), 0.015f, 0.05f, 0.02f, 0.02f);
		}
		else {
			EntityArchetype archetype = EntityManager::CreateEntityArchetype<Position, Rotation, Scale, LocalToWorld>(Position(), Rotation(), Scale(), LocalToWorld());
			_TreeEntity = EntityManager::CreateEntity(archetype);
			_TreeLeaves = new InstancedMeshMaterialComponent();
			_TreeLeaves->_Material = _TreeLeafMaterial;
			_TreeLeaves->_Mesh = Default::Primitives::Quad;
			_TreeLeaves->_Matrices = &_Tree->_LeafList;
			EntityManager::SetSharedComponent<InstancedMeshMaterialComponent>(_TreeEntity, _TreeLeaves);

			_TreeMesh = new MeshMaterialComponent();
			_TreeMesh->_Material = _TreeMeshMaterial;
			_TreeMesh->_Mesh = _Tree->_Mesh;
			EntityManager::SetSharedComponent<MeshMaterialComponent>(_TreeEntity, _TreeMesh);
			Position pos;
			pos.value = _Tree->_Position;
			Scale scale;
			scale.value = glm::vec3(1.5f);
			EntityManager::SetComponentData<Position>(_TreeEntity, pos);
			EntityManager::SetComponentData<Scale>(_TreeEntity, scale);
			RemoveEnvelope();
		}
	}
}

void SpaceColonizationTree::SCTreeSystem::EnvelopeGUIMenu() {
	ImGui::Begin("Envelope Controller");
	ImGui::Combo("Envelope Type", &_SelectedEnvelopeType, EnvelopeTypes, IM_ARRAYSIZE(EnvelopeTypes), 3);
	if (ImGui::Button("Create Aattraction Points")) BuildEnvelope();
	ImGui::SliderInt("Point Amount", &_PointsCount, 100, 16000);
	ImGui::SliderFloat("Envelope Radius", &_EnvelopeRadius, 1.0f, 10.0f);
	ImGui::SliderFloat("Minmum Height", &_MinHeight, 0.1f, _MaxHeight);
	ImGui::SliderFloat("Maximum Height", &_MaxHeight, _MinHeight, 20.0f);
	if (ImGui::Button("Clear Aattraction Points")) RemoveEnvelope();
	ImGui::End();
}

void SpaceColonizationTree::SCTreeSystem::TreeGUIMenu() {
	ImGui::Begin("Tree Controller");
	std::string text = std::string(_DrawOrgan ? "Draw" : "Hide") + " Organs";
	if (ImGui::Button(text.c_str())) {
		_DrawOrgan = !_DrawOrgan;
		if (_DrawOrgan) {
			if (_TreeEntity.Version != 0) {
				if (_TreeLeaves != nullptr) {
					EntityManager::RemoveSharedComponent<InstancedMeshMaterialComponent>(_TreeEntity);
				}
			}
		}
		else {
			if (_TreeEntity.Version != 0) {
				if (_TreeLeaves != nullptr) {
					EntityManager::SetSharedComponent<InstancedMeshMaterialComponent>(_TreeEntity, _TreeLeaves);
				}
			}
		}
	}
	ImGui::SliderFloat("Tree Size", &_TreeSize, 0.2f, 5.0f);
	ImGui::SliderFloat("Grow Distance", &_GrowDist, 0.2f, 0.5f);
	ImGui::SliderFloat("Attract Distance Multiplier", &_AttractDitsMult, 1.0f, 5.0f);
	ImGui::SliderFloat("Remove Distance Multiplier", &_RemoveDistMult, 0.1f, 0.9f);
	if (ImGui::Button("Build Tree")) BuildTree();
	if (ImGui::Button("Delete Tree")) RemoveTree();
	ImGui::Text("Iteration = %d", _Iteration);
	ImGui::End();
}