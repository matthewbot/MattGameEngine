#include "NetworkSystemFactory.h"
#include "NetworkSystem.h"

using namespace mge;

NetworkSystemFactory::NetworkSystemFactory() { }
NetworkSystemFactory::~NetworkSystemFactory() { }

KernelSystem *NetworkSystemFactory::makeKernelSystem(Logger &logger, const KernelSystemMap &map) {
	return new NetworkSystem(logger);
}
