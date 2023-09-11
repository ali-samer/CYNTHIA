#include "CYNTHIA/Core/EntryPoint.h"
#include "CYNTHIA/Cynthia.h"
class ExampleLayer : public Cynthia::Layer
{
public:
	ExampleLayer()
		: Layer("Example---") {}

	void onUpdate() override
	{
		CY_INFO("ExampleLayer::Update");
	}

	void onEvent(Cynthia::Event& event) override
	{
		CY_TRACE("{0}", event);
	}
};
class Sandbox : public Cynthia::Application
{
public:
  Sandbox()
  {
	  PushLayer(new ExampleLayer());
	  PushOverlay(new Cynthia::ImGuiLayer());
  }

  ~Sandbox()
  {

  }

};

Sandbox::Application* Cynthia::CreateApplication ( )
{
	return new Sandbox();
}