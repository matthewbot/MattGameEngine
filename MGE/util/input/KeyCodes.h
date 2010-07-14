#ifndef MGE_UTIL_INPUT_H
#define MGE_UTIL_INPUT_H

namespace mge {
	// Keycode represents a raw key on the keyboard. Shift is a key, not a modifier. 
	// All keys on keyboard that have ASCII codes use their lowercase version. Enter = 13
	typedef unsigned short KeyCode;
	typedef unsigned char MouseButton;

	namespace keycodes {
		static const KeyCode enter = 13; // ASCII
		static const KeyCode escape = 27;
	
		namespace {
			static const KeyCode CUSTOM = 1337;
			static const KeyCode MODIFIERS = CUSTOM + 0;
			static const KeyCode ARROWS = CUSTOM + 10;
			static const KeyCode MISC = CUSTOM + 20;
		}

		static const KeyCode lcontrol = MODIFIERS + 0;
		static const KeyCode lshift = MODIFIERS + 1;
		static const KeyCode lalt = MODIFIERS + 2;
		static const KeyCode rcontrol = MODIFIERS + 3;
		static const KeyCode rshift = MODIFIERS + 4;
		static const KeyCode ralt = MODIFIERS + 5;

		static const KeyCode left = ARROWS + 0;
		static const KeyCode right = ARROWS + 1;
		static const KeyCode up = ARROWS + 2;
		static const KeyCode down = ARROWS + 3;
	}
	
	namespace mousebtns {
		static const MouseButton left = 1;
		static const MouseButton right = 3;
		static const MouseButton middle = 2;
		static const MouseButton wheelup = 4;
		static const MouseButton wheeldown = 5;
	}
}

#endif
