#ifndef MGE_SND_SINGLECLIPPLAYBACK_H
#define MGE_SND_SINGLECLIPPLAYBACK_H

#include "BasePlayback.h"

namespace mge {
	class SingleClip;
	class SourceManager;
	template <typename T> class BaseClip;

	class SingleClipPlayback : public BasePlayback<SingleClip> {
		friend class SingleClip;
		friend class BaseClip<SingleClipPlayback>;

		public:
			virtual ~SingleClipPlayback();
			virtual void setLoop(bool loop);

		protected:
			virtual void start();

		private:
			void update(); // for BaseClip<SingleClipPlayback> to call
			SingleClipPlayback(SourceManager *sourceman, SingleClip *clip, Logger &logger); // for SingleClip to create us
	};
}

#endif
