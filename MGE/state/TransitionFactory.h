#ifndef MGE_STATE_TRANSITIONFACTORY_H
#define MGE_STATE_TRANSITIONFACTORY_H

#include <memory>

namespace mge {
	class GameState;

	class TransitionFactory {
		public:
			inline virtual ~TransitionFactory() { }

			virtual std::auto_ptr<GameState> makeState(std::auto_ptr<GameState> &curstate)=0;
	};
}

#endif
