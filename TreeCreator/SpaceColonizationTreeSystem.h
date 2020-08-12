#pragma once
#include "UniEngine.h"
#include "TreeManager.h"
#include "Envelope.h"
using namespace UniEngine;
using namespace TreeUtilities;
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
    BudSystem* _BudSystem;

    EntityQuery _BudQuery;
    EntityQuery _LeafQuery;
    EntityQuery _TreeQuery;

    EntityArchetype _AttractionPointArchetype;
    EntityQuery _AttractionPointQuery;

    Material* _AttractionPointMaterial;
    Envelope _Envelope;
    int _SelectedEnvelopeType;
    unsigned _AllTreesToGrowIteration;
    unsigned _AttractionPointMaxIndex;

    bool _IterationFinishMark;
#pragma region Popup
    bool _NewTreeMenuOpen;
    glm::vec3 _NewTreePosition;
    glm::vec3 _NewTreeBudColor;
    glm::vec3 _NewTreeConnectionColor;
#pragma endregion

    
    int _PushAttractionPoints;
    void AddAttractionPoint(Translation translation);
    void GrowAllTrees(float attractionDistance = 25.0f, float removeDistance = 5.0f, float growDistance = 1.0f);
    void GrowTree(Entity treeEntity, float attractionDistance = 25.0f, float removeDistance = 5.0f, float growDistance = 1.0f);
    void DrawGUI();
public:
    void OnCreate();
    void OnDestroy();
    void Update();
    void FixedUpdate();
    void ResetEnvelope(float radius, float minHeight, float maxHeight);
    void ResetEnvelope(glm::vec3 spaceOffset, glm::vec3 spaceSize);
    void ResetEnvelopeType(EnvelopeType type);
    void PushAttractionPoints(size_t value);
    void PushGrowAllTreesIterations(size_t iteration);
    void PushGrowIterationToTree(Entity treeEntity, size_t iteration);
    Entity CreateTree(TreeColor color, glm::vec3 position, bool enabled = false);
    void ClearAttractionPoints();
    unsigned AllTreesToGrowIteration();
};

