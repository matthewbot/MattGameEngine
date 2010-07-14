#include "png.h"
#include "PixMap.h"
#include <MGE/util/Exception.h>
#include <png.h>
#include <cassert>
#include <cstring>

using namespace mge;
using namespace std;

static png_bytepp makeRows(PixMap &map) {
	int width = map.getWidth(), height = map.getHeight();
	png_bytepp row_pointers = new png_bytep [height];
	
	for (int i = 0; i < height; ++i) {
		row_pointers[i] = (png_bytep)(map.getData() + i*width);
	}
	
	return row_pointers;
}

static void readData(png_structp png_ptr, png_bytep data, png_size_t length) {
	istream *stream = (istream *)png_get_io_ptr(png_ptr);
	stream->read((char *)data, length);
}

static void writeData(png_structp png_ptr, png_bytep data, png_size_t length) {
	ostream *stream = (ostream *)png_get_io_ptr(png_ptr);
	stream->write((char *)data, length);
}

static void flushData(png_structp png_ptr) {
	ostream *stream = (ostream *)png_get_io_ptr(png_ptr);
	stream->flush();
}

mge::PixMap mge::loadPNG(istream &stream) {
	png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
	if (!png_ptr) 
		throw Exception("Failed to init libpng");
		
	png_infop info_ptr = png_create_info_struct(png_ptr);
	if (!info_ptr) {
		png_destroy_read_struct(&png_ptr, NULL, NULL);
		throw Exception("Failed to init libpng (infostruct)");
	}
	
	if (setjmp(png_jmpbuf(png_ptr))) {
		png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
    throw Exception("Error while reading PNG");
	}
	
	png_set_read_fn(png_ptr, &stream, &readData);

	unsigned long width, height;   
	int bitdepth, colortype;

	png_read_info(png_ptr, info_ptr);     
	png_get_IHDR(png_ptr, info_ptr, &width, &height, &bitdepth, &colortype, NULL, NULL, NULL);
	
	if (bitdepth > 8)
		png_set_strip_16(png_ptr);
	if (colortype == PNG_COLOR_TYPE_GRAY || colortype == PNG_COLOR_TYPE_GRAY_ALPHA)
		png_set_gray_to_rgb(png_ptr);
	if (colortype == PNG_COLOR_TYPE_PALETTE)
		png_set_palette_to_rgb(png_ptr);
		
	png_read_update_info(png_ptr, info_ptr);
	if (png_get_rowbytes(png_ptr, info_ptr) != width*sizeof(PixMap::pixel_t))
		throw Exception("Pixel format doesn't line up with RGBA. Probably missing an alpha channel");
	
	PixMap pixels((int)width, (int)height);
	png_bytepp row_pointers = makeRows(pixels);
		
	png_read_image(png_ptr, row_pointers);
	
	delete[] row_pointers;
	png_destroy_read_struct(&png_ptr, &info_ptr, NULL);

	return pixels;
}

void mge::savePNG(const PixMap &map, ostream &stream) {
	png_structp png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
	if (!png_ptr)
		throw Exception("Failed to init libpng");

	png_infop info_ptr = png_create_info_struct(png_ptr);
	if (!info_ptr) {
		png_destroy_write_struct(&png_ptr, NULL);
		throw Exception("Failed to init libpng (infostruct)");
	}
	
	if (setjmp(png_jmpbuf(png_ptr))) {
		png_destroy_write_struct(&png_ptr, &info_ptr);
		throw Exception("Error while reading png");
	}
	
	png_set_write_fn(png_ptr, &stream, &writeData, &flushData);

	png_set_IHDR(png_ptr, info_ptr, map.getWidth(), map.getHeight(), 8, PNG_COLOR_TYPE_RGB_ALPHA, PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT);
	
	png_bytepp row_pointers = makeRows(const_cast<PixMap &>(map));
	png_set_rows(png_ptr, info_ptr, row_pointers);
	
	png_write_png(png_ptr, info_ptr, PNG_TRANSFORM_IDENTITY, NULL);
	png_write_end(png_ptr, NULL);

	delete[] row_pointers;
	png_destroy_write_struct(&png_ptr, &info_ptr);
}
