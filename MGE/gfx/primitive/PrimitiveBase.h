#ifndef MGE_GFX_PRIMITIVEBASE_H
#define MGE_GFX_PRIMITIVEBASE_H

#include "Primitive.h"
#include <cassert>

namespace mge {
	namespace {
		template <PrimitiveType Type> struct PrimitiveTypeTraits { };
		template <> struct PrimitiveTypeTraits<POINTS> { static const int VertCount = 1; };
		template <> struct PrimitiveTypeTraits<LINES> { static const int VertCount = 2; };
		template <> struct PrimitiveTypeTraits<QUADS> { static const int VertCount = 4; };
	}

	template <PrimitiveType Type, typename Vert> class PrimitiveBase : public Primitive {
		typedef PrimitiveTypeTraits<Type> Traits;
		
		public:
			PrimitiveBase() { }
		
			inline virtual const float *dataBegin() const {
				return reinterpret_cast<const float *>(&verts[0]);
			}
			
			inline virtual const PrimitiveProperties &getProps() const { return props; }
	
			inline Vert &operator[](int i) { assert(i < Traits::VertCount); return verts[i]; }
	
		protected:
			Vert verts[Traits::VertCount];
			
		private:
			static const PrimitiveProperties props; // definition below
	};
	
	template <PrimitiveType Type, typename Vert> 
	const PrimitiveProperties PrimitiveBase<Type, Vert>::props = { 
	  PrimitiveTypeTraits<Type>::VertCount*sizeof(Vert)/sizeof(float), 
	  PrimitiveTypeTraits<Type>::VertCount, 
	  Type };
}

#endif
