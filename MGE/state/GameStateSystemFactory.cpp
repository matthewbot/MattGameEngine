#include "GameStateSystemFactory.h"
#include "GameStateSystem.h"
#include "InitialGameStateFactory.h"
#include "GameState.h"

using namespace mge;

GameStateSystemFactory::GameStateSystemFactory(InitialGameStateFactory *factory) : factory(factory) { }
GameStateSystemFactory::~GameStateSystemFactory() { }

KernelSystem *GameStateSystemFactory::makeKernelSystem(Logger &logger, const KernelSystemMap &map) {
	GameState *state = factory->makeGameState(logger, map);
	GameStateSystem *statesystem = new GameStateSystem(state);
	
	return statesystem;
}
