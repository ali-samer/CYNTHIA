//
// Created by Samer Ali on 8/14/23.
//

#include "CYNTHIA/Core/Application.h"
#include "CYNTHIA/Events/ApplicationEvent.h"
#include "CYNTHIA/Core/Log.h"
#include <GLFW/glfw3.h>
//#include "CYNTHIA/Core/Includes.h"

namespace Cynthia
{

	#define BIND_EVENT_FN(X) std::bind(&Application::X, this, std::placeholders::_1)
	Application::Application ( )
	{
		m_window = std::unique_ptr<Window>(Window::Create());
		m_window->setEventCallback(BIND_EVENT_FN(OnEvent));
	}

	Application::~Application()
	{

	}

	bool Application::onWindowClose ( Cynthia::WindowCloseEvent & event )
	{
		m_running = false;
		return true;
	}

	void Application::OnEvent ( Event & event )
	{
		EventDispatcher dispatcher(event);
		dispatcher.dispatch<WindowCloseEvent>( BIND_EVENT_FN(onWindowClose));
		CY_CORE_TRACE("{0}", event);
	}

	void Application::Run ( )
	{
		WindowResizeEvent e(1280, 720);
		CY_TRACE(e);

		while(m_running)
		{
			glClearColor(0.5f,0.5f,0.5f,1.0f);
			glClear(GL_COLOR_BUFFER_BIT);
			m_window->onUpdate();
		}

	}
} // Cynthia