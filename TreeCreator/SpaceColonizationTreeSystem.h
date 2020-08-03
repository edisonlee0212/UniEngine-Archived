#pragma once
#include "UniEngine.h"
#include "TreeBudSystem.h"
using namespace UniEngine;
using namespace TreeCreator;
struct AttractionPointIndex {
    unsigned Value;
    AttractionPointIndex() { Value = 0; }
    AttractionPointIndex(unsigned value) {
        Value = value;
    }
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

    unsigned _AttractionPointMaxIndex;
    void AddAttractionPoint(Translation translation);
    void Grow();
public:
    void OnCreate();
    void OnDestroy();
    void Update();
    void FixedUpdate();
};

