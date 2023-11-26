#pragma once
#ifndef CORVID_GEOM_H
#define CORVID_GEOM_H
// Explained in the Class Itself
#include "CORVID_CLASS.h"
// This is for if I decide to add the toRect() method back
#include "SDL.h"
// Enum Class for the 9 2D Directions; Used for Relative Point Locations.
enum DIRECTION { INSIDE, ABOVE, BELOW, LEFT, RIGHT, UPLEFT, UPRIGHT, DOWNLEFT, DOWNRIGHT };

// ENGINE_LOCAL, ENGINE_GLOBAL and ENGINE_VECTOR has +y for up, -y for down, +x for right, and -x for left
// ENGINE_LOCAL and ENGINE_GLOBAL coordinates should not be mixed
// SURFACE and SURFACE_VECTOR has +x for right, -x for left, +y for down, and -y for up
// STANDARD is for situations that don't require the values to specify direction
// DEFAULT is for error type
// (0, 0) is Bottom Left in ENGINE Coordinates, and Top Left in Surface Coordinates
enum CORVID_COORDTYPE { ENGINE_LOCAL, ENGINE_GLOBAL, SURFACE, ENGINE_VECTOR, SURFACE_VECTOR, DEFAULT, STANDARD, ENGINE_ACCEL };

// 2 Dimensional geometrical coordinates
class CORVID_R2 {
public:
	// X Coordinate (Horizontal)
	double x;
	// Y Coordinate (Vertical)
	double y;
	// Not particularly in use right now, but if/when I create a custom coordinate system
	// With positive y values indicating up, then this is going to be used with custom methods
	// To convert between said coordinate system, and the positive y down system of SDL
	CORVID_COORDTYPE coordType;
	// Empty Constructor
	// @return Vector at (0, 0)
	CORVID_R2() : x(0), y(0), coordType(DEFAULT) {};
	// First Incomplete Constructor: Uses standard (X, Y) Coordinates with DEFAULT coordinate system
	// @param x x-coordinate
	// @param y y-coordinate
	// @return the point (x, y) in the DEFAULT coordinate system
	CORVID_R2(double x, double y) : x(x), y(y), coordType(DEFAULT) {};
	// First Complete Constructor: Uses standard (X, Y) Coordinates with type coordinate system
	// @param x x-coordinate
	// @param y y-coordinate
	// @param type Coordinate type to be used
	// @return the point (x, y) in the DEFAULT coordinate system
	CORVID_R2(double x, double y, CORVID_COORDTYPE type) : x(x), y(y), coordType(type) {};
	// Overloaded Operator to Add R2's together using standard vector addition
	// TODO This is the method that needs to be significantly altered in order to have the CORVID_COORDTYPE work
	// The entire reason that this class and the CORVID_COORDTYPE exists is for error checking in this method
	// @param num1 Vector to be added
	// @return The sum of the 2 Vectors, located in the memory of the original vector
	CORVID_R2& operator+(CORVID_R2& num1);
};
// pushVector is a temporary variable that is reused every time the player needs displacement after
// entering an object. Since only one of these can happen at a time, there is no risk of variable
// reassignment befor its use is completed. However, I should take note of this, as if significant
// changes to the algorithm are made, it could cause data corruption.
// TODO delete this at the end to prevent memory leak
// TODO Should I use something better for a temp variable
static CORVID_R2* tempVector = new CORVID_R2();
// This static variable is the main reason that the CORVID_COORDTYPE class exists because of the rule surrounding
// It that I am creating:
// 1 - (TODO) This is going to be the only SDL_Rect that exists outside of main, and the CONSTS (Might need to add more variables if there are multiple Rects
// 2 - (TODO) Anytime an SDL_Rect is used, I will use a static toRect method to set this ones value equal to the necessary one
// And move forward from there
// 3 - In that transformation, the coordtypes will be set to Surface, via a change of parameters
static SDL_Rect* rect = new SDL_Rect();
// TODO Write Method
static SDL_Rect* toRect(CORVID_RECT* rectin);
// Rectangle perpendicular to X-Y Plane
// Data stored as a location and a size using CORVID_R2
class CORVID_RECT {
public:
	// Upper Left Corner of Rectangle when the datatype is a Surface Datatype
	// Bottom Left Corner of Rectangle when the datatype is a Engine Datatype
	// If the datatype is one of the Vector types, there is a serious error
	// And checking should be done to avoid that
	// If datatype is DEFAULT, it means I'm being lazy, but I should try to avoid that
	// But low priority
	CORVID_R2 location;
	// Corresponds to the size of the rectangle in length and width
	// Should only be either Engine Vector or Surface Vector
	// Or again, DEFAULT if i'm being lazy, but I will try to avoid that
	// But low priority
	CORVID_R2 size;
	// Empty Constructor
	// @return Rectangle at (0, 0) with width and height 0, and Default coordTypes
	CORVID_RECT() : location(CORVID_R2()), size(CORVID_R2()) {};
	// First Incomplete Constructor: 4 Doubles
	// TODO Deal with assigning CORVID_R2 datatypes instead of DEFAULT
	// @param x1 Location X Value
	// @param y1 Location Y Value
	// @param x2 Size X Value
	// @param y2 Size Y Value
	// @return Rectangle with location (x1, y1) and size (x2, y2), and Default coordTypes
	CORVID_RECT(double x1, double y1, double x2, double y2) : location(CORVID_R2(x1, y1)), size(CORVID_R2(x2, y2)) {};
	// First Complete Constructor: 2 CORVID_R2s
	// TODO make sure it reacts properly to the location and size being incorrect values
	// @param location Location of Rectangle
	// @param size Size of Rectangle
	// @return Rectangle with location location and size size
	CORVID_RECT(CORVID_R2 location, CORVID_R2 size) : location(location), size(size) {};
	// Second Incomplete Constructor: Preexisting CORVID_RECT
	// TODO Do I need 3 Constructors for CORVID_RECT?
	// @param rectangle The Preexisting Rectangle
	// @return A second rectangle with the same properties as rectangle, and Default coordTypes
	CORVID_RECT(CORVID_RECT* rectangle) : location(rectangle->location), size(rectangle->size) {};
	// Second Complete Constructor: 4 Doubles and a COORDTYPE
	// TODO I think there are too many constructors
	// COORDTYPE should only be Surface, Engine_Local, Engine_Global, or Standard
	// @param x1 Location X Value
	// @param y1 Location Y Value
	// @param x2 Size X Value
	// @param y2 Size Y Value
	// @return Rectangle with location (x1, y1) and size (x2, y2), and coordType coordType for the location,
	// and the velocity equivalent for the velocity
	CORVID_RECT(double x1, double y1, double x2, double y2, CORVID_COORDTYPE coordType);
	// TODO may lead to memory leak but also get this working
	//SDL_Rect* toRect();

