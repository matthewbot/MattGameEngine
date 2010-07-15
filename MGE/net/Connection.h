#ifndef MGE_NET_CONNECTION_H
#define MGE_NET_CONNECTION_H

#include <list>
#include "Message.h"

extern "C" {
	typedef struct _ENetPeer ENetPeer;
}

namespace mge {
	class Connection {
		friend class NetworkSystem;

		public:
			~Connection(); // must dealloc peer

			enum State { ESTABLISHING, CONNECTED, DISCONNECTING, DISCONNECTED, TIMEOUT };
			inline State getState() { return state; }

			bool messageAvailable() const;
			Message getMessage();

			void sendMessage(const Message &msg);

			void disconnect();
			void reset();

		private:
			Connection(ENetPeer *peer, State state);

			void onMessageReceived(const Message &msg); // for NetworkSystem
			void onConnected();
			void onDisconnected();
			void onTimedOut();

			State state;
			ENetPeer *peer;
			std::list<Message> messagebuf;
	};
}

#endif
