#include "CORVID_WORLD.h"
#include <iomanip>
using namespace std::filesystem;
using namespace CORVID_FILE;
// This should never run and only exists as a default constructor
CORVID_SCREEN::CORVID_SCREEN() { 
	createDataStructures();
	CORVID_TEXTURE* backgroundTexture = new CORVID_TEXTURE(2);
	background = new CORVID_SCREENOBJECT(0.0, 0.0, backgroundTexture);
}
// This is the constructor used for the base class
CORVID_SCREEN::CORVID_SCREEN(const char* name) { 
	this->name = name;	
	createDataStructures();
};
// This is the constructor that I am actually using
CORVID_SCREEN::CORVID_SCREEN(path fileName, std::vector<CORVID_SCREEN*>* world){
	createDataStructures(fileName);
	this->loadScreen();
	world->push_back(this);
	if (this->background == nullptr) {
		background = new CORVID_SCREENOBJECT(0.0, 0.0, new CORVID_TEXTURE(1));
	}
	if (this->player == nullptr) {
		player = new CORVID_PLAYER(128.0, 128.0, new CORVID_TEXTURE(2));
	}
	// This is just for the example block
	std::vector<int>* blockData = new std::vector<int>(); 
	blockData->push_back(0);
	blockData->push_back(0);
	blockData->push_back(0);
	blockData->push_back(32);
	blockData->push_back(160);
	blockData->push_back(0);
	blockData->push_back(4);
	blockData->push_back(0);
	this->staticList->push_back(new CORVID_SCREENOBJECT(blockData));
}
// TODO find out what this constructor does and if it's redundant
CORVID_SCREEN::CORVID_SCREEN(std::vector<CORVID_SCREEN*>* world, int levelNum) : 
	activeCheckPoint(NULL), cameraLocation(NULL), player(NULL), name("testo") {
	createDataStructures();
	switch (levelNum) {
		case 0:
			background = new CORVID_SCREENOBJECT(0.0, 0.0, new CORVID_TEXTURE(0));
			break;
		case 1:
			background = new CORVID_SCREENOBJECT(0.0, 0.0, new CORVID_TEXTURE(2));
			player = new CORVID_PLAYER(128.0, 128.0, new CORVID_TEXTURE(4));
			break;
		default:
			break;
	}
	world->push_back(this);
}
CORVID_WORLD::CORVID_WORLD() : time(0), activeLevelData(0), lastCheckPointLevel(0), block_x(32), block_y(32), selectedObject(NULL) { 
	levels = new std::vector<CORVID_SCREEN*>();
	textures = new std::vector<SDL_Surface*>();
	CORVID_SCREEN* level = new CORVID_SCREEN(levels, 0);
	CORVID_SCREEN* level1 = new CORVID_SCREEN(levels, 1);
}
// Move this to ScreenObject TODO try to remove fors that are not for eaches to reduce index errors
void CORVID_SCREEN::saveObject(CORVID_SCREENOBJECT* object, std::ofstream* binOut) { 
	int* currentObject = object->dataDump();
	for (int i = 0; i < 8; i++) {
		binOut->write(reinterpret_cast<const char*>(&currentObject[i]), sizeof(currentObject[i]));
	}
};
CORVID_WORLD::CORVID_WORLD(path worldFile, path textureFile) : CORVID_TEXTLIST(textureFile), activeLevelData(0), block_x(32), block_y(32), lastCheckPointLevel(0), time(0) {
	CORVID_TEXTURE::initializeTextures(this->imgfiles);
	textures = new std::vector<SDL_Surface*>();
	levels = new std::vector<CORVID_SCREEN*>();
	loadTextures();
	CORVID_SCREEN* level = new CORVID_SCREEN(levels, 0);
	CORVID_SCREEN* level1 = new CORVID_SCREEN(worldFile, levels);
	// Add Reference to the File Class in Here
	// level1->loadScreen(worldFile);
};
void CORVID_SCREEN::createDataStructures() {
	staticList = new std::vector<CORVID_SCREENOBJECT*>();
	dynamicList = new std::vector<CORVID_SCREENOBJECT*>();
	checkPoints = new std::vector<CORVID_SCREENOBJECT*>();
}
void CORVID_SCREEN::createDataStructures(path fileName) {
	this->createDataStructures();
	dataFile = new CORVID_OBJFILE(fileName);
}
//  TODO I also need to do this for the select function
CORVID_SCREENOBJECT* CORVID_SCREEN::findByPosition(int x, int y) { 
	for (CORVID_SCREENOBJECT* i : *this->dynamicList) { if (i->pointIsInside(x, y)) { return i; } }
	for (CORVID_SCREENOBJECT* i : *this->staticList) { if (i->pointIsInside(x, y)) { return i; } }
	for (CORVID_SCREENOBJECT* i : *this->checkPoints) { if (i->pointIsInside(x, y)) { return i; } }
	return background;
};
void CORVID_SCREEN::loadScreen() {
	for ( std::vector<int>* i : *this->dataFile->objects){
		if (i->size() < 8) { return; }
		CORVID_SCREENOBJECT* j = new CORVID_SCREENOBJECT(i);
		switch (i->at(5)) {
		case(0):
			this->staticList->push_back(j);
			break;
		case(1):
			this->dynamicList->push_back(j);
			break;
		case(2):
			this->background = j;
			break;
		case(3):
			this->checkPoints->push_back(j);
			break;
		default:
			this->staticList->push_back(j);
			break;
		}
	}
};
void CORVID_SCREEN::render(SDL_Surface* surface) {
	background->render(surface);
	for (CORVID_SCREENOBJECT* i : *this->checkPoints)    { i->render(surface); }
	for (CORVID_SCREENOBJECT* i : *this->staticList)     { i->render(surface); }
	for (CORVID_SCREENOBJECT* i : *this->dynamicList)    { i->render(surface); }
	if (player != nullptr) { player->render(surface); }
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
	for (CORVID_SCREENOBJECT* i : *checkPoints) {
		saveObject(i,  binFile);
	}
	std::ifstream in_file(this->name, std::ios::binary);
	in_file.seekg(0, std::ios::end);
	int file_size = (int)in_file.tellg();
	MyFile.close();
}
// TODO I think I can delete this
void CORVID_WORLD::loadTextures() {
	for (path i : *this->imgfiles) {
		std::string pathstring = i.string();
		const char* pathchar = pathstring.c_str();
		this->textures->push_back(IMG_Load(pathchar));
	}
};
// This is the method to select an object, and unselect any objects currently selected
void CORVID_WORLD::selectObject(CORVID_SCREENOBJECT* objectToSelect) {
	if (this->selectedObject != nullptr) {
		this->selectedObject->selected = false;
	}
	objectToSelect->selected = true;
	this->selectedObject = objectToSelect;
	this->activeLevel()->selectedObject = objectToSelect;
};