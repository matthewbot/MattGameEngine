#ifndef MGETEST_TESTSYSTEM_H
#define MGETEST_TESTSYSTEM_H

#include <MGE/util/input/InputAccumulator.h>
#include <MGE/kernel/KernelSystem.h>
#include <boost/shared_ptr.hpp>

namespace mge {
	class GraphicsSystem;
	class ResourceSystem;
	class AudioSystem;
	class Shader;
	class Sprite;
	class Font;
	class Clip;
	class ClipPlayback;
}

namespace mgetest {
	class TestSystem : public mge::KernelSystem {
		public:
			TestSystem(mge::GraphicsSystem &gfx, mge::ResourceSystem &res, mge::AudioSystem &snd);
			~TestSystem();
			
			virtual mge::SystemUpdateValue update();
			virtual const char *getName() const;
			
		private:
			mge::GraphicsSystem &gfx;
			mge::ResourceSystem &res;
			mge::AudioSystem &snd;
			
			float zoom;
			
			mge::InputAccumulator input;
			boost::shared_ptr<mge::Shader> testprogram;
			boost::shared_ptr<mge::Sprite> testsprite;
			boost::shared_ptr<mge::Font> testfont;
			boost::shared_ptr<mge::Clip> testclip;
			mge::ClipPlayback *testclip_play;
			boost::shared_ptr<mge::Clip> testmusic;
			mge::ClipPlayback *testmusic_play;
	};
}

#endif
