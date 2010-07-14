#ifndef MGE_GFX_TIMER_H
#define MGE_GFX_TIMER_H

#include <MGE/util/FPSTimer.h>

namespace mge {
	class Timer : public FPSTimer {
		public:
			Timer();
			virtual ~Timer();
			
			void update();
		
			virtual float getTDelta() const;
			virtual int getFPS() const;
		
		private:
			float tdelta; int lastupdate;
			
			int curfps; 
			int fpsctr; float fpstimer;
	};

}

#endif
