#include "CORVID_WORLD.h"
#include <iomanip>
using namespace std::filesystem;

// Note to self: the Create Data Structures Methods has been folded into the constructors
// TODO fold the save method into the destructor method

// Don't Use this constructor ever
CORVID_CAMERA::CORVID_CAMERA() {
	this->frame = nullptr;
	this->player = nullptr;
	this->cameraLocation = nullptr;
};

CORVID_CAMERA::CORVID_CAMERA(CORVID_RECT* frame, CORVID_PLAYER* player) {
	this->frame = frame;
	this->player = player;
	// TODO Make better COORDS
	cameraLocation = new CORVID_R2(0, 0, ENGINE_GLOBAL);
};
// TODO what is this constructor?
CORVID_CAMERA::CORVID_CAMERA(path worldFile) : CORVID_OBJFILE(worldFile){
	cameraLocation = nullptr;
	frame = nullptr;
	player = nullptr;
};

CORVID_CAMERA::CORVID_CAMERA(std::vector<int>* input) {
	frame = new CORVID_RECT(input->at(1), input->at(2), input->at(3), input->at(5), ENGINE_GLOBAL);
	player = nullptr;
	cameraLocation = new CORVID_R2(0, 0, ENGINE_LOCAL);
};
// TODO Make the camera up and left be the right direction
void CORVID_CAMERA::updateCamera() {
	if (this->cameraLocation->x > 0) {
		this->cameraLocation->x = 0;
	}
	if (this->cameraLocation->x < WINDOW_WIDTH - SCREEN_WIDTH) {
		this->cameraLocation->x = WINDOW_WIDTH - SCREEN_WIDTH;
	}
};
// Moves the camera left or right depending on whether or not the player is on the outside quarter of the screen
// TODO I'm getting rid of camera speed
// TODO Write this Method
void CORVID_CAMERA::centerPlayer() {

};
//TODO All of It
void CORVID_CAMERA::render() {

};
//TODO All of It
void CORVID_CAMERA::save(std::filesystem::path folder) {

};
CORVID_R2* CORVID_CAMERA::getcameraLocation() {
	return cameraLocation;
};

CORVID_PHYSIC::CORVID_PHYSIC() {
	staticList = new std::vector<CORVID_SCREENOBJECT*>();
	dynamicList = new std::vector<CORVID_SCREENOBJECT*>();
};


int CORVID_PHYSIC::totalStaticObjects() {
	return (int)staticList->size();
};

int CORVID_PHYSIC::totalDynamicObjects() {
	return (int)dynamicList->size();
};
// TODO change the pointIsInside method
CORVID_SCREENOBJECT* CORVID_PHYSIC::findByPosition(CORVID_R2* position) {
	for (CORVID_SCREENOBJECT* i : *this->dynamicList) { if (i->pointIsInside(position)) { return i; } }
	for (CORVID_SCREENOBJECT* i : *this->staticList) { if (i->pointIsInside(position)) { return i; } }
	return nullptr;
};

int CORVID_PHYSIC::totalObjectCount() {
	return (int)(staticList->size() + dynamicList->size());
};
// There is no way to use for each methods for the iterators short of making my own data structure
// TODO With the CORVID_PHYSIC class, there is the potential to do something like that
// TODO Might need to add precision to checking if it is the player
// TODO Can currently delete player fix this bug quickly
// And create a filter to avoid removing backgrounds
// Current time O(n)
void CORVID_PHYSIC::removeObject(CORVID_SCREENOBJECT* object) {
	if (object == nullptr) { return; }
	for (int i = 0; i < staticList->size(); i++) { if (staticList->at(i) == object) { staticList->erase(staticList->begin() + i); } }
	for (int i = 0; i < dynamicList->size(); i++) { if (dynamicList->at(i) == object) { dynamicList->erase(dynamicList->begin() + i); } }
};
// Should not use this- use the frame version instead
void CORVID_PHYSIC::addObject(CORVID_SCREENOBJECT* object) {
	if (object->isDynamic()) {
		this->dynamicList->push_back(object);
	}
	else {
		this->staticList->push_back(object);
	}
};

void CORVID_PHYSIC::updateStatics() {
	for (CORVID_SCREENOBJECT* i : *staticList) {
		i->updateFrame();
	}
};

void CORVID_PHYSIC::updateDynamics() {
	for (CORVID_SCREENOBJECT* i : *dynamicList) {
		i->updateFrame();
	}
};
// Handles all collision detection: At the moment it just calls staticPlayerObjectCollision
// but the method will be made more complicated when dynamic objects are added 
void CORVID_PHYSIC::collisionDetect() {
	// staticPlayerObjectCollision();
};

