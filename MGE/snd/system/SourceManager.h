#ifndef MGE_SND_SOURCEMANAGER_H
#define MGE_SND_SOURCEMANAGER_H

#include <vector>
#include <utility>
#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>

namespace mge {
	class Logger;
	class ClipPlayback;
	class SourceHandle;

	class SourceManager {
		public:
			SourceManager(Logger &logger);
			~SourceManager();

			boost::shared_ptr<SourceHandle> getSource(int priority);

		private:
			typedef std::vector<std::pair<int, boost::weak_ptr<SourceHandle> > > SourceList;
			
			SourceList sources;
			Logger &logger;
	};
}

#endif
