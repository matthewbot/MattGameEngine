#ifndef MGE_TEXTURE_H
#define MGE_TEXTURE_H

#include <string>
#include <boost/noncopyable.hpp>

namespace mge {
	enum TexFlags {
		TF_NONE = 0x00, // just so default arguments will compile
		TF_UNIQUE = 0x01,
		TF_SUBPIXEL = 0x02
	};

	class Texture : boost::noncopyable {
		public:
			Texture(int width, int height, int twidth, int theight, const std::string &name, TexFlags flags); // For TextureManager
			~Texture();
		
			inline int getID() const { return id; }
			inline int getWidth() const { return width; }
			inline int getHeight() const { return height; }
			inline int getInternalWidth() const { return twidth; }
			inline int getInternalHeight() const { return theight; }
			inline const std::string &getName() const { return name; }
			inline TexFlags getFlags() const { return flags; }

		private:
			int width, height;
			int twidth, theight;
			int id;

			std::string name;
			TexFlags flags;
	};
}

#endif
