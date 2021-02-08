#include "pch.h"
#include "RigidBody.h"

#include "PhysicsSimulationManager.h"
#include "RenderManager.h"
#include "Transforms.h"
#include "UniEngine.h"

void UniEngine::RigidBody::RegisterCheck()
{
	if (_CurrentRegistered == false && GetOwner().IsValid() && GetOwner().IsEnabled() && IsEnabled()) {
		_CurrentRegistered = true;
		PhysicsSimulationManager::_PhysicsScene->addActor(*_RigidBody);
	}
	if(_CurrentRegistered == true && GetOwner().IsValid() && !(GetOwner().IsEnabled() && IsEnabled()))
	{
		_CurrentRegistered = false;
		PhysicsSimulationManager::_PhysicsScene->removeActor(*_RigidBody);
	}
}

UniEngine::RigidBody::RigidBody()
{
	_Material = PhysicsSimulationManager::_DefaultMaterial;
	_ShapeTransform = glm::translate(glm::vec3(0.0f)) * glm::mat4_cast(glm::quat(glm::vec3(0.0f))) * glm::scale(glm::vec3(1.0f));
	_MassCenter = PxVec3(0.0f);
	_DrawBounds = false;
	_IsStatic = false;
	PxTransform localTm(PxVec3(0, 0, 0));
	_RigidBody = PhysicsSimulationManager::_Physics->createRigidDynamic(PxTransform(localTm));
	_ShapeParam = glm::vec3(1.0f);
	_ShapeType = ShapeType::Box;
	
	UpdateShape();
	_Density = 10.0f;
	PxRigidBodyExt::updateMassAndInertia(*reinterpret_cast<PxRigidDynamic*>(_RigidBody), _Density);
	_CurrentRegistered = false;
	SetEnabled(true);
}

void UniEngine::RigidBody::SetShapeType(ShapeType type)
{
	if (Application::IsPlaying()) {
		Debug::Log("Failed! Pause game to reset!");
		return;
	}
	if(_ShapeType == type) return;
	_ShapeType = type;
	if (_CurrentRegistered)PhysicsSimulationManager::_PhysicsScene->removeActor(*_RigidBody);
	UpdateShape();
	if (!_IsStatic)PxRigidBodyExt::updateMassAndInertia(*reinterpret_cast<PxRigidDynamic*>(_RigidBody), _Density);
	if (_CurrentRegistered)PhysicsSimulationManager::_PhysicsScene->addActor(*_RigidBody);
}

void UniEngine::RigidBody::SetShapeParam(glm::vec3 value)
{
	if (Application::IsPlaying()) {
		Debug::Log("Failed! Pause game to reset!");
		return;
	}
	if(_ShapeParam == value) return;
	_ShapeParam = value;
	if (_CurrentRegistered)PhysicsSimulationManager::_PhysicsScene->removeActor(*_RigidBody);
	UpdateShape();
	if (!_IsStatic)PxRigidBodyExt::updateMassAndInertia(*reinterpret_cast<PxRigidDynamic*>(_RigidBody), _Density);
	if (_CurrentRegistered)PhysicsSimulationManager::_PhysicsScene->addActor(*_RigidBody);
}

void UniEngine::RigidBody::SetStatic(bool value)
{
	if (Application::IsPlaying()) {
		Debug::Log("Failed! Pause game to reset!");
		return;
	}
	if(_IsStatic == value) return;
	_IsStatic = value;
	if (_CurrentRegistered)PhysicsSimulationManager::_PhysicsScene->removeActor(*_RigidBody);
	UpdateBody();
	UpdateShape();
	if (!_IsStatic)PxRigidBodyExt::updateMassAndInertia(*reinterpret_cast<PxRigidDynamic*>(_RigidBody), _Density);
	if (_CurrentRegistered)PhysicsSimulationManager::_PhysicsScene->addActor(*_RigidBody);
}

void UniEngine::RigidBody::SetTransform(glm::mat4 value)
{
	if (Application::IsPlaying()) {
		Debug::Log("Failed! Pause game to reset!");
		return;
	}
	GlobalTransform ltw;
	ltw.Value = value;
	ltw.SetScale(glm::vec3(1.0f));
	_ShapeTransform = ltw.Value;
	if (_CurrentRegistered)PhysicsSimulationManager::_PhysicsScene->removeActor(*_RigidBody);
	UpdateShape();
	if (!_IsStatic)PxRigidBodyExt::updateMassAndInertia(*reinterpret_cast<PxRigidDynamic*>(_RigidBody), _Density);
	if (_CurrentRegistered)PhysicsSimulationManager::_PhysicsScene->addActor(*_RigidBody);
}

