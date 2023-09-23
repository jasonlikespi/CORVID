#pragma once
#ifndef CORVID_GEOM_H
#define CORVID_GEOM_H
#include <string>
#include <math.h>
#include <vector>
#include "CORVID_COORDS.h"
#include "SDL.h"

using namespace CORVID_COORDS;
template <typename NUMBER>
class CORVID_RECT {
public:
	CORVID_R2<NUMBER> location; // Upper Left Corner
	CORVID_R2<NUMBER> size;
	CORVID_RECT() : location(CORVID_R2<NUMBER>()), size(CORVID_R2<NUMBER>()) {};
	CORVID_RECT(NUMBER x1, NUMBER y1, NUMBER x2, NUMBER y2) : location(CORVID_R2(x1, y1)), size(CORVID_R2(x2, y2)) {};
	CORVID_RECT(CORVID_R2<NUMBER> location, CORVID_R2<NUMBER> size) : location(location), size(size) {};
	CORVID_RECT(CORVID_RECT* rectangle) : location(rectangle->location), size(rectangle->size) {};
	//SDL_Rect* toRect(); // TODO may lead to memory leak and also get this working
	bool pointIsInside(NUMBER x_val, NUMBER y_val);
	bool pointIsInside(CORVID_R2<NUMBER> point);
};
template <typename NUMBER>
class CORVID_BOUNDBOX : public CORVID_RECT<NUMBER>{
public:
	CORVID_R2<NUMBER> velocity;
	CORVID_BOUNDBOX() : CORVID_RECT<NUMBER>(), velocity(CORVID_R2<NUMBER>()) {};
	CORVID_BOUNDBOX(CORVID_RECT<NUMBER>* rectangle, CORVID_R2<NUMBER> velocity) : CORVID_RECT<NUMBER>(rectangle), velocity(velocity) {};
	CORVID_BOUNDBOX(CORVID_RECT<NUMBER>* rectangle) : CORVID_RECT<NUMBER>(rectangle), velocity(CORVID_R2<NUMBER>()) {};
	CORVID_BOUNDBOX(NUMBER r1, NUMBER r2, NUMBER s1, NUMBER s2, NUMBER v1, NUMBER v2) : CORVID_RECT<NUMBER>(CORVID_RECT(r1, r2, s1, s2)), velocity(CORVID_R2<NUMBER>(s1, s2)) {};
	CORVID_BOUNDBOX(NUMBER xval, NUMBER yval);
};

/*
* Uncomment this when I add Bezier Curves Back in
class CORVID_BEZIER {
public:
	CORVID_R2 points[4];
	int timeStart;
	int duration;
	CORVID_BEZIER* prev;
	CORVID_BEZIER* next;
	CORVID_BEZIER() :timeStart(0), duration(0), prev(NULL), next(NULL){ for (CORVID_R2 point : points) { point = CORVID_R2(); }; }
};
class CORVID_CURVESEQ {
public:
	CORVID_BEZIER* first;
	int numberOfCurves;
	int totalDuration;
	CORVID_CURVESEQ() : first(NULL), numberOfCurves(0), totalDuration(0) {};
};
*/

#endif