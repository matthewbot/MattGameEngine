#ifndef MGE_STATE_GAMESTATESYSTEMFACTORY_H
#define MGE_STATE_GAMESTATESYSTEMFACTORY_H

#include <MGE/kernel/KernelSystemFactory.h>
#include <boost/scoped_ptr.hpp>

namespace mge {
	class InitialGameStateFactory;

	class GameStateSystemFactory : public KernelSystemFactory {
		public:
			GameStateSystemFactory(InitialGameStateFactory *factory);
			virtual ~GameStateSystemFactory();
			
			virtual KernelSystem *makeKernelSystem(Logger &logger, const KernelSystemMap &map);
			
		private:
			boost::scoped_ptr<InitialGameStateFactory> factory;
	};
}

#endif
