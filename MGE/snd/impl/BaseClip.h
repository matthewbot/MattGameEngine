#ifndef MGE_SND_BASECLIP_H
#define MGE_SND_BASECLIP_H

#include <MGE/snd/Clip.h>
#include <string>
#include <list>

namespace mge {
	class SourceManager;
	class Logger;
	class Playback;

	template <class PlaybackType> class BaseClip : public Clip {
		template <class T> friend class BasePlayback;

		protected:
			BaseClip(const std::string &name, SourceManager *sourceman, Logger &logger) : Clip(name), logger(logger) { 
				this->sourceman = sourceman;
			}

			SourceManager *sourceman;
			Logger &logger;
		private:
			typedef PlaybackType Playback; // for BasePlayback

			typedef std::list<Playback *> PlaybackList;
			PlaybackList playbacks;

			void registerPlayback(Playback *playback) { playbacks.push_back(playback); } 
			void unregisterPlayback(Playback *playback) {
				for (typename PlaybackList::iterator i = playbacks.begin(); i != playbacks.end(); ++i) {
					if (*i == playback) {
						playbacks.erase(i);
						return;
					}
				}
				
				return;
			}

			virtual void updatePlayback() { // for AudioSystem
				for (typename PlaybackList::iterator i = playbacks.begin(); i != playbacks.end(); ++i)
					(*i)->update();
			}
	};
}

#endif
