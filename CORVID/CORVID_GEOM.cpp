#include "CORVID_GEOM.h"

CORVID_R2& CORVID_R2::operator+(CORVID_R2& num1) {
	x += num1.x;
	y += num1.y;
	return *this;
}
bool CORVID_RECT::pointIsInside(double x_val, double y_val) {
	return(this->location.x <= x_val && this->location.x + this->size.x >= x_val && this->location.y <= y_val && this->location.y + this->size.y >= y_val);
};

bool CORVID_RECT::pointIsInside(CORVID_R2 point) {
	return(this->location.x <= point.x && this->location.x + this->size.x >= point.x && this->location.y <= point.y && this->location.y + this->size.y >= point.y);
};

CORVID_BOUNDBOX::CORVID_BOUNDBOX(double xval, double yval) : 
	CORVID_RECT(CORVID_RECT(xval, yval, 32.0, 32.0)), velocity(CORVID_R2()) {};


DIRECTION CORVID_RECT::relativePosition(CORVID_RECT* otherRect) {
	// Above
	if (otherRect->location.y + otherRect->size.y < this->location.y) {
		// Above Left
		if (otherRect->location.x + otherRect->size.x < this->location.x) {
			return DIRECTION::UPLEFT;
		}
		// Above Right
		if (this->location.x + this->size.x < otherRect->location.x) {
			return DIRECTION::UPRIGHT;
		}
		return DIRECTION::ABOVE;
	}
	// Below
	if(location.y + size.y < otherRect->location.y){
		// Below Left
		if (otherRect->location.x + otherRect->size.x < this->location.x) {
			return DIRECTION::DOWNLEFT;
		}
		// Below Right
		if (this->location.x + this->size.x < otherRect->location.x) {
			return DIRECTION::DOWNRIGHT;
		}
		return DIRECTION::BELOW;
	}
	// Left
	if (otherRect->location.x + otherRect->size.x < this->location.x) {
		return DIRECTION::LEFT;
	}
	// Right
	if (this->location.x + this->size.x < otherRect->location.x) {
		return DIRECTION::RIGHT;
	}
	// Inside
	return DIRECTION::INSIDE;
};

// This method should only run if the relativePosition method returns INSIDE
// Could be optimized, and similarly to relativePosition, is a galactic level function
// Intentionally moved the center of the toBeShoved object to the bottom edge, potentially rendering this
// Algorithm obsolete for non player objects.
CORVID_R2* CORVID_RECT::shoveDirection(CORVID_RECT* toBeShoved) {
	pushVector->x = 0;
	pushVector->y = 0;
	double center_x = toBeShoved->location.x + (toBeShoved->size.x * .5);
	double center_y = toBeShoved->location.y + (toBeShoved->size.y);
	double distanceUp = center_y - this->location.y;
	double distanceDown = this->location.y + this->size.y - center_y;
	double distanceLeft = center_x - this->location.x;
	double distanceRight = this->location.x + this->size.x - center_x;
	// Above
	if (distanceUp < distanceDown && distanceUp < distanceLeft && distanceUp < distanceRight) {
		pushVector->y = location.y - toBeShoved->location.y - toBeShoved->size.y;
	}
	// Below
	else if (distanceDown < distanceLeft && distanceDown < distanceRight) {
		pushVector->y = location.y + size.y - toBeShoved->location.y;
	}
	// Left
	else if (distanceLeft < distanceRight) {
		pushVector->x = location.x - toBeShoved->location.x - toBeShoved->size.x;
	} 
	// Right
	else {
		pushVector->x = location.x + size.x - toBeShoved->location.x;
	}
	return pushVector;
};


/*
template <typename NUMBER>
SDL_Rect* CORVID_RECT<NUMBER>::toRect() {
	SDL_Rect* offset = new SDL_Rect();
	offset->x = (int)this->location.x;
	offset->y = (int)this->location.y;
	return &offset;
};
*/