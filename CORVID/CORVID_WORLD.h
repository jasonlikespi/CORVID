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

class CORVID_SCREEN{
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
	CORVID_SCREEN();
	CORVID_SCREEN(const char* name); 
	CORVID_SCREEN(path fileName, std::vector<CORVID_SCREEN*>* world);
	CORVID_SCREEN(std::vector<CORVID_SCREEN*>* world, int levelNum); 
	void loadScreen();
	void saveLevel(path dataFile);
	void loadObject(char* data);
	void render(SDL_Renderer* surface);
	// TODO Move this to the CORVID_SPRITE file or something
	void saveObject(CORVID_SCREENOBJECT* object, std::ofstream* binOut); 
	void removeObject(CORVID_SCREENOBJECT* object);
};

class CORVID_WORLD: public CORVID_TEXTLIST{ // The inherited class is the title screen TODO what does the previous phrase mean
	int activeLevelData;
public:
	std::vector<CORVID_SCREEN*>* levels;
	int lastCheckPointLevel;
	int block_x;
	int block_y;
	CORVID_SCREENOBJECT* selectedObject;
	CORVID_SCREENOBJECT* unselectedObject;
	inline void setLevel(int newLevel) { activeLevelData = newLevel; };
	//inline void setLevel(CORVID_SCREEN* newLevel) {} Need to make this eventually
	inline CORVID_SCREEN* activeLevel() { return levels->at(activeLevelData); };// Needs edge case checking
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
	CORVID_WORLD(); // Default Constructor, should be the main one
	CORVID_WORLD(path worldFile, path textureFile, SDL_Renderer* renderer);
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