#include "InputAccumulator.h"

using namespace mge;

InputAccumulator::InputAccumulator() : mousex(0), mousey(0), wantexit(false) { }
InputAccumulator::~InputAccumulator() { }

void InputAccumulator::update() {
	keys_pressed.clear();
	keys_released.clear();
	wantexit = false;
}


bool InputAccumulator::isKeyDown(KeyCode key) const { return keys.find(key) != keys.end(); }
bool InputAccumulator::isKeyPressed(KeyCode key) const { return keys_pressed.find(key) != keys_pressed.end(); }
bool InputAccumulator::isKeyReleased(KeyCode key) const { return keys_released.find(key) != keys_released.end(); }
bool InputAccumulator::isMouseButtonDown(MouseButton button) const { return buttons.find(button) != buttons.end(); }

void InputAccumulator::mouseMoved(int mousex, int mousey) {
	this->mousex = mousex;
	this->mousey = mousey;
}

void InputAccumulator::mouseDown(MouseButton button) {
	buttons.insert(button);
}

void InputAccumulator::mouseUp(MouseButton button) {
	buttons.erase(button);
}

void InputAccumulator::keyDown(KeyCode key, char ch) {
	keys_pressed.insert(key);
	keys.insert(key);
}

void InputAccumulator::keyUp(KeyCode key) {
	keys_released.insert(key);
	keys.erase(key);
}
void InputAccumulator::exitEvent() {
	wantexit = true;
}


