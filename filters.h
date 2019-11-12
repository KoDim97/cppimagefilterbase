#pragma once
#include "abstract_filter.h"

class Red : public abstract_filter{
public:
	virtual void setFilter(image_data& img, coefficients& area);
};