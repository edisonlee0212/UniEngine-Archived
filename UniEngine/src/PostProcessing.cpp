#include "pch.h"
#include "PostProcessing.h"
using namespace UniEngine;

void PostProcessing::PushLayer(std::unique_ptr<PostProcessingLayer> layer)
{
	layer->ResizeResolution(_ResolutionX, _ResolutionY);
	_Layers.insert({ layer->_Type, std::move(layer) });
}

PostProcessing::PostProcessing()
{
	ResizeResolution(1, 1);
}

void PostProcessing::Process()
{
	auto& cameraComponent = GetOwner().GetPrivateComponent<CameraComponent>();
	for (const auto& layer : _Layers)
	{
		if (layer.second->_Enabled) layer.second->Process(cameraComponent, *this);
	}
}

void PostProcessing::ResizeResolution(int x, int y)
{
	_ResolutionX = x;
	_ResolutionY = y;
	for (auto& layer : _Layers)
	{
		if (layer.second->_Enabled) layer.second->ResizeResolution(x, y);
	}
}

void PostProcessing::OnGui()
{
	auto& cameraComponent = GetOwner().GetPrivateComponent<CameraComponent>();

	for (auto& layer : _Layers)
	{
		layer.second->OnGui(cameraComponent);
	}
}
