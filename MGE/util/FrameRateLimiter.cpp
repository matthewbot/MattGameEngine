#include "FrameRateLimiter.h"
#include <SDL/SDL.h>

using namespace mge;
using namespace std;

FrameRateLimiter::FrameRateLimiter(int desiredfps) 
: desiredfps(desiredfps), actualfps(0), nextactualfps(0) {
	lastframe = lastsecond = SDL_GetTicks();
}

SystemUpdateValue FrameRateLimiter::update() {
	int now = SDL_GetTicks();

	nextactualfps++;
	if (now - lastsecond > 1000) {
		lastsecond = now;
		actualfps = nextactualfps;
		nextactualfps = 0;
	}
	
	int sleepamt = (int)((1000.0f / desiredfps) - (now - lastframe));
	if (sleepamt > 0) {
		SDL_Delay(sleepamt);
		now = SDL_GetTicks();
	}
	
	tdelta = (now - lastframe) / 1000.0f;
	lastframe = now;
	return NONE;
}

const char *FrameRateLimiter::getName() const { return "FrameRateLimiter"; }

float FrameRateLimiter::getTDelta() const { return tdelta; }
int FrameRateLimiter::getFPS() const { return actualfps; }
