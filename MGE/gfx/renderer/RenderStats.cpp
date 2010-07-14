#include "RenderStats.h"

using namespace mge;
using namespace std;

ostream &mge::operator<<(ostream &stream, const RenderStats &stats) {
	stream << "Verts " << stats.verts << " Batches " << stats.batches;

	return stream;
}
