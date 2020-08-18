#pragma once
#include "UniEngineAPI.h"
#include "CameraComponent.h"
#include "TransformSystem.h"
namespace UniEngine {
    class UNIENGINE_API CameraControlSystem :
        public SystemBase
    {
		float _Velocity = 20.0f;
		float _Sensitivity = 0.1f;
		bool _EnableWindowControl = false;
		Translation _CameraPosition;
		Rotation _CameraRotation;
		float _LastX = 0, _LastY = 0, _LastScrollY = 0;
		bool startMouse = false;
		bool startScroll = false;
		float _P[3];
		float _R[4];
	public:
		void Update();
		void EnableWindowControl(bool value);
		void SetPosition(glm::vec3 position);
		void SetVelocity(float velocity);
		void SetSensitivity(float sensitivity);
    };
}
