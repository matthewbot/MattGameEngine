#ifndef MGE_NET_NETWORKSYSTEM_H
#define MGE_NET_NETWORKSYSTEM_H

#include <MGE/kernel/KernelSystem.h>
#include <boost/shared_ptr.hpp>
#include <list>

extern "C" {
	typedef struct _ENetHost ENetHost;
}

namespace mge {
	class Logger;
	class Connection;

	class NetworkSystem : public KernelSystem {
		friend class Connection;

		public:
			NetworkSystem(Logger &logger);
			virtual ~NetworkSystem();

			void start(int port, int peers, int down, int up, int chancount);
			void stop();

			bool connectionAvailable();
			boost::shared_ptr<Connection> acceptConnection(); 
			boost::shared_ptr<Connection> connect(const std::string &host, int port);

			virtual const char *getName() const;
			virtual SystemUpdateValue update();

		private:
			Logger &logger;
			ENetHost *host;
			int chancount;

			typedef std::list<boost::shared_ptr<Connection> > ConnectionList;
			ConnectionList pendingconns;
	};
}

#endif
