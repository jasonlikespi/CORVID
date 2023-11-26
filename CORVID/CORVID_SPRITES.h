#pragma once
#ifndef CORVID_SPRITES_H
#define CORVID_SPRITES_H
// Explained in the Class Itself
#include "CORVID_CLASS.h"
// Needed for CORVID_RECT and other classes
#include "CORVID_GEOM.h"
// Needed for the render method
#include <SDL_Image.h>
// Needed for one of the CORVID_SCREENOBJECT constructors
// TODO Maybe deprecate that constructor or remove?
#include <vector>
// Needed because CORVID_SCREENOBJECT extends this class
#include "CORVID_TEXTURE.h"

	// Effectively abstract class consists of an integer, which indicates the intrinsic physical properties of the Sprite object
	// TODO Consider making class abstract or something
	// Or just an enum class 
	// TODO Consider if replacing with Bitwise Arithmetic would decrease the operation time from O(n) where n is the total number of data types
	// To O(1), but limit the total number of methods to 32?

enum class CORVID_PHYSICTYPE {
	ERROR,
	BACKGROUND,
	STATIC,
	PLAYER,
	DYNAMIC
};
class CORVID_SPRITEDATATYPE {
	public:
		// The Physics Type
		CORVID_PHYSICTYPE physicType;
		// Empty Constructor
		// @return CORVID_SPRITEDATATYPE with Error Type
		CORVID_SPRITEDATATYPE() : physicType(CORVID_PHYSICTYPE::ERROR) {};
		// First Complete Constructor
		// @param physicType
		// @return CORVID_SPRITEDATATYPE with physicType physicType
		CORVID_SPRITEDATATYPE(int physicType);
		// @return true if the Object is affected by Gravity, false otherwise
		bool isAffectedByGravity();
		// TODO Write Method
		// @return true if the object is affected by friction, false otherwise
		bool hasFriction();
		// TODO Write Method
		// @return true if the object can damage the player, false otherwise
		bool canDamage();
		// TODO Write Method
		// TODO What am I doing with this
		// @return true if the object is a checkpoint, false otherwise
		bool isCheckPoint();
		// TODO Write Method
		// TODO What am I doing with this
		// @return true if the object is a levelswap, false otherwise
		bool isLevelSwap();
		// TODO Write Method
		// @return true if the object is dynamic, false otherwise
		bool isDynamic();
};
// Base class for all objects that appear on screen, consisting of a CORVID_BOUNDBOX for location, size, and velocity data,
// a CORVID_TEXTURE for the texture of the object, and a CORVID_SPRITEDATATYPE for the objects interactions properties
class CORVID_SCREENOBJECT : public CORVID_BOUNDBOX, public CORVID_TEXTURE, public CORVID_SPRITEDATATYPE{
	public:
		// Field indicating if the object is selected
		bool selected;
		// Field inicating if the object is in freefall or to be physically precise, experiences any normal force to gravity
		bool freeFall;
		// I also need to include which frame it is referenced as a number
		// TODO Consider removing and having this class feature perpetual usage of the initializer array
		// as a parent class
		int frameNum;
		// Reference to the Frame it is a part of
		CORVID_FRAME* frame;
		// Empty Constructor
		// Should not use
		// @return CORVID_SCREENOBJECT located at (0, 0) with size (0, 0), velocity (0, 0), object id of 0, and texture iD of 3
		CORVID_SCREENOBJECT();
		// First Incomplete Constructor: 2 Doubles and a CORVID_TEXTURE
		// TODO I should deprecate this because of the CORVID_TEXTURE as part of the constructor
		// TODO also make the 32's into UNIT or KUNIT
		// TODO also object id is uninitialized
		// @param x the x-coordinate of the object
		// @param y the y-coordinate of the object
		// @param texture the texture id of the object
		// @return CORVID_SCREENOBJECT located at (x, y) with size (32, 32), velocity (0, 0), object id 0, and texture of texture
		// also selected is set to false and freefall is set to true
		CORVID_SCREENOBJECT(double x, double y, CORVID_TEXTURE* texture) : 
			CORVID_BOUNDBOX(x, y), CORVID_TEXTURE(*texture), selected(false), freeFall(true), frame(nullptr) {};
		// First Incomplete Constructor: Initialization Vector
		// TODO Consider changing to initialization array
		// Even though selected and freeFall are not set by the initialization array, it still counts as a complete constructor
		// Because in all instances of this object, those are the values they should be set to when the simulation starts
		// And even if returned from a paused game or something, the values are still acceptable
		// TODO As I write that I remembered the velocity is unwritten so when I add moving static objects, it will be incomplete
		// TODO maybe freeFall could break if returning from a stopped game but that's a long ways off
		// TODO frame should never initiate to null pointer, I just put it in to get rid of the warning
		// @param data a vector of size 8 containing all of the objects data
		// data(0) - Header Int
		// data(1) - Location X Value
		// data(2) - Location Y Value
		// data(3) - Size X Value
		// data(4) - Size Y Value
		// data(5) - CORVID_SPRITEDATATYPE
		// data(6) - Texture Value
		// data(7) - Movement Behavior Value
		// @return The CORVID_SCREENOBJECT with the properties given by the vector
		CORVID_SCREENOBJECT(std::vector<int>* data) : 
			CORVID_BOUNDBOX(data->at(1), data->at(2), data->at(3), data->at(4), 0, 0),
			CORVID_SPRITEDATATYPE(data->at(5)), CORVID_TEXTURE(data->at(6)), selected(false), freeFall(true), frame(nullptr), frameNum(data->at(0)){};
		// Second Incomplete Constructor: 8 Doubles
		// TODO Should probably remove irrelevant parameters 
		// Even though selected and freeFall are not set by the initialization array, it still counts as a complete constructor
		// Because in all instances of this object, those are the values they should be set to when the simulation starts
		// And even if returned from a paused game or something, the values are still acceptable
		// TODO As I write that I remembered the velocity is unwritten so when I add moving static objects, it will be incomplete
		// TODO maybe freeFall could break if returning from a stopped game but that's a long ways off
		// @param i0 - Header Int
		// @param i1 - Location X Value
		// @param i2 - Location Y Value
		// @param i3 - Size X Value
		// @param i4 - Size Y Value
		// @param i5 - CORVID_SPRITEDATATYPE
		// @param i6 - Texture Value
		// @param i7 - Movement Behavior Value
		// @return The CORVID_SCREENOBJECT located at (i1, i2), size(i3, i4), velocity(0, 0), objectId i5, textureValue i6
		CORVID_SCREENOBJECT(double i0, double i1, double i2, double i3, double i4, double i5, double i6, double i7) : 
			CORVID_BOUNDBOX((int)i1, (int)i2, (int)i3, (int)i4, 0, 0), CORVID_SPRITEDATATYPE((int)i5), CORVID_TEXTURE((int)i6), selected(false), freeFall(true), frame(nullptr), frameNum((int)i0) {};
		// Renders the CORVID_SCREENOBJECT to the screen described by surface, while viewed by cameraLocation
		// TODO Consider reworking class to remove parameters for this method, leaving references to cameraLocation and surface as a part of the class
		// Of note is that would require difficulty with classes referencing recursively, likely the main reason I haven't done this yet
		// @param surface the surface to be rendered to
		// @param cameraLocation the location of the camera
		// @return void
		void render(SDL_Renderer* surface, CORVID_CAMERA* camera);
		// Distills the physical properties of the object to an array of 8 integers
		// This is definitely a memory leak, but considering how broken everything is already, I will fix it later
		// Also it's not a super bad memory leak considering it only runs whenever the game saves
		// @return an array with 8 elements that correspond directly to the constructor parameters
		int* dataDump(); 
		// Updates the Sprites data in accordance with velocity, gravity, and physical properties
		// TODO I should consider renaming this to reflect that frames are not involved, and this is just updating the objects location
		// Once per Frame. Actually that's probably where the frame comes from but I should still change it
		// @return void
		void updateFrame();

