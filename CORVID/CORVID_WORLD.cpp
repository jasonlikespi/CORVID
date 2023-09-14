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
CORVID_SCREEN::CORVID_SCREEN() { // This should never run and only exists as a default constructor
	createDataStructures();
}
CORVID_SCREEN::CORVID_SCREEN(const char* name) {
	this->name = name;
};
CORVID_SCREEN::CORVID_SCREEN(path fileName, std::vector<CORVID_SCREEN*>* world){ // This is the constructor that I am actually using
	
	createDataStructures(fileName);
	this->loadScreen();
	world->push_back(this);
}
CORVID_SCREEN::CORVID_SCREEN(std::vector<CORVID_SCREEN*>* world) : activeCheckPoint(NULL), cameraLocation(NULL), player(NULL), name("testo") {
	
	createDataStructures();
	//const std::string fileName = "titleScreen.png";
	CORVID_TEXTURE* texture = new CORVID_TEXTURE(1, g_textures);
	CORVID_SCREENOBJECT* background = new CORVID_SCREENOBJECT(0, 0, texture);
	//background->texture = IMG_Load(fileName.c_str());
	backgroundList->push_back(background);
	world->push_back(this);
}
CORVID_SCREEN::CORVID_SCREEN(std::vector<CORVID_SCREEN*>* world, int levelNum) : activeCheckPoint(NULL), cameraLocation(NULL), player(NULL), name("testo") {
	
	createDataStructures();
	const std::string fileName = "sky.png";
	switch (levelNum) {
	case 1:
		CORVID_SCREENOBJECT * background = new CORVID_SCREENOBJECT();
		//background->texture = IMG_Load(fileName.c_str());
		backgroundList->push_back(background);
		world->push_back(this);
		break;
	}
}
CORVID_WORLD::CORVID_WORLD() : CORVID_SCREEN("testo"), time(0), activeLevelData(0), lastCheckPointLevel(0), block_x(32), block_y(32) { //'name("testo"),' was included in the list; might be necessary for file naming purposes
	// Levels should not be created before textures are initiated, will result in null textures
	// Not removing because this constructor should never run anyways
	levels = new std::vector<CORVID_SCREEN*>();
	CORVID_SCREEN* level = new CORVID_SCREEN(levels);
	CORVID_SCREEN* level1 = new CORVID_SCREEN(levels, 1);
	textures = new std::vector<SDL_Surface*>();
	g_textures = textures;
	// textureData = new CORVID_TEXTLIST(); // Does Nothing
}
void CORVID_SCREEN::saveObject(CORVID_SCREENOBJECT* object, std::ofstream* binOut) { // Move this to ScreenObject
	int* currentObject = object->dataDump();
	for (int i = 0; i < 8; i++) {
		binOut->write(reinterpret_cast<const char*>(&currentObject[i]), sizeof(currentObject[i]));
		//printf("%d\n", currentObject[i]);
	}
};
CORVID_WORLD::CORVID_WORLD(path worldFile, path textureFile) : CORVID_SCREEN("testo"), CORVID_TEXTLIST(textureFile), activeLevelData(0), block_x(32), block_y(32), lastCheckPointLevel(0), time(0) { //'name("testo"),' was included in the list; might be necessary for file naming purposes
	
	textures = new std::vector<SDL_Surface*>();
	levels = new std::vector<CORVID_SCREEN*>();
	g_textures = textures;
	loadTextures();
	CORVID_SCREEN* level = new CORVID_SCREEN(levels);
	CORVID_SCREEN* level1 = new CORVID_SCREEN(worldFile, levels);
	// Add Reference to the File Class in Here
	// level1->loadScreen(worldFile);
};
CORVID_SCREENOBJECT* CORVID_SCREEN::findByPosition(int x, int y) { //  TODO I also need to do this for the select function
	for (CORVID_SCREENOBJECT* i : *this->dynamicList) {}
	for (CORVID_SCREENOBJECT* i : *this->staticList) {}
	for (CORVID_SCREENOBJECT* i : *this->checkPoints) {}
	for (CORVID_SCREENOBJECT* i : *this->backgroundList) {} 
	return nullptr;
};
void CORVID_SCREEN::loadScreen() {
	
	for (int i = 0; i < this->dataFile->objects->size(); i++) {
		if (this->dataFile->objects->at(i)->size() < 8) { return; }
		//CORVID_TEXTURE* texture = new CORVID_TEXTURE(g_textures->at(this->dataFile->objects->at(i)->at(6)));
		CORVID_SCREENOBJECT* j = new CORVID_SCREENOBJECT(this->dataFile->objects->at(i), g_textures);
		
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
	for (CORVID_SCREENOBJECT* i : *this->backgroundList) { i->render(surface); } 
	for (CORVID_SCREENOBJECT* i : *this->checkPoints)    { i->render(surface); }
	for (CORVID_SCREENOBJECT* i : *this->staticList)     { i->render(surface); }
	for (CORVID_SCREENOBJECT* i : *this->dynamicList)    { i->render(surface); }
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
	for (path i : *this->imgfiles) {
		std::string pathstring = i.string();
		const char* pathchar = pathstring.c_str();
		this->textures->push_back(IMG_Load(pathchar));
	}
};
