//
// Created by Samer Ali on 9/15/23.
//

#pragma once

#include "CYNTHIA/Core/Input.h"

namespace Cynthia
{

	class WindowsInput : public Input
	{
	public:
	protected:
		bool isKeyPressedImpl(int keycode) const override;

		bool isMousePressedImpl(int button) const override;
		std::pair< float , float > getMousePosImpl() const override;


	};
}