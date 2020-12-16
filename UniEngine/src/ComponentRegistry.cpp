#include "pch.h"
#include "Camera.h"
#include "CameraComponent.h"
#include "DirectionalLight.h"
#include "Particles.h"
#include "PointLight.h"
#include "Ray.h"
#include "SpotLight.h"
#include "Transforms.h"
#include "MeshRenderer.h"
#include "RigidBody.h"
using namespace UniEngine;


ComponentDataRegistration<Transform> TransformRegistry(1);
ComponentDataRegistration<GlobalTransform> GlobalTransformRegistry(1);
ComponentDataRegistration<Ray> RayRegistry(1);
ComponentDataRegistration<SpotLight> SpotLightRegistry(1);
ComponentDataRegistration<PointLight> PointLightRegistry(1);
ComponentDataRegistration<DirectionalLight> DirectionalLightRegistry(1);
ComponentDataRegistration<CameraLayerMask> CameraLayerMaskRegistry(1);

SerializableRegistration<CameraComponent> CameraComponentRegistry(1);
SerializableRegistration<Particles> ParticlesRegistry(1);
SerializableRegistration<MeshRenderer> MeshRendererRegistry(1);
SerializableRegistration<RigidBody> RigidBodyRegistry(1);