		void save(std::filesystem::path binFile);
};

// I made a class dedicated to just the player
// TODO Maybe make static or something?
// Contains several other player specific fields
class CORVID_PLAYER : public CORVID_SCREENOBJECT{
	public:
		// Reference to the object that the player is standing on top of
		// Initializes to NULL
		// TODO Currently not used. Should probably use it. Might relate to not being able to move across objects horizontaly.
		// TODO Could eventually caused problems if a game is restarted
		CORVID_SCREENOBJECT* objectStandingOn;
		// Reference to the object that is to the left
		// Initializes to NULL
		// TODO Currently not used. Will probably need to use for moving objects.
		// TODO Could eventually caused problems if a game is restarted
		CORVID_SCREENOBJECT* leftObject;
		// Reference to the object that is to the right
		// Initializes to NULL
		// TODO Currently not used. Will probably need to use for moving objects.
		// TODO Could eventually caused problems if a game is restarted
		CORVID_SCREENOBJECT* rightObject;
		// Equals -1 if the player is in freefall
		// Equals 0 if the player is on the ground, and able to jump
		// For positive integers, refers to the player having been jumping for that many frames
		// Initializes at -1
		// TODO Could eventually caused problems if a game is restarted
		int jumpFrame;
		// Empty Constructor
		// I should change the constructor to make it useful as a default constructor
		// @return CORVID_SCREENOBJECT located at (0, 0), size (0, 0), velocity (0, 0), objectId 0, textureId 3
		// freefall true, selected false, objectStandingOn, leftObject, and rightObject all NULL
		CORVID_PLAYER() : CORVID_SCREENOBJECT(), objectStandingOn(NULL), leftObject(NULL), rightObject(NULL), jumpFrame(-1) {};
		// First Incomplete Constructor
		// TODO I think I should deprecate this constructor, especially with the texture pointer
		// Also Object Id should be dynamic
		// @param xloc the x coordinate
		// @param yloc the y coordinate
		// @param texture pointer to the texture
		// @return CORVID_PLAYER located at (xloc, yloc), size(32, 64), velocity(0, 0), objectId 0, textureValue 2
		// freefall true, selected false, objectStandingOn, leftObject, and rightObject all NULL
		CORVID_PLAYER(double xloc, double yloc, CORVID_TEXTURE* texture) : 
			CORVID_SCREENOBJECT(0, xloc, yloc, 32, 64, 0, 2, 0), objectStandingOn(NULL), leftObject(NULL), rightObject(NULL), jumpFrame(-1) {};
		// Second Incomplete Constructor
		// TODO Should probably remove irrelevant parameters
		// @param i0 - Header Int
		// @param i1 - Location X Value
		// @param i2 - Location Y Value
		// @param i3 - Size X Value
		// @param i4 - Size Y Value
		// @param i5 - Object Type Value (0 is static, 1 is dynamic, 2 is background, 3 is checkpoint)
		// @param i6 - Texture Value
		// @param i7 - Movement Behavior Value
		// @return The CORVID_PLAYER located at (i1, i2), size(i3, i4), velocity(0, 0), objectId i5, textureValue i6
		// freefall true, selected false, objectStandingOn, leftObject, and rightObject all NULL
		CORVID_PLAYER(double i0, double i1, double i2, double i3, double i4, double i5, double i6, double i7) :
			CORVID_SCREENOBJECT(i0, i1, i2, i3, i4, i5, i6, i7), objectStandingOn(NULL), leftObject(NULL), rightObject(NULL), jumpFrame(-1) {};
		// Accelerates the player to the left if they're below the speed cap
		// @return void
		void moveLeft();
		// Accelerates the player to the right if they're below the speed cap
		// @return void
		void moveRight();
		// If player is in freefall, does nothing, if player is on ground, starts accelerating a jump, if midjump, accelerates further
		// Until max jump length is reached
		// @return void
		void jump();
};
	