void UniEngine::RigidBody::SetDensity(float value)
{
	if (Application::IsPlaying()) {
		Debug::Log("Failed! Pause game to reset!");
		return;
	}
	if(_Density == value) return;
	_Density = value;
	if (_Density < 0.0001f) _Density = 0.0001f;
	if (_CurrentRegistered)PhysicsSimulationManager::_PhysicsScene->removeActor(*_RigidBody);
	if (!_IsStatic)PxRigidBodyExt::updateMassAndInertia(*reinterpret_cast<PxRigidDynamic*>(_RigidBody), _Density);
	if (_CurrentRegistered)PhysicsSimulationManager::_PhysicsScene->addActor(*_RigidBody);
}

UniEngine::RigidBody::~RigidBody()
{
	if (_RigidBody) {
		_RigidBody->release();
	}
	if (_Material && _Material != PhysicsSimulationManager::_DefaultMaterial) {
		_Material->release();
	}
	if(_Shape)
	{
		_Shape->release();
	}
}

void UniEngine::RigidBody::SetMaterial(PxMaterial* value)
{
	if(value && _Material != value)
	{
		if (_Material && _Material != PhysicsSimulationManager::_DefaultMaterial) {
			_Material->release();
		}
		_Material = value;
		if (_CurrentRegistered)PhysicsSimulationManager::_PhysicsScene->removeActor(*_RigidBody);
		UpdateShape();
		if (!_IsStatic)PxRigidBodyExt::updateMassAndInertia(*reinterpret_cast<PxRigidDynamic*>(_RigidBody), _Density);
		if (_CurrentRegistered)PhysicsSimulationManager::_PhysicsScene->addActor(*_RigidBody);
	}
}

void UniEngine::RigidBody::UpdateShape()
{
	if (_Shape != nullptr) _Shape->release();
	switch (_ShapeType)
	{
	case ShapeType::Sphere:
		_Shape = PhysicsSimulationManager::_Physics->createShape(PxSphereGeometry(_ShapeParam.x), *_Material);
		break;
	case ShapeType::Box:
		_Shape = PhysicsSimulationManager::_Physics->createShape(PxBoxGeometry(_ShapeParam.x, _ShapeParam.y, _ShapeParam.z), *_Material);
		break;
	case ShapeType::Capsule:
		_Shape = PhysicsSimulationManager::_Physics->createShape(PxCapsuleGeometry(_ShapeParam.x, _ShapeParam.y), *_Material);
		break;
	}
	_RigidBody->attachShape(*_Shape);
}

void UniEngine::RigidBody::UpdateBody()
{
	if (_RigidBody) _RigidBody->release();
	PxTransform localTm(PxVec3(0, 0, 0));
	if(_IsStatic) _RigidBody = PhysicsSimulationManager::_Physics->createRigidStatic(PxTransform(localTm));
	else _RigidBody = PhysicsSimulationManager::_Physics->createRigidDynamic(PxTransform(localTm));
}

void UniEngine::RigidBody::Init()
{
	RegisterCheck();
}

void UniEngine::RigidBody::OnEntityDisable()
{
	_CurrentRegistered = false;
	PhysicsSimulationManager::_PhysicsScene->removeActor(*_RigidBody);
}
void UniEngine::RigidBody::OnEntityEnable()
{
	RegisterCheck();
}
void UniEngine::RigidBody::OnDisable()
{
	_CurrentRegistered = false;
	PhysicsSimulationManager::_PhysicsScene->removeActor(*_RigidBody);
}

