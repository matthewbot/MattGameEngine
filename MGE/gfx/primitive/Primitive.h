#ifndef MGE_GFX_PRIMITIVE_H
#define MGE_GFX_PRIMITIVE_H

#include "Vertex.h"

namespace mge {
	enum PrimitiveType {
		POINTS,
		LINES,
		QUADS
	};

	struct PrimitiveProperties {
		int datacount;
		int vertcount;
		PrimitiveType primtype;
	};

	class Primitive {
		public:
			inline virtual ~Primitive() { }
			
			virtual const float *dataBegin() const = 0;
			virtual const PrimitiveProperties &getProps() const = 0;
	};
}

#endif
