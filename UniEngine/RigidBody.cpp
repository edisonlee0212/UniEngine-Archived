#include "pch.h"
#include "RigidBody.h"

#include "PhysicsSimulationManager.h"
#include "RenderManager.h"
#include "Transforms.h"

UniEngine::RigidBody::RigidBody()
{
	_Material = PhysicsSimulationManager::_DefaultMaterial;
	_ShapeCenter = glm::vec3(0.0f);
	_MassCenter = PxVec3(0.0f);
	_ShapeEulerRotation = glm::vec3(0.0f);
	_DrawBounds = true;
	PxTransform localTm(PxVec3(0, 0, 0));
	_RigidBody = PhysicsSimulationManager::_Physics->createRigidDynamic(PxTransform(localTm));
	_ShapeParam = glm::vec3(1.0f);
	_ShapeType = ShapeType::Box;
	UpdateShape();
	_Density = 10.0f;
	PxRigidBodyExt::updateMassAndInertia(*_RigidBody, _Density);
	SetEnabled(true);
}

UniEngine::RigidBody::~RigidBody()
{
	if (_RigidBody) {
		_RigidBody->release();
	}
	if (_Material && _Material != PhysicsSimulationManager::_DefaultMaterial) {
		_Material->release();
	}
	if(_Shape)
	{
		_Shape->release();
	}
}

void UniEngine::RigidBody::SetMaterial(PxMaterial* value)
{
	if(value && _Material != value)
	{
		if (_Material && _Material != PhysicsSimulationManager::_DefaultMaterial) {
			_Material->release();
		}
		_Material = value;
		UpdateShape();
	}
}

void UniEngine::RigidBody::UpdateShape()
{
	if (_Shape != nullptr) _Shape->release();
	switch (_ShapeType)
	{
	case ShapeType::Sphere:
		_Shape = PhysicsSimulationManager::_Physics->createShape(PxSphereGeometry(_ShapeParam.x), *_Material);
		break;
	case ShapeType::Box:
		_Shape = PhysicsSimulationManager::_Physics->createShape(PxBoxGeometry(_ShapeParam.x, _ShapeParam.y, _ShapeParam.z), *_Material);
		break;
	case ShapeType::Capsule:
		_Shape = PhysicsSimulationManager::_Physics->createShape(PxCapsuleGeometry(_ShapeParam.x, _ShapeParam.y), *_Material);
		break;
	}
	_RigidBody->attachShape(*_Shape);
}

void UniEngine::RigidBody::OnDisable()
{
	PhysicsSimulationManager::_PhysicsScene->removeActor(*_RigidBody);
}

void UniEngine::RigidBody::OnEnable()
{
	PhysicsSimulationManager::_PhysicsScene->addActor(*_RigidBody);
}

void UniEngine::RigidBody::OnGui()
{
	ImGui::Checkbox("Draw bounds", &_DrawBounds);
	bool shapeChanged = false;

	ImGui::DragFloat3("Center Position", &_ShapeCenter.x);
	ImGui::DragFloat3("Rotation", &_ShapeEulerRotation.x);
	
	auto ltw = GetOwner().GetComponentData<LocalToWorld>().Value;
	auto cltw = glm::translate(_ShapeCenter) *
		glm::mat4_cast(glm::quat(_ShapeEulerRotation));
	switch (_ShapeType)
	{
	case ShapeType::Sphere:
		if (ImGui::DragFloat("Radius", &_ShapeParam.x, 0.01f, 0.0001f)) shapeChanged = true;
		if(_DrawBounds) RenderManager::DrawGizmoPoint(glm::vec4(0.0f, 0.0f, 1.0f, 0.5f), ltw * (cltw * glm::scale(glm::vec3(_ShapeParam.x))), 1);
		break;
	case ShapeType::Box:
		if (ImGui::DragFloat3("XYZ Size", &_ShapeParam.x, 0.01f, 0.0001f)) shapeChanged = true;
		if (_DrawBounds) RenderManager::DrawGizmoCube(glm::vec4(0.0f, 0.0f, 1.0f, 0.5f), ltw * (cltw * glm::scale(glm::vec3(_ShapeParam))), 1);
		break;
	case ShapeType::Capsule:
		if (ImGui::DragFloat2("R/HalfH", &_ShapeParam.x, 0.01f, 0.0001f)) shapeChanged = true;
		break;
	}
	if (shapeChanged) UpdateShape();
	if(ImGui::DragFloat("Density", &_Density)) PxRigidBodyExt::updateMassAndInertia(*_RigidBody, _Density);
}
