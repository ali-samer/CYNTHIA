//
// Created by Samer Ali on 8/14/23.
//

#ifndef CYNTHIA_SRC_CYNTHIA_APPLICATION_H
#define CYNTHIA_SRC_CYNTHIA_APPLICATION_H

namespace Cynthia
{

	class Application
	{
	public:
	  Application();
	  virtual ~Application();

	  void Run();

	};

	Application* CreateApplication();

} // Cynthia

#endif //CYNTHIA_SRC_CYNTHIA_APPLICATION_H
