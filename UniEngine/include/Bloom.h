#pragma once
#include "Core.h"
#include "UniEngineAPI.h"
#include "PostProcessing.h"
#include "Bezier.h"
namespace UniEngine
{
	class UNIENGINE_API Bloom : public PostProcessingLayer
	{
		
		std::unique_ptr<GLTexture2D> m_result;
		std::unique_ptr<GLTexture2D> m_brightColor;
		std::unique_ptr<GLTexture2D> m_flatColor;
		std::unique_ptr<GLProgram> m_separateProgram;
		std::unique_ptr<GLProgram> m_filterProgram;
		std::unique_ptr<GLProgram> m_combineProgram;
	public:
		float m_intensity = 0.02f;
		float m_threshold = 1.0f;
		float m_clamp = 0.0f;
		int m_diffusion = 16;
		BezierCubic2D m_bezierGraph;
		void Init() override;
		void ResizeResolution(int x, int y) override;
		void Process(std::unique_ptr<CameraComponent>& cameraComponent, RenderTarget& renderTarget) const override;
		void OnGui(std::unique_ptr<CameraComponent>& cameraComponent) override;
	};
}