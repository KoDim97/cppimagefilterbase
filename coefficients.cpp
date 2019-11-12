#include "coefficients.h"

coefficients::coefficients(vector<string>& res) {
	x0 = stoi(res[1]);
	y0 = stoi(res[2]);
	x1 = stoi(res[3]);
	y1 = stoi(res[4]);
}
void coefficients::transformToArea(int width, int height) {
	x0 != 0 ? x0 = width / x0 : 0;
	y0 != 0 ? y0 = height / y0 : 0;
	x1 != 0 ? x1 = width / x1 : 0;
	y1 != 0 ? y1 = height / y1 : 0;
}
