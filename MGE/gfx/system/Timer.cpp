#include "Timer.h"
#include <SDL/SDL.h>

using namespace mge;

Timer::Timer() : tdelta(0), lastupdate(0), curfps(0), fpsctr(0), fpstimer(0) { }
Timer::~Timer() { }

float Timer::getTDelta() const { return tdelta; }
int Timer::getFPS() const { return curfps; }

void Timer::update() {
	int ticks = SDL_GetTicks();

	if (lastupdate != 0) 
		tdelta = (float)(ticks - lastupdate)/1000.0f;
	lastupdate = ticks;
	
	fpsctr++;
	fpstimer += tdelta;
	if (fpstimer >= 1) {
		curfps = fpsctr;
		fpstimer = 0;
		fpsctr = 0;
	}
}
