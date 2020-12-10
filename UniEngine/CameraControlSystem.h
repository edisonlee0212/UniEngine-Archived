#pragma once
#include "Core.h"
#include "UniEngineAPI.h"
#include "CameraComponent.h"
#include "TransformManager.h"
namespace UniEngine {
    class UNIENGINE_API CameraControlSystem :
        public SystemBase
    {
		float _Velocity = 20.0f;
		float _Sensitivity = 0.1f;
		float _LastX = 0, _LastY = 0, _LastScrollY = 0;
		bool _StartMouse = false;
	public:
		void LateUpdate() override;
		void SetVelocity(float velocity);
		void SetSensitivity(float sensitivity);
    };
}
