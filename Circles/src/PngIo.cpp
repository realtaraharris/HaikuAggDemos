/*
 * Copyright 2023, Tara Harris <3769985+realtaraharris@users.noreply.github.com>
 * All rights reserved. Distributed under the terms of the MIT license.
 */

#include "PngIo.h"

/*
 * writePngFromBBitmap() is Copyright 2015 Haiku, Inc. All rights reserved.
 * Distributed under the terms of the MIT License.
 *
 * Authors:
 *		Andrew Lindesay
 */

// swiped from the Haiku hvif2png utility
bool writePngFromBBitmap(BBitmap* bitmap, FILE* out) {
	png_structp png = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

	if (png == NULL) {
		fprintf(stderr, "unable to setup png write data structures\n");
		return false;
	}

	png_init_io(png, out);
	png_infop info = png_create_info_struct(png);

	bool result = false;

	if (info != NULL) {
		BRect rect = bitmap->Bounds();
		png_uint_32 width = (png_uint_32)rect.Width() + 1;
		png_uint_32 height = (png_uint_32)rect.Height() + 1;

		png_set_IHDR(png, info, width, height, 8, PNG_COLOR_TYPE_RGBA,
			PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);

		png_set_bgr(png);

		png_write_info(png, info);

		uint8 *bitmapData = (uint8*)bitmap->Bits();
		int32 bitmapBytesPerRow = bitmap->BytesPerRow();

		for (png_uint_32 i = 0; i < height; i++) {
			png_write_row(png, (png_bytep)&bitmapData[i * bitmapBytesPerRow]);
		}

		png_write_end(png, NULL);

		png_free_data(png, info, PNG_FREE_ALL, -1);

		result = true;
	} else {
		fprintf(stderr, "unable to setup png info data structures\n");
	}

	png_destroy_write_struct(&png, (png_infopp)NULL);

	return result;
}

int writePngFromBBitmap(BBitmap* bitmap, char* outFilename) {
	FILE* out;
	
	if (outFilename != NULL) {
		out = fopen(outFilename, "wb");
	} else {
		out = stdout;
	}

	if (out == NULL) {
		fprintf(stderr, "unable to open the output file; '%s'\n", outFilename);
		return false;
	}

	int result = 1;

	if (writePngFromBBitmap(bitmap, out)) {
		result = 0;
	}

	// clean up
	if (out != NULL) {
		if (out != stdout)
			fclose(out);
		out = NULL;
	}

	return result;
}

bool writePngFromAggBitmap(agg::rendering_buffer* bitmap, FILE* out) {
	png_structp png = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

	if (png == NULL) {
		fprintf(stderr, "unable to setup png write data structures\n");
		return false;
	}

	png_init_io(png, out);
	png_infop info = png_create_info_struct(png);

	bool result = false;

	if (info != NULL) {
		png_uint_32 width = (png_uint_32)bitmap->width();
		png_uint_32 height = (png_uint_32)bitmap->height();

		png_set_IHDR(png, info, width, height, 8, PNG_COLOR_TYPE_RGBA,
			PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);

		png_set_bgr(png);

		png_write_info(png, info);

		uint8 *bitmapData = (uint8*)bitmap->buf();
		int32 bitmapBytesPerRow = bitmap->stride_abs();

		for (png_uint_32 i = 0; i < height; i++) {
			png_write_row(png, (png_bytep)&bitmapData[i * bitmapBytesPerRow]);
		}

		png_write_end(png, NULL);

		png_free_data(png, info, PNG_FREE_ALL, -1);

		result = true;
	} else {
		fprintf(stderr, "unable to setup png info data structures\n");
	}

	png_destroy_write_struct(&png, (png_infopp)NULL);

	return result;
}

int writePng(agg::rendering_buffer* bitmap, char* outFilename) {
	FILE* out;

	if (outFilename != NULL) {
		out = fopen(outFilename, "wb");
	} else {
		out = stdout;
	}

	if (out == NULL) {
		fprintf(stderr, "unable to open the output file; '%s'\n", outFilename);
		return false;
	}

	int result = 1;

	if (writePngFromAggBitmap(bitmap, out)) {
		result = 0;
	}

	// clean up
	if (out != NULL) {
		if (out != stdout)
			fclose(out);
		out = NULL;
	}

	return result;
}
