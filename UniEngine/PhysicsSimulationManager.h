#pragma once
#include "Core.h"
#include "UniEngineAPI.h"
#include "PxPhysicsAPI.h"
using namespace physx;

#define PX_RELEASE(x)	if(x)	{ x->release(); x = NULL;	}
namespace UniEngine {
	
	class UNIENGINE_API PhysicsSimulationManager :
		public ManagerBase
	{
		friend class RigidBody;
		static PxDefaultAllocator		_Allocator;
		static PxDefaultErrorCallback	_ErrorCallback;
		static PxFoundation* _PhysicsFoundation;
		static PxPhysics* _Physics;
		static PxDefaultCpuDispatcher* _Dispatcher;
		static PxScene* _PhysicsScene;
		static PxPvd* _PhysVisDebugger;
		
		static PxMaterial* _DefaultMaterial;
		static PxReal stackZ;

		static PxRigidDynamic* createDynamic(const PxTransform& t, const PxGeometry& geometry, const PxVec3& velocity = PxVec3(0));
		static void createStack(const PxTransform& t, PxU32 size, PxReal halfExtent);
	public:
		static bool Enabled;
		static void Init();
		static void Destroy();
		static void Simulate(float time);
	};
}

