#pragma once
#ifndef CORVID_WORLD_H
#define CORVID_WORLD_H

#include <vector>

#include "CORVID_SPRITES.h"

#include <fstream>

#include <iostream>

#include <exception>

#include <string>

#include <stdio.h>

#include "CORVID_FILE.h"

#include <filesystem>
// Explained in the Class Itself
#include "CORVID_CLASS.h"

#include "CORVID_STRUCTURE.h"
using namespace std::filesystem;

//Classes I'm tryna add
// CORVID_FRAME for each rectangular segment
// CORVID_CONTIG for sets of CORVID_FRAMEs that connect, and can have the camera scroll between them
// CORVID_CAMERA because in order to do the above I'm going to need to create more complex camera work. Subclass of CORIVD_CONTIG
// CORVID_LEVEL for sets of CORVID_CONTIGs which can be crossed by doors/portals
// CORVID_PHYSIC abstract base class for CORVID_FRAME, CORVID_CONTIG, and CORVID_LEVEL
// CORVID_LEVEL based on current CORVID_WORLD class
// CORVID_PHYSIC based on CORVID_SCREEN
// TODO Expand the CORVID_COORDTYPE class to differentiate between local coordinates (used within the same CORVID_FRAME) and 
// global coordinates (used between CORVID_FRAMES within the same CORVID_CONTIG)
// There will be no global coordinate system in a CORVID_LEVEL between CORVID_CONTIGs because they are not part of the same metric space
// TODO I think I am going to have every CORVID_LEVEL save as its own file, and have an unused part of the object data (the header)
// indicate which CORVID_FRAME it is part of
// Also I think I'm going to have CORVID_CONTIG extend CORVID_FRAME, but not have CORVID_LEVEL extend CORVID_CONTIG or CORVID_FRAME
// But have all of them extend CORVID_PHYSIC

// Class to describe the camera behavior
// For now I'm just going to use a simple procedure
// 1- Assume each camera is on a rectanglar CORVID_FRAME
// 2- If the player is in the middle of the screen, center the player
// 3- If the player is on the edge of the screen, don't scroll past the end of the screen
// Also Note this class is a combination of the old CORVID_CAMERA class and the depracated CORVID_RENDER class
// Which could cause some sort of issue 
class CORVID_CAMERA : public CORVID_OBJFILE{
public:
	// The Current Location of the Camera
	CORVID_R2* cameraLocation;
	// The size of the frame the camera is on in the extended coordinate system
	CORVID_RECT* frame;
	// Is going to be needed for every method anyways so I might as well put it here
	CORVID_PLAYER* player;
	// Don't Use this constructor ever
	CORVID_CAMERA();

	CORVID_CAMERA(CORVID_RECT* frame, CORVID_PLAYER* player);

	CORVID_CAMERA(path worldFile);

	CORVID_CAMERA(std::vector<int>* input);
	
	virtual void updateCamera();

	virtual void centerPlayer();

	// std::vector<CORVID_BACKGROUND*>* backgrounds;

	static SDL_Renderer* surface;

	virtual void render();

	void save(std::filesystem::path folder) override;

	virtual CORVID_R2* getcameraLocation();

};
// Note to self
// Scratch what I said earlier, initialize every class blank,
// Add all of the objects later from one method in CORVID_LEVEL


// Abstract class?
// Not used for saving or loading data, CORVID_OBJFILE constructor is used to simplify
// case of class created on startup with a lot of objects
// For saving and loading initial data, use CORVID_FRAME class
// Also not used for rendering data
// Just used for physics interactions
class CORVID_PHYSIC{

public:
	// TODO Create automatic sorting of objects added to these lists via overloaded methods
	std::vector<CORVID_SCREENOBJECT*>* staticList; 

	std::vector<CORVID_SCREENOBJECT*>* dynamicList;

	CORVID_PHYSIC();

	virtual int totalStaticObjects();

	virtual int totalDynamicObjects();
	// Okay I might have to deal with NULL now
	virtual CORVID_SCREENOBJECT* findByPosition(CORVID_R2* position);
	
	virtual int totalObjectCount();
	
	virtual void removeObject(CORVID_SCREENOBJECT* object);

	virtual void addObject(CORVID_SCREENOBJECT* object);

	virtual void updateStatics();

	virtual void updateDynamics();
	
	virtual void collisionDetect();

	virtual void playerMoveLeft();

	virtual void playerMoveRight();

	virtual void playerJump();

	virtual void stopJump();
	
	virtual void updatePlayer();

	virtual void staticPlayerObjectCollision();
};

class CORVID_FRAME : public CORVID_PHYSIC, public CORVID_CAMERA{

public:

