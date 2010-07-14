#ifndef MGE_STATE_GAMESTATE_H
#define MGE_STATE_GAMESTATE_H

namespace mge {
	class GameStateStatus;
	
	class GameState {
		public:
			inline virtual ~GameState() { }

			virtual GameStateStatus update()=0;
	};
}

#endif
