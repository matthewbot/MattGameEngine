#ifndef MGE_NET_UTILS_H
#define MGE_NET_UTILS_H

#include "Message.h"
#include <enet/enet.h>
#include <ostream>

namespace mge {
	ENetPeer *enet_host_getpeer(ENetHost *host, ENetPeer *curpeer);

	std::ostream &operator<<(std::ostream &stream, const ENetAddress &addr);
	
	int typeToEnet(Message::Type type);
	Message::Type enetToType(int type);
}

#endif
