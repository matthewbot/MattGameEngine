#ifndef MGE_KERNEL_KERNELBUILDER_H
#define MGE_KERNEL_KERNELBUILDER_H

#include <boost/noncopyable.hpp>
#include <vector>
#include "KernelSystemFactory.h"
#include <utility>

namespace mge {
	class Kernel;
	class Logger;

	class KernelBuilder : boost::noncopyable {
		public:
			KernelBuilder();
			~KernelBuilder();
			
			void addFactory(short weight, KernelSystemFactory *factory);
			Kernel buildKernel(Logger &logger) const;
			
		private:
			typedef std::vector<std::pair<KernelSystemFactory *, short> > FactoryList;
			FactoryList factories;
	};
}

#endif
