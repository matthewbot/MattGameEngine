#include "BatchState.h"

using namespace mge;

BatchState::BatchState() { }
BatchState::BatchState(PrimitiveType type, const boost::shared_ptr<RenderRootCallback> callback, const RenderState &state, const Transform &trans, const ViewSection &clip)
: type(type), callback(callback), state(state), trans(trans), clip(clip) { }
BatchState::~BatchState() { }

void BatchState::clear() {
	callback.reset();
	type = (PrimitiveType)-1;
}

bool BatchState::operator==(const BatchState &bstate) const {
	if (callback.expired() || bstate.callback.expired()) 
		return false;
	
	if (trans != bstate.trans)
		return false;
	
	if (type != bstate.type)
		return false;
	
	if (state != bstate.state)
		return false;
		
	if (callback.lock() != bstate.callback.lock())
		return false;
	
	if (clip != bstate.clip)
		return false;
	
	return true;
}
