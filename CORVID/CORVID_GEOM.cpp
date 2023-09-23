#include "CORVID_GEOM.h"

// TODO Write Method
template <typename NM>
bool CORVID_RECT<NM>::pointIsInside(NM x_val, NM y_val) {
	return 0;
};

// TODO Write Method
template <typename NM>
bool CORVID_RECT<NM>::pointIsInside(CORVID_R2<NM> point) {
	return 0;
};

CORVID_BOUNDBOX<int>::CORVID_BOUNDBOX(int xval, int yval) : 
	CORVID_RECT<int>(CORVID_RECT(xval, yval, 16, 16)), velocity(CORVID_R2<int>()) {};

CORVID_BOUNDBOX<double>::CORVID_BOUNDBOX(double xval, double yval) : 
	CORVID_RECT<double>(CORVID_RECT(xval, yval, 16.0, 16.0)), velocity(CORVID_R2<double>()) {};

/*
template <typename NUMBER>
SDL_Rect* CORVID_RECT<NUMBER>::toRect() {
	SDL_Rect* offset = new SDL_Rect();
	offset->x = (int)this->location.x;
	offset->y = (int)this->location.y;
	return &offset;
};
*/