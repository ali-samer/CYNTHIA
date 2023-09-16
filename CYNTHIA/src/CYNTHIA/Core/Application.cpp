//
// Created by Samer Ali on 8/14/23.
//

#include "CYNTHIA/Core/Application.h"
#include "CYNTHIA/Events/ApplicationEvent.h"
#include "CYNTHIA/Core/Log.h"
#include "CYNTHIA/Core/Assert.h"
#include "CYNTHIA/Core/Input.h"
#include <glad/glad.h>

namespace Cynthia
{

	#define BIND_EVENT_FN(X) std::bind(&Application::X, this, std::placeholders::_1)
	class Application* Application::s_instance = nullptr; // singleton design pattern to allow only one
														  // instance of the class to exist
	Application::Application ( )
	{
		CY_CORE_ASSERT(!s_instance, "Application already exists")
		s_instance = this;
		m_window = std::unique_ptr<Window>(Window::Create());
		m_window->setEventCallback(BIND_EVENT_FN(OnEvent));
	}

	Application::~Application()
	{

	}

	void Application::PushLayer ( Cynthia::Layer* layer )
	{
		m_layerStack.pushLayer(layer);
		layer->onAttach();
	}

	void Application::PushOverlay ( Cynthia::Layer* overlay )
	{
		m_layerStack.pushOverlay(overlay);
		overlay->onAttach();
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
		if(event.getEventType() != EventType::MouseMoved) // Mouse moved is handles by run()
		CY_CORE_TRACE("{0}", event);

		for(auto i = m_layerStack.end(); i != m_layerStack.begin();)
		{
			(*--i)->onEvent(event);
			if(event.m_handled)
				break;
		}
	}

	void Application::Run ( )
	{
		WindowResizeEvent e(1280, 720);
		CY_TRACE(e);

		while(m_running)
		{
			glClearColor(0.5f,0.5f,0.5f,1.0f);
			glClear(GL_COLOR_BUFFER_BIT);
			for(Layer* layer : m_layerStack)
					layer->onUpdate();
			auto [x, y] = Input::GetMousePos();
			CY_CORE_TRACE("{0}, {1}", x, y);
			m_window->onUpdate();
		}

	}
} // Cynthia