#ifndef CYNTHIA_EVENT_MOUSE_EVENT_H
#define CYNTHIA_EVENT_MOUSE_EVENT_H


#include "Event.h"
#include "CYNTHIA/Core/Includes.h"


namespace Cynthia
{
	class MouseMovedEvent : public Event
	{
	public:
		MouseMovedEvent ( float x , float y )
			: mouse_x( x ) ,
			  mouse_y( y ) { }

		inline float getX ( ) const { return mouse_x; }
		inline float getY ( ) const { return mouse_y; }

		std::string toString ( ) const override
		{
			std::stringstream ss;
			ss << "MouseMovedEvent: " << mouse_x << ", " << mouse_y;
			return ss.str( );
		}

		EVENT_CLASS_TYPE( MouseMoved )
		EVENT_CLASS_CATEGORY( Mouse | Input )
	private:
		float mouse_x , mouse_y;
	};

	class MouseScrolledEvent : public Event
	{
	public:
		MouseScrolledEvent ( float _xOffset , float _yOffset )
			: xOffset( _xOffset ) ,
			  yOffset( _yOffset ) { }

		inline float getXOffset ( ) const { return xOffset; }
		inline float getYOffset ( ) const { return yOffset; }

		std::string toString ( ) const override
		{
			std::stringstream ss;
			ss << "MouseScrolledEvent: " << xOffset << ", " << yOffset;
			return ss.str( );
		}

		EVENT_CLASS_TYPE( MouseScrolled )
		EVENT_CLASS_CATEGORY( Mouse | Input )
	private:
		float xOffset , yOffset;
	};

	class MouseButtonEvent : public Event
	{
	public:
		inline bool getMouseButton ( ) { return button; }
		EVENT_CLASS_CATEGORY( Mouse | Input )

	protected:
		MouseButtonEvent ( int _button ) : button( _button ) { }
		int button;
	};

	class MouseButtonPressedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonPressedEvent ( int _button ) : MouseButtonEvent( _button ) { }

		std::string toString ( ) const override
		{
			std::stringstream ss;
			ss << "MouseButtonPressedEvent: " << button;
			return ss.str( );
		}
		EVENT_CLASS_TYPE( MouseButtonPressed )
	};

	class MouseButtonReleasedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonReleasedEvent ( int _button ) : MouseButtonEvent( _button ) { }

		std::string toString ( ) const override
		{
			std::stringstream ss;
			ss << "MouseButtonReleasedEvent: " << button;
			return ss.str( );
		}
		EVENT_CLASS_TYPE( MouseButtonReleased )
	};


}

#endif //CYNTHIA_EVENT_MOUSE_EVENT_H