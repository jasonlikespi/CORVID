#include "CORVID_GEOM.h"

// TODO Write Method
//template <typename NM>
bool CORVID_RECT::pointIsInside(double x_val, double y_val) {
	return(this->location.x < x_val && this->location.x + this->size.x > x_val && this->location.y < y_val && this->location.y + this->size.y > y_val);
};

// TODO Write Method
// template <typename NM>
bool CORVID_RECT::pointIsInside(CORVID_R2 point) {
	return(this->location.x < point.x && this->location.x + this->size.x > point.x && this->location.y < point.y && this->location.y + this->size.y > point.y);
};
/*
CORVID_BOUNDBOX<int>::CORVID_BOUNDBOX(int xval, int yval) : 
	CORVID_RECT<int>(CORVID_RECT(xval, yval, 16, 16)), velocity(CORVID_R2<int>()) {};
*/

CORVID_BOUNDBOX::CORVID_BOUNDBOX(double xval, double yval) : 
	CORVID_RECT(CORVID_RECT(xval, yval, 32.0, 32.0)), velocity(CORVID_R2()) {};

/*
template <typename NUMBER>
SDL_Rect* CORVID_RECT<NUMBER>::toRect() {
	SDL_Rect* offset = new SDL_Rect();
	offset->x = (int)this->location.x;
	offset->y = (int)this->location.y;
	return &offset;
};
*/