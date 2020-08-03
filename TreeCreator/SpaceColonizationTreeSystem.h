#pragma once
#include "UniEngine.h"
#include "TreeBudSystem.h"
#include "Envelope.h"
using namespace UniEngine;
using namespace TreeCreator;
struct AttractionPointIndex {
    unsigned Value;
    AttractionPointIndex() { Value = 0; }
    AttractionPointIndex(unsigned value) {
        Value = value;
    }
};

struct AttractionPointCurrentStatus {
    bool remove;
    unsigned budEntityIndex;
    float distance;
    glm::vec3 growDirDelta;
};

class SpaceColonizationTreeSystem :
    public SystemBase
{
    TreeBudSystem* _TreeBudSystem;
    EntityArchetype _BudArchetype;
    EntityArchetype _LeafArchetype;
    EntityArchetype _TreeArchetype;
    EntityQuery _BudQuery;
    EntityQuery _LeafQuery;
    EntityQuery _TreeQuery;

    EntityArchetype _AttractionPointArchetype;
    EntityQuery _AttractionPointQuery;

    Material* _AttractionPointMaterial;

    std::vector<Entity> _Trees;
    Envelope _Envelope;
    unsigned _ToGrowIteration;
    unsigned _AttractionPointMaxIndex;
    void AddAttractionPoint(Translation translation);
    void Grow();
public:
    void OnCreate();
    void OnDestroy();
    void Update();
    void FixedUpdate();
    void ResetEnvelope(float radius, float minHeight, float maxHeight);
    void ResetEnvelope(glm::vec3 spaceOffset, glm::vec3 spaceSize);
    void PushAttractionPoints(unsigned value);
    void PushGrowIterations(unsigned iteration);
};

