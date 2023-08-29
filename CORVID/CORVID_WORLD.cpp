#include "CORVID_WORLD.h"
#include <iomanip>
using namespace std::filesystem;
using namespace CORVID_FILE;

void CORVID_SCREEN::createDataStructures(path fileName) {
	staticList = new std::vector<CORVID_SCREENOBJECT*>();
	dynamicList = new std::vector<CORVID_SCREENOBJECT*>();
	backgroundList = new std::vector<CORVID_SCREENOBJECT*>();
	checkPoints = new std::vector<CORVID_SCREENOBJECT*>();
	dataFile = new CORVID_OBJFILE(fileName);
}
void CORVID_SCREEN::createDataStructures() {
	staticList = new std::vector<CORVID_SCREENOBJECT*>();
	dynamicList = new std::vector<CORVID_SCREENOBJECT*>();
	backgroundList = new std::vector<CORVID_SCREENOBJECT*>();
	checkPoints = new std::vector<CORVID_SCREENOBJECT*>();
}
CORVID_SCREEN::CORVID_SCREEN(path fileName, std::vector<CORVID_SCREEN*>* world){
	createDataStructures(fileName);
	this->loadScreen();
	world->push_back(this);
}
CORVID_SCREEN::CORVID_SCREEN(std::vector<CORVID_SCREEN*>* world) : activeCheckPoint(NULL), cameraLocation(NULL), player(NULL), name("testo") {
	createDataStructures();
	const std::string fileName = "titleScreen.png";
	CORVID_SCREENOBJECT* background = new CORVID_SCREENOBJECT();
	background->texture = IMG_Load(fileName.c_str());
	backgroundList->push_back(background);
	world->push_back(this);
}
CORVID_SCREEN::CORVID_SCREEN(std::vector<CORVID_SCREEN*>* world, int levelNum) : activeCheckPoint(NULL), cameraLocation(NULL), player(NULL), name("testo") {
	createDataStructures();
	const std::string fileName = "sky.png";
	switch (levelNum) {
	case 1:
		CORVID_SCREENOBJECT * background = new CORVID_SCREENOBJECT();
		background->texture = IMG_Load(fileName.c_str());
		backgroundList->push_back(background);
		world->push_back(this);
		break;
	}
}
CORVID_WORLD::CORVID_WORLD() : time(0), activeLevelData(0), lastCheckPointLevel(0), name("testo"), block_x(32), block_y(32) {
	levels = new std::vector<CORVID_SCREEN*>();
	CORVID_SCREEN* level = new CORVID_SCREEN(levels);
	CORVID_SCREEN* level1 = new CORVID_SCREEN(levels, 1);
	textures = new std::vector<SDL_Surface*>();
	textureData = new CORVID_FILE::CORVID_TEXTLIST(); // Does Nothing
}
void CORVID_SCREEN::saveObject(CORVID_SCREENOBJECT* object, std::ofstream* binOut) { // Move this to ScreenObject
	int* currentObject = object->dataDump();
	for (int i = 0; i < 8; i++) {
		binOut->write(reinterpret_cast<const char*>(&currentObject[i]), sizeof(currentObject[i]));
		//printf("%d\n", currentObject[i]);
	}
};
CORVID_WORLD::CORVID_WORLD(path worldFile, path textureFile) : activeLevelData(0), block_x(32), block_y(32), lastCheckPointLevel(0), name("testo"), time(0) {
	textureData = new CORVID_TEXTLIST(textureFile);
	textures = new std::vector<SDL_Surface*>();
	levels = new std::vector<CORVID_SCREEN*>();
	CORVID_SCREEN* level = new CORVID_SCREEN(levels);
	CORVID_SCREEN* level1 = new CORVID_SCREEN(worldFile, levels);

	// Add Reference to the File Class in Here
	// level1->loadScreen(worldFile);
};
void CORVID_SCREEN::loadScreen() {
	for (int i = 0; i < this->dataFile->objects->size(); i++) {
		if (this->dataFile->objects->at(i)->size() < 8) { return; }
		CORVID_SCREENOBJECT* j = new CORVID_SCREENOBJECT(this->dataFile->objects->at(i));
		switch (this->dataFile->objects->at(i)->at(5)) {
		case(0):
			this->staticList->push_back(j);
			break;
		case(1):
			this->dynamicList->push_back(j);
			break;
		case(2):
			this->backgroundList->push_back(j);
			break;
		case(3):
			this->checkPoints->push_back(j);
			break;
		default:
			this->backgroundList->push_back(j);
			break;
		}
	}
};
void CORVID_SCREEN::render(SDL_Surface* surface) {
	for (CORVID_SCREENOBJECT* i : *this->backgroundList) {	CORVID_SPRITE::render(i, surface);}
	for (CORVID_SCREENOBJECT* i : *this->checkPoints)    {	CORVID_SPRITE::render(i, surface);}
	for (CORVID_SCREENOBJECT* i : *this->staticList)     {  CORVID_SPRITE::render(i, surface);}
	for (CORVID_SCREENOBJECT* i : *this->dynamicList)    {  CORVID_SPRITE::render(i, surface);}
};
void CORVID_SCREEN::loadObject(char* data) {

}
void CORVID_WORLD::saveWorld() {
	path testo = current_path() / "testo";
	create_directory(testo);
	testo = testo / "testo.bin";
	levels->at(1)->saveLevel(testo);
};
void CORVID_SCREEN::saveLevel(path dataFile) {
	std::ofstream MyFile(dataFile, std::ios::binary);
	std::ofstream* binFile = &MyFile;
	std::cout << this->totalCount();
	for (CORVID_SCREENOBJECT* i : *staticList) {
		saveObject(i, binFile);
	}
	for (CORVID_SCREENOBJECT* i : *dynamicList) {
		saveObject(i, binFile);
	}
	for (CORVID_SCREENOBJECT* i : *backgroundList) {
		saveObject(i, binFile);
	}
	for (CORVID_SCREENOBJECT* i : *checkPoints) {
		saveObject(i,  binFile);
	}
	std::ifstream in_file(this->name, std::ios::binary);
	in_file.seekg(0, std::ios::end);
	int file_size = (int)in_file.tellg();
	MyFile.close();
}
void CORVID_WORLD::loadTextures() {
	
};
