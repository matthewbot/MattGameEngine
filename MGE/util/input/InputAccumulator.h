#ifndef MGE_UTIL_INPUTACCUMULATOR_H
#define MGE_UTIL_INPUTACCUMULATOR_H

#include "InputListener.h"
#include <set>

namespace mge {
	class InputAccumulator : public InputListener {
		public:
			InputAccumulator();
			virtual ~InputAccumulator();
			
			void update();
			
			bool isKeyDown(KeyCode code) const;
			bool isKeyPressed(KeyCode code) const;
			bool isKeyReleased(KeyCode code) const;
			inline bool getExit() const { return wantexit; }
			
			bool isMouseButtonDown(MouseButton button) const;
			inline float getMouseX() const { return mousex; }
			inline float getMouseY() const { return mousey; }
			
			// InputListener
			
			virtual void mouseMoved(int x, int y);
			virtual void mouseDown(MouseButton button);
			virtual void mouseUp(MouseButton button);
			
			virtual void keyDown(KeyCode key, char ch);
			virtual void keyUp(KeyCode key);
			
			virtual void exitEvent();
			
		private:
			std::set<KeyCode> keys;		
			std::set<KeyCode> keys_pressed;
			std::set<KeyCode> keys_released;
			std::set<MouseButton> buttons;
			
			float mousex, mousey;
			bool wantexit;
	};
}

#endif

