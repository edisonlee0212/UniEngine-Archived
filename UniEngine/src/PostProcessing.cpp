#include "pch.h"
#include "PostProcessing.h"
using namespace UniEngine;

void PostProcessing::PushLayer(std::unique_ptr<PostProcessingLayer> layer)
{
	if (!layer) return;
	layer->Init();
	layer->ResizeResolution(m_resolutionX, m_resolutionY);
	_Layers[layer->m_name] = std::move(layer);
}

void PostProcessing::RemoveLayer(const std::string& layerName)
{
	if (_Layers[layerName]) _Layers.erase(layerName);
}

void PostProcessing::SetEnableLayer(const std::string& layerName, bool enabled)
{
	if (_Layers[layerName]) _Layers[layerName]->m_enabled = enabled;
}

PostProcessing::PostProcessing()
{
	ResizeResolution(1, 1);
	SetEnabled(true);
}

void PostProcessing::Process()
{
	auto& cameraComponent = GetOwner().GetPrivateComponent<CameraComponent>();
	if(_Layers["SSAO"] && _Layers["SSAO"]->m_enabled)
	{
		_Layers["SSAO"]->Process(cameraComponent, *this);
	}
	if (_Layers["Bloom"] && _Layers["Bloom"]->m_enabled)
	{
		_Layers["Bloom"]->Process(cameraComponent, *this);
	}

	if (_Layers["GreyScale"] && _Layers["GreyScale"]->m_enabled)
	{
		_Layers["GreyScale"]->Process(cameraComponent, *this);
	}
}

void PostProcessing::ResizeResolution(int x, int y)
{
	if(m_resolutionX == x && m_resolutionY == y) return;
	m_resolutionX = x;
	m_resolutionY = y;
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
			ImGui::Checkbox(layer.second->m_name.c_str(), &layer.second->m_enabled);
			if(layer.second->m_enabled) layer.second->OnGui(cameraComponent);
		}
	}
}
