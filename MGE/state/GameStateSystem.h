#ifndef MGE_STATE_GAMESTATESYSTEM_H
#define MGE_STATE_GAMESTATESYSTEM_H

#include <MGE/kernel/KernelSystem.h>
#include <boost/shared_ptr.hpp>

namespace mge {
	class GameState;

	class GameStateSystem : public KernelSystem {
		public:
			explicit GameStateSystem(GameState *newstate);
			explicit GameStateSystem(std::auto_ptr<GameState> &newstate);

			virtual SystemUpdateValue update();
			virtual const char *getName() const;

		private:
			std::auto_ptr<GameState> state;
	};
}

#endif
