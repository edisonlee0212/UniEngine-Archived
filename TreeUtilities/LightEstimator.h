#pragma once
#include "TreeUtilitiesAPI.h"
using namespace UniEngine;
namespace TreeUtilities {
	class LightSnapShot {
		GLTexture2D* _SnapShotTexture;
		GLPPBO* _PPBO;
		float* _SRC;
		glm::vec3 _Direction;
		float _CenterDistance;
		float _Width;
		float _Weight;
		float _Score;
		size_t _Resolution;
	public:
		GLTexture2D* SnapShotTexture() { return _SnapShotTexture; }
		GLPPBO* GetPixelBuffer() { return _PPBO; }
		float* GetSRC() { return _SRC; }
		LightSnapShot(size_t resolution, glm::vec3 direction, float centerDistance, float weight);
		glm::mat4 GetViewMatrix(glm::vec3& centerPosition);
		glm::vec3 GetDirection();
		float CalculateScore();
		float CenterDistance();
		float Width();
		float GetBlockerDistance(glm::vec3& centerPosition, glm::vec3& estimatePosition);
		~LightSnapShot();
	};

	class TREEUTILITIES_API LightEstimator
	{
		RenderTarget* _RenderTarget = nullptr;
		size_t _Resolution = 2048;
		std::vector<LightSnapShot*> _SnapShots;
		GLProgram* _SnapShotProgram = nullptr;
		GLRenderBuffer* _DepthBuffer = nullptr;
		float _LightEstimationScore = 0;
		friend class TreeSystem;
		float _SnapShotWidth = 100.0f;
		float _CenterDistance = 200.0f;
	public:
		LightEstimator(size_t resolution = 2048, float centerDistance = 200.0f);
		void ResetCenterDistance(float distance);
		void ResetSnapShotWidth(float width);
		void PushSnapShot(glm::vec3 direction, float weight);
		void Clear();
		void TakeSnapShot(Entity treeEntity, bool calculateScore = false);
		void DrawSnapShots(Camera* camera);
		float CalculateScore();
		float GetScore();
		std::vector<LightSnapShot*>* GetSnapShots();
	};

}