#pragma once
#include "Core.h"
#include "UniEngineAPI.h"
#include "PostProcessing.h"

namespace UniEngine
{
	class UNIENGINE_API SSAO : public PostProcessingLayer
	{
		/*
		 * static bool _EnableSSAO;
		static std::unique_ptr<GLProgram> _SSAOGeometryPass;
		static std::unique_ptr<GLProgram> _SSAOBlurPass;

		static float _SSAOKernelRadius;
		static float _SSAOKernelBias;
		static float _SSAOScale;
		static float _SSAOFactor;
		static int _SSAOSampleSize;
		 */
		std::unique_ptr<GLTexture2D> _SSAOPosition;
		std::unique_ptr<GLTexture2D> _SSAOBlur;
		std::unique_ptr<GLProgram> _PositionProgram;
		std::unique_ptr<GLProgram> _BlurProgram;
		std::unique_ptr<GLProgram> _CombineProgram;
	public:
		SSAO();
		void ResizeResolution(int x, int y) override;
		void Process(std::unique_ptr<CameraComponent>& cameraComponent, RenderTarget& renderTarget) const override;
		void OnGui(std::unique_ptr<CameraComponent>& cameraComponent) override;
	};
}