#include "WindowInput.h"
#include <MGE/util/Exception.h>
#include <algorithm>
#include <MGE/util/input/KeyCodes.h>
#include <SDL/SDL.h>

using namespace mge;
using namespace std;
using namespace boost;

WindowInput::WindowInput(int width, int height) : width(width), height(height) { 
	SDL_EnableUNICODE(true);
}

void WindowInput::update() {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
			case SDL_QUIT:
				dispatch.exitEvent();
				break;

			case SDL_KEYDOWN:
			case SDL_KEYUP:
			{
				KeyCode key = convertKey(event.key.keysym.sym);
				
				if (key != 0) {
					if (event.type == SDL_KEYDOWN) {		
						int unicode = event.key.keysym.unicode;
						if (unicode) {
							if (unicode & 0xFF80)
								unicode = 0;
							else
								unicode &= 0x7F;
						}
						
						dispatch.keyDown(key, (char)unicode);
					} else
						dispatch.keyUp(key);
				}
				
				break;
			}

			case SDL_MOUSEMOTION:
				dispatch.mouseMoved(event.motion.x, height - event.motion.y);
				break;
				
			case SDL_MOUSEBUTTONDOWN:
				dispatch.mouseDown(event.button.button);
				break;
				
			case SDL_MOUSEBUTTONUP:
				dispatch.mouseUp(event.button.button);
				break;
		}
	}
}

WindowInput::KeyCodeConvertor::KeyCodeConvertor() {
	lookup[SDLK_LEFT] = keycodes::left;
	lookup[SDLK_RIGHT] = keycodes::right;
	lookup[SDLK_UP] = keycodes::up;
	lookup[SDLK_DOWN] = keycodes::down;

	lookup[SDLK_LCTRL] = keycodes::lcontrol;
	lookup[SDLK_LSHIFT] = keycodes::lshift;
	lookup[SDLK_LALT] = keycodes::lalt;
	lookup[SDLK_RCTRL] = keycodes::rcontrol;
	lookup[SDLK_RSHIFT] = keycodes::rshift;
	lookup[SDLK_RALT] = keycodes::ralt;
}

KeyCode WindowInput::KeyCodeConvertor::operator()(int sdlkey) const {
	if (sdlkey < 128) // SDL cleverly matches ASCII for the first 128 chars
		return (KeyCode)sdlkey;
	else {
		LookupMap::const_iterator i = lookup.find(sdlkey);
		if (i != lookup.end())
			return i->second;
		else
			return 0;
	}
}

const WindowInput::KeyCodeConvertor WindowInput::convertKey;
