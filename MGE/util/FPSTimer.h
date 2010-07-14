#ifndef MGE_UTIL_FPSTIMER_H
#define MGE_UTIL_FPSTIMER_H

namespace mge {
	class FPSTimer {
		public:
			inline virtual ~FPSTimer() { }
			
			virtual float getTDelta() const = 0;
			virtual int getFPS() const = 0;
	};
}

#endif
