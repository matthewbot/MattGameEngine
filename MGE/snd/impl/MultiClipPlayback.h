#ifndef MGE_SND_MULTICLIPPLAYBACK_H
#define MGE_SND_MULTICLIPPLAYBACK_H

#include "BasePlayback.h"
#include <set>
#include <list>
#include <boost/scoped_array.hpp>
#include <boost/scoped_ptr.hpp>

namespace mge {
	class MultiClip;
	template <typename T> class BaseClip;
	class AudioStream;

	class MultiClipPlayback : public BasePlayback<MultiClip> {
		friend class MultiClip;
		friend class BaseClip<MultiClipPlayback>;

		public:
			virtual void setLoop(bool loop);

		protected:
			virtual void start();
			virtual ~MultiClipPlayback();

		private:
			MultiClipPlayback(SourceManager *sourceman, MultiClip *clip, Logger &logger); // for MultiClip to create us
			
			void update(); // for BaseClip<MultiClipPlayback> to call

			void fillBufs(); // unqueues buffers, fills them and queues them again. Returns true if there are any buffers queued
			bool fillBuf(int buf);

			typedef std::set<unsigned int> BufSet;
			typedef std::list<unsigned int> BufList;

			BufList bufs_unqueued;
			BufSet bufs_queued;

			boost::scoped_array<char> buf;
			boost::scoped_ptr<AudioStream> stream;
	};
}

#endif
