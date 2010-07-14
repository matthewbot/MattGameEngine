#ifndef MGE_RES_SHADERFACTORY_H
#define MGE_RES_SHADERFACTORY_H

#include <MGE/res/system/ResourceFactory.h>

namespace mge {
	class ShaderManager;

	class ShaderFactory : public ResourceFactory {
		public:
			ShaderFactory(ShaderManager &shademan);
			virtual Resource *makeResource(const std::string &name, const ResourceNode &props);

		private:
			ShaderManager &shademan;
	};
}

#endif
