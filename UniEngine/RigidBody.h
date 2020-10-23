#pragma once
#include "Core.h"
#include "UniEngineAPI.h"
#include "PxPhysicsAPI.h"
using namespace physx;
namespace UniEngine {
    class RigidBody :
        public SharedComponentBase
    {
        PxRigidDynamic* _RigidBody;
        PxMaterial* _Material;
        PxGeometry* _Geometry;
        float _Density;
        PxVec3 _MassCenter;
    public:
        RigidBody();
    	~RigidBody();
        bool GetTransform(glm::mat4& transform);
        void SetMaterial(PxMaterial* value);
        void SetRigidBody(PxRigidDynamic* value);
        void Refresh();
    	void OnDisable() override;
    	void OnEnable() override;
        size_t GetHashCode() override;
        void OnGui() override;
    };
}

