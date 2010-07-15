#ifndef MGE_RES_SPRITEFACTORY_H
#define MGE_RES_SPRITEFACTORY_H

#include <MGE/res/system/ResourceFactory.h>

namespace mge {
	class TextureManager;

	class SpriteFactory : public ResourceFactory {
		public:
			SpriteFactory(TextureManager &tm);
			virtual Resource *makeResource(const std::string &name, const ResourceNode &props);

		private:
			TextureManager &texman;
	};
}

#endif
