//
// Created by Samer Ali on 8/15/23.
//

#ifndef CYNTHIA_EVENT_APPLICATION_EVENT_H
#define CYNTHIA_EVENT_APPLICATION_EVENT_H


#include "Event.h"
#include "CYNTHIA/Core/Includes.h"


namespace Cynthia
{

	class WindowResizeEvent : public Event
	{
	public:
		WindowResizeEvent ( unsigned int _width , unsigned int _height )
			: width( _width ) ,
			  height( _height ) { }

		inline unsigned int getWidth ( ) const { return width; }
		inline unsigned int getHeight ( ) const { return height; }

		std::string toString ( ) const override
		{
			std::stringstream ss;
			ss << "WindowResizeEvent: " << width << ", " << height;
			return ss.str( );
		}

		EVENT_CLASS_TYPE( WindowResize )
		EVENT_CLASS_CATEGORY( Application )
	private:
		unsigned int width , height;
	};

	class WindowCloseEvent : public Event
	{
	public:
		WindowCloseEvent ( ) { }

		EVENT_CLASS_TYPE( WindowClose )
		EVENT_CLASS_CATEGORY( Application  )
	};

	class AppTickEvent : public Event
	{
	public:
		AppTickEvent ( ) { }

		EVENT_CLASS_TYPE( AppTick )
		EVENT_CLASS_CATEGORY( Application )
	};

	class AppUpdateEvent : public Event
	{
	public:
		AppUpdateEvent ( ) { }

		EVENT_CLASS_TYPE( AppUpdate )
		EVENT_CLASS_CATEGORY( Application )
	};

	class AppRenderEvent : public Event
	{
	public:
		AppRenderEvent ( ) { }

		EVENT_CLASS_TYPE( AppRender )
		EVENT_CLASS_CATEGORY( Application )
	};

}

#endif //CYNTHIA_EVENT_APPLICATION_EVENT_H
