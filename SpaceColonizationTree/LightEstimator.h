#pragma once
#include "UniEngine.h"
#include "Tree.h"

using namespace UniEngine;
namespace SpaceColonizationTree {
	class LightSnapShot {
		GLTexture2D* _SnapShotTexture;
		GLPPBO* _PPBO;
		float* _SRC;
		float _Angle;
		float _Weight;
		float _Score;
		size_t _Resolution;
	public:
		GLTexture2D* SnapShotTexture() { return _SnapShotTexture; }
		GLPPBO* GetPixelBuffer() { return _PPBO; }
		float GetAngle() { return _Angle; };
		float* GetSRC() { return _SRC; }
		LightSnapShot(size_t resolution, float angle, float weight);
		float CalculateScore();
		~LightSnapShot();
	};

	class LightEstimator
	{
		RenderTarget* _RenderTarget;
		size_t _Resolution;
		std::vector<LightSnapShot*> _SnapShots;
		GLProgram* _SnapShotProgram;
		GLRenderBuffer* _DepthBuffer;
		float _LightEstimationScore;
	public:
		LightEstimator(size_t resolution);
		void TakeSnapShot(Tree* tree, float shotWidth = 5.0f, bool calculateScore = false);
		float CalculateScore();
	};

}