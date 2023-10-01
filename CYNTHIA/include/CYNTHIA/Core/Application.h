//
// Created by Samer Ali on 8/14/23.
//

#ifndef CYNTHIA_CORE_APPLICATION_H
#define CYNTHIA_CORE_APPLICATION_H

#include "../Events/Event.h"
#include "../Events/ApplicationEvent.h"
#include "LayerStack.h"
#include "CYNTHIA/Core/Window.h"
#include "CYNTHIA/GUI/ImGuiLayer.h"
#include "CYNTHIA/Image/ImageLayer.h"


namespace Cynthia
{

	class Application
	{
	public:

	    Application();
		virtual ~Application();

		void Run();
		void OnEvent(Event& event);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);
		inline static Application& Get() { return *s_instance; }
		inline Window& getWindowObj() { return *m_window; }
	private:
		static Application* s_instance;
		bool onWindowClose(WindowCloseEvent& event);
		std::unique_ptr<Window> m_window;
		ImGuiLayer* m_imGuiLayer;
		ImageLayer* m_imageLayer;
		bool  m_running = true;
		static LayerStack m_layerStack;

	};

	class Application* CreateApplication();

} // Cynthia

#endif //CYNTHIA_CORE_APPLICATION_H
