// EntitiesTest.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "Entities.h"
#include "UniEngine.h"
#include <iostream>
using namespace UniEngine;
using namespace UniEngine::Entities;
int main()
{
    std::cout << "Hello World!\n";
    EntityManager em = EntityManager();
    EntityArchetype a = em.CreateEntityArchetype<Position, Rotation>(Position(), Rotation());

    Entities::Entity e = em.CreateEntity(a);

    em.DeleteEntity(e);
    em.DeleteEntity(e);

    e = em.CreateEntity(a);
    e = em.CreateEntity(a);

    EntityArchetype a1 = em.CreateEntityArchetype<Position, Rotation, LocalPosition>(Position(), Rotation(), LocalPosition());
    e = em.CreateEntity(a1);
    em.DeleteEntity(e);
    e = em.CreateEntity(a1);
    e = em.CreateEntity(a);
    
    Position pos;
    pos.value = glm::vec3(0.0f, 0.1f, 0.5f);
    Rotation rot;
    rot.value = glm::quat(1, 2, 3, 4);
    em.SetComponentData<Position>(e, pos);
    em.SetComponentData<Rotation>(e, rot);
    pos = em.GetComponentData<Position>(e);
    rot = em.GetComponentData<Rotation>(e);
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
