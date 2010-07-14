#ifndef MGE_SND_BUFUTIL_H
#define MGE_SND_BUFUTIL_H

namespace mge {
	// --- utility functions		
	int getBufferID(); // utility methods for allocating and freeing OpenAL buffers
	void freeBufferID(int bufid);
}

#endif
