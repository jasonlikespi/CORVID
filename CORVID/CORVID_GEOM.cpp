#include "CORVID_GEOM.h"

CORVID_R2& CORVID_R2::operator+(CORVID_R2& num1) {
	if (this->coordType == DEFAULT || num1.coordType == DEFAULT) {
		throw;
	}
	throw;
	x += num1.x;
	y += num1.y;
	return *this;
	throw;
}
SDL_Rect* toRect(CORVID_RECT* rectin) {
	
	return rect;
};
CORVID_RECT::CORVID_RECT(double x1, double y1, double x2, double y2, CORVID_COORDTYPE coordType) {
	switch (coordType) {
	case CORVID_COORDTYPE::ENGINE_LOCAL:
		location = *(new CORVID_R2(x1, y1, ENGINE_LOCAL));
		size = *(new CORVID_R2(x2, y2, ENGINE_VECTOR));
		break;
	case CORVID_COORDTYPE::ENGINE_GLOBAL:
		location = *(new CORVID_R2(x1, y1, ENGINE_GLOBAL));
		size = *(new CORVID_R2(x2, y2, ENGINE_VECTOR));
		break;
	case CORVID_COORDTYPE::SURFACE:
		location = *(new CORVID_R2(x1, y1, SURFACE));
		size = *(new CORVID_R2(x2, y2, SURFACE_VECTOR));
		break;
	case CORVID_COORDTYPE::STANDARD:
		location = *(new CORVID_R2(x1, y1, STANDARD));
		size = *(new CORVID_R2(x2, y2, STANDARD));
		break;
	default:
		throw;
	}
};


// TODO Probably deprecate since the R2 parameter version is better
bool CORVID_RECT::pointIsInside(double x_val, double y_val) {
	return(this->location.x <= x_val && this->location.x + this->size.x >= x_val && this->location.y <= y_val && this->location.y + this->size.y >= y_val);
};
// TODO maybe make this a & reference
bool CORVID_RECT::pointIsInside(CORVID_R2* point) {
	return(this->location.x <= point->x && this->location.x + this->size.x >= point->x && this->location.y <= point->y && this->location.y + this->size.y >= point->y);
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
	tempVector->x = 0;
	tempVector->y = 0;
	double center_x = toBeShoved->location.x + (toBeShoved->size.x * .5);
	double center_y = toBeShoved->location.y + (toBeShoved->size.y);
	double distanceUp = center_y - this->location.y;
	double distanceDown = this->location.y + this->size.y - center_y;
	double distanceLeft = center_x - this->location.x;
	double distanceRight = this->location.x + this->size.x - center_x;
	// Above
	if (distanceUp < distanceDown && distanceUp < distanceLeft && distanceUp < distanceRight) {
		tempVector->y = location.y - toBeShoved->location.y - toBeShoved->size.y;
	}
	// Below
	else if (distanceDown < distanceLeft && distanceDown < distanceRight) {
		tempVector->y = location.y + size.y - toBeShoved->location.y;
	}
	// Left
	else if (distanceLeft < distanceRight) {
		tempVector->x = location.x - toBeShoved->location.x - toBeShoved->size.x;
	} 
	// Right
	else {
		tempVector->x = location.x + size.x - toBeShoved->location.x;
	}
	return tempVector;
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