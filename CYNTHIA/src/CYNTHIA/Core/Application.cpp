//
// Created by Samer Ali on 8/14/23.
//

#include "CYNTHIA/Core/Application.h"
#include "CYNTHIA/Events/ApplicationEvent.h"
#include "CYNTHIA/Core/Log.h"
//#include "CYNTHIA/Core/Includes.h"

namespace Cynthia
{
	Application::Application ( )
	{
		window = std::unique_ptr<Window>(Window::Create());
	}

	Application::~Application()
	{

	}

	void Application::Run ( )
	{
		WindowResizeEvent e(1280, 720);
		CY_TRACE(e);

		while(running)
		{
			window->onUpdate();
		}

	}
} // Cynthia