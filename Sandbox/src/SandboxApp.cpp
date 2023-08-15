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

Cynthia::Application* Cynthia::CreateApplication ( )
{
	return new Sandbox();
}