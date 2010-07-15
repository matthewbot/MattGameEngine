#ifndef MGE_RES_FONT_H
#define MGE_RES_FONT_H

#include "Resource.h"
#include <MGE/gfx/util/Color.h>
#include <MGE/gfx/Transform.h>
#include <boost/shared_ptr.hpp>
#include <utility>

namespace mge {
	class Texture;
	class FontDef;
	class Viewport;

	class Font : public Resource {
		public:
			Font(std::auto_ptr<FontDef> &def, const boost::shared_ptr<Texture> &tex, const std::string &name);

			float render(const Viewport &out, float xpos, float ypos, const std::string &str, const Color &col = Color::WHITE, const Transform &trans=Transform());
			int getWidth(const std::string &str);
			int getLineHeight();
		private:
			boost::shared_ptr<Texture> tex;
			std::auto_ptr<FontDef> def;
	};
}

#endif