void UniEngine::RigidBody::OnEnable()
{
	RegisterCheck();
}
static const char* RigidBodyShapeShape[]{ "Sphere", "Box", "Capsule" };
void UniEngine::RigidBody::OnGui()
{
	ImGui::Checkbox("Draw bounds", &_DrawBounds);
	ImGui::Spacing();
	ImGui::Separator();
	ImGui::Spacing();
	
	if(!_IsStatic)
	{
		PxRigidBody* rigidBody = static_cast<PxRigidBody*>(_RigidBody);
		if (Application::IsPlaying()) {
			_LinearVelocity = rigidBody->getLinearVelocity();
			_AngularVelocity = rigidBody->getAngularVelocity();
		}
		if (ImGui::DragFloat3("Angular V", &_AngularVelocity.x, 0.01f)){
			rigidBody->setAngularVelocity(_AngularVelocity);
		}
		if (ImGui::DragFloat3("Linear V", &_LinearVelocity.x, 0.01f)) {
			rigidBody->setLinearVelocity(_LinearVelocity);
		}
	}
	if(Application::IsPlaying())
	{
		ImGui::Text("Pause Engine to edit shape.");
	}
	else {
		bool statusChanged = false;
		bool staticChanged = false;
		bool savedVal = _IsStatic;
		ImGui::Checkbox("Static", &_IsStatic);
		if (_IsStatic != savedVal) {
			statusChanged = true;
			staticChanged = true;
		}
		ImGui::Combo("Shape", reinterpret_cast<int*>(&_ShapeType), RigidBodyShapeShape, IM_ARRAYSIZE(RigidBodyShapeShape));
		glm::vec3 scale;
		glm::vec3 trans;
		glm::quat rotation;
		glm::vec3 skew;
		glm::vec4 perspective;
		glm::decompose(_ShapeTransform, scale, rotation, trans, skew, perspective);
		skew = glm::degrees(glm::eulerAngles(rotation));
		bool shapeTransChanged = false;
		if (ImGui::DragFloat3("Center Position", &trans.x, 0.01f)) shapeTransChanged = true;
		if (ImGui::DragFloat3("Rotation", &skew.x, 0.01f)) shapeTransChanged = true;
		if (shapeTransChanged)_ShapeTransform = glm::translate(trans) * glm::mat4_cast(glm::quat(glm::radians(skew))) * glm::scale(glm::vec3(1.0f));

		auto ltw = GetOwner().GetComponentData<GlobalTransform>();
		ltw.SetScale(glm::vec3(1.0f));
		switch (_ShapeType)
		{
		case ShapeType::Sphere:
			if (ImGui::DragFloat("Radius", &_ShapeParam.x, 0.01f, 0.0001f)) statusChanged = true;
			if (_DrawBounds) RenderManager::DrawGizmoPoint(glm::vec4(0.0f, 0.0f, 1.0f, 0.5f), ltw.Value * (_ShapeTransform * glm::scale(glm::vec3(_ShapeParam.x * 2.0f))), 1);
			break;
		case ShapeType::Box:
			if (ImGui::Button("Apply mesh bound"))
			{
				statusChanged = true;
				auto& meshRenderer = GetOwner().GetPrivateComponent<MeshRenderer>();
				if (meshRenderer)
				{
					auto bound = meshRenderer->Mesh->GetBound();
					glm::vec3 scale = GetOwner().GetComponentData<GlobalTransform>().GetScale();
					_ShapeParam = bound.Size() * scale;
					_ShapeParam = glm::max(glm::vec3(0.01f), _ShapeParam);
				}
			}
			if (ImGui::DragFloat3("XYZ Size", &_ShapeParam.x, 0.01f, 0.0f)) statusChanged = true;
			if (_DrawBounds) RenderManager::DrawGizmoCube(glm::vec4(0.0f, 0.0f, 1.0f, 0.5f), ltw.Value * (_ShapeTransform * glm::scale(glm::vec3(_ShapeParam))), 1);
			break;
		case ShapeType::Capsule:
			if (ImGui::DragFloat2("R/HalfH", &_ShapeParam.x, 0.01f, 0.0001f)) statusChanged = true;
			if (_DrawBounds) RenderManager::DrawGizmoMesh(Default::Primitives::Cylinder.get(), glm::vec4(0.0f, 0.0f, 1.0f, 0.5f), ltw.Value * (_ShapeTransform * glm::scale(glm::vec3(_ShapeParam))), 1);
			break;
		}
		if (ImGui::DragFloat("Density", &_Density, 0.1f, 0.001f)) statusChanged = true;
		if (statusChanged) {
			if(_CurrentRegistered)PhysicsSimulationManager::_PhysicsScene->removeActor(*_RigidBody);
			if (staticChanged) UpdateBody();
			UpdateShape();
			if(!_IsStatic)PxRigidBodyExt::updateMassAndInertia(*reinterpret_cast<PxRigidDynamic*>(_RigidBody), _Density);
			if (_CurrentRegistered)PhysicsSimulationManager::_PhysicsScene->addActor(*_RigidBody);
		}
	}
}
