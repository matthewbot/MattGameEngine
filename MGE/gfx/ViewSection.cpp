#include "ViewSection.h"

using namespace mge;

bool ViewSection::inside(int xp, int yp) const { 
	return xp >= x && yp >= y && xp <= x + w && yp <= y + h;
}

bool ViewSection::operator==(const ViewSection &sect) const { 
	return x == sect.x && y == sect.y && w == sect.w && h == sect.h;
}
