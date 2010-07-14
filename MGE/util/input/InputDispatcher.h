#ifndef MGE_UTIL_INPUTDISPATCHER_H
#define MGE_UTIL_INPUTDISPATCHER_H

#include "InputListener.h"
#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp> 
#include <vector>

namespace mge {
	class InputDispatcher : public InputListener {
		public:
			InputDispatcher();
			~InputDispatcher();
			
			void add(InputListener &listener);
			void remove(InputListener &listener);
			
			// InputListener
			
			virtual void mouseMoved(int x, int y);
			virtual void mouseDown(MouseButton button);
			virtual void mouseUp(MouseButton button);
			
			virtual void keyDown(KeyCode key, char ch);
			virtual void keyUp(KeyCode key);
			
			virtual void exitEvent();
			
		private:
			typedef std::vector<InputListener *> ListenerList;
			ListenerList listeners;
	};
}

#endif
