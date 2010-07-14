#ifndef MGE_SND_AUDIOSYSTEM_H
#define MGE_SND_AUDIOSYSTEM_H

#include "AudioListener.h"
#include "SourceManager.h"
#include <MGE/kernel/KernelSystem.h>
#include <boost/scoped_ptr.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>
#include <list>
#include <vector>

namespace mge {
	class AudioLoader;
	class Clip;
	class Logger;
	
	class AudioSystem : public KernelSystem {
		friend class Clip; // TODO see if these are needed
		friend class ClipPlayback;

		public:
			AudioSystem(Logger &logger);
			virtual ~AudioSystem();

			void addLoader(AudioLoader *loader);

			boost::shared_ptr<Clip> loadClip(const std::string &str, bool stream);

			inline AudioListener &getListener() { return listener; }
			inline const AudioListener &getListener() const { return listener; }

			virtual SystemUpdateValue update();
			virtual const char *getName() const;
		private:
			void initContext();
			void makeSources();
			
			Logger &logger;
			
			struct SubSystemHandler {
				SubSystemHandler(Logger &logger);
				~SubSystemHandler();
				
				struct ALdata;
				boost::scoped_ptr<ALdata> aldata; // pimpl-esque thing to avoid having to pull in AL/al.h
			} subsystem;
			AudioListener listener;
			SourceManager sources;

			typedef std::list<boost::weak_ptr<Clip> > ClipList;
			typedef std::vector<AudioLoader *> LoaderList;

			ClipList clips;
			LoaderList loaders;
	};
}
#endif
