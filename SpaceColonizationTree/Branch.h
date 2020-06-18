#pragma once
#include "UniEngine.h"
#include "RingMesh.h"
#include "UniEngine.h"
#include "BezierCurve.h"
using namespace UniEngine;
namespace SpaceColonizationTree {
	class Branch
	{
	public:
		glm::vec3 position;
		glm::vec3 growDir;
		int growIteration;
		float radius;
		Branch* parent;
		std::vector<Branch*> mChildren;
		glm::mat4 transform;
		bool hasLeaves;
		bool isTrunk;
		std::vector<RingMesh> mRings;
		bool isSubdivided;
		Branch(glm::vec3 position, Branch* parent, bool isTrunk, int growIteration, float initialRadius = 0.01f);

		~Branch();

		void CollectPoint(std::vector<glm::mat4>* matrices);

		float CalculateRadius(int _MaxGrowIteration, float n = 3.0f, float minRadius = 0.01f);

		Branch* Grow(float growDist, bool growTrunk, glm::vec3 tropism, float distDec = 0.015f, float minDist = 0.1f, float decimationDistChild = 0.05f, float decimationDistParent = 0.05f);

		void Relocation();

		void Subdivision(glm::vec3 fromPos, glm::vec3 fromDir, float fromRadius);

		void CalculateMesh(glm::vec3 rootPos, std::vector<Vertex>* vertices, int resolution = 32);

		void GenerateOrgan(std::vector<glm::mat4>* matrices, int _MaxGrowIteration, int maxLeaf = 5);
	};
}