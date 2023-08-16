//
// Created by Samer Ali on 8/14/23.
//

#include "CYNTHIA/Core/Application.h"
#include "CYNTHIA/Events/ApplicationEvent.h"
#include "CYNTHIA/Core/Log.h"

namespace Cynthia
{
	Application::Application ( )
	{

	}

	Application::~Application()
	{

	}

	void Application::Run ( )
	{
		WindowResizeEvent e(1280, 720);
		CY_TRACE(e);

		while(true);
	}
} // Cynthia