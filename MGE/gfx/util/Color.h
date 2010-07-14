#ifndef MGE_GFX_COLOR_H
#define MGE_GFX_COLOR_H

namespace mge {
	struct Color {
		float r, g, b, a;

		static const Color fromInt(int r, int g, int b, int a = 255);
		static const Color fromFloat(float r, float g, float b, float a = 1);
		
		static const Color WHITE, BLACK, RED, ORANGE, YELLOW, GREEN, BLUE, PURPLE;
	};
}

#endif	
