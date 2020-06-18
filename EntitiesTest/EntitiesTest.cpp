// EntitiesTest.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "Entities.h"
#include "EntityManager.h"
#include "UniEngine.h"
#include <iostream>
using namespace UniEngine;
int main()
{
    Engine* engine = new Engine();
    engine->Start();
    World* world = engine->GetWorld();
    Entities::EntityManager::SetWorld(world);
    Entities::EntityArchetype a = Entities::EntityManager::CreateEntityArchetype<Position, Rotation>(Position(), Rotation());
    std::cout << a.Index << "\n";
    Entities::EntityArchetype b = Entities::EntityManager::CreateEntityArchetype<Position, Rotation>(Position(), Rotation());
    std::cout << b.Index << "\n";
    Entities::EntityArchetype c = Entities::EntityManager::CreateEntityArchetype<Position, Rotation>(Position(), Rotation());
    std::cout << c.Index << "\n";
    Entities::Entity e = Entities::EntityManager::CreateEntity(a);
    
    Entities::EntityManager::DeleteEntity(e);
    Entities::EntityManager::DeleteEntity(e);

    e = Entities::EntityManager::CreateEntity(a);
    e = Entities::EntityManager::CreateEntity(a);

    Entities::EntityArchetype a1 = Entities::EntityManager::CreateEntityArchetype<Position, Rotation, LocalPosition>(Position(), Rotation(), LocalPosition());
    e = Entities::EntityManager::CreateEntity(a1);
    Entities::EntityManager::DeleteEntity(e);
    e = Entities::EntityManager::CreateEntity(a1);
    e = Entities::EntityManager::CreateEntity(a);
    
    Position pos;
    pos.value = glm::vec3(0.0f, 0.1f, 0.5f);
    Rotation rot;
    rot.value = glm::quat(1, 2, 3, 4);
    Entities::EntityManager::SetComponentData<Position>(e, pos);
    Entities::EntityManager::SetComponentData<Rotation>(e, rot);
    pos = Entities::EntityManager::GetComponentData<Position>(e);
    rot = Entities::EntityManager::GetComponentData<Rotation>(e);
    Debug::Log("Finished");
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
