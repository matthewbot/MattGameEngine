#ifndef MGE_KERNEL_H
#define MGE_KERNEL_H

#include "KernelSystemEntry.h"
#include <vector>

namespace mge {
	class Kernel {
		typedef std::vector<KernelSystemEntry> SystemList;
		public:
			Kernel();
			~Kernel();

			void addSystem(const KernelSystemEntry &entry);
			void addSystem(KernelSystem *system, short weight);
			void run();

			typedef SystemList::const_iterator const_iterator;
			const_iterator begin();
			const_iterator end();

		private:
			SystemList systems;
	};
}
#endif
