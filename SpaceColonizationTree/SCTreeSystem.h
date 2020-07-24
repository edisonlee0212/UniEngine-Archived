#pragma once
#include "UniEngine.h"
#include "Envelope.h"
#include "Tree.h"
#include "LightEstimator.h"

using namespace UniEngine;
namespace SpaceColonizationTree {
	class SCTreeSystem :
		public SystemBase
	{
	public:
		void OnCreate();

		void BuildEnvelope();

		void BuildTree();

		void RemoveTree();

		void RemoveEnvelope();

		void OnDestroy();

		void Update();

		void FixedUpdate();
	private:
#pragma region Tree Generation
		Material* _EnvelopePointMaterial;
		Texture2D* _EnvelopeTexture;
		Material* _TreePointMaterial;
		Texture2D* _TreePointTexture;
		Material* _TreeMeshMaterial;
		Texture2D* _TreeMeshTexture;
		Material* _TreeLeafMaterial;
		Texture2D* _TreeLeafTexture;

		int _PointsCount;
		Entity _TreeEntity;
		InstancedMeshMaterialComponent* _TreeLeaves;
		MeshMaterialComponent* _TreeMesh;
		Envelope* _Envelope;
		int _SelectedEnvelopeType;
		float _GrowDist, _AttractDitsMult, _RemoveDistMult, _AttractDist, _RemoveDist;
		int _Iteration;
		Tree* _Tree;
		float _EnvelopeRadius, _MinHeight, _MaxHeight;
		bool _DrawOrgan;
		float _TreeSize;
		void EnvelopeGUIMenu();
		void TreeGUIMenu();
#pragma endregion

#pragma region Light Estimation
		LightEstimator* _LightEstimator;
#pragma endregion


		
	};
}