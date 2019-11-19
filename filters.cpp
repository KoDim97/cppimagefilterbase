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
	image_data imgCopy;
	imgCopy.h = img.h;
	imgCopy.w = img.w;
	imgCopy.compPerPixel = img.compPerPixel;
	int img_size = img.w * img.h * img.compPerPixel;
	imgCopy.pixels = new stbi_uc[img_size];
	memcpy(imgCopy.pixels, img.pixels, img_size);
	int curPix, median;
	int size = size_threshold_matrix;
	for (int i = area.y0; i < area.y1; i++) {
		for (int j = area.x0; j < area.x1; j++) {
			curPix = img.compPerPixel * (i * img.w + j);
			coefficients curMatrix(i - size / 2, j - size / 2, 
				i + size / 2, j + size / 2);
			median = getMedian(imgCopy, curMatrix, area);
			if (img.pixels[curPix] < median) {
				img.pixels[curPix] = 0;
				img.pixels[curPix + 1] = 0;
				img.pixels[curPix + 2] = 0;
			}
		}
	}
	delete[] imgCopy.pixels;
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
			monochrome = (3 * curRed + 6 * curGreen + curBlue) / 10;
			img.pixels[curPix] = monochrome;
			img.pixels[curPix + 1] = monochrome;
			img.pixels[curPix + 2] = monochrome;
		}
	}
}
int Threshold::getMedian(image_data& imgCopy, coefficients& matrix_area, coefficients& filter_area) {
	vector<stbi_uc> curElements;
	int curPix;
		for (int i = matrix_area.y0; i <= matrix_area.y1; i++) {
			if (i < 0 ||  i >= filter_area.y1) {
				continue;
			}
			for (int j = matrix_area.x0; j <= matrix_area.x1; j++) {
				if (j > -1 && j < filter_area.x1) {
					curPix = imgCopy.compPerPixel * (i * imgCopy.w + j);
					curElements.push_back(imgCopy.pixels[curPix]);
				}
			}
		}
	std::sort(curElements.begin(), curElements.end());
	return curElements[curElements.size() / 2];
}

Blur::Blur(int size) {
	size_blur_matrix = size;
}
void Blur::setFilter(image_data& img, coefficients& area) {
	int curPix;
	int newValue[3];
	image_data imgCopy;
	imgCopy.h = img.h;
	imgCopy.w = img.w;
	imgCopy.compPerPixel = img.compPerPixel;
	int img_size = img.w * img.h * img.compPerPixel;
	imgCopy.pixels = new stbi_uc[img_size];
	memcpy(imgCopy.pixels, img.pixels, img_size);
	int size = size_blur_matrix;
	for (int i = area.y0; i < area.y1; i++) {
		for (int j = area.x0; j < area.x1; j++) {
			curPix = img.compPerPixel * (i * img.w + j);
			coefficients curMatrix(i - size / 2, j - size / 2,
				i + size / 2, j + size / 2);
			getKernalValue(imgCopy, curMatrix, area, newValue);
			img.pixels[curPix] = newValue[0];
			img.pixels[curPix + 1] = newValue[1];
			img.pixels[curPix + 2] = newValue[2];
		}
	}
	delete[] imgCopy.pixels;
	return;
}
void Blur::getKernalValue(image_data& imgCopy, coefficients& matrix_area, coefficients& filter_area, int* newValue){
	int curPix;
	for (int i = 0; i < 3; i++) {
		newValue[i] = 0;
	}
	for (int i = matrix_area.y0; i <= matrix_area.y1; i++) {
		if (i < filter_area.y0 || i >= filter_area.y1) {
			continue;
		}
		for (int j = matrix_area.x0; j <= matrix_area.x1; j++) {
			if (j >= filter_area.x0 && j < filter_area.x1) {
				curPix = imgCopy.compPerPixel * (i * imgCopy.w + j);
				newValue[0] += imgCopy.pixels[curPix];
				newValue[1] += imgCopy.pixels[curPix + 1];
				newValue[2] += imgCopy.pixels[curPix + 2];
			}
		}
	}
	for (int i = 0; i < 3; i++) {
		newValue[i] /= 9;
	}
	return;
}

Edge::Edge(int size) {
	size_edge_matrix = size;
}
void Edge::setFilter(image_data& img, coefficients& area) {
	int curPix, newValue;
	setMonochrome(img, area);
	image_data imgCopy;
	imgCopy.h = img.h;
	imgCopy.w = img.w;
	imgCopy.compPerPixel = img.compPerPixel;
	int img_size = img.w * img.h * img.compPerPixel;
	imgCopy.pixels = new stbi_uc[img_size];
	memcpy(imgCopy.pixels, img.pixels, img_size);
	int size = size_edge_matrix;
	for (int i = area.y0; i < area.y1; i++) {
		for (int j = area.x0; j < area.x1; j++) {
			curPix = img.compPerPixel * (i * img.w + j);
			coefficients curMatrix(i - size / 2, j - size / 2,
				i + size / 2, j + size / 2);
			newValue = getKernalValue(imgCopy, curMatrix, area);
			img.pixels[curPix] = newValue;
			img.pixels[curPix + 1] = newValue;
			img.pixels[curPix + 2] = newValue;
		}
	}
	delete[] imgCopy.pixels;
	return;
}
int Edge::getKernalValue(image_data& imgCopy, coefficients& matrix_area, coefficients& filter_area) {
	int curPix, count = 0, sum = 0;
	int numOfElements = size_edge_matrix * size_edge_matrix;
	for (int i = matrix_area.y0; i <= matrix_area.y1; i++) {
		if (i < filter_area.y0 || i >= filter_area.y1) {
			count += size_edge_matrix;
			continue;
		}
		for (int j = matrix_area.x0; j <= matrix_area.x1; j++) {
			if (j >= filter_area.x0 && j < filter_area.x1) {
				curPix = imgCopy.compPerPixel * (i * imgCopy.w + j);
				if (count == (numOfElements / 2)) {
					sum += 9 * imgCopy.pixels[curPix];
				}
				else {
					sum -= imgCopy.pixels[curPix];
				}
			}
			count++;
		}
	}
	return clump(sum);
}
void Edge::setMonochrome(image_data& img, coefficients& area) {
	int curPix;
	int curRed, curGreen, curBlue;
	int monochrome;
	for (int i = area.y0; i < area.y1; i++) {
		for (int j = area.x0; j < area.x1; j++) {
			curPix = img.compPerPixel * (i * img.w + j);
			curRed = img.pixels[curPix];
			curGreen = img.pixels[curPix + 1];
			curBlue = img.pixels[curPix + 2];
			monochrome = (3 * curRed + 6 * curGreen + curBlue) / 10;
			img.pixels[curPix] = monochrome;
			img.pixels[curPix + 1] = monochrome;
			img.pixels[curPix + 2] = monochrome;
		}
	}
}
int Edge::clump(int num) {
	if (num >= 0 && num <= 255) {
		return num;
	}
	else if (num < 0) {
		return 0;
	}
	else {
		return 255;
	}	
}