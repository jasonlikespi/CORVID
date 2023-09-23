#include "CORVID_GEOM.h"

template <typename NUMBER>
bool CORVID_RECT<NUMBER>::pointIsInside(NUMBER x_val, NUMBER y_val) {// TODO
	return 0;
};
template <typename NUMBER>
bool CORVID_RECT<NUMBER>::pointIsInside(CORVID_R2<NUMBER> point) {// TODO
	return 0;
};
CORVID_BOUNDBOX<int>::CORVID_BOUNDBOX(int xval, int yval) : CORVID_RECT<int>(CORVID_RECT(xval, yval, 16, 16)), velocity(CORVID_R2<int>()) {};
CORVID_BOUNDBOX<double>::CORVID_BOUNDBOX(double xval, double yval) : CORVID_RECT<double>(CORVID_RECT(xval, yval, 16.0, 16.0)), velocity(CORVID_R2<double>()) {};