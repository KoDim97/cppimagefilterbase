#pragma once
#include <array>
#include <algorithm>
#include "abstract_filter.h"

class Red : public abstract_filter{
public:
	virtual void setFilter(image_data& img, coefficients& area) override;
};

class Threshold : public abstract_filter {
public:
	Threshold(int size = 5);
	virtual void setFilter(image_data& img, coefficients& area) override;
private:
	int size_threshold_matrix;
	void setMonochrome(image_data& img, coefficients& area);
	void cutLessMedian(image_data& img, coefficients& matrix_area, coefficients& filter_area);
};

//class Blur : public abstract_filter {
//public:
//	Blur(int size = 3);
//	virtual void setFilter(image_data& img, coefficients& area) override;
//private:
//	int size_blur_matrix;
//	int getKernalValue(image_data& img, coefficients& matrix_area, coefficients& filter_area);
//};