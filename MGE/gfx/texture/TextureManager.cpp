#include "TextureManager.h"
#include "PixMap.h"
#include "png.h"
#include <MGE/gfx/renderer/Renderer.h>
#include <MGE/util/Exception.h>
#include <MGE/util/Logger.h>
#include <MGE/util/FileStreamProducer.h>
#include <boost/scoped_array.hpp>
#include <boost/scoped_ptr.hpp>
#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>
#include <GL/gl.h>

using namespace std;
using namespace mge;
using namespace boost;

static int pow2(int x) {
	int c=1;
	while (c < x)
		c *= 2;
	return c;
}

static shared_ptr<Texture> surfaceToTexture(Logger &logger, SDL_Surface *surface, Renderer &renderer, TexFlags flags, const std::string &name); // will delete surface, made a non-instance method to avoid having to pre-declare SDL_Surface in TextureManager.h
static void setFlags(const shared_ptr<Texture> &tex, TexFlags flags); // this sets texture flags on a texture. Conveniently leaves the texture bound


#ifdef _MSC_VER
#pragma warning(disable:4355)
#endif

TextureManager::TextureManager(Logger &logger, FileStreamProducer &fsp, Renderer &renderer) : logger(logger), fsp(fsp), renderer(renderer) { }

shared_ptr<Texture> TextureManager::loadTexture(const string &name, TexFlags flags) {
	logger.log("gfx", DEBUG) << "Loading texture " << name << " flags: " << flags << endl;

	if (!(flags & TF_UNIQUE)) { // unless we're requesting a unique texture
		TexCache::iterator i = texcache.find(make_pair(name, flags)); // ask the cache if we've already got a texture like this one
		if (i != texcache.end()) {// if we do
			if (shared_ptr<Texture> tex = i->second.lock()) { // and the weak pointer is still good
				logger.log("gfx", DEBUG) << "  cache hit id " << tex->getID() << endl;

				return tex; // and return it
			}
		}
	}
	
	scoped_ptr<istream> stream(fsp.readFile(name));
	shared_ptr<Texture> tex(createTexture(loadPNG(*stream), flags));
	
	texcache[make_pair(name, flags)] = tex;
	
	return tex;
}

shared_ptr<Texture> TextureManager::createBlankTexture(int w, int h) {
	throw Exception("TODO: createBlankTexture!");
}

shared_ptr<Texture> TextureManager::createTexture(const PixMap &map, TexFlags flags) {
	SDL_Surface *img = SDL_CreateRGBSurfaceFrom(const_cast<PixMap::pixel_t *>(map.getData()), map.getWidth(), map.getHeight(), 32, map.getWidth()*4, 0x000000FF, 0x0000FF00, 0x00FF0000, 0xFF000000);
	
	return surfaceToTexture(logger, img, renderer, flags, "#PIXMAP");
}

boost::shared_ptr<Texture> TextureManager::duplicateTexture(const boost::shared_ptr<Texture> tex, TexFlags flags) {
	if (!(flags & TF_UNIQUE)) {
		if (tex->getFlags() == flags) // the dummy case
			return tex;
		
		TexCache::iterator i = texcache.find(make_pair(tex->getName(), flags)); 
		if (i != texcache.end()) { // check cache
			if (shared_ptr<Texture> cachetex = i->second.lock()) { // and the weak pointer is still good
				logger.log("gfx", DEBUG) << "  duplicateTexture cache hit id " << tex->getID() << endl;

				return cachetex; // and return it
			}
		}		
	}
	
	// if we get here, we need to actually duplicate it
	
	scoped_array<unsigned char> data(new unsigned char [tex->getInternalWidth()*tex->getInternalHeight()]); // allocate enough memory to read it back
	glBindTexture(GL_TEXTURE_2D, tex->getID());
	glGetTexImage(GL_TEXTURE_2D, 0, GL_RGBA, GL_UNSIGNED_BYTE, data.get()); // perform the read
	
	shared_ptr<Texture> duptex(new Texture(tex->getWidth(), tex->getHeight(), tex->getInternalWidth(), tex->getInternalHeight(), tex->getName(), flags)); // create our texture object
	setFlags(duptex, flags); // set flags on it
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, duptex->getInternalWidth(), duptex->getInternalHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, data.get()); // upload data
	
	glBindTexture(GL_TEXTURE_2D, 0); // clean up
	renderer.damageTexture();
	
	if (!(flags & TF_UNIQUE))
		texcache[make_pair(duptex->getName(), flags)] = duptex; // add the texture object to the image cache
	
	return duptex; // return duplicate
}

static void setFlags(const shared_ptr<Texture> &tex, TexFlags flags) {
	glBindTexture(GL_TEXTURE_2D, tex->getID()); // bind the texture
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	if (flags & TF_SUBPIXEL) {
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	} else {
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	}
}

static shared_ptr<Texture> surfaceToTexture(Logger &logger, SDL_Surface *img_raw, Renderer &renderer, TexFlags flags, const std::string &name) {
	SDL_Surface *img = SDL_CreateRGBSurface(SDL_SWSURFACE, pow2(img_raw->w), pow2(img_raw->h), 32, 0x000000FF, 0x0000FF00, 0x00FF0000, 0xFF000000); // create a new surface in ideal OpenGL format
	SDL_SetAlpha(img_raw, 0, SDL_ALPHA_OPAQUE);
	SDL_BlitSurface(img_raw, NULL, img, NULL); // blit the raw image to the opengl surface

	shared_ptr<Texture> tex(new Texture(img_raw->w, img_raw->h, img->w, img->h, name, flags)); // create our texture object
	setFlags(tex, flags); // set the flags on it

	if (SDL_MUSTLOCK(img))
		SDL_LockSurface(img);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, img->w, img->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, img->pixels); // send image data
	if (SDL_MUSTLOCK(img))
		SDL_UnlockSurface(img);

	logger.log("gfx", DEBUG) << "  uploaded w " << img->w << " h " << img->h << " id " << tex->getID() << endl;

	SDL_FreeSurface(img_raw); // free raw surface
	SDL_FreeSurface(img); // free the surface
	
	glBindTexture(GL_TEXTURE_2D, 0);
	renderer.damageTexture(); // make sure the renderer knows we scribbled on its state (TODO: don't require us to 0 out the texture)
	
	return tex;
}
