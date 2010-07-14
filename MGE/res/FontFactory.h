#ifndef MGE_RES_FONTFACTORY_H
#define MGE_RES_FONTFACTORY_H

#include <MGE/res/system/ResourceFactory.h>
#include <memory>
#include <string>

namespace mge {
	class TextureManager;
	class Resource;
	class ResourceNode;
	class FileStreamProducer;
	class FontDef;
	
	// finally, the factory and font classes
	class FontFactory : public ResourceFactory {
		public:
			FontFactory(TextureManager &tm, FileStreamProducer &fsp);
			virtual Resource *makeResource(const std::string &name, const ResourceNode &props);

		private:
			TextureManager &texman;
			FileStreamProducer &fsp;
			
			std::auto_ptr<FontDef> parseFnt(const std::string &fname);
	};
}

#endif
