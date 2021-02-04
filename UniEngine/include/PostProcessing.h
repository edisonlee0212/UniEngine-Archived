#pragma once
#include "CameraComponent.h"
#include "Core.h"
#include "UniEngineAPI.h"
#include "RenderTarget.h"
namespace UniEngine
{
	class UNIENGINE_API PostProcessingLayer
	{
		friend class PostProcessing;
	protected:
		std::string _Name = "";
	public:
		bool Enabled = false;
		virtual void Init() = 0;
		virtual void ResizeResolution(int x, int y) = 0;
		virtual void Process(std::unique_ptr<CameraComponent>& cameraComponent, RenderTarget& renderTarget) const = 0;
		virtual void OnGui(std::unique_ptr<CameraComponent>& cameraComponent) = 0;
	};
	
	class UNIENGINE_API PostProcessing final : public PrivateComponentBase, public RenderTarget
	{
		std::map<std::string, std::unique_ptr<PostProcessingLayer>> _Layers;
	public:
		template <typename T>
		T* GetLayer();
		void PushLayer(std::unique_ptr<PostProcessingLayer> layer);
		void RemoveLayer(const std::string& layerName);
		void SetEnableLayer(const std::string& layerName, bool enabled);
		PostProcessing();
		void Process();
		void ResizeResolution(int x, int y);
		void OnGui() override;
	};

	template <typename T>
	T* PostProcessing::GetLayer()
	{
		for(auto& layer : _Layers)
		{
			if(dynamic_cast<T*>(layer.second.get()))
			{
				return dynamic_cast<T*>(layer.second.get());
			}
		}
		return nullptr;
	}
}
