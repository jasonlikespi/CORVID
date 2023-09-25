#pragma once
#ifndef CORVID_COORDS_H
#define CORVID_COORDS_H

// ENGINE and ENGINE_VECTOR has +y for up, -y for down, +x for right, and -x for left
// SURFACE and SURFACE_VECTOR has +x for right, -x for left, +y for down, and -y for up
// DEFAULT is for situations that don't require the values to specify direction
namespace CORVID_COORDS {
	enum CORVID_COORDTYPE { ENGINE, SURFACE, ENGINE_VECTOR, SURFACE_VECTOR, DEFAULT };
	
	// template <typename NM>
	class CORVID_R2 {
	public:
		double x;
		double y;
		CORVID_COORDTYPE coordType;
		CORVID_R2() : x(0), y(0), coordType(DEFAULT) {};
		CORVID_R2(double x, double y) : x(x), y(y), coordType(DEFAULT) {};
		CORVID_R2(double x, double y, CORVID_COORDTYPE type) : x(x), y(y), coordType(type) {};
	};
};
#endif