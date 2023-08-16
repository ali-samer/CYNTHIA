#include "CYNTHIA/Core/EntryPoint.h"

class Sandbox : public Cynthia::Application
{
public:
  Sandbox()
  {

  }

  ~Sandbox()
  {

  }

};

Sandbox::Application* Cynthia::CreateApplication ( )
{
	return new Sandbox();
}