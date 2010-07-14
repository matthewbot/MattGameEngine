#include "NetworkSystem.h"
#include "Connection.h"
#include "netutils.h"
#include <MGE/util/Logger.h>
#include <MGE/util/Exception.h>
#include <enet/enet.h>
#include <cassert>

using namespace mge;
using namespace boost;
using namespace std;

NetworkSystem::NetworkSystem(Logger &logger) : logger(logger), host(0), chancount(0) {
	if (enet_initialize() != 0) 
		throw Exception("Failed to init ENet!");
}

NetworkSystem::~NetworkSystem() {
	if (host)
		stop();

	enet_deinitialize();
}

void NetworkSystem::start(int port, int peers, int down, int up, int chancount) {
	if (host)
		stop();
		
	if (port == -1) {
		host = enet_host_create(NULL, peers, down, up);
	} else {
		ENetAddress address;
		address.host = ENET_HOST_ANY;
		address.port = port;
		host = enet_host_create(&address, peers, down, up);
	}
	
	if (!host)
		throw Exception("Failed to create ENet host");
		
	this->chancount = chancount;
}

void NetworkSystem::stop() {
	assert(host);
	
	enet_host_destroy(host);
	host = 0;
}

bool NetworkSystem::connectionAvailable() {
	return pendingconns.size() > 0;
}

shared_ptr<Connection> NetworkSystem::acceptConnection() {
	assert(connectionAvailable());
	
	shared_ptr<Connection> conn(pendingconns.front());
	pendingconns.pop_front();
	return conn;
}

#include <iostream>

shared_ptr<Connection> NetworkSystem::connect(const string &hostname, int port) {
	assert(host);

	ENetAddress address;
	enet_address_set_host(&address, hostname.c_str());
	address.port = port;
	
	ENetPeer *peer = enet_host_connect(host, &address, chancount);
	if (!peer)
		throw Exception("Failed to initiate connection");
	
	Connection *conn = new Connection(peer, Connection::ESTABLISHING);
	peer->data = conn;
	
	return shared_ptr<Connection>(conn);
}

SystemUpdateValue NetworkSystem::update() {
	if (!host)
		return NONE;
		
	int val;
	ENetEvent event;
	
	while ((val = enet_host_service(host, &event, 0)) > 0) {
		Connection *conn = (Connection *)event.peer->data;
	
		switch (event.type) {
			case ENET_EVENT_TYPE_NONE: // shuts the compiler up
				break;
		
			case ENET_EVENT_TYPE_CONNECT:
				cout << "Got connection" << endl;
				if (!conn) { // if this peer doesn't have a connection object
					conn = new Connection(event.peer, Connection::ESTABLISHING);
					event.peer->data = conn;
					pendingconns.push_back(shared_ptr<Connection>(conn));
				}
				
				conn->onConnected();	
				break;
				
			case ENET_EVENT_TYPE_DISCONNECT:
				if (event.data)
					conn->onDisconnected();
				else
					conn->onTimedOut();
				break;
					
			case ENET_EVENT_TYPE_RECEIVE:
				cout << "Received packet" << endl;
				ENetPacket *packet = event.packet;
				conn->onMessageReceived(Message(Blob((char *)packet->data, packet->dataLength), event.channelID, enetToType(packet->flags)));
				enet_packet_destroy(packet);
				break;
		}
	}
	
	if (val < 0)
		throw Exception("Failed to service ENet host");
	
	return NONE;
}

const char *NetworkSystem::getName() const { return "NetworkSystem"; }