void CORVID_PHYSIC::playerMoveLeft() {
	// player->moveLeft();
};

void CORVID_PHYSIC::playerMoveRight() {
	// player->moveRight();
};

void CORVID_PHYSIC::playerJump() {
	// player->jump();
};

void CORVID_PHYSIC::stopJump() {
	// player->jumpFrame = -1;
};
// TODO Write part of method that effects leftAdjacent and rightAdjacent
void CORVID_PHYSIC::updatePlayer() {
	// player->updateFrame();
};
// TODO check if CORVID_PHYSIC should just be made virtual
void CORVID_PHYSIC::staticPlayerObjectCollision() {

};
// TODO Also figure out what the deal is with virtual methods because I feel like
// they have purpose beyond just indicating it is a method that can be overridden


// Should never run and only exists as default constructor
CORVID_FRAME::CORVID_FRAME() : CORVID_PHYSIC(){
	contig = nullptr;
	frameAbove = nullptr;
	frameBelow = nullptr;
	frameLeft = nullptr;
	frameRight = nullptr;
	background = nullptr;
	contigNum = -1;
	frameNum = -1;
};
// TODO Add advanced naming system, possibly different constructor, more likely
// Initializing method
CORVID_FRAME::CORVID_FRAME(CORVID_CONTIG* contig) {
	this->contig = contig;
	frameAbove = nullptr;
	frameBelow = nullptr;
	frameLeft = nullptr;
	frameRight = nullptr;
	background = nullptr;
	frameNum = contig->totalFrames() + 1;
	contig->add(this);
	contigNum = -1;
};
// TODO Instantiate frameAbove, frameBelow, frameLeft, frameRight
CORVID_FRAME::CORVID_FRAME(CORVID_LEVEL* level, std::vector<int>* input) : CORVID_PHYSIC(), CORVID_CAMERA(input){	
	background = new CORVID_BACKGROUND(input);
	contigNum = input->at(0);
	frameNum = input->at(5);
	contig = nullptr; 
	frameAbove = nullptr;
	frameBelow = nullptr;
	frameLeft = nullptr;
	frameRight = nullptr;
};
// TODO All of it
int* CORVID_FRAME::dataDump() {
	return nullptr;
};
// TODO I don't remember what this is supposed to do
void CORVID_FRAME::loadScreen() {

};
// TODO This one doesn't need to be overloaded
int CORVID_FRAME::totalStaticObjects() {
	return (int)this->staticList->size();
};
// TODO This one doesn't need to be overloaded
int CORVID_FRAME::totalDynamicObjects() {
	return (int)this->dynamicList->size();
};
// TODO
CORVID_SCREENOBJECT* CORVID_FRAME::findByPosition(CORVID_R2* position) {
	return nullptr;
};
// TODO This one doesn't need to be overloaded
int CORVID_FRAME::totalObjectCount() {
	return (int)(this->staticList->size() + this->dynamicList->size());
};
// TODO may be overload
void CORVID_FRAME::removeObject(CORVID_SCREENOBJECT* object) {
	if (object == nullptr || object == player) { return; }
	for (int i = 0; i < staticList->size(); i++) { if (staticList->at(i) == object) { staticList->erase(staticList->begin() + i); } }
	for (int i = 0; i < dynamicList->size(); i++) { if (dynamicList->at(i) == object) { dynamicList->erase(dynamicList->begin() + i); } }
};

void CORVID_FRAME::addObject(CORVID_SCREENOBJECT* object) {
	if (object->isDynamic()) {
		this->dynamicList->push_back(object);
	}
	else {
		this->staticList->push_back(object);
	}
	object->frame = this;
};

void CORVID_FRAME::updateStatics() {
	for (CORVID_SCREENOBJECT* i : *staticList) {
		i->updateFrame();
	}
};

void CORVID_FRAME::updateDynamics() {
	for (CORVID_SCREENOBJECT* i : *dynamicList) {
		i->updateFrame();
	}
};
// Handles all collision detection: At the moment it just calls staticPlayerObjectCollision
// but the method will be made more complicated when dynamic objects are added 
void CORVID_FRAME::collisionDetect() {
	staticPlayerObjectCollision();
};

void CORVID_FRAME::playerMoveLeft() {
	player->moveLeft();
};

void CORVID_FRAME::playerMoveRight() {
	player->moveRight();
};

void CORVID_FRAME::playerJump() {
	player->jump();
};

void CORVID_FRAME::stopJump() {
	player->jumpFrame = -1;
};

