#include "pch.h"
#include "PostProcessing.h"
using namespace UniEngine;

void PostProcessing::PushLayer(std::unique_ptr<PostProcessingLayer> layer)
{
	layer->ResizeResolution(_ResolutionX, _ResolutionY);
	_Layers[layer->_Type] = std::move(layer);
}

PostProcessing::PostProcessing()
{
	ResizeResolution(1, 1);
	_Layers[PostProcessingLayerType::SSAO] = nullptr;
	_Layers[PostProcessingLayerType::Bloom] = nullptr;
	SetEnabled(true);
}

void PostProcessing::Process()
{
	auto& cameraComponent = GetOwner().GetPrivateComponent<CameraComponent>();
	if(_Layers[PostProcessingLayerType::SSAO] && _Layers[PostProcessingLayerType::SSAO]->_Enabled)
	{
		_Layers[PostProcessingLayerType::SSAO]->Process(cameraComponent, *this);
	}
	if (_Layers[PostProcessingLayerType::Bloom] && _Layers[PostProcessingLayerType::Bloom]->_Enabled)
	{
		_Layers[PostProcessingLayerType::Bloom]->Process(cameraComponent, *this);
	}
}

void PostProcessing::ResizeResolution(int x, int y)
{
	_ResolutionX = x;
	_ResolutionY = y;
	for (auto& layer : _Layers)
	{
		if (layer.second && layer.second->_Enabled) layer.second->ResizeResolution(x, y);
	}
}

void PostProcessing::OnGui()
{
	auto& cameraComponent = GetOwner().GetPrivateComponent<CameraComponent>();
	for (auto& layer : _Layers)
	{
		if (layer.second) {
			ImGui::Checkbox(layer.second->_Name.c_str(), &layer.second->_Enabled);
			if(layer.second->_Enabled) layer.second->OnGui(cameraComponent);
		}
	}
}
