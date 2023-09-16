//
// Created by Samer Ali on 9/15/23.
//

#include "Platform/Windows/WindowsInput.h"
#include "GLFW/glfw3.h"
#include "CYNTHIA/Core/Application.h"

namespace Cynthia
{
	class Input* Input::s_instance =  new WindowsInput();
	bool WindowsInput::isKeyPressedImpl ( int keycode ) const
	{
		auto window = static_cast<GLFWwindow*>(Application::Get( ).getWindowObj( ).getNativeWindow());
		auto state = glfwGetKey( window ,keycode);
		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}
	bool WindowsInput::isMousePressedImpl ( int button ) const
	{
		auto window = static_cast<GLFWwindow*>(Application::Get( ).getWindowObj( ).getNativeWindow());
		auto state = glfwGetMouseButton(window, button);
		return state == GLFW_PRESS;
	}
	std::pair< float , float > WindowsInput::getMousePosImpl ( ) const
	{
		auto window = static_cast<GLFWwindow*>(Application::Get( ).getWindowObj( ).getNativeWindow());
		double x, y;
		glfwGetCursorPos(window, &x, &y);
		return { (float)x, (float)y };
	}

}