void CORVID_FRAME::updatePlayer() {
	player->updateFrame();
};

void CORVID_FRAME::staticPlayerObjectCollision() {
	for (CORVID_SCREENOBJECT* i : *staticList) {
		if (i->relativePosition(player) == DIRECTION::INSIDE) {
			if (i->shoveDirection(player)->y < 0) { player->jumpFrame = 0; player->velocity.y = 0; }
			player->location = player->location + *i->shoveDirection(player);
		}
	}
};

// TODO might not need to be overloaded
void CORVID_FRAME::save(std::filesystem::path folder) {

};

void CORVID_FRAME::render() {
	// for (CORVID_SCREENOBJECT* i : *this->backgrounds) { i->render(surface, this); }
	this->background->render(surface, this);
	for (CORVID_SCREENOBJECT* i : *this->staticList) { i->render(surface, this); }
	for (CORVID_SCREENOBJECT* i : *this->dynamicList) { i->render(surface, this); }
	if (player != nullptr) { player->render(surface, this); }
};

CORVID_R2* CORVID_FRAME::getcameraLocation() {
	return this->cameraLocation;
};

CORVID_CONTIG::CORVID_CONTIG() : CORVID_PHYSIC(), CORVID_CAMERA(){
	frames = new std::vector<CORVID_FRAME*>();
	activeFrame = nullptr;
	level = nullptr;
	contigNum = -1;
};

CORVID_CONTIG::CORVID_CONTIG(CORVID_LEVEL* level) : CORVID_PHYSIC(), CORVID_CAMERA(){
	frames = new std::vector<CORVID_FRAME*>();
	activeFrame = nullptr;
	this->level = level;
};

int CORVID_CONTIG::totalFrames() {
	return (int)this->frames->size();
};
// TODO All of it. Also I believe that this refers to which number CONTIG it is within
// the level, and thus should have a corresponding field
int CORVID_CONTIG::contigNumber() {
	return contigNum;
};
int CORVID_CONTIG::totalStaticObjects() {
	int total = 0;
	for (CORVID_FRAME* i : *frames) {
		total += i->totalStaticObjects();
	}
	return total;
};

int CORVID_CONTIG::totalDynamicObjects() {
	int total = 0;
	for (CORVID_FRAME* i : *frames) {
		total += i->totalDynamicObjects();
	}
	return total;
};
// TODO
CORVID_SCREENOBJECT* CORVID_CONTIG::findByPosition(CORVID_R2* position) {
	return nullptr;
};

int CORVID_CONTIG::totalObjectCount() {
	return totalStaticObjects() + totalDynamicObjects();
};
// TODO may be overload
void CORVID_CONTIG::removeObject(CORVID_SCREENOBJECT* object) {
	for (int i = 0; i < staticList->size(); i++) { if (staticList->at(i) == object) { staticList->erase(staticList->begin() + i); } }
	for (int i = 0; i < dynamicList->size(); i++) { if (dynamicList->at(i) == object) { dynamicList->erase(dynamicList->begin() + i); } }
};
// TODO
void CORVID_CONTIG::addObject(CORVID_SCREENOBJECT* object) {

};

void CORVID_CONTIG::updateStatics() {
	activeFrame->updateStatics();
};

void CORVID_CONTIG::updateDynamics() {
	activeFrame->updateDynamics();
};

void CORVID_CONTIG::collisionDetect() {
	activeFrame->collisionDetect();
};
// TODO This one doesn't need to be overloaded
void CORVID_CONTIG::playerMoveLeft() {
	player->moveLeft();
};
// TODO This one doesn't need to be overloaded
void CORVID_CONTIG::playerMoveRight() {
	player->moveRight();
};
// TODO This one doesn't need to be overloaded
void CORVID_CONTIG::playerJump() {
	player->jump();
};
// TODO This one doesn't need to be overloaded
void CORVID_CONTIG::stopJump() {
	player->jumpFrame = -1;
};
// TODO This one doesn't need to be overloaded
void CORVID_CONTIG::updatePlayer() {
	player->updateFrame();
};
// Not Urgent, but when Dynamic Objects are added, this method should be expanded to include that
void CORVID_CONTIG::staticPlayerObjectCollision() {
	activeFrame->staticPlayerObjectCollision();
};
// TODO All of it
void CORVID_CONTIG::save(std::filesystem::path folder) {

};

// TODO Allow simultaneous rendering of multiple frames in edge cases
// Not urgent but I want to do this eventually
void CORVID_CONTIG::render() {
	this->activeFrame->render();
};

