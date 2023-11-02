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

using namespace std::filesystem;

using namespace CORVID_SPRITE;

using namespace CORVID_FILE;

const std::string defaultFile = "titleScreen.png";

const std::string defaultBackground = "sky.png";

const int totalNumberLevels = 1;
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
class CORVID_CAMERA {
	// The Current Location of the Camera
	CORVID_R2* cameraLocation;
	// The size of the frame the camera is on in the extended coordinate system
	CORVID_RECT* frame;
	// Is going to be needed for every method anyways so I might as well put it here
	CORVID_PLAYER* player;


};

class CORVID_PHYSIC{

	void createDataStructures(path fileName);

	void createDataStructures();
public:

	const char* name;

	CORVID_PLAYER* player;

	CORVID_R2* cameraLocation;

	CORVID_R2* cameraSpeed;

	CORVID_SCREENOBJECT* activeCheckPoint;

	CORVID_SCREENOBJECT* selectedObject;

	CORVID_SCREENOBJECT* unselectedObject;

	CORVID_OBJFILE* dataFile;

	// TODO Create automatic sorting of objects added to these lists via overloaded methods
	std::vector<CORVID_SCREENOBJECT*>* staticList; 

	std::vector<CORVID_SCREENOBJECT*>* dynamicList;

	std::vector<CORVID_SCREENOBJECT*>* checkPoints;

	CORVID_SCREENOBJECT* background;

	inline int totalStaticObjects() { return (int)staticList->size(); }

	inline int totalDynamicObjects() { return (int)dynamicList->size(); }
	
	inline int totalCheckPoints() { return (int)checkPoints->size(); }
	
	CORVID_SCREENOBJECT* findByPosition(int x, int y);
	
	int totalCount() { return (int)(staticList->size() + dynamicList->size() + checkPoints->size()); };
	
	CORVID_PHYSIC();
	
	CORVID_PHYSIC(const char* name); 
	
	CORVID_PHYSIC(path fileName, std::vector<CORVID_PHYSIC*>* world);
	
	CORVID_PHYSIC(std::vector<CORVID_PHYSIC*>* world, int levelNum); 
	
	void loadScreen();
	
	void saveLevel(path dataFile);
	
	void loadObject(char* data);
	
	void render(SDL_Renderer* surface);
	
	// TODO Move this to the CORVID_SPRITE file or something
	void saveObject(CORVID_SCREENOBJECT* object, std::ofstream* binOut); 
	
	void removeObject(CORVID_SCREENOBJECT* object);
};

class CORVID_FRAME {

};

class CORVID_CONTIG {

};

class CORVID_LEVEL: public CORVID_TEXTLIST{ // The inherited class is the title screen TODO what does the previous phrase mean
	
	int activeLevelData;
public:
	
	std::vector<CORVID_PHYSIC*>* levels;
	
	int lastCheckPointLevel;
	
	int block_x;
	
	int block_y;
	
	CORVID_SCREENOBJECT* selectedObject;
	
	CORVID_SCREENOBJECT* unselectedObject;
	
	inline void setLevel(int newLevel) { activeLevelData = newLevel; };
	
	//inline void setLevel(CORVID_SCREEN* newLevel) {} Need to make this eventually
	
	inline CORVID_PHYSIC* activeLevel() { return levels->at(activeLevelData); };// Needs edge case checking
	
	inline CORVID_PLAYER* player() { return activeLevel()->player; };
	
	inline CORVID_R2* getcameraLocation() { return activeLevel()->cameraLocation; };
	
	inline CORVID_R2* getcameraSpeed() { return activeLevel()->cameraSpeed; }
	
	inline CORVID_SPRITE::CORVID_SCREENOBJECT* activeCheckPoint() { return activeLevel()->activeCheckPoint; };
	
	inline std::vector<CORVID_SCREENOBJECT*>* staticList() { return activeLevel()->staticList; };
	
	inline std::vector<CORVID_SCREENOBJECT*>* dynamicList() { return activeLevel()->dynamicList; };
	
	inline CORVID_SCREENOBJECT* getbackground() { return activeLevel()->background; };
	
	inline std::vector<CORVID_SCREENOBJECT*>* checkPoints() { return activeLevel()->checkPoints; };
	
	inline CORVID_SCREENOBJECT* staticList(int index) { return activeLevel()->staticList->at(index); };
	
	inline CORVID_SCREENOBJECT* dynamicList(int index) { return activeLevel()->dynamicList->at(index); };
	
	inline CORVID_SCREENOBJECT* checkPoints(int index) { return activeLevel()->checkPoints->at(index); };
	
	inline int totalStaticObjects() { return (int)activeLevel()->staticList->size(); }
	
	inline int totalDynamicObjects() { return (int)activeLevel()->dynamicList->size(); }
	
	inline int totalCheckPoints() { return (int)activeLevel()->checkPoints->size(); }
	
	inline int totalCount() { return (int)activeLevel()->totalCount(); }
	
	inline CORVID_SCREENOBJECT* findByPosition(int x, int y) { return activeLevel()->findByPosition(x, y); };
	
	CORVID_LEVEL(); // Default Constructor, should be the main one
	
	CORVID_LEVEL(path worldFile, path textureFile, SDL_Renderer* renderer);
	
	void saveWorld();
	
	inline void render(SDL_Renderer* surface) { activeLevel()->render(surface); }
	
	void selectObject(CORVID_SCREENOBJECT* objectToSelect);
	
	void unselectObject();
	
	void deleteObject();
	
	void playerMoveLeft();
	
	void playerMoveRight();
	
	void playerJump();
	
	void stopJump();
	
	void updateStatics();
	
	void updateDynamics();
	
	void updatePlayer();
	
	void collisionDetect();
	
	void updateCamera();
	
	void centerPlayer();
	
	void staticPlayerObjectCollision();
};
#endif