#ifndef MGE_NET_NETWORKSYSTEMFACTORY_H
#define MGE_NET_NETWORKSYSTEMFACTORY_H

#include <MGE/kernel/KernelSystemFactory.h>

namespace mge {
	class NetworkSystemFactory : public KernelSystemFactory {
		public:
			NetworkSystemFactory();
			virtual ~NetworkSystemFactory();
			
			virtual KernelSystem *makeKernelSystem(Logger &logger, const KernelSystemMap &map);
	};
}

#endif
