#pragma once
#include "UniEngine.h"
using namespace UniEngine;
namespace Planet {
    class CameraControlSystem :
        public SystemBase
    {
        Entity* _TargetCameraEntity;
        CameraComponent* _TargetCameraComponent;
        Camera* _TargetCamera;
        float _Velocity;
        float _Sensitivity;
        float _LastX = 0, _LastY = 0, _LastScrollY = 0;
        bool startMouse = false;
        bool startScroll = false;
    public:
        void Update();
        void SetTargetCamera(Entity* targetCameraEntity);
        void SetVelocity(float velocity);
        void SetSensitivity(float sensitivity);
    };
}
