#include "Kernel.h"
#include <MGE/util/Exception.h>
#include <exception>
#include <algorithm>

using namespace mge;
using namespace std;
using namespace boost;

Kernel::Kernel() { }
Kernel::~Kernel() {
	for (SystemList::reverse_iterator i = systems.rbegin(); i != systems.rend(); ++i) { // ensure we clear pointers in reverse order. 
		i->clear();
	}
}

void Kernel::addSystem(const KernelSystemEntry &entry) {
	systems.push_back(entry);
}
void Kernel::addSystem(KernelSystem *sys, short weight) {
	systems.push_back(KernelSystemEntry(sys, weight));
}

Kernel::const_iterator Kernel::begin() { return systems.begin(); }
Kernel::const_iterator Kernel::end() { return systems.end(); }

void Kernel::run() {
	bool end = false;
	SystemList sortedsystems(systems.begin(), systems.end());
	
	sort(sortedsystems.begin(), sortedsystems.end());

	while (!end) {
		for (SystemList::iterator i = sortedsystems.begin(); i != sortedsystems.end(); ++i) {
			try {
				SystemUpdateValue val = (*i)->update();
				if (val == STOP)
					end = true;
			} catch (std::exception &ex) {
				throw Exception(string("Got exception while updating ") + (*i)->getName() + string(": ") + ex.what());
			}
		}
	}
}