// I made a class dedicated to just the background
// TODO literally anything with this class
// Or remove the class
class CORVID_BACKGROUND : public CORVID_SCREENOBJECT{ 
	public:
		// Empty Constructor
		// @return An Empty CORVID_SCREENOBJECT
		CORVID_BACKGROUND() {};
		// First Incomplete Constructor
		// @param i0 - Header Int
		// @param i1 - Location X Value
		// @param i2 - Location Y Value
		// @param i3 - Size X Value
		// @param i4 - Size Y Value
		// @param i5 - Object Type Value (0 is static, 1 is dynamic, 2 is background, 3 is checkpoint)
		// @param i6 - Texture Value
		// @param i7 - Movement Behavior Value
		// @return The CORVID_BACKGROUND located at (i1, i2), size(i3, i4), velocity(0, 0), objectId i6, textureValue i6
		// freefall true, selected false, objectStandingOn, leftObject, and rightObject all NULL
		CORVID_BACKGROUND(double i0, double i1, double i2, double i3, double i4, double i5, double i6, double i7) :
			CORVID_SCREENOBJECT(i0, i1, i2, i3, i4, i5, i6, i7) {};
		CORVID_BACKGROUND(std::vector<int>* data) :
			CORVID_SCREENOBJECT(data) {};

};
#endif