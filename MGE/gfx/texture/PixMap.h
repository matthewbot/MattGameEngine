#ifndef MGE_PIXMAP_H
#define MGE_PIXMAP_H

#include <cstring>

namespace mge {
	template <typename PixT> class ImageMap {
		public:
			typedef PixT pixel_t;
		
			ImageMap() : width(0), height(0), data(0) { }
			ImageMap(int width, int height) : width(width), height(height) {
				long count = width*height;
				data = new PixT[count];
			}
			ImageMap(int width, int height, const PixT &pix) : width(width), height(height) {
				int count = width*height;
				data = new PixT[count];
				PixT *ptr = data;
				while (count--)
					*ptr++ = pix;
			}
			ImageMap(const ImageMap<PixT> &map) : width(map.width), height(map.height) {
				if (map.data) {
					int count = width * height;
					data = new PixT[count];
					memcpy(data, map.data, count*sizeof(pixel_t));
				} else {
					data = 0;
				}
			}
			~ImageMap() { 
				delete[] data;
			}
			
			const ImageMap<PixT> &operator=(const ImageMap<PixT> &map) {
				if (this == &map)
					return *this;
		
				int count = map.width * map.height;
	
				if (!(width == map.width && height == map.height)) {
					width = map.width;
					height = map.height;
					delete[] data;
					data = new PixT[count];
				}
	
				memcpy(data, map.data, count*sizeof(PixT));
	
				return *this;
			}
		
			inline int getWidth() const { return width; }
			inline int getHeight() const { return height; }
		
			inline PixT *getData() { return data; }
			inline const PixT *getData() const { return data; }
			inline const PixT *getEnd() const { return data + width*height; }
			
			inline PixT &pix(int x, int y) { return data[x + y*width]; }
			inline const PixT &pix(int x, int y) const { return data[x + y*width]; }
			
		private:
			int width, height;
			PixT *data;
	};
	
	typedef union {
		int val;
		struct {
			unsigned char r, g, b, a;
		} col;
	} Pixel;
	
	typedef ImageMap<Pixel> PixMap;
}

#endif
