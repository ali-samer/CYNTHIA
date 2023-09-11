#ifndef CYNTHIA_GUI_IMGUILAYER_H
#define CYNTHIA_GUI_IMGUILAYER_H

#include "../Core/Layer.h"
#include <imgui.h>
#include <backends/imgui_impl_opengl3.h>


namespace Cynthia
{
	class ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		void onAttach();
		void onDetach();
		void onUpdate();
		void onEvent(Event& event);
	private:
		float m_time = 0.0f;

	};
}

#endif // CYNTHIA_GUI_IMGUILAYER_H