#pragma once
#include "Core.h"
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
        glm::mat4 _ShapeTransform;
        bool _DrawBounds;
        glm::vec3 _ShapeParam;
        ShapeType _ShapeType;
        bool _IsStatic;
        friend class PhysicsSimulationManager;
        PxRigidActor* _RigidBody = nullptr;
        PxMaterial* _Material = nullptr;
        PxShape* _Shape = nullptr;
        float _Density;
        PxVec3 _MassCenter;
        bool _CurrentRegistered;
        PxVec3 _LinearVelocity;
        PxVec3 _AngularVelocity;
        void RegisterCheck();
    public:
        RigidBody();
        void SetShapeType(ShapeType type);
        void SetShapeParam(glm::vec3 value);
        void SetStatic(bool value);
        void SetTransform(glm::mat4 value);
        void SetDensity(float value);
    	~RigidBody() override;
        void SetMaterial(PxMaterial* value);
        void UpdateShape();
        void UpdateBody();
    	void Init() override;
    	void OnEntityDisable() override;
    	void OnEntityEnable() override;
    	void OnDisable() override;
    	void OnEnable() override;
        void OnGui() override;
    };
}

