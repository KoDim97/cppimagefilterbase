#include "coefficients.h"

coefficients::coefficients(int y0, int x0, int y1, int x1) {
	this->x0 = x0;
	this->y0 = y0;
	this->x1 = x1;
	this->y1 = y1;
}
coefficients::coefficients(vector<string>& res) {
	y0 = stoi(res[1]);
	x0 = stoi(res[2]);
	y1 = stoi(res[3]);
	x1 = stoi(res[4]);
}
void coefficients::transformToArea(int width, int height) {
	x0 = x0 != 0 ? width / x0 : 0;
	y0 = y0 != 0 ? height / y0 : 0;
	x1 = x1 != 0 ? width / x1 : 0;
	y1  = y1 != 0 ? height / y1 : 0;
}
