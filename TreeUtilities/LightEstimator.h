#pragma once
#include "TreeUtilitiesAPI.h"
using namespace UniEngine;
namespace TreeUtilities {
	class TREEUTILITIES_API LightSnapShot {
		GLTexture2D* _SnapShotTexture;
		GLPPBO* _PPBO;
		float* _SRC;
		glm::vec3 _Direction;
		float _CenterDistance;
		float _Width;
		float _Weight;
		float _Score;
		size_t _Resolution;
		friend class LightEstimator;
		glm::vec3 _CenterPosition;
	public:
		GLTexture2D* SnapShotTexture() { return _SnapShotTexture; }
		GLPPBO* GetPixelBuffer() { return _PPBO; }
		float* GetSRC() { return _SRC; }
		LightSnapShot(size_t resolution, glm::vec3 centerPosition, glm::vec3 direction, float centerDistance, float width, float weight);
		glm::mat4 GetViewMatrix();
		glm::mat4 GetLightSpaceMatrix();
		glm::vec3 GetDirection();
		float CalculateScore();
		float CenterDistance();
		float Width();
		float Weight();
		float Resolution();

		float GetBlockerDistance(glm::vec3& position);
		unsigned GetEntityIndex(size_t x, size_t y);
		glm::vec3 GetDepth(size_t x, size_t y);
		~LightSnapShot();
	};

	class TREEUTILITIES_API LightEstimator
	{
		RenderTarget* _RenderTarget = nullptr;
		size_t _Resolution = 2048;
		std::vector<LightSnapShot*> _SnapShots;
		GLProgram* _SnapShotProgram = nullptr;
		
		RenderTarget* _BlurFilterRenderTarget = nullptr;
		GLProgram* _SnapShotVBlurProgram = nullptr;
		GLProgram* _SnapShotHBlurProgram = nullptr;
		GLTexture2D* _BlurFilter = nullptr;

		GLRenderBuffer* _DepthBuffer = nullptr;
		float _LightEstimationScore = 0;
		friend class TreeSystem;
		float _SnapShotWidth = 50.0f;
		float _CenterDistance = 200.0f;
		glm::vec3 _CenterPositon = glm::vec3(0.0f);
	public:
		glm::vec3 GetCenterPosition();
		LightEstimator(size_t resolution = 512, float centerDistance = 100.0f);
		void ResetCenterPosition(glm::vec3 position);
		void ResetCenterDistance(float distance);
		void ResetSnapShotWidth(float width);
		void PushSnapShot(glm::vec3 direction, float weight);
		void Clear();
		void TakeSnapShot(bool storeSnapShot, float budNodeSize = 1.0f);
		void DrawSnapShots(Camera* camera);
		float CalculateScore();
		std::vector<LightSnapShot*>* GetSnapShots();
	};

} 