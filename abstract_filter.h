#pragma once
#include "png_toolkit.h"

class abstract_filter {
public:
	virtual void setFilter(image_data img) = 0;
	virtual ~abstract_filter() {};
};