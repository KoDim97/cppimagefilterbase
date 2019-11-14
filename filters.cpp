#include <array>
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
Threshold::Threshold(int size) {
	size_threshold_matrix = size;
}
void Threshold::setFilter(image_data& img, coefficients& area) {
	setMonochrome(img, area);
	int intensity;
	for (int i = area.y0; i < area.y1; i += size_threshold_matrix) {
		for (int j = area.x0; j < area.x1; j += size_threshold_matrix) {
			coefficients curMatrix(i, j, i + size_threshold_matrix, j + size_threshold_matrix);
			intensity = getMedian(img, curMatrix, area);
			cutLess(img, curMatrix, intensity);		
		}
	}
	return;
}
void Threshold::setMonochrome(image_data& img, coefficients& area) {
	int curPix;
	int curRed, curGreen, curBlue;
	int monochrome;
	for (int i = area.y0; i < area.y1; i++) {
		for (int j = area.x0; j < area.x1; j++) {
			curPix = img.compPerPixel * (i * img.w + j);
			curRed = img.pixels[curPix];
			curGreen = img.pixels[curPix + 1];
			curBlue = img.pixels[curPix + 2];
			monochrome = 0.3 * curRed + 0.6 * curGreen + 0.1 * curBlue;
			img.pixels[curPix] = monochrome;
			img.pixels[curPix + 1] = monochrome;
			img.pixels[curPix + 2] = monochrome;
		}
	}
}
int Threshold::getMedian(image_data& img, coefficients& matrix_area, coefficients& filter_area) {
	vector<int> curElements;
	int curPix;
	for (int i = matrix_area.y0; i < matrix_area.y1; i++) {
		for (int j = matrix_area.x0; j < matrix_area.x1; j++) {
			if (i < filter_area.y1 && j < filter_area.x1) {
				curPix = img.compPerPixel * (i * img.w + j);
				curElements.push_back(img.pixels[curPix]);
			}
			else {
				curElements.push_back(0);
			}
			
		}
	}
	std::sort(curElements.begin(), curElements.end());
	return curElements[curElements.size()/2];
}
void Threshold::cutLess(image_data& img, coefficients& area, int intensity) {
	int curPix;
	for (int i = area.y0; i < area.y1; i++) {
		for (int j = area.x0; j < area.x1; j++) {
			if (area.x1 < img.w && area.y1 < img.h) {
				curPix = img.compPerPixel * (i * img.w + j);
				if (img.pixels[curPix] < intensity) {
					img.pixels[curPix] = 0;
					img.pixels[curPix + 1] = 0;
					img.pixels[curPix + 2] = 0;
				}
			}
		}
	}
}