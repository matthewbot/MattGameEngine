#ifndef MGE_SND_SINGLECLIP_H
#define MGE_SND_SINGLECLIP_H

#include "BaseClip.h"
#include "SingleClipPlayback.h"

namespace mge {
	class AudioFile;

	// singleclip is a base class that represents any clip that is loaded into a single OpenAL buffer
	class SingleClip : public BaseClip<SingleClipPlayback> {
		public:
			SingleClip(const std::string &name, SourceManager *sourceman, AudioFile *file, Logger &logger); // for AudioSystem
			virtual ~SingleClip();
		
			virtual ClipPlayback *makePlayback();
			
			inline unsigned int getBufID() { return bufid; }
			
		private:
			unsigned int bufid;
	};
}

#endif
