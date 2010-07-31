#include "Connection.h"
#include "netutils.h"
#include <enet/enet.h>
#include <cassert>

using namespace mge;
using namespace std;

Connection::Connection(ENetPeer *peer, State state) : state(state), peer(peer) { }

Connection::~Connection() {
	if (peer)
		reset();
}

int Connection::getPing() const { return peer->roundTripTime; }
string Connection::getIP() const {
	char buf[20];
	enet_address_get_host_ip(&peer->address, buf, sizeof(buf));
	return buf;
}

bool Connection::messageAvailable() const {
	return messagebuf.size() > 0;
}

Message Connection::getMessage() {
	Message msg = messagebuf.front();
	messagebuf.pop_front();
	return msg;
}

void Connection::sendMessage(const Message &msg) {
	assert(state == CONNECTED);
	const Blob &data = msg.getData();
	ENetPacket *packet = enet_packet_create(data.get(), data.getRemaining(), typeToEnet(msg.getType()));
	enet_peer_send(peer, msg.getChannel(), packet);
}

void Connection::disconnect() {
	assert(state == CONNECTED);
	enet_peer_disconnect(peer, 1);
	state = DISCONNECTING;
}

void Connection::reset() {
	if (state != CONNECTED)
		return;
		
	enet_peer_reset(peer);
	state = DISCONNECTED;
	peer = 0;
}

void Connection::onMessageReceived(const Message &msg) {
	messagebuf.push_back(msg);
}

void Connection::onConnected() {
	state = CONNECTED;
}

void Connection::onDisconnected() {
	state = DISCONNECTED;
	peer = 0;
}

void Connection::onTimedOut() {
	state = TIMEOUT;
	peer = 0;
}
