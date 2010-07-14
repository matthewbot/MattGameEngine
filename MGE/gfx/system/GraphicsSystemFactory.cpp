#include "GraphicsSystemFactory.h"
#include "GraphicsSystem.h"
#include <MGE/util/StandardFileStreamProducer.h>
#include <MGE/kernel/factoryutils.h>

using namespace mge;

GraphicsSystemFactory::GraphicsSystemFactory(int w, int h, bool vsync, const std::string &title)
: w(w), h(h), vsync(vsync), title(title) { }

KernelSystem *GraphicsSystemFactory::makeKernelSystem(Logger &logger, const KernelSystemMap &map) {
	KernelSystemMap::const_iterator i = map.find("FileSystem");
	
	FileStreamProducer *prod = findInterface<FileStreamProducer>(map);
	if (!prod)
		prod = &StandardFileStreamProducer::inst;

	return new GraphicsSystem(logger, *prod, w, h, vsync, title);
}


