#ifndef MGE_SND_SOURCEHANDLE_H
#define MGE_SND_SOURCEHANDLE_H

#include <boost/noncopyable.hpp>
#include <cassert>

namespace mge {
	class SourceManager;

	class SourceHandle : public boost::noncopyable {
		friend class SourceManager;
		
		public:
			inline SourceHandle(int sourceid, int priority) : sourceid(sourceid), priority(priority) { }
			
			inline bool hasSource() const { return sourceid != -1; }
			inline int getSourceID() const { assert(hasSource()); return sourceid; }
			inline operator int() const { return getSourceID(); }
			
			inline int getPriority() const { return priority; }
			
			inline void clearSource() { sourceid = -1; }
			
		private:
			int sourceid;
			int priority;
	};
}

#endif
