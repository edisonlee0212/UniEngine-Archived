#pragma once
#include "Core.h"
#include "UniEngineAPI.h"
#include "PxPhysicsAPI.h"
#include "RigidBody.h"
using namespace physx;

#define PX_RELEASE(x)	if(x)	{ x->release(); x = NULL;	}
namespace UniEngine {

	class UNIENGINE_API PhysicsSimulationManager :
		public ManagerBase
	{
		friend class RigidBody;
		static PxDefaultAllocator _Allocator;
		static PxDefaultErrorCallback _ErrorCallback;
		static PxFoundation* _PhysicsFoundation;
		static PxPhysics* _Physics;
		static PxDefaultCpuDispatcher* _Dispatcher;
		static PxScene* _PhysicsScene;
		static PxPvd* _PhysVisDebugger;

		static PxMaterial* _DefaultMaterial;
		static PxReal stackZ;
	public:
		static bool Enabled;
		static void Init();
		static void Destroy();
		static void UploadTransforms();
		static void Simulate(float time);
	};
}

