#include "InputDispatcher.h"
#include <MGE/util/Exception.h>
#include <functional>

using namespace mge;
using namespace boost;
using namespace std;

InputDispatcher::InputDispatcher() { }
InputDispatcher::~InputDispatcher() { }

void InputDispatcher::add(InputListener &listener) {
	listeners.push_back(&listener);
}

void InputDispatcher::remove(InputListener &listener) {
	remove_if(listeners.begin(), listeners.end(), bind1st(equal_to<InputListener *>(), &listener));
}

namespace {
	template <typename T> struct WeakPtrEqual {
		shared_ptr<T> ptr;
		WeakPtrEqual(const shared_ptr<T> &ptr) : ptr(ptr) { }
		
		bool operator()(const weak_ptr<T> &weakptr) { return weakptr.lock() == ptr; }
	};
}

// TODO: Ditch ugly copy-paste

void InputDispatcher::mouseMoved(int x, int y) {
	for (ListenerList::iterator i = listeners.begin(); i != listeners.end(); ++i) {
		(*i)->mouseMoved(x, y);
	}	
}

void InputDispatcher::mouseDown(MouseButton button) {
	for (ListenerList::iterator i = listeners.begin(); i != listeners.end(); ++i) {
		(*i)->mouseDown(button);
	}	
}

void InputDispatcher::mouseUp(MouseButton button) {
	for (ListenerList::iterator i = listeners.begin(); i != listeners.end(); ++i) {
		(*i)->mouseUp(button);
	}	
}

void InputDispatcher::keyDown(KeyCode key, char ch) { 
	for (ListenerList::iterator i = listeners.begin(); i != listeners.end(); ++i) {
		(*i)->keyDown(key, ch);
	}	
}

void InputDispatcher::keyUp(KeyCode key) {
	for (ListenerList::iterator i = listeners.begin(); i != listeners.end(); ++i) {
		(*i)->keyUp(key);
	}	
}

void InputDispatcher::exitEvent() {
	for (ListenerList::iterator i = listeners.begin(); i != listeners.end(); ++i) {
		(*i)->exitEvent();
	}	
}
