#ifndef MGE_SND_BASEPLAYBACK_H
#define MGE_SND_BASEPLAYBACK_H

#include <MGE/snd/ClipPlayback.h>

namespace mge {
	class Logger;
	class SourceManager;

	template <class ClipType> class BasePlayback : public ClipPlayback {
		public:
			BasePlayback(SourceManager *sourceman, ClipType *clip, Logger &logger) : ClipPlayback(sourceman), logger(logger), clip(clip) {
				clip->registerPlayback((typename ClipType::Playback *)this);
			}

			virtual ~BasePlayback() {
				clip->unregisterPlayback((typename ClipType::Playback *)this);
			}

		protected:
			Logger &logger;
			ClipType *clip;
	};
}

#endif
