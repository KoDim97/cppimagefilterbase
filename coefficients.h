#pragma once
#include<vector>
#include <string>

using namespace std;

struct coefficients {
public:
	int x0, y0, x1, y1;
	coefficients(int x0 = 0, int y0 = 0, int x1 = 0, int y1 = 0);
	coefficients(vector<string>& res);
	void transformToArea(int width, int height);
};