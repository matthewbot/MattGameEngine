#include "GameStateStatus.h"
#include "TransitionFactory.h"

using namespace mge;
using namespace boost;

GameStateStatus::GameStateStatus(Action action) : action(action) { }
GameStateStatus::GameStateStatus(const shared_ptr<TransitionFactory> &transition) : action(TRANSITION), transition(transition) { }
GameStateStatus::GameStateStatus(TransitionFactory *transition) : action(TRANSITION), transition(transition) { }GameStateStatus::~GameStateStatus() { }

