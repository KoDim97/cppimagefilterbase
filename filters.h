#pragma once
#include "abstract_filter.h"

class red : public abstract_filter{
public:
	virtual void setFilter(image_data img);
};