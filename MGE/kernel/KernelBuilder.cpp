#include "KernelBuilder.h"
#include "KernelSystemFactory.h"
#include "Kernel.h"
#include "KernelSystem.h"

using namespace mge;
using namespace std;

KernelBuilder::KernelBuilder() { }
KernelBuilder::~KernelBuilder() {
	for (FactoryList::iterator i = factories.begin(); i != factories.end(); ++i) {
		delete i->first;
	}
}

void KernelBuilder::addFactory(short weight, KernelSystemFactory *factory) {
	factories.push_back(make_pair(factory, weight));
}

Kernel KernelBuilder::buildKernel(Logger &logger) const {
	KernelSystemMap systemmap;
	Kernel kernel;
	
	for (FactoryList::const_iterator i = factories.begin(); i != factories.end(); ++i) {
		KernelSystem *system = i->first->makeKernelSystem(logger, systemmap);
		
		systemmap[system->getName()] = system;
		kernel.addSystem(system, i->second);
	}
	
	return kernel;
}
