#ifndef CYNTHIA_EVENT_KEY_EVENT_H
#define CYNTHIA_EVENT_KEY_EVENT_H

#include "Event.h"
#include "CYNTHIA/Core/Includes.h"

namespace Cynthia
{
	class KeyEvent : public Event
	{
	public:
		inline int GetKeyCode() const { return key_code; }
		EVENT_CLASS_CATEGORY(Keyboard | Input)

	protected:
		KeyEvent(int keycode) : key_code(keycode) {}
		int key_code;
	};

	// when a key is press on keyboard
	class KeyPressEvent : public KeyEvent
	{
	public:
		KeyPressEvent(int keycode, int repeatcount)
			: KeyEvent(keycode), repeat_count(repeatcount) {}

		inline int getRepeatCount() const { return repeat_count; }

		std::string toString() const override
		{
			std::stringstream ss;
			ss << "KeyPressedEvent: " << key_code << " (" << repeat_count << " repeats)";
			return ss.str();
		}
		EVENT_CLASS_TYPE(KeyPressed)
	private:
		int repeat_count;
	};

	// when key is released from keyboard
	class KeyReleasedEvent : public KeyEvent
	{
	public:
		std::string toString() const override
		{
			std::stringstream ss;
			ss << "KeyReleasedEvent : " << key_code;
			return ss.str();
		}
		EVENT_CLASS_TYPE(KeyReleased)
		KeyReleasedEvent(int keycode) : KeyEvent(keycode) {}
	};
}

#endif //CYNTHIA_EVENT_KEY_EVENT_H
