#ifndef MGETEST_TESTSYSTEMFACTORY_H
#define MGETEST_TESTSYSTEMFACTORY_H

#include <MGE/kernel/KernelSystemFactory.h>

namespace mgetest {
	class TestSystemFactory : public mge::KernelSystemFactory {
		public:
			TestSystemFactory();
			
			virtual mge::KernelSystem *makeKernelSystem(mge::Logger &logger, const mge::KernelSystemMap &map);
	};
}

#endif
