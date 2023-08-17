//
// Created by Samer Ali on 8/16/23.
//

#ifndef CYNTHIA_CORE_WINDOW_H
#define CYNTHIA_CORE_WINDOW_H


//#include "CYNTHIA/Core/Includes.h"

#include "CYNTHIA/Events/Event.h"


namespace Cynthia
{

	struct WindowProps
	{
	public:
		 explicit WindowProps ( const std::string_view _title = "Cynthia" , unsigned int _width = 1280 ,
		                       unsigned int _height = 720 )
					: title( _title ) ,
					  width( _width ) ,
					  height( _height ) { }

		std::string  title;
		unsigned int width;
		unsigned int height;
	};

	class Window
	{
	public:
		using EventCallBackFunc = std::function< void ( Event & ) >;

		virtual ~Window ( ) { };

		virtual void onUpdate ( ) const = 0;

		virtual unsigned int getWidth ( ) const = 0;
		virtual unsigned int getHeight ( ) const = 0;

		virtual void setEventCallback ( const EventCallBackFunc & callback ) = 0;
		virtual void setVSync ( bool enabled ) = 0;
		virtual bool isVSync ( ) const = 0;

		static Window* Create ( const WindowProps & props = WindowProps( ) );
	};


}

#endif //CYNTHIA_CORE_WINDOW_H
