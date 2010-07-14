#ifndef MGE_SND_OGGSTREAM_H
#define MGE_SND_OGGSTREAM_H

#include <MGE/snd/file/AudioStream.h>
#include <boost/scoped_ptr.hpp>
#include <string>

namespace mge {
	class FileStreamProducer;

	class OggStream : public AudioStream {
		friend class OggFile;

		public:
			virtual ~OggStream();

			virtual void load(char *buf, int length);
			virtual void rewind();
			virtual int available() const;

		private:
			OggStream(const std::string &filename, int bytespersample, FileStreamProducer &fsp);

			std::string filename;
			int bytespersample;
			bool atbeginning; // used to optimize out unecessary rewinds, which currently just close and open the file
			
			struct VBdata;
			boost::scoped_ptr<VBdata> data;
			
			FileStreamProducer &fsp;
	};
}

#endif
