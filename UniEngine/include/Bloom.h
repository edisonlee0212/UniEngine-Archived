#pragma once
#include "Core.h"
#include "UniEngineAPI.h"
#include "PostProcessing.h"
#include "Bezier.h"
namespace UniEngine
{
	class UNIENGINE_API Bloom : public PostProcessingLayer
	{
		float _Intensity = 0.02f;
		float _Threshold = 1.0f;
		float _Clamp = 0.0f;
		int _Diffusion = 16;
		Bezier2D _Bezier2D;
		std::unique_ptr<GLTexture2D> _Result;
		std::unique_ptr<GLTexture2D> _BrightColor;
		std::unique_ptr<GLTexture2D> _FlatColor;
		std::unique_ptr<GLProgram> _SeparateProgram;
		std::unique_ptr<GLProgram> _FilterProgram;
		std::unique_ptr<GLProgram> _CombineProgram;
	public:
		void Init() override;
		void ResizeResolution(int x, int y) override;
		void Process(std::unique_ptr<CameraComponent>& cameraComponent, RenderTarget& renderTarget) const override;
		void OnGui(std::unique_ptr<CameraComponent>& cameraComponent) override;
	};
}