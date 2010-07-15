#ifndef MGE_KERNEL_SYSTEMENTRY_H
#define MGE_KERNEL_SYSTEMENTRY_H

#include "KernelSystem.h"
#include <boost/shared_ptr.hpp>

namespace mge {
	class KernelSystemEntry {
		friend class Kernel;
	
		public:
			KernelSystemEntry(KernelSystem *sys, short weight);

			bool operator==(const KernelSystemEntry &entry) const;
			bool operator<(const KernelSystemEntry &entry) const;

			inline KernelSystem &get() const { return *sys; }
			inline KernelSystem *operator->() const { return &*sys; }

		private:
			boost::shared_ptr<KernelSystem> sys; // make us copyable
			short weight;
						
			inline void clear() { sys.reset(); }
	};
}

#endif
