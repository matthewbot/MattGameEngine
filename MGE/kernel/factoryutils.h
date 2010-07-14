#ifndef MGE_KERNEL_FACTORYUTILS_H
#define MGE_KERNEL_FACTORYUTILS_H

#include "KernelSystemFactory.h"

namespace mge {
	template <class C> C *findInterface(const KernelSystemMap &map) {
		for (typename KernelSystemMap::const_iterator i = map.begin(); i != map.end(); ++i) {
			C *ret = dynamic_cast<C *>(i->second);
			if (ret)
				return ret;
		}
		
		return 0;
	}
}
#endif
