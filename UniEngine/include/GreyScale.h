#pragma once
#include "Core.h"
#include "UniEngineAPI.h"
#include "PostProcessing.h"

namespace UniEngine
{
	class UNIENGINE_API GreyScale : public PostProcessingLayer
	{
		std::unique_ptr<GLTexture2D> m_greyColor;
		std::unique_ptr<GLProgram> m_transferProgram;
		std::unique_ptr<GLProgram> m_copyProgram;
	public:
		void Init() override;
		void ResizeResolution(int x, int y) override;
		void Process(std::unique_ptr<CameraComponent>& cameraComponent, RenderTarget& renderTarget) const override;
		void OnGui(std::unique_ptr<CameraComponent>& cameraComponent) override;
	};
}
