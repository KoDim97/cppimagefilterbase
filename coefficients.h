#pragma once
#include<vector>
#include <string>

using namespace std;

struct coefficients {
public:
	int x0, y0, x1, y1;
	coefficients(vector<string>& res);
	void transformToArea(int width, int height);
};