void CORVID_CONTIG::add(CORVID_FRAME* frameToAdd) {
	frames->push_back(frameToAdd);
	frameToAdd->contig = this;
};

CORVID_R2* CORVID_CONTIG::getcameraLocation() {
	return activeFrame->getcameraLocation();
};
// TODO Have it so that if there is no file chosen, there is a default file chosen and have it link to this one
CORVID_LEVEL::CORVID_LEVEL() {
	contigs = new std::vector<CORVID_CONTIG*>();
	// frames = new std::vector<CORVID_FRAME*>();
	activeContig = nullptr;
	activeFrame = nullptr;
	selectedObject = nullptr;
	unselectedObject = nullptr;
};
// TODO Make it where a file needs to be selected to have this constructor run; otherwise use blank constructor
// TODO Movement behavior of -1 indicates that it is a FRAME, use this to remove buffer
// TODO I broke initializeTextures
CORVID_LEVEL::CORVID_LEVEL(path worldFile, path textureFile, SDL_Renderer* renderer) : CORVID_TEXTLIST(textureFile), CORVID_PHYSIC(), CORVID_CAMERA(worldFile){
	surface = renderer;
	// CORVID_TEXTURE::initializeTextures(this->imgfiles, renderer);
	contigs = new std::vector<CORVID_CONTIG*>();
	// frames = new std::vector<CORVID_FRAME*>();
	activeContig = nullptr;
	activeFrame = nullptr;
	selectedObject = nullptr;
	unselectedObject = nullptr;
	for (std::vector<int>* i : *this->CORVID_OBJFILE::objects) {
		add(i);
	}
	for (CORVID_CONTIG* i : *contigs) {
		if (i->frames->size() == 0) {
			throw;
		} else {
			i->activeFrame = i->frames->at(0);
		}
	}
	if (contigs->size() == 0) {
		throw;
	} else {
		activeContig = contigs->at(0);
	}
	activeFrame = activeContig->activeFrame;
};
// This is the method to select an object, and unselect any objects currently selected
void CORVID_LEVEL::selectObject(CORVID_SCREENOBJECT* objectToSelect) {
	if (this->selectedObject != nullptr) {
		this->selectedObject->selected = false;
	}
	objectToSelect->selected = true;
	this->selectedObject = objectToSelect;
};
// If there is a selected object, this unselects it
void CORVID_LEVEL::unselectObject() {
	if (this->selectedObject != nullptr) {
		this->selectedObject->selected = false;
	}
};
int CORVID_LEVEL::totalFrames() {
	int returnValue = 0;
	for (CORVID_CONTIG* i : *contigs) {
		returnValue += i->totalFrames();
	}
	return returnValue;
};
// Sets a new active frame
void CORVID_LEVEL::setFrame(CORVID_FRAME* newFrame) {
	this->activeContig = newFrame->contig;
	this->activeFrame = newFrame;
};
void CORVID_LEVEL::deleteObject(CORVID_SCREENOBJECT* object) {
	object->frame->removeObject(object);
	object->frame->contig->removeObject(object);
	removeObject(object);
	delete(object);
};
int CORVID_LEVEL::totalStaticObjects() {
	int total = 0;
	for (CORVID_CONTIG* i : *contigs) {
		total += i->totalStaticObjects();
	}
	return total;
};

int CORVID_LEVEL::totalDynamicObjects() {
	int total = 0;
	for (CORVID_CONTIG* i : *contigs) {
		total += i->totalDynamicObjects();
	}
	return total;
};
// TODO
CORVID_SCREENOBJECT* CORVID_LEVEL::findByPosition(CORVID_R2* position) {
	return nullptr;
};

