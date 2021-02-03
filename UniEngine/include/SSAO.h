#pragma once
#include "Bezier.h"
#include "Core.h"
#include "UniEngineAPI.h"
#include "PostProcessing.h"

namespace UniEngine
{
	class UNIENGINE_API SSAO : public PostProcessingLayer
	{
		std::unique_ptr<GLTexture2D> _OriginalColor;
		std::unique_ptr<GLTexture2D> _Position;
		std::unique_ptr<GLTexture2D> _SSAOPosition;
		std::unique_ptr<GLTexture2D> _SSAOBlur;
		std::unique_ptr<GLProgram> _PositionReconstructProgram;
		std::unique_ptr<GLProgram> _GeometryProgram;
		std::unique_ptr<GLProgram> _BlurProgram;
		std::unique_ptr<GLProgram> _CombineProgram;
	public:
		float Intensity = 0.07f;
		int Diffusion = 16;
		float BlurScale = 0.25f;
		BezierCubic2D Graph;
		float SSAOKernelRadius = 0.1f;
		float SSAOKernelBias = 0.03f;
		float SSAOScale = 0.25f;
		int SSAOSampleSize = 32;
		
		void Init() override;
		void ResizeResolution(int x, int y) override;
		void Process(std::unique_ptr<CameraComponent>& cameraComponent, RenderTarget& renderTarget) const override;
		void OnGui(std::unique_ptr<CameraComponent>& cameraComponent) override;
	};
}