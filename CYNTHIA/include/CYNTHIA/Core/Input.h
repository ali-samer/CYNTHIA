//
// Created by Samer Ali on 9/15/23.
//
#pragma once

namespace Cynthia
{

	class Input
	{
	public:
		static bool IsKeyPressed(int keycode) { return s_instance->isKeyPressedImpl(keycode); }
	protected:
		virtual bool isKeyPressedImpl(int keycode) = 0;
	private:
		static Input* s_instance;
	};
}