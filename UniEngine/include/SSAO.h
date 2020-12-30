#pragma once
#include "Bezier.h"
#include "Core.h"
#include "UniEngineAPI.h"
#include "PostProcessing.h"

namespace UniEngine
{
	class UNIENGINE_API SSAO : public PostProcessingLayer
	{
		float _Intensity = 0.07f;
		int _Diffusion = 16;
		float _BlurScale = 0.25f;
		Bezier2D _Bezier2D;

		
		float _SSAOKernelRadius = 0.1f;
		float _SSAOKernelBias = 0.03f;
		float _SSAOScale = 0.25f;
		int _SSAOSampleSize = 32;

		std::unique_ptr<GLTexture2D> _OriginalColor;
		std::unique_ptr<GLTexture2D> _Position;
		std::unique_ptr<GLTexture2D> _SSAOPosition;
		std::unique_ptr<GLTexture2D> _SSAOBlur;
		std::unique_ptr<GLProgram> _PositionReconstructProgram;
		std::unique_ptr<GLProgram> _GeometryProgram;
		std::unique_ptr<GLProgram> _BlurProgram;
		std::unique_ptr<GLProgram> _CombineProgram;
	public:
		void Init() override;
		void ResizeResolution(int x, int y) override;
		void Process(std::unique_ptr<CameraComponent>& cameraComponent, RenderTarget& renderTarget) const override;
		void OnGui(std::unique_ptr<CameraComponent>& cameraComponent) override;
	};
}