#ifndef MGE_STATE_INITIALGAMESTATEFACTORY_H
#define MGE_STATE_INITIALGAMESTATEFACTORY_H

#include <MGE/kernel/KernelSystemFactory.h>

namespace mge {
	class GameState;
	class Logger;

	class InitialGameStateFactory {
		public:
			inline virtual ~InitialGameStateFactory() { }
			
			virtual GameState *makeGameState(Logger &log, const KernelSystemMap &systems)=0;
	};
}

#endif
