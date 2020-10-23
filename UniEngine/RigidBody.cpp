#include "pch.h"
#include "RigidBody.h"

#include "PhysicsSimulationManager.h"

UniEngine::RigidBody::RigidBody()
{
	_Material = PhysicsSimulationManager::_DefaultMaterial;
	_RigidBody = PhysicsSimulationManager::_Physics->createRigidDynamic(PxTransform());
	
	OnEnable();
}

UniEngine::RigidBody::~RigidBody()
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

bool UniEngine::RigidBody::GetTransform(glm::mat4& transform)
{
	PxTransform t;
	bool retVal = _RigidBody->getKinematicTarget(t);
	//transform = glm::mat4(t.)
	//TODO: ?
	return retVal;
}

void UniEngine::RigidBody::SetMaterial(PxMaterial* value)
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

void UniEngine::RigidBody::SetRigidBody(PxRigidDynamic* value)
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

void UniEngine::RigidBody::Refresh()
{
	auto shape = PhysicsSimulationManager::_Physics->createShape(*_Geometry, *_Material);
	_RigidBody->attachShape(*shape);
	PxRigidBodyExt::updateMassAndInertia(*_RigidBody, _Density, &_MassCenter);
	if (shape) {
		shape->release();
		shape = nullptr;
	}
}

void UniEngine::RigidBody::OnDisable()
{
	PhysicsSimulationManager::_PhysicsScene->removeActor(*_RigidBody);
}

void UniEngine::RigidBody::OnEnable()
{
	PhysicsSimulationManager::_PhysicsScene->addActor(*_RigidBody);
}

size_t UniEngine::RigidBody::GetHashCode()
{
	return (size_t)this;
}

void UniEngine::RigidBody::OnGui()
{
	
}
