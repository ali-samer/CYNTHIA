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

	void Application::OnEvent ( Event & event )
	{
		CY_CORE_TRACE("{0}", event);
	}

	void Application::Run ( )
	{
		WindowResizeEvent e(1280, 720);
		CY_TRACE(e);

		while(m_running)
		{
			glClearColor(1,0,1,1);
			glClear(GL_COLOR_BUFFER_BIT);
			m_window->onUpdate();
		}

	}
} // Cynthia