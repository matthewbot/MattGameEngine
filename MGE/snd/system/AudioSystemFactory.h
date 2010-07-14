#ifndef MGE_SND_AUDIOSYSTEMFACTORY_H
#define MGE_SND_AUDIOSYSTEMFACTORY_H

#include <MGE/kernel/KernelSystemFactory.h>

namespace mge {
	class AudioSystemFactory : public KernelSystemFactory {
		public:
			AudioSystemFactory();
			virtual ~AudioSystemFactory();
			
			virtual KernelSystem *makeKernelSystem(Logger &logger, const KernelSystemMap &map);
	};
}

#endif
