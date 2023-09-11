//
// Created by Samer Ali on 8/17/23.
//

#include "Platform/Win32Window.h"
#include "CYNTHIA/Core/Log.h"
#include "CYNTHIA/Core/Assert.h"

#include "CYNTHIA/Events/MouseEvent.h"
#include "CYNTHIA/Events/KeyEvent.h"
#include "CYNTHIA/Events/ApplicationEvent.h"
#include <glad/glad.h>


namespace Cynthia
{
	static bool GLFWInitialized = false;

	void GLFWErrorCallback(int error, const char* description)
	{
		CY_CORE_ERROR("GLFW Error ({0}): ", error, description);
	}

	Window* Window::Create ( const Cynthia::WindowProps & props )
	{
		return new Win32Window(props);
	}

	Win32Window::Win32Window ( const Cynthia::WindowProps & props )
	{
		init(props);
	}

	Win32Window::~Win32Window ( )
	{
		shutdown();
	}

	void Win32Window::init ( const Cynthia::WindowProps & props )
	{
		m_data.title  = props.title;
		m_data.width  = props.width;
		m_data.height = props.height;

		CY_CORE_INFO("Creating window {0} ({1}, {2})", props.title, props.width, props.height);

		if(!GLFWInitialized)
		{
			int success = glfwInit();
			#ifdef CY_ENABLE_ASSERTS
			CY_CORE_ASSERT(success, "Could not initialize glfw");
			#endif
			glfwSetErrorCallback(GLFWErrorCallback);
			GLFWInitialized = true;
		}

		const char* glsl_version = "#version 150";
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

		m_window = glfwCreateWindow( (int)props.width, (int)props.height, m_data.title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent( m_window);

		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		CY_CORE_ASSERT(status, "Failed to initialize GLAD!");
		glfwSetWindowUserPointer( m_window, &m_data);
		setVSync( true);

		glfwSetWindowSizeCallback(m_window, [](GLFWwindow* window, int width, int height)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			data.width = width;
			data.height = height;

			WindowResizeEvent event(width, height);
			data.eventCallBack(event);
		});

		glfwSetWindowCloseCallback(m_window, [](GLFWwindow* window)
		{
			WindowData& data = *(WindowData*) glfwGetWindowUserPointer(window);
			WindowCloseEvent event;
			data.eventCallBack(event);
		});

		glfwSetKeyCallback(m_window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
		{
			WindowData& data = *(WindowData*) glfwGetWindowUserPointer(window);

			switch(action)
			{
				case GLFW_PRESS:
				{
					KeyPressEvent event( key , 0 );
					data.eventCallBack( event );
					break;
				}
				case GLFW_RELEASE:
				{
					KeyReleasedEvent event(key);
					data.eventCallBack(event);
					break;
				}
				case GLFW_REPEAT:
				{
					KeyPressEvent event(key, 1);
					data.eventCallBack(event);
					break;
				}
			}
		});

		glfwSetMouseButtonCallback(m_window, [](GLFWwindow* window, int button, int action, int mods)
		{
			WindowData& data = *(WindowData*) glfwGetWindowUserPointer(window);

			switch(action)
			{
				case GLFW_PRESS:
				{
					MouseButtonPressedEvent event(button);
					data.eventCallBack(event);
					break;
				}
				case GLFW_RELEASE:
				{
					MouseButtonReleasedEvent event(button);
					data.eventCallBack(event);
					break;
				}
			}
		});

		glfwSetScrollCallback(m_window, [](GLFWwindow* window, double xOffSet, double yOffSet)
		{
			WindowData& data = *(WindowData*) glfwGetWindowUserPointer(window);

			MouseScrolledEvent event(static_cast<float>(xOffSet), static_cast<float>(yOffSet));
			data.eventCallBack(event);
		});

		glfwSetCursorPosCallback(m_window, [](GLFWwindow* window, double xPos, double yPos)
		{
		  WindowData& data = *(WindowData*) glfwGetWindowUserPointer(window);
		  MouseMovedEvent event(static_cast<float>(xPos), static_cast<float>(yPos));
		  data.eventCallBack(event);
		});
	}

	void Win32Window::shutdown ( )
	{
		glfwDestroyWindow( m_window);
	}

	void Win32Window::onUpdate ( ) const
	{
		glfwPollEvents();
		glfwSwapBuffers( m_window);
	}

	void Win32Window::setVSync ( bool enabled )
	{
		if(enabled)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);

		m_data.vSync = enabled;
	}

	bool Win32Window::isVSync ( ) const
	{
		return m_data.vSync;
	}
}