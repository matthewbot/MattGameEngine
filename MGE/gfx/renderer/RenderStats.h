#ifndef MGE_RENDERSTATS_H
#define MGE_RENDERSTATS_H

#include <ostream>

namespace mge {
	struct RenderStats {
		int verts;
		int batches;
	};
	
	std::ostream &operator<<(std::ostream &stream, const RenderStats &stats);
}

#endif
