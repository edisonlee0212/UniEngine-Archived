#include "TransformSystem.h"
#include "EntityCollection.h"
#include "Math.h"
using namespace UniEngine;
glm::mat4 UniEngine::TransformSystem::TRS(glm::vec3 translation, glm::vec4 rotation, glm::vec3 scale) {
	
	float4 r = float4(rotation.x, rotation.y, rotation.z, rotation.w);
	float3x3 rm = Asfloat3x3(r);
	return glm::mat4(
		glm::vec4(rm.c0.x * scale.x, rm.c0.y * scale.x, rm.c0.z * scale.x, 0.0f),
		glm::vec4(rm.c1.x * scale.x, rm.c1.y * scale.x, rm.c1.z * scale.x, 0.0f),
		glm::vec4(rm.c2.x * scale.x, rm.c2.y * scale.x, rm.c2.z * scale.x, 0.0f),
		glm::vec4(translation, 1.0f));
}

void UniEngine::TransformSystem::CalculateTransform(Entity* parent)
{
	for (auto i : *(parent->Children())) {
		LocalToWorld ltw = LocalToWorld();
		auto pltw = _EntityCollection->GetFixedData<LocalToWorld>(parent).value;
		auto ltp = _EntityCollection->GetFixedData<LocalToParent>(i).value;
		ltw.value = pltw * ltp;
		_EntityCollection->SetFixedData<LocalToWorld>(i, ltw);
		CalculateTransform(i);
	}
}

UniEngine::TransformSystem::TransformSystem()
{

}

void UniEngine::TransformSystem::OnCreate()
{
	Enable();
}

void UniEngine::TransformSystem::OnDestroy()
{
	Disable();
}



void UniEngine::TransformSystem::Update()
{
	for (auto i : *(_EntityCollection->Entities())) {
		if (i->Parent() != nullptr) {
			LocalToParent ltp = LocalToParent();
			auto lp = _EntityCollection->GetFixedData<LocalPosition>(i).value;
			auto lr = _EntityCollection->GetFixedData<LocalRotation>(i).value;
			auto ls = _EntityCollection->GetFixedData<LocalScale>(i).value;
			ltp.value = TRS(lp, lr, ls);
			_EntityCollection->SetFixedData<LocalToParent>(i, ltp);
		}
		else {
			LocalToWorld ltw = LocalToWorld();
			auto p = _EntityCollection->GetFixedData<Position>(i).value;
			auto r = _EntityCollection->GetFixedData<Rotation>(i).value;
			auto s = _EntityCollection->GetFixedData<Scale>(i).value;
			ltw.value = TRS(p, r, s);
			_EntityCollection->SetFixedData<LocalToWorld>(i, ltw);
		}
	}
	for (auto i : *(_EntityCollection->Entities())) {
		if (i->Parent() == nullptr) {
			CalculateTransform(i);
		}
	}
}
