//
// Created by Samer Ali on 8/28/23.
//

#include "CYNTHIA/Core/LayerStack.h"

namespace Cynthia
{

	LayerStack::LayerStack ( )
	{
	}

	LayerStack::~LayerStack ( )
	{
		for(Layer* layer: m_layer)
		{
			delete layer;
		}
	}

	void LayerStack::pushLayer ( Cynthia::Layer* layer )
	{
		m_layer.emplace(m_layer.begin() + m_layerInsertIndex, layer);
		m_layerInsertIndex++;
	}

	void LayerStack::pushOverlay ( Cynthia::Layer* overlay )
	{
		m_layer.emplace_back(overlay);
	}

	void LayerStack::popLayer ( Cynthia::Layer* layer )
	{
		auto it = std::find(m_layer.begin(), m_layer.end(), layer);
		if(it != m_layer.end())
		{
			m_layer.erase(it);
			m_layerInsertIndex--;
		}
	}

	void LayerStack::popOverlay ( Cynthia::Layer* overlay )
	{
		auto it = std::find(m_layer.begin(), m_layer.end(), overlay);
		if(it != m_layer.end())
		{
			m_layer.erase(it);
		}
	}
}