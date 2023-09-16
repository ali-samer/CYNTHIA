//
// Created by Samer Ali on 8/17/23.
//

#ifndef CYNTHIA_PLATFORM_WIN32WINDOW_H
#define CYNTHIA_PLATFORM_WIN32WINDOW_H


#include "glfw/include/GLFW/glfw3.h"

#include "CYNTHIA/Core/Window.h"


namespace Cynthia
{

	class Win32Window : public Window
	{
	public:
		Win32Window ( const WindowProps & props );
		virtual ~Win32Window ( );

		void onUpdate ( ) const override;

		inline unsigned int getWidth ( ) const override { return m_data.width; }
		inline unsigned int getHeight ( ) const override { return m_data.height; }
		inline GLFWwindow* getWindow() const override { return m_window; }

		// attributes
		inline void setEventCallback ( const EventCallBackFunc & callback ) override { m_data.eventCallBack = callback; }
		void setVSync ( bool enabled ) override;
		bool isVSync ( ) const override;

	private:
		virtual void init ( const WindowProps & props );
		virtual void shutdown ( );
	private:
		GLFWwindow* m_window;

		struct WindowData
		{
			std::string       title;
			unsigned int      width , height;
			bool              vSync;
			EventCallBackFunc eventCallBack;
		};

		WindowData m_data;
	};
}

#endif //CYNTHIA_PLATFORM_WIN32WINDOW_H
