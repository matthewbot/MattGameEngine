#include "AudioSystemFactory.h"
#include "AudioSystem.h"
#include <MGE/snd/builtin/OggLoader.h>
#include <MGE/snd/builtin/WavLoader.h>
#include <MGE/util/StandardFileStreamProducer.h>
#include <MGE/kernel/factoryutils.h>

using namespace mge;

AudioSystemFactory::AudioSystemFactory() { }
AudioSystemFactory::~AudioSystemFactory() { }

KernelSystem *AudioSystemFactory::makeKernelSystem(Logger &logger, const KernelSystemMap &map) {
	AudioSystem *snd = new AudioSystem(logger);
	
	FileStreamProducer *prod = findInterface<FileStreamProducer>(map);
	if (!prod)
		prod = &StandardFileStreamProducer::inst;
	
	snd->addLoader(new OggLoader(logger, *prod));
	snd->addLoader(new WavLoader(logger, *prod));
	
	return snd;
}
