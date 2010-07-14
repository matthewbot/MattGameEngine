#ifndef MGE_GFX_GRAPHICSSYSTEMFACTORY_H
#define MGE_GFX_GRAPHICSSYSTEMFACTORY_H

#include <MGE/kernel/KernelSystemFactory.h>
#include <string>

namespace mge {
	class GraphicsSystemFactory : public KernelSystemFactory {
		public:
			GraphicsSystemFactory(int w, int h, bool vsync, const std::string &title="Matt's Game Engine");
			
			virtual KernelSystem *makeKernelSystem(Logger &logger, const KernelSystemMap &map);
			
		private:
			int w, h;
			bool vsync;
			std::string title;
	};
}

#endif
