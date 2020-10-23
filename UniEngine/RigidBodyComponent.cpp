#include "pch.h"
#include "RigidBodyComponent.h"

#include "PhysicsSimulationManager.h"

UniEngine::RigidBodyComponent::RigidBodyComponent()
{
	_Material = PhysicsSimulationManager::_DefaultMaterial;
	_RigidBody = PhysicsSimulationManager::_Physics->createRigidDynamic(PxTransform());
	
	OnEnable();
}

UniEngine::RigidBodyComponent::~RigidBodyComponent()
{
	if (_RigidBody) {
		_RigidBody->release();
		_RigidBody = nullptr;
	}
	if (_Material && _Material != PhysicsSimulationManager::_DefaultMaterial) {
		_Material->release();
		_Material = nullptr;
	}
}

bool UniEngine::RigidBodyComponent::GetTransform(glm::mat4& transform)
{
	PxTransform t;
	bool retVal = _RigidBody->getKinematicTarget(t);
	//transform = glm::mat4(t.)
	//TODO: ?
	return retVal;
}

void UniEngine::RigidBodyComponent::SetMaterial(PxMaterial* value)
{
	if(value && _Material != value)
	{
		if (_Material && _Material != PhysicsSimulationManager::_DefaultMaterial) {
			_Material->release();
		}
		_Material = value;
		Refresh();
	}
}

void UniEngine::RigidBodyComponent::SetRigidBody(PxRigidDynamic* value)
{
	if(value && _RigidBody != value)
	{
		if (_RigidBody) {
			_RigidBody->release();
			_RigidBody = nullptr;
		}
		_RigidBody = value;
		Refresh();
	}
	
}

void UniEngine::RigidBodyComponent::Refresh()
{
	auto shape = PhysicsSimulationManager::_Physics->createShape(*_Geometry, *_Material);
	_RigidBody->attachShape(*shape);
	PxRigidBodyExt::updateMassAndInertia(*_RigidBody, _Density, &_MassCenter);
	if (shape) {
		shape->release();
		shape = nullptr;
	}
}

void UniEngine::RigidBodyComponent::OnDisable()
{
	PhysicsSimulationManager::_PhysicsScene->removeActor(*_RigidBody);
}

void UniEngine::RigidBodyComponent::OnEnable()
{
	PhysicsSimulationManager::_PhysicsScene->addActor(*_RigidBody);
}

void UniEngine::RigidBodyComponent::OnGui()
{
	
}
