//
// Created by Samer Ali on 8/14/23.
//

#ifndef CYNTHIA_CORE_APPLICATION_H
#define CYNTHIA_CORE_APPLICATION_H

#include "../Events/Event.h"
#include "../Events/ApplicationEvent.h"
#include "LayerStack.h"
#include "CYNTHIA/Core/Window.h"


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
	private:
		bool onWindowClose(WindowCloseEvent& event);
		std::unique_ptr<Window> m_window;
		bool  m_running = true;
		LayerStack m_layerStack;

	};

	class Application* CreateApplication();

} // Cynthia

#endif //CYNTHIA_CORE_APPLICATION_H
