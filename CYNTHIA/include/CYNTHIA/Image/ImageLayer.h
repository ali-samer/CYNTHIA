#pragma once

#include <vector>
#include "CYNTHIA/Image/Image.h"
#include "CYNTHIA/Core/Layer.h"

namespace Cynthia
{
	class ImageLayer: public Layer
	{
	public:
		ImageLayer();
		~ImageLayer();

		virtual void onAttach() override;
		virtual void onDetach() override;
		virtual void onImageRender() override;

		void begin();
		void end();
	private:
		float m_time = 0.0f;
	};
}
