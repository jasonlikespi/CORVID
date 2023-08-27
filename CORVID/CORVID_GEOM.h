#pragma once
#ifndef CORVID_GEOM_H
#define CORVID_GEOM_H
#include <string>
#include <math.h>
#include <vector>

class CORVID_R2{
public:
	double x;
	double y;
	CORVID_R2() : x(0), y(0) {};
	CORVID_R2(double x, double y) : x(x), y(y) {};
	CORVID_R2(int x, int y) : x((double)x), y((double)y) {};
};
class CORVID_RECT{
public:
	CORVID_R2 location;
	CORVID_R2 size;
	CORVID_RECT() : location(CORVID_R2()), size(CORVID_R2()){};
	CORVID_RECT(double x1, double y1, double x2, double y2) : location(CORVID_R2(x1, y1)), size(CORVID_R2(x2, y2)) {};
	CORVID_RECT(int x1, int y1, int x2, int y2) : location(CORVID_R2(x1, y1)), size(CORVID_R2(x2, y2)) {};
	CORVID_RECT(CORVID_R2 location, CORVID_R2 size) : location(location), size(size) {};
};
class CORVID_BOUNDBOX{
public:
	CORVID_RECT rectangle;
	CORVID_R2 velocity;
	CORVID_BOUNDBOX() : rectangle(CORVID_RECT()), velocity(CORVID_R2()) {};
	CORVID_BOUNDBOX(CORVID_RECT rectangle, CORVID_R2 velocity) : rectangle(rectangle), velocity(velocity) {};
	CORVID_BOUNDBOX(CORVID_RECT rectangle) : rectangle(rectangle), velocity(CORVID_R2()) {};
	CORVID_BOUNDBOX(double r1, double r2, double s1, double s2, double v1, double v2) : rectangle(CORVID_RECT(r1, r2, s1, s2)), velocity(CORVID_R2(s1, s2)) {};
	CORVID_BOUNDBOX(int r1, int r2, int s1, int s2, int v1, int v2) : rectangle(CORVID_RECT(r1, r2, s1, s2)), velocity(CORVID_R2(s1, s2)) {};
	CORVID_BOUNDBOX(int xval, int yval) : rectangle(CORVID_RECT(xval, yval, 16, 16)), velocity(CORVID_R2()) {};
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