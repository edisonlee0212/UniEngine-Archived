#include "SCTreeSystem.h"
#include "CubeEnvelope.h"
#include "SurfaceOfRevolutionEnvelope.h"
#include "CoilEnvelope.h"
#include "CylinderEnvelope.h"
using namespace SCTree;
void SCTree::SCTreeSystem::OnCreate()
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
	_PointsCount = 4000;
	_EnvelopeRadius = 6.0f;
	_MinHeight = 2.0f;
	_MaxHeight = 8.0f;
	_TreeSize = 1.0f;
	_DrawOrgan = false;
	Enable();
}

void SCTree::SCTreeSystem::BuildEnvelope() {
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
	//Debug::Log("Generating attraction points...");
	_Envelope->GeneratePoints(_PointsCount);
	//Debug::Log("Attraction points generation complete. [Amount: " + std::to_string(_PointsCount) + "]");
}


void SCTree::SCTreeSystem::BuildTree() {
	if (_Envelope == nullptr || !_Envelope->PointsGenerated()) BuildEnvelope();
	RemoveTree();
	_Iteration = 0;
	_Tree = new Tree(glm::vec3(0.0f), Default::Materials::StandardMaterial, Default::Materials::StandardMaterial, Default::Materials::StandardMaterial);
	_AttractDist = _GrowDist * _AttractDitsMult;
	_RemoveDist = _GrowDist * _RemoveDistMult;
	//Debug::Log("Trunk growing...");
	_Tree->GrowTrunk(_GrowDist, _AttractDist, _Envelope, glm::vec3(0.0f));
	//Debug::Log("Trunk grow complete.");
}

void SCTree::SCTreeSystem::RemoveTree() {
	if (_Tree != nullptr) {
		delete _Tree;
		_Tree = nullptr;
	}
	if (_TreeEntity != nullptr) {
		_EntityCollection->DeleteEntity(_TreeEntity);
		_TreeEntity = nullptr;
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
	Camera* mainCamera = dynamic_cast<CameraComponent*>(_EntityCollection->QuerySharedComponents<CameraComponent>()->at(0)->first)->Value;
	if (_Envelope != nullptr) _Envelope->Draw(mainCamera, _EnvelopePointMaterial, glm::vec3(_TreeSize));
	if (_Tree != nullptr && _Tree->_NeedsToGrow) _Tree->Draw(mainCamera, _TreePointMaterial, glm::vec3(_TreeSize));
	if (_TreeEntity != nullptr) {
		Scale scale;
		scale.value = glm::vec3(_TreeSize);
		_EntityCollection->SetFixedData<Scale>(_TreeEntity, scale);
	}
}

void SCTree::SCTreeSystem::FixedUpdate() {
	if (_Envelope != nullptr && _Tree != nullptr) {
		if (_Tree->_NeedsToGrow) {
			_Iteration++;
			_Tree->Grow(_GrowDist, _AttractDist, _RemoveDist, _Envelope, glm::vec3(0.0f), 0.015f, 0.05f, 0.02f, 0.02f);
		}
		else {
			_TreeEntity = _EntityCollection->CreateEntity();
			_TreeLeaves = new InstancedMeshMaterialComponent();
			_TreeLeaves->_Material = _TreeLeafMaterial;
			_TreeLeaves->_Mesh = Default::Primitives::Quad;
			_TreeLeaves->_Matrices = &_Tree->_LeafList;
			_EntityCollection->SetSharedComponent<InstancedMeshMaterialComponent>(_TreeEntity, _TreeLeaves);

			_TreeMesh = new MeshMaterialComponent();
			_TreeMesh->_Material = _TreeMeshMaterial;
			_TreeMesh->_Mesh = _Tree->_Mesh;
			_EntityCollection->SetSharedComponent<MeshMaterialComponent>(_TreeEntity, _TreeMesh);
			Position pos;
			pos.value = _Tree->_Position;
			Scale scale;
			scale.value = glm::vec3(1.5f);
			_EntityCollection->SetFixedData<Position>(_TreeEntity, pos);
			_EntityCollection->SetFixedData<Scale>(_TreeEntity, scale);
			RemoveEnvelope();
		}
	}
}
