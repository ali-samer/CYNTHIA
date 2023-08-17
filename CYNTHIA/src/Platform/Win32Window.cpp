//
// Created by Samer Ali on 8/17/23.
//

#include "Platform/Win32Window.h"
#include "CYNTHIA/Core/Log.h"
#include "CYNTHIA/Core/Assert.h"


namespace Cynthia
{
	static bool GLFWInitialized = false;

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
		data.title = props.title;
		data.width = props.width;
		data.height = props.height;

		CY_CORE_INFO("Creating window {0} ({1}, {2})", props.title, props.width, props.height);

		if(!GLFWInitialized)
		{
			int success = glfwInit();
			#ifdef CY_ENABLE_ASSERTS
			CY_CORE_ASSERT(success, "Could not initialize glfw");
			#endif
			GLFWInitialized = true;
		}

		window = glfwCreateWindow((int)props.width, (int)props.height, data.title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(window);
		glfwSetWindowUserPointer(window, &data);
		setVSync( true);
	}

	void Win32Window::shutdown ( )
	{
		glfwDestroyWindow(window);
	}

	void Win32Window::onUpdate ( ) const
	{
		glfwPollEvents();
		glfwSwapBuffers(window);
	}

	void Win32Window::setVSync ( bool enabled )
	{
		if(enabled)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);

		data.vSync = enabled;
	}

	bool Win32Window::isVSync ( ) const
	{
		return data.vSync;
	}
}