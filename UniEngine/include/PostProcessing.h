#pragma once
#include "CameraComponent.h"
#include "Core.h"
#include "UniEngineAPI.h"
#include "RenderTarget.h"
namespace UniEngine
{
	enum class PostProcessingLayerType
	{
		Bloom
	};
	class UNIENGINE_API PostProcessingLayer
	{
		friend class PostProcessing;
	protected:
		bool _Enabled = true;
		PostProcessingLayerType _Type;
	public:
		virtual void ResizeResolution(int x, int y) = 0;
		virtual void Process(std::unique_ptr<CameraComponent>& cameraComponent, RenderTarget& renderTarget) const = 0;
		virtual void OnGui(std::unique_ptr<CameraComponent>& cameraComponent) = 0;
	};
	
	class UNIENGINE_API PostProcessing final : public PrivateComponentBase, public RenderTarget
	{
		std::map<PostProcessingLayerType, std::unique_ptr<PostProcessingLayer>> _Layers;
	public:
		void PushLayer(std::unique_ptr<PostProcessingLayer> layer);
		PostProcessing();
		void Process();
		void ResizeResolution(int x, int y);
		void OnGui() override;
	};
}
