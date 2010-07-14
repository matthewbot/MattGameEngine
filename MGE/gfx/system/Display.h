#ifndef MGE_GFX_DISPLAY_H
#define MGE_GFX_DISPLAY_H

#include <MGE/gfx/RenderRoot.h>

namespace mge {
	class Display : public RenderRoot {
		public:
			Display(int w, int h, RenderManager &rendman);
			virtual ~Display();

			void update(); 
	};
}

#endif
