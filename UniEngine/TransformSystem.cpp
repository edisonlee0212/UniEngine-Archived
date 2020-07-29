#include "pch.h"
#include "TransformSystem.h"
using namespace UniEngine;

UniEngine::TransformSystem::TransformSystem()
{

}

void UniEngine::TransformSystem::OnCreate()
{
	_LP = EntityManager::CreateEntityQuery();
	EntityManager::SetEntityQueryAllFilters<LocalToParent, LocalPosition>(_LP, LocalToParent(), LocalPosition());
	EntityManager::SetEntityQueryNoneFilters<LocalRotation, LocalScale>(_LP, LocalRotation(), LocalScale());
	_LPR = EntityManager::CreateEntityQuery();
	EntityManager::SetEntityQueryAllFilters<LocalToParent, LocalPosition, LocalRotation>(_LPR, LocalToParent(), LocalPosition(), LocalRotation());
	EntityManager::SetEntityQueryNoneFilters<LocalScale>(_LPR, LocalScale());
	_LPS = EntityManager::CreateEntityQuery();
	EntityManager::SetEntityQueryAllFilters<LocalToParent, LocalPosition, LocalScale>(_LPS, LocalToParent(), LocalPosition(), LocalScale());
	EntityManager::SetEntityQueryNoneFilters<LocalRotation>(_LPS, LocalRotation());
	_LPRS = EntityManager::CreateEntityQuery();
	EntityManager::SetEntityQueryAllFilters<LocalToParent, LocalPosition, LocalRotation, LocalScale>(_LPRS, LocalToParent(), LocalPosition(), LocalRotation(), LocalScale());
	_LR = EntityManager::CreateEntityQuery();
	EntityManager::SetEntityQueryAllFilters<LocalToParent, LocalRotation>(_LR, LocalToParent(), LocalRotation());
	EntityManager::SetEntityQueryNoneFilters<LocalPosition, LocalScale>(_LR, LocalPosition(), LocalScale());
	_LRS = EntityManager::CreateEntityQuery();
	EntityManager::SetEntityQueryAllFilters<LocalToParent, LocalRotation, LocalScale>(_LRS, LocalToParent(), LocalRotation(), LocalScale());
	EntityManager::SetEntityQueryNoneFilters<LocalPosition>(_LRS, LocalPosition());
	_LS = EntityManager::CreateEntityQuery();
	EntityManager::SetEntityQueryAllFilters<LocalToParent, LocalScale>(_LS, LocalToParent(), LocalScale());
	EntityManager::SetEntityQueryNoneFilters<LocalPosition, LocalRotation>(_LS, LocalPosition(), LocalRotation());

	_P = EntityManager::CreateEntityQuery();
	EntityManager::SetEntityQueryAllFilters<LocalToWorld, Translation>(_P, LocalToWorld(), Translation());
	EntityManager::SetEntityQueryNoneFilters<Rotation, Scale>(_P, Rotation(), Scale());
	_PR = EntityManager::CreateEntityQuery();
	EntityManager::SetEntityQueryAllFilters<LocalToWorld, Translation, Rotation>(_PR, LocalToWorld(), Translation(), Rotation());
	EntityManager::SetEntityQueryNoneFilters<Scale>(_PR, Scale());
	_PS = EntityManager::CreateEntityQuery();
	EntityManager::SetEntityQueryAllFilters<LocalToWorld, Translation, Scale>(_PS, LocalToWorld(), Translation(), Scale());
	EntityManager::SetEntityQueryNoneFilters<Rotation>(_PS, Rotation());
	_PRS = EntityManager::CreateEntityQuery();
	EntityManager::SetEntityQueryAllFilters<LocalToWorld, Translation, Rotation, Scale>(_PRS, LocalToWorld(), Translation(), Rotation(), Scale());
	_R = EntityManager::CreateEntityQuery();
	EntityManager::SetEntityQueryAllFilters<LocalToWorld, Rotation>(_R, LocalToWorld(), Rotation());
	EntityManager::SetEntityQueryNoneFilters<Translation, Scale>(_R, Translation(), Scale());
	_RS = EntityManager::CreateEntityQuery();
	EntityManager::SetEntityQueryAllFilters<LocalToWorld, Rotation, Scale>(_RS, LocalToWorld(), Rotation(), Scale());
	EntityManager::SetEntityQueryNoneFilters<Translation>(_RS, Translation());
	_S = EntityManager::CreateEntityQuery();
	EntityManager::SetEntityQueryAllFilters<LocalToWorld, Scale>(_S, LocalToWorld(), Scale());
	EntityManager::SetEntityQueryNoneFilters<Translation, Rotation>(_S, Translation(), Rotation());

	Enable();
}

