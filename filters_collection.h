#pragma once
#include <map>
#include "abstract_filter.h"
#include "filters.h"

using namespace std;

class filters_collections {
private:
	map<string, abstract_filter*> collections;
public:
	void addFilter(string name, abstract_filter* item);
	abstract_filter* getFilter(string name);
	filters_collections();
	~filters_collections();
};