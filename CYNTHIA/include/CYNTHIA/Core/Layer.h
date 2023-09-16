//
// Created by Samer Ali on 8/28/23.
//

#ifndef CYNTHIA_CORE_LAYER_H
#define CYNTHIA_CORE_LAYER_H


#include "Includes.h"
#include "../Events/Event.h"


namespace Cynthia
{
	class Layer
	{
	public:
		Layer ( const std::string & name = "Layer" );
		virtual ~Layer ( );

		virtual void onAttach ( ) { }
		virtual void onDetach ( ) { }
		virtual void onUpdate ( ) { }
		virtual void onEvent ( Event & event ) { }
		virtual void onImGuiRender() { };
		inline const std::string & getName ( ) const { return m_debugName; }
	protected:
		std::string m_debugName;
	};
}

#endif //CYNTHIA_CORE_LAYER_H
