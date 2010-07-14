#ifndef MGE_STATE_GAMESTATESTATUS_H
#define MGE_STATE_GAMESTATESTATUS_H

#include <memory>
#include <boost/shared_ptr.hpp>

namespace mge {
	class TransitionFactory;

	class GameStateStatus {
		public:
			enum Action { CONTINUE, TRANSITION, TERMINATE };
			GameStateStatus(Action action=CONTINUE);
			GameStateStatus(const boost::shared_ptr<TransitionFactory> &transition);
			GameStateStatus(TransitionFactory *factory);
			~GameStateStatus();

			inline Action getAction() const { return action; }
			inline const boost::shared_ptr<TransitionFactory> &getTransition() { return transition; }

		private:
			Action action;
			boost::shared_ptr<TransitionFactory> transition;
	};
}

#endif
