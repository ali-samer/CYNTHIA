//
// Created by Samer Ali on 9/15/23.
//
#pragma once
#include <tuple>
#include <memory>
namespace Cynthia
{

	class Input
	{
	public:
		inline static bool IsKeyPressed(int keycode) { return s_instance->isKeyPressedImpl(keycode); }

		inline static bool IsMouseButtonPressed(int button) { return s_instance->isMousePressedImpl(button); }
		inline static std::pair< float , float > GetMousePos() { return s_instance->getMousePosImpl(); }
	protected:
		virtual bool isKeyPressedImpl(int keycode) const = 0;

		virtual bool isMousePressedImpl(int button) const = 0;
		virtual std::pair< float , float > getMousePosImpl() const = 0;
	public:
		static Input* s_instance; // singleton instance
	};
}