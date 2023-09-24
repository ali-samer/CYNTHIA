#include "CYNTHIA/Core/EntryPoint.h"
#include "CYNTHIA/Cynthia.h"
class ExampleLayer : public Cynthia::Layer
{
public:
	ExampleLayer()
		: Layer("Example---") {}

	void onUpdate() override
	{
//		CY_INFO("ExampleLayer::Update");

		if(Cynthia::Input::IsKeyPressed(CY_KEY_TAB))
			CY_INFO("Tab key is pressed");
	}

	void onImGuiRender() override
	{
		ImGui::Begin("Test");
		ImGui::Text("Hello, World!");
//		ImGui::ColorEdit4("", new float[4]);
		ImGui::End();
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
  }

  ~Sandbox()
  {

  }

};

Sandbox::Application* Cynthia::CreateApplication ( )
{
	return new Sandbox();
}