	CORVID_CONTIG* contig;

	CORVID_BACKGROUND* background;
	CORVID_FRAME* frameAbove;
	CORVID_FRAME* frameBelow;
	CORVID_FRAME* frameLeft;
	CORVID_FRAME* frameRight;
	int frameNum;
	int contigNum;

	CORVID_FRAME();

	CORVID_FRAME(CORVID_CONTIG* contig);

	CORVID_FRAME(CORVID_LEVEL* level, std::vector<int>* input);
	int* dataDump();
	void loadScreen();
	int totalStaticObjects() override;
	int totalDynamicObjects() override;
	CORVID_SCREENOBJECT* findByPosition(CORVID_R2* position) override;
	int totalObjectCount() override;
	void removeObject(CORVID_SCREENOBJECT* object) override;
	void addObject(CORVID_SCREENOBJECT* object) override;
	void updateStatics() override;
	void updateDynamics() override;
	void collisionDetect() override;
	void playerMoveLeft() override;
	void playerMoveRight() override;
	void playerJump() override;
	void stopJump() override;
	void updatePlayer() override;
	void staticPlayerObjectCollision() override;
	void save(std::filesystem::path folder) override;
	void render() override;
	CORVID_R2* getcameraLocation() override;
};

class CORVID_CONTIG : public CORVID_PHYSIC, public CORVID_CAMERA {

public:
	std::vector<CORVID_FRAME*>* frames;

	CORVID_FRAME* activeFrame;

	CORVID_LEVEL* level;

	int contigNum;

	CORVID_CONTIG();

	CORVID_CONTIG(CORVID_LEVEL* level);

	int totalFrames();
	int contigNumber();
	int totalStaticObjects() override;
	int totalDynamicObjects() override;
	CORVID_SCREENOBJECT* findByPosition(CORVID_R2* position) override;
	int totalObjectCount() override;
	void removeObject(CORVID_SCREENOBJECT* object) override;
	void addObject(CORVID_SCREENOBJECT* object) override;
	void updateStatics() override;
	void updateDynamics() override;
	void collisionDetect() override;
	void playerMoveLeft() override;
	void playerMoveRight() override;
	void playerJump() override;
	void stopJump() override;
	void updatePlayer() override;
	void staticPlayerObjectCollision() override;
	void save(std::filesystem::path folder) override;
	void render() override;
	void add(CORVID_FRAME* frameToAdd);
	CORVID_R2* getcameraLocation() override;
};

class CORVID_LEVEL: public CORVID_TEXTLIST, public CORVID_PHYSIC, public CORVID_CAMERA {

public:
	
	std::vector<CORVID_CONTIG*>* contigs;
	// TODO Don't know if a vector is the right one,
	// but I need some sort of data structure of 
	// FRAMEs for saving the game
	// I'm using data structures instead
	// std::vector<CORVID_FRAME*>* frames;

	CORVID_CONTIG* activeContig;

	CORVID_FRAME* activeFrame;

	CORVID_SCREENOBJECT* selectedObject;
	
	CORVID_SCREENOBJECT* unselectedObject;
	
	// Default Constructor, should be the main one
	CORVID_LEVEL();
	
	CORVID_LEVEL(path worldFile, path textureFile, SDL_Renderer* renderer);
	
	void selectObject(CORVID_SCREENOBJECT* objectToSelect);
	
	void unselectObject();

	int totalFrames();
	// inline void setLevel(int newLevel) { activeLevelData = newLevel; };
	void setFrame(CORVID_FRAME* newFrame);
	// Note: This is more permenant than removeObject
	void deleteObject(CORVID_SCREENOBJECT* object);
	int totalStaticObjects() override;
	int totalDynamicObjects() override;
	CORVID_SCREENOBJECT* findByPosition(CORVID_R2* position) override;
	int totalObjectCount() override;
	void removeObject(CORVID_SCREENOBJECT* object) override;
	void addObject(CORVID_SCREENOBJECT* object) override;
	void updateStatics() override;
	void updateDynamics() override;
	void collisionDetect() override;
	void playerMoveLeft() override;
	void playerMoveRight() override;
	void playerJump() override;
	void stopJump() override;
	void updatePlayer() override;
	void staticPlayerObjectCollision() override;
	void save(std::filesystem::path folder) override;
	void render() override;
	void add(std::vector<int>* input);
	void add(CORVID_FRAME* frameToAdd);
	void add(CORVID_CONTIG* contigToAdd);
	CORVID_FRAME* getFrame(int frameNumber);
	CORVID_R2* getcameraLocation() override;
};
#endif