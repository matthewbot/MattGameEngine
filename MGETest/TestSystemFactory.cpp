#include "TestSystemFactory.h"
#include "TestSystem.h"
#include <MGE/gfx/system/GraphicsSystem.h>
#include <MGE/res/system/ResourceSystem.h>
#include <MGE/snd/system/AudioSystem.h>
#include <cassert>

using namespace mgetest;
using namespace mge;


TestSystemFactory::TestSystemFactory() { }

KernelSystem *TestSystemFactory::makeKernelSystem(Logger &logger, const KernelSystemMap &map) {
	KernelSystemMap::const_iterator i = map.find("GraphicsSystem");
	assert(i != map.end());
		
	GraphicsSystem &gfx = (GraphicsSystem &)*i->second;
	
	i = map.find("ResourceSystem");
	assert(i != map.end());

	ResourceSystem &res = (ResourceSystem &)*i->second;
	
	i = map.find("AudioSystem");
	assert(i != map.end());
	
	AudioSystem &snd = (AudioSystem &)*i->second;

	return new TestSystem(gfx, res, snd);
}

