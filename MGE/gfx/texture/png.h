#ifndef MGE_GFX_PNG_H
#define MGE_GFX_PNG_H

#include "PixMap.h"
#include <istream>
#include <ostream>

namespace mge {
	PixMap loadPNG(std::istream &stream);
	void savePNG(const PixMap &map, std::ostream &stream);
}

#endif
