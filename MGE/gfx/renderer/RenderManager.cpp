#include "RenderManager.h"
#include "RenderRootCallback.h"
#include "Renderer.h"
#include <cassert>

using namespace mge;
using namespace std;
using namespace boost;

RenderManager::RenderManager(Renderer &renderer) : renderer(renderer), hasbatch(false) { }

RenderManager::~RenderManager() { 
	flush();
}

void RenderManager::render(const boost::shared_ptr<RenderRootCallback> &callback, const RenderState &state, const Transform &trans, const ViewSection &clip, const Primitive &prim) {
	const PrimitiveProperties &props = prim.getProps();
	BatchState newbatchstate(props.primtype, callback, state, trans, clip);

	if (!hasbatch) { // if there's no current batch.
		setBatch(newbatchstate); // set one
	} else if (batchstate != newbatchstate) { // if we have one, and it isn't compatible
		renderBatch(); // render the current batch.
		clearBatch(); // clear it
		setBatch(newbatchstate); // update the batch state
	} 
	
	appendBatch(prim); // append the new primitive
}

void RenderManager::clear(const shared_ptr<RenderRootCallback> &callback, const Color &color) {
	if (hasbatch && batchstate.getCallback() == callback)  // if we're clearing something we have a batch for
		clearBatch(); // we don't need to render the batch, obviously
		
	callback->prepareRenderer(renderer);
	renderer.drawClear(color);
}

void RenderManager::flush() {
	if (!hasbatch)
		return;

	if (batchstate.getCallback())  // we check the context because as a weak_ptr it can disappear
		renderBatch();
	
	clearBatch();
}

void RenderManager::setBatch(const BatchState &newbatchstate) {
	assert(!hasbatch);
	hasbatch = true;
	batchstate = newbatchstate;
}

void RenderManager::appendBatch(const Primitive &prim) {
	assert(hasbatch);
	assert(prim.getProps().primtype == batchstate.getType());
	
	if (!renderer.appendBuf(prim)) { // try to append the primitive. If it fails
		renderBatch(); // render the current batch.
		renderer.clearBuf(); // clear the render's buffer only
		assert(renderer.appendBuf(prim)); // and append it again (should not fail after being cleared)
	}
}

void RenderManager::renderBatch() {
	assert(hasbatch);
	shared_ptr<RenderRootCallback> callback = batchstate.getCallback();
	
	if (callback) {	
		callback->prepareRenderer(renderer); // do renderroot-specific setup
		renderer.setState(batchstate.getRenderState(), batchstate.getTransform(), batchstate.getClip()); // do render state specific setup
		renderer.drawBuf(batchstate.getType()); // draw the buffer
	}
}

void RenderManager::clearBatch() {
	assert(hasbatch);
	
	hasbatch = false;
	batchstate.clear();
	renderer.clearBuf();
}

const RenderStats &RenderManager::getStats() const { return renderer.getStats(); }

