//
// Created by Samer Ali on 8/14/23.
//

#ifndef CYNTHIA_CORE_APPLICATION_H
#define CYNTHIA_CORE_APPLICATION_H

//#include "../Events/Event.h"
#include "CYNTHIA/Core/Window.h"


namespace Cynthia
{

	class Application
	{
	public:
	  Application();
	  virtual ~Application();

	  void Run();
	private:
		std::unique_ptr<Cynthia::Window> window;
		bool running = true;

	};

	class Application* CreateApplication();

} // Cynthia

#endif //CYNTHIA_CORE_APPLICATION_H
