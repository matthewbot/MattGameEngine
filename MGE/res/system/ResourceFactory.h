#ifndef MGE_RES_FACTORY_H
#define MGE_RES_FACTORY_H

#include <string>

namespace mge {
	class ResourceNode;
	class Resource;

	class ResourceFactory {
		public:
			virtual ~ResourceFactory();
			virtual Resource *makeResource(const std::string &name, const ResourceNode &props) = 0;
	};
}

#endif
