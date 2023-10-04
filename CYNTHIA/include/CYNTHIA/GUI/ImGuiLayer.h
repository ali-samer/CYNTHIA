#ifndef CYNTHIA_GUI_IMGUILAYER_H
#define CYNTHIA_GUI_IMGUILAYER_H

#include "../Core/Layer.h"
#include "CYNTHIA/Events/MouseEvent.h"
#include "CYNTHIA/Events/KeyEvent.h"
#include "CYNTHIA/Events/ApplicationEvent.h"
#include <imgui.h>
#include <backends/imgui_impl_opengl3.h>


namespace Cynthia
{
	class ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void onAttach() override;
		virtual void onDetach() override;
//		virtual void onUpdate() override;
		virtual void onImGuiRender() override;
		void setDarkThemeColors();
		uint32_t GetActiveWidgetID() const;
		void begin();
		void end();
	private:
		float m_time = 0.0f;

	};
}

#endif // CYNTHIA_GUI_IMGUILAYER_H