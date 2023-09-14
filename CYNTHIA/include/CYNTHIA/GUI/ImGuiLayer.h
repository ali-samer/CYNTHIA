#ifndef CYNTHIA_GUI_IMGUILAYER_H
#define CYNTHIA_GUI_IMGUILAYER_H

#include "../Core/Layer.h"
#include "CYNTHIA/Events/MouseEvent.h"
#include "CYNTHIA/Events/KeyEvent.h"
#include "CYNTHIA/Events/ApplicationEvent.h"
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
		bool onMouseButtonPressedEvent(MouseButtonPressedEvent& event);
		bool onMouseButtonReleasedEvent(MouseButtonReleasedEvent& event);
		bool onMouseScrolledEvent(MouseScrolledEvent& event);
		bool onMouseMovedEvent(MouseMovedEvent& event);
		bool onKeyPressedEvent(KeyPressEvent& event);
		bool onKeyReleasedEvent(KeyReleasedEvent& event);
		bool onKeyTypedEvent(KeyTypedEvent& event);
		bool onWindowResizeEvent(WindowResizeEvent& event);
	private:
		float m_time = 0.0f;

	};
}

#endif // CYNTHIA_GUI_IMGUILAYER_H