#ifndef MGE_RES_SPRITE_H
#define MGE_RES_SPRITE_H

#include "Resource.h"
#include <boost/shared_ptr.hpp>

namespace mge {
	class Texture;	class Viewport;

	struct SpriteProps {
		int tx, ty, tw, th;
		float ox, oy;
		float rotoffset;
	};

	class Sprite : public Resource {
		friend class SpriteFactory;

		public:
			Sprite(const std::string &name, boost::shared_ptr<Texture> tex, const SpriteProps &props);

			inline const boost::shared_ptr<Texture> &getTexture() { return tex; }
			void render(const Viewport &out, float x, float y);
			void renderRotated(const Viewport &out, float x, float y, float rot);
			void renderTiled(const Viewport &out, float x, float y, int xctr, int yctr);
			
			inline int getWidth() const { return props.tw; }
			inline int getHeight() const { return props.th; }

		private:
			boost::shared_ptr<Texture> tex;
			SpriteProps props;
	};
}


#endif
