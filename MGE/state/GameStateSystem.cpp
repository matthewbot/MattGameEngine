#include "GameStateSystem.h"
#include "GameState.h"
#include "GameStateStatus.h"
#include "TransitionFactory.h"

using namespace mge;
using namespace std;

GameStateSystem::GameStateSystem(GameState *newstate) : state(newstate) { }
GameStateSystem::GameStateSystem(auto_ptr<GameState> &newstate) : state(newstate) { }

SystemUpdateValue GameStateSystem::update() {
	GameStateStatus status = state->update();

	switch (status.getAction()) {
		case GameStateStatus::TRANSITION:
			state = status.getTransition()->makeState(state);
			break;

		case GameStateStatus::TERMINATE:
			return STOP;
			
		case GameStateStatus::CONTINUE:
			break;
	}

	return NONE;
}

const char *GameStateSystem::getName() const {
	return "GameStateSystem";
}
