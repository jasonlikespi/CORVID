#include "CORVID_WORLD.h"
#include <iomanip>
using namespace std::filesystem;
void CORVID_SCREEN::saveObject(CORVID_SCREENOBJECT* object, std::ofstream* binOut) { // Move this to ScreenObject
	int* currentObject = object->dataDump();
	for (int i = 0; i < 8; i++) {
		binOut->write(reinterpret_cast<const char*>(&currentObject[i]), sizeof(currentObject[i]));
		//printf("%d\n", currentObject[i]);
	}
};
CORVID_WORLD::CORVID_WORLD(path worldFile, path textureFile) : activeLevelData(0), block_x(32), block_y(32), lastCheckPointLevel(0), name("testo"), time(0) {
	
	levels = new std::vector<CORVID_SCREEN*>();
	CORVID_SCREEN* level = new CORVID_SCREEN(levels);
	CORVID_SCREEN* level1 = new CORVID_SCREEN(worldFile, levels);

	// Add Reference to the File Class in Here
	// level1->loadScreen(worldFile);
};
void CORVID_SCREEN::loadScreen() {
	/*
	std::ifstream* fs = new std::ifstream(fileName, std::ios::binary);
	if (!fs->good()) {
		return false;
	}
	int index = 0;
	int buffer;
	std::vector<std::vector<int>*>* objects = new std::vector<std::vector<int>*>();
	while (!fs->eof()) {
		fs->read(reinterpret_cast<char*>(&buffer), sizeof(buffer));
		if (index % 8 == 0) {
				objects->push_back(new std::vector<int>());
				objects->back()->push_back(buffer);
		} else {
			objects->back()->push_back(buffer);
		}
		index++;
	}
	return true;
	*/
	for (int i = 0; i < this->objects->size(); i++) {
		if (this->objects->at(i)->size() < 8) { return; }
		CORVID_SCREENOBJECT* j = new CORVID_SCREENOBJECT(this->objects->at(i));
		switch (this->objects->at(i)->at(5)) {
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
	//binFile->write("\0", 1);
	std::ifstream in_file(this->name, std::ios::binary);
	in_file.seekg(0, std::ios::end);
	int file_size = (int)in_file.tellg();
	MyFile.close();
}
void CORVID_WORLD::loadTextures() {
	
};
