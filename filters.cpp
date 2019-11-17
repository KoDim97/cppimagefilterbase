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
	for (int i = area.y0; i < area.y1; i += size_threshold_matrix) {
		for (int j = area.x0; j < area.x1; j += size_threshold_matrix) {
			coefficients curMatrix(i, j, i + size_threshold_matrix, j + size_threshold_matrix);
			cutLessMedian(img, curMatrix, area);	
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

bool comp(stbi_uc* a, stbi_uc* b) {
	return *a < *b;
}

void Threshold::cutLessMedian(image_data& img, coefficients& matrix_area, coefficients& filter_area) {
	vector<stbi_uc*> curElements;
	int curPix;
		for (int i = matrix_area.y0; i < matrix_area.y1; i++) {
			for (int j = matrix_area.x0; j < matrix_area.x1; j++) {
				if (i < filter_area.y1 && j < filter_area.x1) {
					curPix = img.compPerPixel * (i * img.w + j);
					curElements.push_back(img.pixels + curPix);
				}
			}
		}
	std::stable_sort(curElements.begin(), curElements.end(), comp);
	for (int i = 0; i < curElements.size() / 2; i++) {
		*curElements[i] = 0;
		*(curElements[i] + 1) = 0;
		*(curElements[i] + 2) = 0;
	}
}