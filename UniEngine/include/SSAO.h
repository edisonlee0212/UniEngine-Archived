#pragma once
#include "Bezier.h"
#include "Core.h"
#include "UniEngineAPI.h"
#include "PostProcessing.h"

namespace UniEngine
{
	class UNIENGINE_API SSAO : public PostProcessingLayer
	{
		std::unique_ptr<GLTexture2D> m_originalColor;
		std::unique_ptr<GLTexture2D> m_position;
		std::unique_ptr<GLTexture2D> m_ssaoPosition;
		std::unique_ptr<GLTexture2D> m_ssaoBlur;
		std::unique_ptr<GLProgram> m_positionReconstructProgram;
		std::unique_ptr<GLProgram> m_geometryProgram;
		std::unique_ptr<GLProgram> m_blurProgram;
		std::unique_ptr<GLProgram> m_combineProgram;
	public:
		float m_intensity = 0.07f;
		int m_diffusion = 16;
		float m_blurScale = 0.25f;
		BezierCubic2D m_graph;
		float m_ssaoKernelRadius = 0.1f;
		float m_ssaoKernelBias = 0.03f;
		float m_ssaoScale = 0.25f;
		int m_ssaoSampleSize = 32;
		
		void Init() override;
		void ResizeResolution(int x, int y) override;
		void Process(std::unique_ptr<CameraComponent>& cameraComponent, RenderTarget& renderTarget) const override;
		void OnGui(std::unique_ptr<CameraComponent>& cameraComponent) override;
	};
}