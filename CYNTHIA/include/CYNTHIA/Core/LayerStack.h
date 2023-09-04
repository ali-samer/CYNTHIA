//
// Created by Samer Ali on 8/28/23.
//

#ifndef CYNTHIA_CORE_LAYERSTACK_H
#define CYNTHIA_CORE_LAYERSTACK_H

#include "Layer.h"
#include "Includes.h"

namespace Cynthia
{

	class LayerStack
	{
	public:
		LayerStack();
		~LayerStack();

		void pushLayer(Layer* layer);
		void pushOverlay(Layer* overlay);
		void popLayer(Layer* layer);
		void popOverlay(Layer* overlay);

		std::vector<Layer*>::iterator begin() { return m_layer.begin(); }
		std::vector<Layer*>::iterator end() { return m_layer.end(); }
	private:
		std::vector<Layer*> m_layer;
		std::vector<Layer*>::iterator m_layerInsert;
	};

}

#endif //CYNTHIA_CORE_LAYERSTACK_H
