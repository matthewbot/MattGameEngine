#include "TestSystem.h"
#include <MGE/gfx/system/GraphicsSystem.h>
#include <MGE/gfx/system/Display.h>
#include <MGE/gfx/primitive/Quad.h>
#include <MGE/gfx/primitive/Line.h>
#include <MGE/gfx/primitive/Point.h>
#include <MGE/gfx/primitive/MultiTexQuad.h>
#include <MGE/gfx/shader/ShaderVariableValue.h>
#include <MGE/gfx/Viewport.h>
#include <MGE/gfx/Transform.h>
#include <MGE/res/system/ResourceSystem.h>
#include <MGE/res/Shader.h>
#include <MGE/res/Sprite.h>
#include <MGE/res/Font.h>
#include <MGE/util/input/InputAccumulator.h>
#include <MGE/snd/system/AudioSystem.h>
#include <MGE/snd/Clip.h>
#include <MGE/snd/ClipPlayback.h>

using namespace mge;
using namespace mgetest;
using namespace boost;
using namespace std;

TestSystem::TestSystem(GraphicsSystem &gfx, ResourceSystem &res, AudioSystem &snd) : gfx(gfx), res(res), snd(snd), zoom(1) {
	testprogram = res.get<Shader>("shd_test");
	testsprite = res.get<Sprite>("spr_test");
	testfont = res.get<Font>("fnt_test");
	testclip = snd.loadClip("testsound.wav", false);
	testmusic = snd.loadClip("testmusic.ogg", true);
	testclip_play = testclip->makePlayback();
	testmusic_play = testmusic->makePlayback();
	
	gfx.getWindowInput().addInputListener(input);
	
	testmusic_play->setLoop(true);
	testmusic_play->play();
}

TestSystem::~TestSystem() {
	gfx.getWindowInput().removeInputListener(input);
	delete testclip_play;
}

SystemUpdateValue TestSystem::update() {
	Display &disp = gfx.getDisplay();
	disp.clear();
	
	Transform trans;
	trans.scale(zoom, zoom); // zoom....
	
	Viewport view(disp, trans);
	
	RenderState state;

	Quad quad(Color::RED, 10, 10, 10, 10);
	Line line(Color::GREEN, 30, 30, 40, 10);
	Point point(Color::BLUE, 10, 80);

	view.render(state, trans, quad);
	view.render(state, trans, line);
	view.render(state, trans, point);
	
	testsprite->renderRotated(view, 200, 200, .7854);

	if (input.isMouseButtonDown(mousebtns::left))
		zoom *= 1.1;
	else if (input.isMouseButtonDown(mousebtns::right))
		zoom /= 1.1;
		
	if (input.isKeyPressed('s')) 
		testclip_play->play();
	
	bool exit = input.getExit();
	
	input.update();

	if (exit)
		return STOP;
	else
		return NONE;
}

const char *TestSystem::getName() const { return "TestSystem"; }