	// Finds if point is located inside of the Rectangle
	// TODO Results assume DEFAULT datatype and I should change that
	// @param x_val The x-coordinate
	// @param y_val the y-coordinate
	// @return True if the point is inside of the Rectangle, False otherwise
	bool pointIsInside(double x_val, double y_val);
	// Finds if point is located inside of the Rectangle
	// TODO Results assume DEFAULT datatype and I should change that
	// @param point The Point in Question
	// @return True if the point is inside of the Rectangle, False otherwise
	bool pointIsInside(CORVID_R2* point);
	// Returns the Direction of the other Rectangle relative to this one as such
	// 1- If they intersect in any way, it will return INSIDE
	// 2- The outer quadrants will only return if the entirety of the other rectangle
	// within that quadrant
	// Defaults to Surface Coordinates
	// TODO Need to fix that
	// Each use of the function requires a maximum of 4 float additions and 4 float compares
	// If I for some reason need galactic level efficiency and need to rewrite portions of this in assembly
	// This method should probably be the one to start on.
	// @param otherRect the Rectangle being compared
	// @return The direction of otherRect relative to the current one
	DIRECTION relativePosition(CORVID_RECT* otherRect);
	// Returns the most suitible direction for toBeShoved to be moved in
	// So that it no longer intersects with the current object
	// Should only run immediately following the method relativePosition returning INSIDE
	// TODO Definitely a memory leak
	// @param toBeShoved The Rectangle to be shoved
	// @return the Vector corresponding to the shoving direction
	CORVID_R2* shoveDirection(CORVID_RECT* toBeShoved);

	CORVID_R2* center();

	double radius();
};

// Rectangle with the added property of Velocity
class CORVID_BOUNDBOX : public CORVID_RECT{
public:
	// Velocity of the Rectangle: Should only have Vector Coordtype
	// But probably has DEFAULT
	// TODO Fix That
	CORVID_R2 velocity;
	// Empty Constructor
	// @return Rectangle at location (0, 0) with size (0, 0) and velocity (0, 0)
	CORVID_BOUNDBOX() : CORVID_RECT(), velocity(CORVID_R2()) {};
	// First Incomplete Constructor: CORVID_RECT
	// @param rectangle Rectangle of the BOUNDBOX
	// @return BOUNDBOX consisting of rectangle with velocity (0, 0)
	CORVID_BOUNDBOX(CORVID_RECT* rectangle) : CORVID_RECT(rectangle), velocity(CORVID_R2()) {};
	// First Complete Constructor: CORVID_RECT and CORVID_R2
	// TODO Should the velocity be a pointer?
	// TODO Should velocity relate to CORVID_COORDTYPE?
	// @param rectangle Rectangle of the BOUNDBOX
	// @param velocity Velocity of the BOUNDBOX
	// @return BOUNDBOX consisting of rectangle with the velocity of velocity
	CORVID_BOUNDBOX(CORVID_RECT* rectangle, CORVID_R2 velocity) : CORVID_RECT(rectangle), velocity(velocity) {};
	// First Complete Constructor: 6 Doubles
	// TODO I'm having it default to ENGINE_GLOBAL Coordtypes; I don't think that there is a scenario where other
	// other coordtypes would be needed, but for completeness, I should have it where the constructor takes coordtype
	// as input. I haven't done that yet because I am lazy.
	// @param r1 Location x-value
	// @param r2 Location y-value
	// @param s1 Width
	// @param s2 Height
	// @param v1 Velocity x-value
	// @param v2 Velocity y-value
	// @return BOUNDBOX at location (r1, r2) with size (s1, s2) and velocity (v1, v2)
	CORVID_BOUNDBOX(double r1, double r2, double s1, double s2, double v1, double v2) :
		CORVID_RECT(CORVID_RECT(r1, r2, s1, s2, CORVID_COORDTYPE::ENGINE_GLOBAL)), velocity(CORVID_R2(v1, v2, CORVID_COORDTYPE::ENGINE_VECTOR)) {};
	// Second Incomplete Constructor: 2 Doubles
	// TODO Maybe deprecate this or other constructors, and if I don't deprecate, make size based on UNIT or KUNIT from consts
	// @param xval Location x-value
	// @param yval Location y-value
	// @return Rectangle at location (xval, yval) with size (32, 32) and velocity(0, 0)
	CORVID_BOUNDBOX(double xval, double yval);
};
// The below comment will be uncommented when I add back Bezier Curves
/*
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