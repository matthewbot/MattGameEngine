#ifndef MGE_KERNEL_KERNELSYSTEMFACTORY_H
#define MGE_KERNEL_KERNELSYSTEMFACTORY_H

#include <map>
#include <string>

namespace mge {
	class KernelSystem;
	class Logger;

	typedef std::map<std::string, KernelSystem *> KernelSystemMap;

	class KernelSystemFactory {
		public:
			inline virtual ~KernelSystemFactory() { }
			
			virtual KernelSystem *makeKernelSystem(Logger &logger, const KernelSystemMap &map) = 0;
	};
}

#endif
