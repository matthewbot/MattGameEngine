#ifndef MGE_SND_CLIP_H
#define MGE_SND_CLIP_H

#include <boost/noncopyable.hpp>
#include <string>

namespace mge {
	class ClipPlayback;

	class Clip : boost::noncopyable {
		friend class AudioSystem;

		public:
			inline Clip(const std::string &name) { this->name = name; }
			inline virtual ~Clip() { };

			virtual ClipPlayback *makePlayback() = 0;
			
			inline const std::string &getName() const { return name; }

			inline bool operator<(const Clip &c) const { return name < c.name; }

		private:
			virtual void updatePlayback() = 0; // for AudioSystem

			std::string name;
	};
}

#endif
