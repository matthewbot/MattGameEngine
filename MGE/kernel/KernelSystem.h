#ifndef MGE_KERNEL_SYSTEM_H
#define MGE_KERNEL_SYSTEM_H

namespace mge {
	enum SystemUpdateValue {
		NONE,
		STOP
	};

	class KernelSystem {
		public:
			inline virtual ~KernelSystem() { }

			virtual const char *getName() const=0;
			virtual SystemUpdateValue update();
	};
}

#endif
