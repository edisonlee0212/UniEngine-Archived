#pragma once
#include "Core.h"
#include "UniEngineAPI.h"
#include "PxPhysicsAPI.h"
#include "RigidBody.h"
using namespace physx;

#define PX_RELEASE(x)	if(x)	{ x->release(); x = nullptr;	}
namespace UniEngine {

	class UNIENGINE_API PhysicsSimulationManager :
		public Singleton<PhysicsSimulationManager>
	{
		friend class RigidBody;
		PxDefaultAllocator m_allocator;
		PxDefaultErrorCallback m_errorCallback;
		PxFoundation* m_physicsFoundation = nullptr;
		PxPhysics* m_physics = nullptr;
		PxDefaultCpuDispatcher* m_dispatcher = nullptr;
		PxScene* m_physicsScene = nullptr;
		PxPvd* m_physVisDebugger = nullptr;
		PxMaterial* m_defaultMaterial = nullptr;
		PxReal m_stackZ = 10.0f;
	public:
		bool m_enabled = false;
		static void Init();
		static void Destroy();
		static void UploadTransforms();
		static void Simulate(float time);
	};
}

