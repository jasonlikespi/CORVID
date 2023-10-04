#include "CORVID_WORLD.h"
#include <iomanip>
using namespace std::filesystem;
using namespace CORVID_FILE;
// This should never run and only exists as a default constructor
CORVID_SCREEN::CORVID_SCREEN() :
	activeCheckPoint(NULL), cameraLocation(new CORVID_R2(0, 0)), player(NULL), name("testo") {
	createDataStructures();
	CORVID_TEXTURE* backgroundTexture = new CORVID_TEXTURE(2);
	background = new CORVID_SCREENOBJECT(0.0, 0.0, backgroundTexture);
}
// This is the constructor used for the base class
CORVID_SCREEN::CORVID_SCREEN(const char* name) :
	activeCheckPoint(NULL), cameraLocation(new CORVID_R2(0, 0)), player(NULL), name("testo") {
	this->name = name;	
	createDataStructures();
};
// This is the constructor that I am actually using
CORVID_SCREEN::CORVID_SCREEN(path fileName, std::vector<CORVID_SCREEN*>* world) :
	activeCheckPoint(NULL), cameraLocation(new CORVID_R2(0, 0)), player(NULL), name("testo"), cameraSpeed(new CORVID_R2(0, 0)) {
	createDataStructures(fileName);
	this->loadScreen();
	world->push_back(this);
	if (this->background == nullptr) {
		background = new CORVID_SCREENOBJECT(0.0, 0.0, new CORVID_TEXTURE(1));
	}
	if (this->player == nullptr) {
		player = new CORVID_PLAYER(128.0, 128.0, new CORVID_TEXTURE(2));
	}
	// This is for the unselected block
	unselectedObject = new CORVID_SCREENOBJECT(0, 256, 256, 32, 32, 0, 5, 0);
}
// TODO find out what this constructor does and if it's redundant
CORVID_SCREEN::CORVID_SCREEN(std::vector<CORVID_SCREEN*>* world, int levelNum) : 
	activeCheckPoint(NULL), cameraLocation(new CORVID_R2(0, 0)), player(NULL), name("testo"), cameraSpeed(new CORVID_R2(0, 0)) {
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
CORVID_WORLD::CORVID_WORLD() : frame(0), activeLevelData(0), lastCheckPointLevel(0), block_x(32), block_y(32), selectedObject(NULL) { 
	levels = new std::vector<CORVID_SCREEN*>();
	textures = new std::vector<SDL_Surface*>();
}
// Move this to ScreenObject TODO try to remove fors that are not for eaches to reduce index errors
void CORVID_SCREEN::saveObject(CORVID_SCREENOBJECT* object, std::ofstream* binOut) { 
	int* currentObject = object->dataDump();
	for (int i = 0; i < 8; i++) {
		binOut->write(reinterpret_cast<const char*>(&currentObject[i]), sizeof(currentObject[i]));
	}
};
CORVID_WORLD::CORVID_WORLD(path worldFile, path textureFile) : CORVID_TEXTLIST(textureFile), activeLevelData(0), block_x(32), block_y(32), lastCheckPointLevel(0), frame(0) {
	CORVID_TEXTURE::initializeTextures(this->imgfiles);
	textures = new std::vector<SDL_Surface*>();
	levels = new std::vector<CORVID_SCREEN*>();
	loadTextures();
	CORVID_SCREEN* level = new CORVID_SCREEN(levels, 0);
	CORVID_SCREEN* level1 = new CORVID_SCREEN(worldFile, levels);
	this->unselectedObject = level1->unselectedObject;
	// Add Reference to the File Class in Here
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

CORVID_SCREENOBJECT* CORVID_SCREEN::findByPosition(int x, int y) {
	if (player != nullptr && player->pointIsInside(x, y)) { return player; }
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
	if (unselectedObject != nullptr) { unselectedObject->render(surface); }
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
	// std::ifstream in_file(this->name, std::ios::binary);
	// in_file.seekg(0, std::ios::end);
	// int file_size = (int)in_file.tellg();
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

// If there is a selected object, this unselects it
void CORVID_WORLD::unselectObject() {
	if (this->selectedObject != nullptr) {
		this->selectedObject->selected = false;
	}
};
// There is no way to use for each methods for the iterators short of making my own vector class
void CORVID_SCREEN::removeObject(CORVID_SCREENOBJECT* object) {
	for (int i = 0; i < checkPoints->size(); i++) { if (checkPoints->at(i) == object) { checkPoints->erase(checkPoints->begin() + i); } }
	for (int i = 0; i < staticList->size(); i++) { if (staticList->at(i) == object) { staticList->erase(staticList->begin() + i); } }
	for (int i = 0; i < dynamicList->size(); i++) { if (dynamicList->at(i) == object) { dynamicList->erase(dynamicList->begin() + i); } }
};


// TODO Will completely break if the selected object is not from the same level as the active level 
void CORVID_WORLD::deleteObject() {
	if (this->selectedObject != nullptr && this->selectedObject != this->getbackground() && this->selectedObject != this->player()) {
		this->activeLevel()->removeObject(this->selectedObject);
	}
};

void CORVID_WORLD::playerMoveLeft() {
	player()->moveLeft();
};

void CORVID_WORLD::playerMoveRight() {
	player()->moveRight();
};

void CORVID_WORLD::playerJump() {
	player()->jump();
};

void CORVID_WORLD::stopJump() {
	player()->jumpFrame = -1;
}

void CORVID_WORLD::updateStatics() {
	for (CORVID_SCREENOBJECT* i : *staticList()) {
		i->updateFrame();
	}
};

void CORVID_WORLD::updateDynamics() {
	for (CORVID_SCREENOBJECT* i : *dynamicList()) {
		i->updateFrame();
	}
};
// TODO Write part of method that effects leftAdjacent and rightAdjacent
void CORVID_WORLD::updatePlayer() {
	player()->updateFrame();
	centerPlayer();
};

void CORVID_WORLD::collisionDetect() {
	staticPlayerObjectCollision();
};

void CORVID_WORLD::updateCamera() {
	this->getcameraLocation()->x = this->getcameraLocation()->x + getcameraSpeed()->x;
	this->getcameraLocation()->y = this->getcameraLocation()->y + getcameraSpeed()->y;
};
void CORVID_WORLD::centerPlayer() {
	if (player()->location.x + getcameraLocation()->x > RIGHT_QUARTER_SCREEN) {
		getcameraSpeed()->x -= .5;
		return;
	}
	if (player()->location.x + getcameraLocation()->x < LEFT_QUARTER_SCREEN && getcameraLocation()->x < 0) {
		getcameraSpeed()->x += .5;
		return;
	}
	getcameraSpeed()->x = 0;
};

void CORVID_WORLD::staticPlayerObjectCollision() {
	for (CORVID_SCREENOBJECT* i : *staticList()) {
		if (i->relativePosition(player()) == DIRECTION::INSIDE) {
			if (i->shoveDirection(player())->y < 0) { player()->jumpFrame = 0; player()->velocity.y = 0; }
			player()->location = player()->location + *i->shoveDirection(player());

		}
	}
};

// So complicated I'm putting it off until later if at all
// Used to merge rectangles that are added
/*void CORVID_WORLD::assembleRectangles() {
	int current_x = 0;
	int current_y = 0;
	for (int i = 0; staticList()->at(i) != *staticList()->end(); i++) {
		current_x = i->location.x + 16;
		current_y = i->location.y + 16;
		if (findByPosition(current_x - 32, current_y) != getbackground()) { mergeRectangles(i, findByPosition(current_x - 32, current_y)); }
		if (findByPosition(current_x + 32, current_y) != getbackground()) { mergeRectangles(i, findByPosition(current_x + 32, current_y)); }
		if (findByPosition(current_x, current_y - 32) != getbackground()) { mergeRectangles(i, findByPosition(current_x, current_y - 32)); }
		if (findByPosition(current_x, current_y + 32) != getbackground()) { mergeRectangles(i, findByPosition(current_x, current_y + 32)); }
	}
};
void CORVID_WORLD::mergeRectangles(CORVID_SCREENOBJECT* obj1, CORVID_SCREENOBJECT* obj2) {

};
*/