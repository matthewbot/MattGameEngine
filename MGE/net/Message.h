#ifndef MGE_NET_MESSAGE_H
#define MGE_NET_MESSAGE_H

#include <MGE/util/Blob.h>
#include <string>

namespace mge {
	class Message {
		public:
			enum Type { NORMAL, SEQUENCED, RELIABLE };

			Message();
			Message(const Blob &d, int chan, Type t=NORMAL);

			inline const Blob &getData() const { return data; }
			inline int getChannel() const { return channel; }
			inline Type getType() const { return type; }

		private:
			Blob data;
			int channel;
			Type type;
	};
	

}

#endif
