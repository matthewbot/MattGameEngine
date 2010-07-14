#ifndef MGE_UTIL_INPUTLISTENER_H
#define MGE_UTIL_INPUTLISTENER_H

#include "KeyCodes.h"

namespace mge {
	class InputListener {
		public:
			inline virtual ~InputListener() { }
			
			virtual void mouseMoved(int x, int y) = 0;
			virtual void mouseDown(MouseButton button) = 0;
			virtual void mouseUp(MouseButton button) = 0;
			
			virtual void keyDown(KeyCode key, char ch) = 0;
			virtual void keyUp(KeyCode key) = 0;
			
			virtual void exitEvent() = 0;
	};
}

#endif
