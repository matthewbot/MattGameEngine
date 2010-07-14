#include "FrameRateLimiterFactory.h"
#include "FrameRateLimiter.h"

using namespace mge;

FrameRateLimiterFactory::FrameRateLimiterFactory(int fps) : fps(fps) { }

KernelSystem *FrameRateLimiterFactory::makeKernelSystem(Logger &logger, const KernelSystemMap &map) {
	return new FrameRateLimiter(fps);
}

