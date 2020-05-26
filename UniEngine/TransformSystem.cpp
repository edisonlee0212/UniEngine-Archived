#include "TransformSystem.h"

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
			ltp.value = TRS(_EntityCollection->GetFixedData<LocalPosition>(i).value
				, _EntityCollection->GetFixedData<LocalRotation>(i).value
				, _EntityCollection->GetFixedData<LocalScale>(i).value);
			_EntityCollection->SetFixedData<LocalToParent>(i, ltp);
		}
		else {
			LocalToWorld ltw = LocalToWorld();
			ltw.value = TRS(_EntityCollection->GetFixedData<Position>(i).value
				, _EntityCollection->GetFixedData<Rotation>(i).value
				, _EntityCollection->GetFixedData<Scale>(i).value);
			_EntityCollection->SetFixedData<LocalToWorld>(i, ltw);
		}
	}
	for (auto i : *(_EntityCollection->Entities())) {
		if (i->Parent() == nullptr) {
			CalculateTransform(i);
		}
	}
}
