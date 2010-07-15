#ifndef MGE_UTIL_FRAMERATELIMITER_H
#define MGE_UTIL_FRAMERATELIMITER_H

#include "FPSTimer.h"
#include <MGE/kernel/KernelSystem.h>

namespace mge {
	class FrameRateLimiter : public KernelSystem, public FPSTimer {
		public:
			FrameRateLimiter(int desiredfps);
			inline virtual ~FrameRateLimiter() { }
			
			inline int getDesiredFPS() const { return desiredfps; }
			inline void setDesiredFPS(int newfps) { desiredfps = newfps; }
			
			// KernelSystem
			
			virtual SystemUpdateValue update();
			virtual const char *getName() const;

			// FPSTimer
			
			virtual float getTDelta() const;
			virtual int getFPS() const;
			
		private:
			int desiredfps;
			int lastframe;
			
			int actualfps;
			int lastsecond;
			int nextactualfps;
			
			float tdelta;
	};
}

#endif
