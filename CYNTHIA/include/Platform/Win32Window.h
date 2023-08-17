//
// Created by Samer Ali on 8/17/23.
//

#ifndef CYNTHIA_PLATFORM_WIN32WINDOW_H
#define CYNTHIA_PLATFORM_WIN32WINDOW_H


#include <GLFW/glfw3.h>

#include "CYNTHIA/Core/Window.h"


namespace Cynthia
{

	class Win32Window : public Window
	{
	public:
		Win32Window ( const WindowProps & props );
		virtual ~Win32Window ( );

		void onUpdate ( ) const override;

		inline unsigned int getWidth ( ) const override { return data.width; }
		inline unsigned int getHeight ( ) const override { return data.height; }

		// attributes
		inline void setEventCallback ( const EventCallBackFunc & callback ) override { data.eventCallBack = callback; }
		void setVSync ( bool enabled ) override;
		bool isVSync ( ) const override;

	private:
		virtual void init ( const WindowProps & props );
		virtual void shutdown ( );
	private:
		GLFWwindow* window;

		struct WindowData
		{
			std::string       title;
			unsigned int      width , height;
			bool              vSync;
			EventCallBackFunc eventCallBack;
		};

		WindowData data;
	};
}

#endif //CYNTHIA_PLATFORM_WIN32WINDOW_H
