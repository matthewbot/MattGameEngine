#include "SpriteFactory.h"
#include "Sprite.h"
#include <MGE/res/system/ResourceNode.h>
#include <MGE/gfx/texture/TextureManager.h>
#include <MGE/gfx/texture/Texture.h>
#include <boost/shared_ptr.hpp>

using namespace std;
using namespace mge;
using namespace boost;

SpriteFactory::SpriteFactory(TextureManager &tm) : texman(tm) { }

Resource *SpriteFactory::makeResource(const std::string &name, const ResourceNode &resnode) {
	if (resnode.getString("type") != "sprite")
		return NULL;

	string filename = resnode.getString("filename");
	string subpixel = resnode.getString("subpixel", "on");

	TexFlags tf = (subpixel == "on") ? TF_SUBPIXEL : TF_NONE;

	shared_ptr<Texture> tex = texman.loadTexture(filename, tf);

	SpriteProps props;
	props.tx = resnode.getInt("tx", 0);
	props.ty = resnode.getInt("ty", 0);
	props.tw = resnode.getInt("tw", tex->getWidth());
	props.th = resnode.getInt("th", tex->getHeight());
	props.rotoffset = resnode.getFloat("rotoffset", 0)/180*3.14159265;

	if (resnode.getString("origin", "") == "centered") {
		props.ox = props.tw/2;
		props.oy = props.th/2;
	} else {
		props.ox = resnode.getFloat("ox", 0);
		props.oy = resnode.getFloat("oy", 0);
	}

	return new Sprite(name, tex, props);
}
