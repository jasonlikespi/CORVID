#pragma once
#ifndef CORVID_GEOM_H
#define CORVID_GEOM_H
#include <string>
#include <math.h>
#include <vector>
#include "CORVID_COORDS.h"
#include "SDL.h"

using namespace CORVID_COORDS;
enum DIRECTION { INSIDE, ABOVE, BELOW, LEFT, RIGHT, UPLEFT, UPRIGHT, DOWNLEFT, DOWNRIGHT };
// If I was less of a chaos demon, I would make this a vector to keep track of location
// But I am a risk taker, so I will just use one static variable
static CORVID_R2* pushVector = new CORVID_R2();
class CORVID_RECT {
public:

	CORVID_R2 location; // Upper Left Corner
	CORVID_R2 size;
	CORVID_RECT() : location(CORVID_R2()), size(CORVID_R2()) {};
	CORVID_RECT(double x1, double y1, double x2, double y2) : location(CORVID_R2(x1, y1)), size(CORVID_R2(x2, y2)) {};
	CORVID_RECT(CORVID_R2 location, CORVID_R2 size) : location(location), size(size) {};
	CORVID_RECT(CORVID_RECT* rectangle) : location(rectangle->location), size(rectangle->size) {};
	//SDL_Rect* toRect(); // TODO may lead to memory leak and also get this working
	bool pointIsInside(double x_val, double y_val);
	bool pointIsInside(CORVID_R2 point);
	DIRECTION relativePosition(CORVID_RECT* otherRect);
	// TODO Definitely a memory leak
	CORVID_R2* shoveDirection(CORVID_RECT* toBeShoved); // This is what I was working on
};
class CORVID_BOUNDBOX : public CORVID_RECT{
public:
	CORVID_R2 velocity;
	CORVID_BOUNDBOX() : CORVID_RECT(), velocity(CORVID_R2()) {};
	CORVID_BOUNDBOX(CORVID_RECT* rectangle, CORVID_R2 velocity) : CORVID_RECT(rectangle), velocity(velocity) {};
	CORVID_BOUNDBOX(CORVID_RECT* rectangle) : CORVID_RECT(rectangle), velocity(CORVID_R2()) {};
	CORVID_BOUNDBOX(double r1, double r2, double s1, double s2, double v1, double v2) :
		CORVID_RECT(CORVID_RECT(r1, r2, s1, s2)), velocity(CORVID_R2(v1, v2)) {};
	CORVID_BOUNDBOX(double xval, double yval);
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