#pragma once
#include "png_toolkit.h"
#include "coefficients.h"

class abstract_filter {
public:
	virtual void setFilter(image_data& img, coefficients& area) = 0;
	virtual ~abstract_filter() {};
};