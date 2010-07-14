#ifndef MGE_UTIL_FRAMERATELIMITERFACTORY_H
#define MGE_UTIL_FRAMERATELIMITERFACTORY_H

#include <MGE/kernel/KernelSystemFactory.h>

namespace mge {
	class FrameRateLimiterFactory : public KernelSystemFactory {
		public:
			FrameRateLimiterFactory(int fps);
			virtual KernelSystem *makeKernelSystem(Logger &logger, const KernelSystemMap &map);
			
		private:
			int fps;
	};
}

#endif
