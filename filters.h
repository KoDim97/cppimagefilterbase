#pragma once
#include <array>
#include <algorithm>
#include <cstring>
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
	int getMedian(image_data& imgCopy, coefficients& matrix_area, coefficients& filter_area);
};

class Blur : public abstract_filter {
public:
	Blur(int size = 3);
	virtual void setFilter(image_data& img, coefficients& area) override;
private:
	int size_blur_matrix;
	void getKernalValue(image_data& imgCopy, coefficients& matrix_area, coefficients& filter_area, int* newValue);
};

class Edge : public abstract_filter {
public:
	Edge(int size = 3);
	virtual void setFilter(image_data& img, coefficients& area) override;
private:
	int size_edge_matrix;
	void setMonochrome(image_data& img, coefficients& area);
	int getKernalValue(image_data& imgCopy, coefficients& matrix_area, coefficients& filter_area);
	int clump(int num);
};