#include "pch.h"
#include "PhysicsSimulationManager.h"
#include "RigidBody.h"
#include "Transforms.h"
#include "UniEngine.h"
using namespace physx;

PxDefaultAllocator		UniEngine::PhysicsSimulationManager::_Allocator;
PxDefaultErrorCallback	UniEngine::PhysicsSimulationManager::_ErrorCallback;
PxFoundation* UniEngine::PhysicsSimulationManager::_PhysicsFoundation = NULL;
PxPhysics* UniEngine::PhysicsSimulationManager::_Physics = NULL;
PxDefaultCpuDispatcher* UniEngine::PhysicsSimulationManager::_Dispatcher = NULL;
PxScene* UniEngine::PhysicsSimulationManager::_PhysicsScene = NULL;
PxPvd* UniEngine::PhysicsSimulationManager::_PhysVisDebugger = NULL;

PxMaterial* UniEngine::PhysicsSimulationManager::_DefaultMaterial = NULL;
PxReal UniEngine::PhysicsSimulationManager::stackZ = 10.0f;
bool UniEngine::PhysicsSimulationManager::Enabled = true;
void UniEngine::PhysicsSimulationManager::Init()
{
	_PhysicsFoundation = PxCreateFoundation(PX_PHYSICS_VERSION, _Allocator, _ErrorCallback);

	_PhysVisDebugger = PxCreatePvd(*_PhysicsFoundation);
	PxPvdTransport* transport = PxDefaultPvdSocketTransportCreate("127.0.0.1", 5425, 10);
	_PhysVisDebugger->connect(*transport, PxPvdInstrumentationFlag::eALL);

	_Physics = PxCreatePhysics(PX_PHYSICS_VERSION, *_PhysicsFoundation, PxTolerancesScale(), true, _PhysVisDebugger);

	PxSceneDesc sceneDesc(_Physics->getTolerancesScale());
	sceneDesc.gravity = PxVec3(0.0f, -9.81f, 0.0f);
	_Dispatcher = PxDefaultCpuDispatcherCreate(_ThreadPool->Size());
	sceneDesc.cpuDispatcher = _Dispatcher;
	sceneDesc.filterShader = PxDefaultSimulationFilterShader;
	_PhysicsScene = _Physics->createScene(sceneDesc);

	PxPvdSceneClient* pvdClient = _PhysicsScene->getScenePvdClient();
	if (pvdClient)
	{
		pvdClient->setScenePvdFlag(PxPvdSceneFlag::eTRANSMIT_CONSTRAINTS, true);
		pvdClient->setScenePvdFlag(PxPvdSceneFlag::eTRANSMIT_CONTACTS, true);
		pvdClient->setScenePvdFlag(PxPvdSceneFlag::eTRANSMIT_SCENEQUERIES, true);
	}
	_DefaultMaterial = _Physics->createMaterial(0.5f, 0.5f, 0.6f);
}

void UniEngine::PhysicsSimulationManager::Destroy()
{
	PX_RELEASE(_PhysicsScene);
	PX_RELEASE(_Dispatcher);
	PX_RELEASE(_Physics);
	if (_PhysVisDebugger)
	{
		PxPvdTransport* transport = _PhysVisDebugger->getTransport();
		_PhysVisDebugger->release();	_PhysVisDebugger = NULL;
		PX_RELEASE(transport);
	}
	PX_RELEASE(_PhysicsFoundation);
}

void UniEngine::PhysicsSimulationManager::UploadTransforms()
{
#pragma region Send transform to physX
	const std::vector<Entity>* rigidBodyEntities = EntityManager::GetPrivateComponentOwnersList<RigidBody>();
	if (rigidBodyEntities != nullptr)
	{
		for (auto rigidBodyEntity : *rigidBodyEntities) {
			auto& rigidBody = rigidBodyEntity.GetPrivateComponent<RigidBody>();
			if (rigidBody->IsEnabled()) {
				auto temp = rigidBodyEntity.GetComponentData<GlobalTransform>();
				temp.SetScale(glm::vec3(1.0f));
				auto ltw = temp.Value * rigidBody->_ShapeTransform;
				PxMat44 matrix = *(PxMat44*)(void*)&ltw;
				rigidBody->_RigidBody->setGlobalPose(PxTransform(matrix));
			}
		}
	}
#pragma endregion
}

void UniEngine::PhysicsSimulationManager::Simulate(float time)
{

	const std::vector<Entity>* rigidBodyEntities = EntityManager::GetPrivateComponentOwnersList<RigidBody>();
#pragma region Get transforms from physX
	if (rigidBodyEntities)
	{
		std::vector<std::shared_future<void>> futures;
		auto& list = rigidBodyEntities;
		auto threadSize = _ThreadPool->Size();
		size_t capacity = rigidBodyEntities->size() / threadSize;
		size_t reminder = rigidBodyEntities->size() % threadSize;
		for (size_t i = 0; i < threadSize; i++) {
			futures.push_back(_ThreadPool->Push([&list, i, capacity](int id)
				{
					for (size_t j = 0; j < capacity; j++)
					{
						size_t index = capacity * i + j;
						const auto& rigidBodyEntity = list->at(index);
						auto& rigidBody = rigidBodyEntity.GetPrivateComponent<RigidBody>();
						if (rigidBody->IsEnabled()) {
							PxTransform transform = rigidBody->_RigidBody->getGlobalPose();
							auto matrix = PxMat44(transform);
							GlobalTransform temp = *(GlobalTransform*)(void*)&matrix;
							temp.Value *= glm::inverse(rigidBody->_ShapeTransform);
							glm::vec3 scale;
							glm::vec3 pos;
							glm::quat rot;
							temp.GetTRS(pos, rot, scale);
							scale = rigidBodyEntity.GetComponentData<GlobalTransform>().GetScale();
							temp.SetValue(pos, rot, scale);
							Transform ltp;
							auto parentEntity = EntityManager::GetParent(rigidBodyEntity);
							const glm::mat4 pltw = parentEntity.IsNull() ? GlobalTransform().Value : parentEntity.GetComponentData<GlobalTransform>().Value;
							ltp.Value = glm::inverse(pltw) * temp.Value;
							rigidBodyEntity.SetComponentData(ltp);
						}
					}
				}
			).share());
		}
		for (size_t i = 0; i < reminder; i++) {
			size_t index = capacity * threadSize + i;
			const auto& rigidBodyEntity = list->at(index); auto& rigidBody = rigidBodyEntity.GetPrivateComponent<RigidBody>();
			if (rigidBody->IsEnabled()) {
				PxTransform transform = rigidBody->_RigidBody->getGlobalPose();
				auto matrix = PxMat44(transform);
				GlobalTransform temp = *(GlobalTransform*)(void*)&matrix;
				temp.Value *= glm::inverse(rigidBody->_ShapeTransform);
				glm::vec3 scale;
				glm::vec3 pos;
				glm::quat rot;
				temp.GetTRS(pos, rot, scale);
				scale = rigidBodyEntity.GetComponentData<GlobalTransform>().GetScale();
				temp.SetValue(pos, rot, scale);
				Transform ltp;
				auto parentEntity = EntityManager::GetParent(rigidBodyEntity);
				const glm::mat4 pltw = parentEntity.IsNull() ? GlobalTransform().Value : parentEntity.GetComponentData<GlobalTransform>().Value;
				ltp.Value = glm::inverse(pltw) * temp.Value;
				rigidBodyEntity.SetComponentData(ltp);
			}
		}
		for (const auto& i : futures) i.wait();
	}
#pragma endregion

	_PhysicsScene->simulate(time);
	_PhysicsScene->fetchResults(true);
}