void UniEngine::TransformSystem::OnDestroy()
{
	Disable();
}



void UniEngine::TransformSystem::Update()
{
	EntityManager::ForEach<LocalToParent, LocalPosition>(_LP, [](int i, LocalToParent* ltp, LocalPosition* lp) {
		ltp->value = glm::translate(glm::mat4(1.0f), lp->value) * glm::identity<glm::mat4>();
		});
	EntityManager::ForEach<LocalToParent, LocalPosition, LocalRotation>(_LPR, [](int i, LocalToParent* ltp, LocalPosition* lp, LocalRotation* lr) {
		ltp->value = glm::translate(glm::mat4(1.0f), lp->value) * glm::mat4_cast(lr->value) * glm::identity<glm::mat4>();
		});
	EntityManager::ForEach<LocalToParent, LocalPosition, LocalScale>(_LPS, [](int i, LocalToParent* ltp, LocalPosition* lp, LocalScale* ls) {
		ltp->value = glm::translate(glm::mat4(1.0f), lp->value) * glm::identity<glm::mat4>() * glm::scale(ls->value);
		});
	EntityManager::ForEach<LocalToParent, LocalPosition, LocalRotation, LocalScale>(_LPRS, [](int i, LocalToParent* ltp, LocalPosition* lp, LocalRotation* lr, LocalScale* ls) {
		ltp->value = glm::translate(glm::mat4(1.0f), lp->value) * glm::mat4_cast(lr->value) * glm::scale(ls->value);
		});
	EntityManager::ForEach<LocalToParent, LocalRotation>(_LR, [](int i, LocalToParent* ltp, LocalRotation* lr) {
		ltp->value = glm::mat4_cast(lr->value) * glm::identity<glm::mat4>();
		});
	EntityManager::ForEach<LocalToParent, LocalRotation, LocalScale>(_LRS, [](int i, LocalToParent* ltp, LocalRotation* lr, LocalScale* ls) {
		ltp->value = glm::mat4_cast(lr->value) * glm::identity<glm::mat4>() * glm::scale(ls->value);
		});
	EntityManager::ForEach<LocalToParent, LocalScale>(_LS, [](int i, LocalToParent* ltp, LocalScale* ls) {
		ltp->value = glm::identity<glm::mat4>() * glm::scale(ls->value);
		});

	EntityManager::ForEach<LocalToWorld, Translation>(_P, [](int i, LocalToWorld* ltw, Translation* lp) {
		ltw->value = glm::translate(glm::mat4(1.0f), lp->value) * glm::identity<glm::mat4>();
		});
	EntityManager::ForEach<LocalToWorld, Translation, Rotation>(_PR, [](int i, LocalToWorld* ltw, Translation* lp, Rotation* lr) {
		ltw->value = glm::translate(glm::mat4(1.0f), lp->value) * glm::mat4_cast(lr->value) * glm::identity<glm::mat4>();
		});
	EntityManager::ForEach<LocalToWorld, Translation, Scale>(_PS, [](int i, LocalToWorld* ltw, Translation* lp, Scale* ls) {
		ltw->value = glm::translate(glm::mat4(1.0f), lp->value) * glm::identity<glm::mat4>() * glm::scale(ls->value);
		});
	EntityManager::ForEach<LocalToWorld, Translation, Rotation, Scale>(_PRS, [](int i, LocalToWorld* ltw, Translation* lp, Rotation* lr, Scale* ls) {
		ltw->value = glm::translate(glm::mat4(1.0f), lp->value) * glm::mat4_cast(lr->value) * glm::scale(ls->value);
		});
	EntityManager::ForEach<LocalToWorld, Rotation>(_R, [](int i, LocalToWorld* ltw, Rotation* lr) {
		ltw->value = glm::mat4_cast(lr->value) * glm::identity<glm::mat4>();
		});
	EntityManager::ForEach<LocalToWorld, Rotation, Scale>(_RS, [](int i, LocalToWorld* ltw, Rotation* lr, Scale* ls) {
		ltw->value = glm::identity<glm::mat4>() * glm::mat4_cast(lr->value) * glm::scale(ls->value);
		});
	EntityManager::ForEach<LocalToWorld, Scale>(_S, [](int i, LocalToWorld* ltw, Scale* ls) {
		ltw->value = glm::scale(ls->value) * glm::identity<glm::mat4>();
		});
}
