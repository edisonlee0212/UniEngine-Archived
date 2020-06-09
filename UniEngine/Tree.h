#pragma once
#include "Misc.h"
#include "Branch.h"
#include "Envelope.h"
namespace SCTree {
	class Tree
	{
	public:
		Branch* _Root;
		std::vector<Branch*> _GrowingBranches;
		bool _NeedsToGrow, _MeshGenerated, _OrganGenerated;
		int _MaxGrowIteration;
		glm::vec3 _Position;
		Mesh* _Mesh;
		std::vector<glm::mat4> _PointMatrices;
		std::vector<glm::mat4> _LeafList;
		Tree(glm::vec3 position, Material* pointMaterial, Material* meshMaterial, Material* organMaterial);
		
		void Draw(Camera* camera, Material* pointMaterial, glm::vec3 scale, bool drawOrgan = true);

		~Tree();

		void GrowTrunk(float growDist, float attractionDist, Envelope* envelope, glm::vec3 tropism);

		void Grow(float growDist, float attractionDist, float removeDist, Envelope* envelope, glm::vec3 tropism = glm::vec3(0.0f),
			float distDec = 0.015f, float minDist = 0.01f, float decimationDistChild = 0.02f, float decimationDistParent = 0.02f);

		void CalculateMesh(int resolution = 4, int triangleLimit = 8192);
	private:
		inline void CalculateRadius();

		inline void CollectPoints();

		inline void NodeRelocation();

		inline void NodeSubdivision();

		inline void GenerateOrgan();
	};
}