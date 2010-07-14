#include "ResourceSystemFactory.h"
#include "ResourceSystem.h"
#include <MGE/util/StandardFileStreamProducer.h>
#include <MGE/gfx/system/GraphicsSystem.h>
#include <MGE/res/SpriteFactory.h>
#include <MGE/res/FontFactory.h>
#include <MGE/res/ShaderFactory.h>
#include <MGE/kernel/factoryutils.h>

using namespace mge;
using namespace std;

namespace {
	void nullInitFunc(ResourceSystem &res, const KernelSystemMap &map) { }
	
	struct resfileInitFunc {
		string resfile;
		
		resfileInitFunc(const string &resfile) : resfile(resfile) { }
		
		void operator()(ResourceSystem &res, const KernelSystemMap &map) { res.loadFile(resfile); }
	};
}

ResourceSystemFactory::ResourceSystemFactory() : initfunc(&nullInitFunc) { }
ResourceSystemFactory::ResourceSystemFactory(const string &resfile) : initfunc(resfileInitFunc(resfile)) { }
ResourceSystemFactory::ResourceSystemFactory(const InitFunc &initfunc) : initfunc(initfunc) { }
ResourceSystemFactory::~ResourceSystemFactory() { }

KernelSystem *ResourceSystemFactory::makeKernelSystem(Logger &logger, const KernelSystemMap &map) {
	FileStreamProducer *prod = findInterface<FileStreamProducer>(map);
	if (!prod)
		prod = &StandardFileStreamProducer::inst;

	ResourceSystem *res = new ResourceSystem(*prod, logger);
	
	KernelSystemMap::const_iterator i = map.find("GraphicsSystem");
	if (i != map.end()) {
		GraphicsSystem &gfx = (GraphicsSystem &)*i->second;
		res->registerResourceFactory(new SpriteFactory(gfx.getTextureManager()));
		res->registerResourceFactory(new FontFactory(gfx.getTextureManager(), StandardFileStreamProducer::inst));
		res->registerResourceFactory(new ShaderFactory(gfx.getShaderManager()));
	}
	
	initfunc(*res, map);
	
	return res;
}
