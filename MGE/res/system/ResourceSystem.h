#ifndef MGE_RES_RESOURCESYSTEM_H
#define MGE_RES_RESOURCESYSTEM_H

#include <MGE/res/Resource.h>
#include "ResourceNode.h"
#include "ResourceFactory.h"
#include <MGE/kernel/KernelSystem.h>
#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>
#include <map>
#include <string>
#include <vector>

namespace mge {
	class FileStreamProducer;
	class Logger;

	class ResourceSystem : public KernelSystem {
		public:
			ResourceSystem(FileStreamProducer &fsp, Logger &log);
			virtual ~ResourceSystem();

			void registerResourceFactory(ResourceFactory *fact);

			void mergeProperties(const ResourceNode &val);
			void loadFile(const std::string &name);
			inline const ResourceNode &getRoot() const { return props; }
			boost::shared_ptr<Resource> getResource(const std::string &name) const;

			template <class ResClass> boost::shared_ptr<ResClass> get(const std::string &name) const {
				return boost::static_pointer_cast<ResClass>(getResource(name));
			}

			virtual const char *getName() const;

		private:
			FileStreamProducer &fsp;
			Logger &log;
			ResourceNode props;

			typedef std::map<std::string, boost::weak_ptr<Resource> > ResourceCacheMap;
			mutable ResourceCacheMap cache;

			typedef std::vector<ResourceFactory *> ResourceFactoryList;
			ResourceFactoryList factories;
	};
}

#endif
