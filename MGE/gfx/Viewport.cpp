#include "Viewport.h"
#include "RenderState.h"
#include "RenderRoot.h"
#include <MGE/util/Vector2D.h>
#include <cmath>

using namespace mge;
using namespace std;

Viewport::Viewport(RenderRoot &root) : root(&root) {
	genRootClip();
}

Viewport::Viewport(const Viewport &view, const Transform &transform) : trans(transform), root(view.root), rootclip(view.rootclip) {
	trans.compose(view.trans);
}

void Viewport::genRootClip() {
	rootclip.x = rootclip.y = 0;
	rootclip.w = root->getWidth();
	rootclip.h = root->getHeight();
}

static int iround(float f) { return (int)floor(f + 0.5f); }

Viewport::Viewport(const Viewport &view, const ViewSection &viewclip) : trans(view.trans), root(view.root) {
	Vector2D lowerleft(viewclip.x, viewclip.y), upperright(viewclip.x + viewclip.w, viewclip.y + viewclip.h);
	
	lowerleft = trans.transform(lowerleft); // convert clip to root coordinates
	upperright = trans.transform(upperright);
	
	float minx = min(lowerleft.getX(), upperright.getX());
	float maxx = max(lowerleft.getX(), upperright.getX());
	float miny = min(lowerleft.getY(), upperright.getY());
	float maxy = max(lowerleft.getY(), upperright.getY());
	
	
	rootclip.x = iround(minx); rootclip.y = iround(miny);
	rootclip.w = iround(maxx - minx); rootclip.h = iround(maxy - miny);
}

void Viewport::render(const Primitive &prim) const {
	root->render(RenderState(), trans, rootclip, prim);
}

void Viewport::render(const RenderState &state, const Primitive &prim) const {
	root->render(state, trans, rootclip, prim);
}

void Viewport::render(const RenderState &state, const Transform &transform, const Primitive &prim) const {
	Transform composed(transform);
	composed.compose(trans);
	
	root->render(state, composed, rootclip, prim);
}

void Viewport::renderPrecmp(const RenderState &state, const Transform &transformprecmp, const Primitive &prim) const {
	root->render(state, transformprecmp, rootclip, prim);
}

bool Viewport::contains(const Vector2D &vec) const {
	Vector2D rootpos(trans.transform(vec));
	
	return rootclip.inside((int)rootpos.getX(), (int)rootpos.getY()); //*/
}

bool Viewport::contains(float x, float y) const {
	return contains(Vector2D(x, y));
}

bool Viewport::contains(const Vector2D &vec, const Transform &vectrans) const {
	Vector2D rootpos(trans.transform(vectrans.transform(vec)));
	
	return rootclip.inside((int)rootpos.getX(), (int)rootpos.getY());
}

bool Viewport::contains(float x, float y, const Transform &vectrans) const {
	return contains(Vector2D(x, y), vectrans);
}
