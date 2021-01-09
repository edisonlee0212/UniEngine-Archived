#include "pch.h"
#include "PostProcessing.h"
using namespace UniEngine;

void PostProcessing::PushLayer(std::unique_ptr<PostProcessingLayer> layer)
{
	if (!layer) return;
	layer->Init();
	layer->ResizeResolution(_ResolutionX, _ResolutionY);
	_Layers[layer->_Name] = std::move(layer);
}

PostProcessing::PostProcessing()
{
	ResizeResolution(1, 1);
	SetEnabled(true);
}

void PostProcessing::Process()
{
	auto& cameraComponent = GetOwner().GetPrivateComponent<CameraComponent>();
	if(_Layers["SSAO"] && _Layers["SSAO"]->Enabled)
	{
		_Layers["SSAO"]->Process(cameraComponent, *this);
	}
	if (_Layers["Bloom"] && _Layers["Bloom"]->Enabled)
	{
		_Layers["Bloom"]->Process(cameraComponent, *this);
	}

	if (_Layers["GreyScale"] && _Layers["GreyScale"]->Enabled)
	{
		_Layers["GreyScale"]->Process(cameraComponent, *this);
	}
}

void PostProcessing::ResizeResolution(int x, int y)
{
	if(_ResolutionX == x && _ResolutionY == y) return;
	_ResolutionX = x;
	_ResolutionY = y;
	for (auto& layer : _Layers)
	{
		if (layer.second) layer.second->ResizeResolution(x, y);
	}
}

void PostProcessing::OnGui()
{
	auto& cameraComponent = GetOwner().GetPrivateComponent<CameraComponent>();
	for (auto& layer : _Layers)
	{
		if (layer.second) {
			ImGui::Checkbox(layer.second->_Name.c_str(), &layer.second->Enabled);
			if(layer.second->Enabled) layer.second->OnGui(cameraComponent);
		}
	}
}
