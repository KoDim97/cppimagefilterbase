#include "filters.h"

void Red::setFilter(image_data& img, coefficients& area) {

	int curPix;
	for (int i = area.y0; i < area.y1; i++) {
		for (int j = area.x0; j < area.x1; j++) {
			curPix = img.compPerPixel * (i * img.w + j);
			img.pixels[curPix] = 255;
			img.pixels[curPix + 1] = 0;
			img.pixels[curPix + 2] = 0;
		}
	}
	return;
}