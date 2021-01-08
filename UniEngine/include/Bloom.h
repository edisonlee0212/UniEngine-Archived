#pragma once
#include "Core.h"
#include "UniEngineAPI.h"
#include "PostProcessing.h"
#include "Bezier.h"
namespace UniEngine
{
	class UNIENGINE_API Bloom : public PostProcessingLayer
	{
		
		std::unique_ptr<GLTexture2D> _Result;
		std::unique_ptr<GLTexture2D> _BrightColor;
		std::unique_ptr<GLTexture2D> _FlatColor;
		std::unique_ptr<GLProgram> _SeparateProgram;
		std::unique_ptr<GLProgram> _FilterProgram;
		std::unique_ptr<GLProgram> _CombineProgram;
	public:
		float Intensity = 0.02f;
		float Threshold = 1.0f;
		float Clamp = 0.0f;
		int Diffusion = 16;
		Bezier2D BezierGraph;
		void Init() override;
		void ResizeResolution(int x, int y) override;
		void Process(std::unique_ptr<CameraComponent>& cameraComponent, RenderTarget& renderTarget) const override;
		void OnGui(std::unique_ptr<CameraComponent>& cameraComponent) override;
	};
}