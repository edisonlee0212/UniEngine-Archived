#include "pch.h"
#include "TransformSystem.h"
using namespace UniEngine;

UniEngine::TransformSystem::TransformSystem()
{

}

void UniEngine::TransformSystem::OnCreate()
{
	_LP = EntityManager::CreateEntityQuery();
	EntityManager::SetEntityQueryAllFilters(_LP, LocalToParent(), LocalTranslation());
	EntityManager::SetEntityQueryNoneFilters(_LP, LocalRotation(), LocalScale());
	_LPR = EntityManager::CreateEntityQuery();
	EntityManager::SetEntityQueryAllFilters(_LPR, LocalToParent(), LocalTranslation(), LocalRotation());
	EntityManager::SetEntityQueryNoneFilters(_LPR, LocalScale());
	_LPS = EntityManager::CreateEntityQuery();
	EntityManager::SetEntityQueryAllFilters(_LPS, LocalToParent(), LocalTranslation(), LocalScale());
	EntityManager::SetEntityQueryNoneFilters(_LPS, LocalRotation());
	_LPRS = EntityManager::CreateEntityQuery();
	EntityManager::SetEntityQueryAllFilters(_LPRS, LocalToParent(), LocalTranslation(), LocalRotation(), LocalScale());
	_LR = EntityManager::CreateEntityQuery();
	EntityManager::SetEntityQueryAllFilters(_LR, LocalToParent(), LocalRotation());
	EntityManager::SetEntityQueryNoneFilters(_LR, LocalTranslation(), LocalScale());
	_LRS = EntityManager::CreateEntityQuery();
	EntityManager::SetEntityQueryAllFilters(_LRS, LocalToParent(), LocalRotation(), LocalScale());
	EntityManager::SetEntityQueryNoneFilters(_LRS, LocalTranslation());
	_LS = EntityManager::CreateEntityQuery();
	EntityManager::SetEntityQueryAllFilters(_LS, LocalToParent(), LocalScale());
	EntityManager::SetEntityQueryNoneFilters(_LS, LocalTranslation(), LocalRotation());

	_P = EntityManager::CreateEntityQuery();
	EntityManager::SetEntityQueryAllFilters(_P, LocalToWorld(), Translation());
	EntityManager::SetEntityQueryNoneFilters(_P, Rotation(), Scale());
	_PR = EntityManager::CreateEntityQuery();
	EntityManager::SetEntityQueryAllFilters(_PR, LocalToWorld(), Translation(), Rotation());
	EntityManager::SetEntityQueryNoneFilters(_PR, Scale());
	_PS = EntityManager::CreateEntityQuery();
	EntityManager::SetEntityQueryAllFilters(_PS, LocalToWorld(), Translation(), Scale());
	EntityManager::SetEntityQueryNoneFilters(_PS, Rotation());
	_PRS = EntityManager::CreateEntityQuery();
	EntityManager::SetEntityQueryAllFilters(_PRS, LocalToWorld(), Translation(), Rotation(), Scale());
	_R = EntityManager::CreateEntityQuery();
	EntityManager::SetEntityQueryAllFilters(_R, LocalToWorld(), Rotation());
	EntityManager::SetEntityQueryNoneFilters(_R, Translation(), Scale());
	_RS = EntityManager::CreateEntityQuery();
	EntityManager::SetEntityQueryAllFilters(_RS, LocalToWorld(), Rotation(), Scale());
	EntityManager::SetEntityQueryNoneFilters(_RS, Translation());
	_S = EntityManager::CreateEntityQuery();
	EntityManager::SetEntityQueryAllFilters(_S, LocalToWorld(), Scale());
	EntityManager::SetEntityQueryNoneFilters(_S, Translation(), Rotation());

	Enable();
}

void UniEngine::TransformSystem::OnDestroy()
{
	Disable();
}



void UniEngine::TransformSystem::Update()
{
	EntityManager::ForEach<LocalToParent, LocalTranslation>(_LP, [](int i, LocalToParent* ltp, LocalTranslation* lp) {
		ltp->value = glm::translate(glm::mat4(1.0f), lp->value) * glm::identity<glm::mat4>();
		});
	EntityManager::ForEach<LocalToParent, LocalTranslation, LocalRotation>(_LPR, [](int i, LocalToParent* ltp, LocalTranslation* lp, LocalRotation* lr) {
		ltp->value = glm::translate(glm::mat4(1.0f), lp->value) * glm::mat4_cast(lr->value) * glm::identity<glm::mat4>();
		});
	EntityManager::ForEach<LocalToParent, LocalTranslation, LocalScale>(_LPS, [](int i, LocalToParent* ltp, LocalTranslation* lp, LocalScale* ls) {
		ltp->value = glm::translate(glm::mat4(1.0f), lp->value) * glm::identity<glm::mat4>() * glm::scale(ls->value);
		});
	EntityManager::ForEach<LocalToParent, LocalTranslation, LocalRotation, LocalScale>(_LPRS, [](int i, LocalToParent* ltp, LocalTranslation* lp, LocalRotation* lr, LocalScale* ls) {
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
