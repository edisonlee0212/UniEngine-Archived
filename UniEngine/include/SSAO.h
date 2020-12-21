#pragma once
#include "Core.h"
#include "UniEngineAPI.h"
#include "PostProcessing.h"

namespace UniEngine
{
	class UNIENGINE_API SSAO : public PostProcessingLayer
	{
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