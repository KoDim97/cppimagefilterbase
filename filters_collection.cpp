#include "filters_collection.h"

void filters_collections::addFilter(string name, abstract_filter* item) {
	collections[name] = item;
}
filters_collections::filters_collections() {
	collections["Red"] = new Red();
	collections["Threshold"] = new Threshold();
	collections["Blur"] = new Blur();
	collections["Edge"] = new Edge();
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
		throw "Collection does not contain this filter";
	}
}