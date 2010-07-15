#include "netutils.h"
#include <MGE/util/Exception.h>

using namespace mge;
using namespace std;

ENetPeer *mge::enet_host_getpeer(ENetHost *host, ENetPeer *peer) {
	int peernum;

	if (peer == NULL) {
		peer = host->peers;
		peernum = 0;
	} else {
		peer++;
		peernum = peer - host->peers;
	}

	for (;peernum < (int)host->peerCount; ++peer, ++peernum) {
		if (peer->state)
			return peer;
	}

	return NULL;
}

ostream &mge::operator<<(ostream &stream, const ENetAddress &addr) {
	char buf[17]; // (3 digits + 1 period) * 4 parts + \0 = 17 chars
	enet_address_get_host_ip(&addr, buf, sizeof(buf));

	stream << buf << ":" << addr.port;

	return stream;
}

int mge::typeToEnet(Message::Type type) {
	switch (type) {
		case Message::NORMAL:
			return ENET_PACKET_FLAG_UNSEQUENCED;
			
		case Message::SEQUENCED:
			return 0;
			
		case Message::RELIABLE:
			return ENET_PACKET_FLAG_RELIABLE;
			
		default:
			throw Exception("Bad MGE type?");
	}
}

Message::Type mge::enetToType(int type) {
	switch (type) {
		case ENET_PACKET_FLAG_UNSEQUENCED:
			return Message::NORMAL;
			
		case 0:
			return Message::SEQUENCED;
			
		case ENET_PACKET_FLAG_RELIABLE:
			return Message::RELIABLE;
			
		default:
			throw Exception("Bad ENet type?");
	}
}

