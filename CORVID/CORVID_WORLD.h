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
	CORVID_R2<int>* cameraLocation;
	CORVID_SCREENOBJECT* activeCheckPoint;
	CORVID_OBJFILE* dataFile;
	// TODO Create automatic sorting of objects added to these lists via overloaded methods
	std::vector<CORVID_SCREENOBJECT*>* staticList; 
	std::vector<CORVID_SCREENOBJECT*>* dynamicList;
	std::vector<CORVID_SCREENOBJECT*>* checkPoints;
	CORVID_SCREENOBJECT* background;
	inline int totalStaticObjects() { return (int)staticList->size(); }
	inline int totalDynamicObjects() { return (int)dynamicList->size(); }
	//inline int totalBackgroundObjects() { return (int)backgroundList->size(); }
	inline int totalCheckPoints() { return (int)checkPoints->size(); }
	CORVID_SCREENOBJECT* findByPosition(int x, int y);
	int totalCount() { return (int)(staticList->size() + dynamicList->size() + checkPoints->size()); };
	CORVID_SCREEN();
	// Used as base class for CORVID_WORLD
	// TODO have it where the base class holds the data for active level to prevent NULL data and perhaps efficiency in some way
	CORVID_SCREEN(const char* name); 
	CORVID_SCREEN(path fileName, std::vector<CORVID_SCREEN*>* world);
	CORVID_SCREEN(std::vector<CORVID_SCREEN*>* world, int levelNum); 
	void loadScreen();
	//void save();
	void saveLevel(path dataFile);
	void loadObject(char* data);
	void render(SDL_Surface* surface);
	// TODO Move this to the CORVID_SPRITE file or something
	void saveObject(CORVID_SCREENOBJECT* object, std::ofstream* binOut); 

};

class CORVID_WORLD: public CORVID_TEXTLIST{ // The inherited class is the title screen
	int activeLevelData;
	void loadTextures();
public:
	std::vector<CORVID_SCREEN*>* levels;
	int lastCheckPointLevel;
	int time;
	int block_x;
	int block_y;
	std::vector<SDL_Surface*>* textures;
	inline void setLevel(int newLevel) { activeLevelData = newLevel; };
	//inline void setLevel(CORVID_SCREEN* newLevel) {} Need to make this eventually
	inline CORVID_SCREEN* activeLevel() { return levels->at(activeLevelData); };// Needs edge case checking
	inline CORVID_PLAYER* player() { return activeLevel()->player; };
	inline CORVID_R2<int>* cameraLocation() { return activeLevel()->cameraLocation; };
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
	CORVID_WORLD(path worldFile, path textureFile);
	void saveWorld();
	//void saveLevel();
	inline void render(SDL_Surface* surface) { activeLevel()->render(surface); }
};
/*
inline CORVID_SCREENOBJECT<float>** load(const char* fileName) {
	std::fstream fileStream;
	fileStream.open(fileName);
	return NULL;
}
*/
#endif