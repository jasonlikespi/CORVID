#include "CORVID_COORDS.h"

CORVID_COORDS::CORVID_R2& CORVID_COORDS::CORVID_R2::operator+(CORVID_COORDS::CORVID_R2& num1) {
	x += num1.x;
	y += num1.y;
	return *this;
}