int CORVID_LEVEL::totalObjectCount() {
	return this->totalStaticObjects() + this->totalDynamicObjects();
};
// TODO may be overload
void CORVID_LEVEL::removeObject(CORVID_SCREENOBJECT* object) {
	for (int i = 0; i < staticList->size(); i++) { if (staticList->at(i) == object) { staticList->erase(staticList->begin() + i); } }
	for (int i = 0; i < dynamicList->size(); i++) { if (dynamicList->at(i) == object) { dynamicList->erase(dynamicList->begin() + i); } }
};
// TODO this runs really inefficiently
// If there are multiple frames with the same id accidentally, the objects is added to both
// And chaos could potentially ensue
// Also I'm pretty sure that this needs to rely on its overridden methods to simplify the code
void CORVID_LEVEL::addObject(CORVID_SCREENOBJECT* object) {
	if (object->isDynamic()) {
		dynamicList->push_back(object);
	} else {
		staticList->push_back(object);
	}
	for (CORVID_CONTIG* i : *contigs) {
		for (CORVID_FRAME* j : *i->frames) {
			if (object->frameNum = j->frameNum) {
				if (object->isDynamic()) {
					j->dynamicList->push_back(object);
					j->contig->dynamicList->push_back(object);
				} else {
					j->staticList->push_back(object);
					j->contig->staticList->push_back(object);
				}
				object->frame = j;
			}
		}
	}
};
// TODO
void CORVID_LEVEL::updateStatics() {
	activeFrame->updateStatics();
};
// TODO
void CORVID_LEVEL::updateDynamics() {
	activeFrame->updateDynamics();
};
// TODO
void CORVID_LEVEL::collisionDetect() {};
// TODO This one doesn't need to be overloaded
void CORVID_LEVEL::playerMoveLeft() {
	player->moveLeft();
};
// TODO This one doesn't need to be overloaded
void CORVID_LEVEL::playerMoveRight() {
	player->moveRight();
};
// TODO This one doesn't need to be overloaded
void CORVID_LEVEL::playerJump() {
	player->jump();
};
// TODO This one doesn't need to be overloaded
void CORVID_LEVEL::stopJump() {
	player->jumpFrame = -1;
};
// TODO This one doesn't need to be overloaded
void CORVID_LEVEL::updatePlayer() {
	player->updateFrame();
};

void CORVID_LEVEL::staticPlayerObjectCollision() {
	activeFrame->staticPlayerObjectCollision();
};
// TODO
void CORVID_LEVEL::save(std::filesystem::path folder) {
	std::filesystem::path binFile = folder / objFile;
	for (CORVID_CONTIG* i : *contigs) {
		i->save(binFile);
	}
	for (CORVID_SCREENOBJECT* i : *staticList) {
		i->save(binFile);
	}
	for (CORVID_SCREENOBJECT* i : *dynamicList) {
		i->save(binFile);
	}
};

void CORVID_LEVEL::render() {
	this->activeContig->render();
	if (unselectedObject != nullptr) { unselectedObject->render(surface, this); }
};
void CORVID_LEVEL::add(std::vector<int>* input) {
	if (input->size() < 8) { return; }
	int dataType = input->at(0) & (0xFF000000);
	input->at(0) = input->at(0) & (0x00FFFFFF);
	CORVID_SCREENOBJECT* j;
	CORVID_FRAME* newFrame;
	switch (dataType) {
	case 0x01000000: // Object Type
		j = new CORVID_SCREENOBJECT(input);
		addObject(j);
		break;
	case 0x02000000: // Frame Type
		newFrame = new CORVID_FRAME(this, input);
		add(newFrame);
		break;
	default:
		throw;
	}
};
// TODO Write Method
void CORVID_LEVEL::add(CORVID_FRAME* frameToAdd) {
	for (CORVID_CONTIG* i : *contigs) {
		if (i->contigNum == frameToAdd->contigNum) {
			i->frames->push_back(frameToAdd);
			return;
		}
	}
	CORVID_CONTIG* newContig = new CORVID_CONTIG(this);
	contigs->push_back(newContig);
	newContig->contigNum = frameToAdd->contigNum;
	newContig->add(frameToAdd);
};
// TODO Have AutoSort
void CORVID_LEVEL::add(CORVID_CONTIG* contigToAdd) {
	contigs->push_back(contigToAdd);
};
// TODO Write Method
CORVID_FRAME* CORVID_LEVEL::getFrame(int frameNumber) {
	return nullptr;
};

CORVID_R2* CORVID_LEVEL::getcameraLocation() {
	return activeContig->getcameraLocation();
};
// TODO make the Object Type Value an Enum Value maybe
/*
void CORVID_FRAME::saveObject(CORVID_SCREENOBJECT* object, std::ofstream* binOut) {
	int* currentObject = object->dataDump();
	for (int i = 0; i < 8; i++) {
		binOut->write(reinterpret_cast<const char*>(&currentObject[i]), sizeof(currentObject[i]));
	}
};
*/
/*
void CORVID_FRAME::save(std::filesystem::path folder) {
	std::ofstream MyFile(dataFile, std::ios::binary);
	std::ofstream* binFile = &MyFile;
	std::cout << this->totalCount();
	for (CORVID_SCREENOBJECT* i : *staticList) {
		saveObject(i, binFile);
	}
	for (CORVID_SCREENOBJECT* i : *dynamicList) {
		saveObject(i, binFile);
	}
	MyFile.close();
};
*/

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