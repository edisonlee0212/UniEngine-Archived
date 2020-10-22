#include "pch.h"
#include "RigidBody.h"

UniEngine::RigidBody::RigidBody()
{
	
}

UniEngine::RigidBody::~RigidBody()
{
	if (_PhysXRigidBody) {
		_PhysXRigidBody->release();
		_PhysXRigidBody = nullptr;
	}
}

void UniEngine::RigidBody::OnDisable()
{
	
}

void UniEngine::RigidBody::OnEnable()
{
}

size_t UniEngine::RigidBody::GetHashCode()
{
	return (size_t)this;
}

void UniEngine::RigidBody::OnGui()
{
	
}
