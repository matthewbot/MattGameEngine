#ifndef MGE_GFX_VIEWSECTION_H
#define MGE_GFX_VIEWSECTION_H

namespace mge {
	struct ViewSection {
		int x, y, w, h;
		
		bool operator==(const ViewSection &sect) const;
		inline bool operator!=(const ViewSection &sect) const { return !(*this == sect); }
		
		bool inside(int xp, int yp) const;
	};
}

#endif
