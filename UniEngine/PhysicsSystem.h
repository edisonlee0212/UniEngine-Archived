#pragma once
#include "Core.h"
#include "UniEngineAPI.h"
#include "PxPhysicsAPI.h"
using namespace physx;

#define PX_RELEASE(x)	if(x)	{ x->release(); x = NULL;	}
namespace UniEngine {
	class UNIENGINE_API PhysicsSystem :
		public SystemBase
	{
		PxDefaultAllocator		_Allocator;
		PxDefaultErrorCallback	_ErrorCallback;
		PxFoundation* _PhysicsFoundation = NULL;
		PxPhysics* _Physics = NULL;
		PxDefaultCpuDispatcher* _Dispatcher = NULL;
		PxScene* _PhysicsScene = NULL;
		PxPvd* _PhysVisDebugger = NULL;
		
		PxMaterial* gMaterial = NULL;
		PxReal stackZ = 10.0f;

		PxRigidDynamic* createDynamic(const PxTransform& t, const PxGeometry& geometry, const PxVec3& velocity = PxVec3(0));
		void createStack(const PxTransform& t, PxU32 size, PxReal halfExtent);
	public:
		void OnCreate() override;
		void OnDestroy() override;
		void FixedUpdate() override;
	};
}

