#ifndef MGE_SND_MULTICLIP_H
#define MGE_SND_MULTICLIP_H

#include "MultiClipPlayback.h"
#include "BaseClip.h"
#include <boost/scoped_ptr.hpp>

namespace mge {
	class SourceManager;
	class AudioFile;
	class Logger;

	class MultiClip : public BaseClip<MultiClipPlayback> {
		friend class MultiClipPlayback;

		public:
			MultiClip(const std::string &name, SourceManager *sourceman, AudioFile *file, Logger &logger, int bufcount, size_t bufsize);
			virtual ~MultiClip();
		
			virtual ClipPlayback *makePlayback();

		private:
			boost::scoped_ptr<AudioFile> file;

			int bufcount;
			int bufsize;
	};
}

#endif
