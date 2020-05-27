#include "TransformSystem.h"
#include "EntityCollection.h"
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
			ltp.value = glm::translate(glm::mat4(1.0f), lp);
			ltp.value = glm::scale(ltp.value, ls);
			_EntityCollection->SetFixedData<LocalToParent>(i, ltp);
		}
		else {
			LocalToWorld ltw = LocalToWorld();
			auto p = _EntityCollection->GetFixedData<Position>(i).value;
			auto r = _EntityCollection->GetFixedData<Rotation>(i).value;
			auto s = _EntityCollection->GetFixedData<Scale>(i).value;
			ltw.value = glm::translate(glm::mat4(1.0f), p);
			ltw.value = glm::scale(ltw.value, s);
			_EntityCollection->SetFixedData<LocalToWorld>(i, ltw);
		}
	}
	for (auto i : *(_EntityCollection->Entities())) {
		if (i->Parent() == nullptr) {
			CalculateTransform(i);
		}
	}
}
