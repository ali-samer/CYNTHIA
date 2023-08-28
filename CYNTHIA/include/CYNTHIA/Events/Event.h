//
// Created by Samer Ali on 8/15/23.
//

#ifndef CYNTHIA_EVENT_EVENT_H
#define CYNTHIA_EVENT_EVENT_H


#include "CYNTHIA/Core/Includes.h"

namespace Cynthia
{

	enum EventCategory
	{
		None = 0 ,
		Application = CY_SHIFT( 0 ) ,
		Input       = CY_SHIFT( 1 ) ,
		Keyboard    = CY_SHIFT( 2 ) ,
		Mouse       = CY_SHIFT( 3 ) ,
		MouseButton = CY_SHIFT( 4 ) ,

	};

	enum class EventType
	{
		None = 0 ,
		WindowClose ,
		WindowResize ,
		WindowFocus ,
		WindowLostFocus ,
		WindowMoved ,
		AppTick ,
		AppUpdate ,
		AppRender ,
		KeyPressed ,
		KeyReleased ,
		MouseButtonPressed ,
		MouseButtonReleased ,
		MouseMoved ,
		MouseScrolled
	};
#define EVENT_CLASS_TYPE( T ) static EventType GetStaticType() { return EventType::T; } \
                              virtual EventType getEventType() const override { return GetStaticType(); } \
                              virtual const char* getName() const override { return #T; }

#define EVENT_CLASS_CATEGORY( C ) virtual int getCategoryFlags() const override { return C; }

	class Event
	{
		friend class EventDispatcher;
	public:
		virtual EventType getEventType ( ) const = 0;
		virtual const char* getName ( ) const = 0;
		virtual int getCategoryFlags ( ) const = 0;
		virtual std::string toString ( ) const { return getName( ); }

		inline bool isInCategory ( EventCategory category ) { return getCategoryFlags( ) & category; }
	protected:
		bool m_handled = false; //check if an m_event has been m_handled
	};

	class EventDispatcher
	{
		template < typename T >
		using EventFn = std::function< bool ( T & ) >;
	public:
		EventDispatcher ( Event & event_ )
			: m_event( event_ ) { }
		template < typename T >
		bool dispatch ( EventFn< T > func )
		{
			if ( m_event.getEventType( ) == T::GetStaticType( ) )
			{
				m_event.m_handled = func( *( T* ) &m_event );
				return true;
			}
			return false;
		}
	private:
		Event & m_event;
	};

	inline std::ostream & operator<< ( std::ostream & os , const Event & event )
	{
		os << event.toString( );
		return os;
	}
}

#endif //CYNTHIA_EVENT_EVENT_H
