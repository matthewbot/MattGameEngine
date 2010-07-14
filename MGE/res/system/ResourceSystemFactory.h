#ifndef MGE_GFX_RESOURCESYSTEMFACTORY_H
#define MGE_GFX_RESOURCESYSTEMFACTORY_H

#include <MGE/kernel/KernelSystemFactory.h>
#include <boost/function.hpp>
#include <vector>
#include <string>

namespace mge {
	class ResourceSystem;
	class ResourceFactory;
	class TextureManager;

	class ResourceSystemFactory : public KernelSystemFactory {
		public:
			typedef boost::function<void (ResourceSystem &, const KernelSystemMap &)> InitFunc;
		
			ResourceSystemFactory();
			ResourceSystemFactory(const std::string &resfile);
			ResourceSystemFactory(const InitFunc &initfunc);
			virtual ~ResourceSystemFactory();
			
			KernelSystem *makeKernelSystem(Logger &logger, const KernelSystemMap &map);
			
		private:
			InitFunc initfunc;
	};
}

#endif
