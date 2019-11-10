#include "filters.h"

void red::setFilter(image_data img) {
	for (int i = img.h / 2 * img.w * img.compPerPixel; i < img.h * img.w * img.compPerPixel; i += 4) {
		img.pixels[i] = 255;
		img.pixels[i + 1] = 0;
		img.pixels[i + 2] = 0;
	}
	return;
}