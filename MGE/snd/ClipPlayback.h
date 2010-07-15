#ifndef MGE_SND_CLIPPLAYBACK_H
#define MGE_SND_CLIPPLAYBACK_H

#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>

namespace mge {
	class SourceHandle;
	class SourceManager;

	class ClipPlayback : boost::noncopyable { 
		public:
			virtual ~ClipPlayback();

			enum State { WAITING, PLAYING, PAUSED, STOPPED };

			inline float getX() const { return xpos; }
			inline float getY() const { return ypos; }
			inline float getGain() const { return gain; }
			inline bool getRelative() const { return relative; }
			inline bool getLoop() const { return loop; }
			inline float getMinDist() const { return mindist; }
			inline float getMaxDist() const { return maxdist; }
			inline float getPitch() const { return pitch; }
			inline int getPriority() const { return priority; }
			State getState() const;

			void setPos(float x, float y);
			void setGain(float gain);
			void setRelative(bool relative);
			virtual void setLoop(bool loop);
			void setDist(float min, float max);
			void setPitch(float pitch);

			void play();
			void pause();
			void stop();

		protected:
			ClipPlayback(SourceManager *sourceman);	

			virtual void start() = 0;

			void getSource();

			boost::shared_ptr<SourceHandle> source;
			bool wantplay;

		private:
			SourceManager *sourceman;

			float xpos, ypos;
			float mindist, maxdist;
			float pitch, gain;
			bool relative;
			int priority;
			bool loop;
	};
}

#endif
