#include "filters_collection.h"

void filters_collections::addFilter(string name, abstract_filter* item) {
	collections[name] = item;
}
filters_collections::filters_collections() {
	abstract_filter* redFilter = new red();
	collections["red"] = redFilter;
}
filters_collections::~filters_collections() {
	for (auto var : collections)
	{
		delete var.second;
	}
}
abstract_filter* filters_collections::getFilter(string name) {
	if (collections.find(name) != collections.end()) {
		return collections.find(name)->second;
	}
	else{
		return NULL;
	}
}