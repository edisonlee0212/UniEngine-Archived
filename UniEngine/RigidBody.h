#pragma once
#include "Core.h"
#include "UniEngineAPI.h"
#include "PxPhysicsAPI.h"
using namespace physx;
namespace UniEngine {
    class RigidBody :
        public SharedComponentBase
    {
        PxRigidDynamic* _PhysXRigidBody;
    public:
        RigidBody();
    	~RigidBody();
    	void OnDisable() override;
    	void OnEnable() override;
        size_t GetHashCode() override;
        void OnGui() override;
    };
}

