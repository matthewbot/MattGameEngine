#ifndef MGE_RES_RESOURCE_H
#define MGE_RES_RESOURCE_H

#include <boost/noncopyable.hpp>
#include <string>

namespace mge {
	class Resource : boost::noncopyable {
		friend class ResourceSystem;

		public:
			Resource(const std::string &name);
			virtual ~Resource();

			inline const std::string &getName() const { return name; }

		protected:
			const std::string name;
	};
}

#endif
