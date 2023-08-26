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

const std::string defaultFile = "titleScreen.png";
const std::string defaultBackground = "sky.png";
const int totalNumberLevels = 1;

class CORVID_SCREEN : CORVID_FILE{
public:
	const char* name;
	CORVID_PLAYER* player;
	CORVID_R2* cameraLocation;
	CORVID_SCREENOBJECT* activeCheckPoint;
	std::vector<CORVID_SCREENOBJECT*>* staticList; // Create automatic sorting of objects added to these lists via overloaded methods
	std::vector<CORVID_SCREENOBJECT*>* dynamicList;
	std::vector<CORVID_SCREENOBJECT*>* backgroundList;
	std::vector<CORVID_SCREENOBJECT*>* checkPoints;
	inline int totalStaticObjects() { return (int)staticList->size(); }
	inline int totalDynamicObjects() { return (int)dynamicList->size(); }
	inline int totalBackgroundObjects() { return (int)backgroundList->size(); }
	inline int totalCheckPoints() { return (int)checkPoints->size(); }
	int totalCount() { return (int)(staticList->size() + dynamicList->size() + backgroundList->size() + checkPoints->size()); };
	CORVID_SCREEN(path fileName, std::vector<CORVID_SCREEN*>* world) : CORVID_FILE(fileName){
		staticList = new std::vector<CORVID_SCREENOBJECT*>();
		dynamicList = new std::vector<CORVID_SCREENOBJECT*>();
		backgroundList = new std::vector<CORVID_SCREENOBJECT*>();
		checkPoints = new std::vector<CORVID_SCREENOBJECT*>();
		this->loadScreen();
		world->push_back(this);
	}
	CORVID_SCREEN(std::vector<CORVID_SCREEN*>* world) : activeCheckPoint(NULL), cameraLocation(NULL), player(NULL), name("testo"){
		staticList = new std::vector<CORVID_SCREENOBJECT*>();
		dynamicList = new std::vector<CORVID_SCREENOBJECT*>();
		backgroundList = new std::vector<CORVID_SCREENOBJECT*>();
		checkPoints = new std::vector<CORVID_SCREENOBJECT*>();
		const std::string fileName = "titleScreen.png";
		CORVID_SCREENOBJECT* background = new CORVID_SCREENOBJECT();
		background->texture = IMG_Load(fileName.c_str());
		backgroundList->push_back(background);
		world->push_back(this);
	}
	CORVID_SCREEN(std::vector<CORVID_SCREEN*>* world, int levelNum) : activeCheckPoint(NULL), cameraLocation(NULL), player(NULL), name("testo") {
		staticList = new std::vector<CORVID_SCREENOBJECT*>();
		dynamicList = new std::vector<CORVID_SCREENOBJECT*>();
		backgroundList = new std::vector<CORVID_SCREENOBJECT*>();
		checkPoints = new std::vector<CORVID_SCREENOBJECT*>();
		const std::string fileName = "sky.png";
		switch (levelNum) {
			case 1:
				CORVID_SCREENOBJECT* background = new CORVID_SCREENOBJECT();
				background->texture = IMG_Load(fileName.c_str());
				backgroundList->push_back(background);
				world->push_back(this);
				break;
		}
	}
	void loadScreen();
	//void save();
	void saveLevel(path dataFile);
	void loadObject(char* data);
	void render(SDL_Surface* surface);
	void saveObject(CORVID_SCREENOBJECT* object, std::ofstream* binOut); // Move this to the CORVID_SPRITE file or something
};
class CORVID_WORLD{
	int activeLevelData;
	void loadTextures();
public:
	const char* name;
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
	inline CORVID_R2* cameraLocation() { return activeLevel()->cameraLocation; };
	inline CORVID_SCREENOBJECT* activeCheckPoint() { return activeLevel()->activeCheckPoint; };
	inline std::vector<CORVID_SCREENOBJECT*>* staticList() { return activeLevel()->staticList; };
	inline std::vector<CORVID_SCREENOBJECT*>* dynamicList() { return activeLevel()->dynamicList; };
	inline std::vector<CORVID_SCREENOBJECT*>* backgroundList() { return activeLevel()->backgroundList; };
	inline std::vector<CORVID_SCREENOBJECT*>* checkPoints() { return activeLevel()->checkPoints; };
	inline CORVID_SCREENOBJECT* staticList(int index) { return activeLevel()->staticList->at(index); };
	inline CORVID_SCREENOBJECT* dynamicList(int index) { return activeLevel()->dynamicList->at(index); };
	inline CORVID_SCREENOBJECT* backgroundList(int index) { return activeLevel()->backgroundList->at(index); };
	inline CORVID_SCREENOBJECT* checkPoints(int index) { return activeLevel()->checkPoints->at(index); };
	inline int totalStaticObjects() { return (int)activeLevel()->staticList->size(); }
	inline int totalDynamicObjects() { return (int)activeLevel()->dynamicList->size(); }
	inline int totalBackgroundObjects() { return (int)activeLevel()->backgroundList->size(); }
	inline int totalCheckPoints() { return (int)activeLevel()->checkPoints->size(); }
	inline int totalCount() { return (int)activeLevel()->totalCount(); }
	CORVID_WORLD() : time(0), activeLevelData(0), lastCheckPointLevel(0), name("testo"), block_x(32), block_y(32){
		levels = new std::vector<CORVID_SCREEN*>();
		CORVID_SCREEN* level = new CORVID_SCREEN(levels);
		CORVID_SCREEN* level1 = new CORVID_SCREEN(levels, 1);
		textures = new std::vector<SDL_Surface*>();
	}
	CORVID_WORLD(path worldFile, path textureFile);
	void saveWorld();
	//void saveLevel();
	inline void render(SDL_Surface* surface) {
		activeLevel()->render(surface);
	}
};
inline CORVID_SCREENOBJECT** load(const char* fileName) {
	std::fstream fileStream;
	fileStream.open(fileName);
	return NULL;
}
#endif