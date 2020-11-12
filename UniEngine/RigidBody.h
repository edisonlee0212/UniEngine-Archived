#pragma once
#include "Core.h"
#include "UniEngineAPI.h"
#include "PxPhysicsAPI.h"
using namespace physx;
namespace UniEngine {
	enum class UNIENGINE_API ShapeType
	{
		Sphere,
		Box,
		Capsule
	};
    class UNIENGINE_API RigidBody :
        public PrivateComponentBase
    {
        glm::vec3 _ShapeCenter;
        glm::vec3 _ShapeEulerRotation;
        bool _DrawBounds;
        glm::vec3 _ShapeParam;
        ShapeType _ShapeType;
        friend class PhysicsSimulationManager;
        PxRigidDynamic* _RigidBody = nullptr;
        PxMaterial* _Material = nullptr;
        PxShape* _Shape = nullptr;
        float _Density;
        PxVec3 _MassCenter;
    public:
        RigidBody();
    	~RigidBody() override;
        void SetMaterial(PxMaterial* value);
        void UpdateShape();
    	void OnDisable() override;
    	void OnEnable() override;
        void OnGui() override;
    };
}

