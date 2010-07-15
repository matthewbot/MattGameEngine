#include "Color.h"

using namespace mge;

const Color Color::fromInt(int r, int g, int b, int a) {
	Color col;
	col.r = (float)r/255;
	col.g = (float)g/255;
	col.b = (float)b/255;
	col.a = (float)a/255;
	
	return col;
}

const Color Color::fromFloat(float r, float g, float b, float a) {
	Color Color;
	Color.r = r;
	Color.g = g;
	Color.b = b;
	Color.a = a;
	
	return Color;
}

const Color Color::WHITE = {1, 1, 1, 1};
const Color Color::BLACK = {0, 0, 0, 1};
const Color Color::RED = {1, 0, 0, 1};
const Color Color::ORANGE = {1, .5, .25, 1};
const Color Color::YELLOW = {1, 1, 0, 1};
const Color Color::GREEN = {0, 1, 0, 1};
const Color Color::BLUE = {0, 0, 1, 1};
const Color Color::PURPLE = {0.75, 0, 1, 1};

