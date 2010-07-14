#ifndef MGE_GFX_TEXTUREMANAGER_H
#define MGE_GFX_TEXTUREMANAGER_H

#include "Texture.h"
#include "PixMap.h" // PITA to predeclare unfortunately. TODO: Write a predec header
#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>
#include <map>

namespace mge {
	class Logger;
	class FileStreamProducer;
	class Renderer;

	class TextureManager : boost::noncopyable {
		friend class GraphicsSystem;
		friend class TextureDeleter;
		
		typedef std::map<std::pair<std::string, TexFlags>, boost::weak_ptr<Texture> > TexCache; // a cache is a pairing of a texture's filename and flags to a texture. 
		                                                                        // This way we can load the same texture with two different flags and it works
		public:
			boost::shared_ptr<Texture> loadTexture(const std::string &name, TexFlags flags = TF_NONE);
			boost::shared_ptr<Texture> createTexture(const PixMap &map, TexFlags flags = TF_NONE);
			boost::shared_ptr<Texture> createBlankTexture(int w, int h);
			boost::shared_ptr<Texture> duplicateTexture(const boost::shared_ptr<Texture> tex, TexFlags flags); // use TF_UNIQUE to force a duplication

		private:
			TextureManager(Logger &logger, FileStreamProducer &fsp, Renderer &renderer); // for GraphicsSystem

			TexCache texcache;
			Logger &logger;
			FileStreamProducer &fsp;
			Renderer &renderer;
	};
}

#endif
