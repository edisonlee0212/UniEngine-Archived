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
		PxDefaultAllocator		gAllocator;
		PxDefaultErrorCallback	gErrorCallback;

		PxFoundation* gFoundation = NULL;
		PxPhysics* gPhysics = NULL;

		PxDefaultCpuDispatcher* gDispatcher = NULL;
		PxScene* gScene = NULL;

		PxMaterial* gMaterial = NULL;

		PxPvd* gPvd = NULL;

		PxReal stackZ = 10.0f;

		PxRigidDynamic* createDynamic(const PxTransform& t, const PxGeometry& geometry, const PxVec3& velocity = PxVec3(0));
		void createStack(const PxTransform& t, PxU32 size, PxReal halfExtent);
	public:
		void OnCreate() override;
		void OnDestroy() override;
		void FixedUpdate() override;
	};
}

