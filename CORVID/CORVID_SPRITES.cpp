#include "CORVID_SPRITES.h"
using namespace std;

CORVID_SPRITEDATATYPE::CORVID_SPRITEDATATYPE(int physicType) {
	switch (physicType) {
		case 0:
			this->physicType = CORVID_PHYSICTYPE::ERROR;
			break;
		case 1:
			this->physicType = CORVID_PHYSICTYPE::BACKGROUND;
			break;
		case 2:
			this->physicType = CORVID_PHYSICTYPE::STATIC;
			break;
		case 3:
			this->physicType = CORVID_PHYSICTYPE::PLAYER;
			break;
		case 4:
			this->physicType = CORVID_PHYSICTYPE::DYNAMIC;
			break;
		default:
			this->physicType = CORVID_PHYSICTYPE::ERROR;
			break;
	}
};

bool CORVID_SPRITEDATATYPE::isAffectedByGravity() {
	switch (physicType) {
	case(CORVID_PHYSICTYPE::PLAYER):
		return true;
		break;
	default:
		return false;
		break;
	}
};
// TODO Write Method
bool CORVID_SPRITEDATATYPE::hasFriction() {
	return true;
};
// TODO Write Method
bool CORVID_SPRITEDATATYPE::canDamage() {
	return true;
};
// TODO Write Method
bool CORVID_SPRITEDATATYPE::isCheckPoint() {
	return true;
};
// TODO Write Method
bool CORVID_SPRITEDATATYPE::isLevelSwap() {
	return true;
};
bool CORVID_SPRITEDATATYPE::isDynamic() {
	return false;
}
// This is only remaining because a default constructor is required; it should not be used
CORVID_SCREENOBJECT::CORVID_SCREENOBJECT() : 
	CORVID_BOUNDBOX(CORVID_BOUNDBOX()), CORVID_TEXTURE(), CORVID_SPRITEDATATYPE(), selected(false), freeFall(false), frame(nullptr){

}; 
// TODO I haven't fixed this function from when I used a R2 for the camera
void CORVID_SCREENOBJECT::render(SDL_Renderer* surface, CORVID_CAMERA* cameraLocation) {
	// TODO Make not broke
	// SDL_Rect offset = { (int)((((this->location.x + cameraLocation->x)) * MINI_SCREEN_FACTOR) + MINI_SCREEN_CORNER_WIDTH), (int)((this->location.y * MINI_SCREEN_FACTOR) + MINI_SCREEN_CORNER_HEIGHT), (int)(this->size.x * MINI_SCREEN_FACTOR), (int)(this->size.y * MINI_SCREEN_FACTOR) };
	SDL_Rect offset = { (int)((((this->location.x)) * MINI_SCREEN_FACTOR) + MINI_SCREEN_CORNER_WIDTH), (int)((this->location.y * MINI_SCREEN_FACTOR) + MINI_SCREEN_CORNER_HEIGHT), (int)(this->size.x * MINI_SCREEN_FACTOR), (int)(this->size.y * MINI_SCREEN_FACTOR) };

	if (this->selected) {
		CORVID_TEXTURE::render(surface, &offset, 1);
	} else {
		CORVID_TEXTURE::render(surface, &offset, 0);
	}
};

int* CORVID_SCREENOBJECT::dataDump() {
	int* dataDump = new int[8];
	dataDump[0] = 0;
	dataDump[1] = (int)this->location.x;
	dataDump[2] = (int)this->location.y;
	dataDump[3] = (int)this->size.x;
	dataDump[4] = (int)this->size.y;
	dataDump[5] = 0;
	dataDump[6] = (int)(this->physicType);
	dataDump[7] = 0;
	return dataDump;
};

void CORVID_SCREENOBJECT::updateFrame() {
	if (isAffectedByGravity() && freeFall) {
		velocity.y += STRENGTH_OF_GRAVITY;
	}
	velocity.x *= FRICTION_CONSTANT_HORIZONTAL;
	velocity.y *= FRICTION_CONSTANT_VERTICAL;
	location = location + velocity;
	if (location.x < 0) {
		location.x = 0;
	}
	if (location.x > SCREEN_WIDTH - size.x) {
		location.x = SCREEN_WIDTH - size.x;
	}
};
void CORVID_SCREENOBJECT::save(std::filesystem::path binFile) {

};
void CORVID_PLAYER::moveLeft() {
	if (velocity.x > -SPEED_CAP) {
		velocity.x -= ACCELERATION;
	}
};

void CORVID_PLAYER::moveRight() {
	if (velocity.x < SPEED_CAP) {
		velocity.x += ACCELERATION;
	}
};

void CORVID_PLAYER::jump() {
	switch(jumpFrame){
		case(0):
			this->velocity.y -= PLAYER_JUMP_FORCE_1;
			break;
		case(1):
			this->velocity.y -= PLAYER_JUMP_FORCE_2;
			break;
		case(2):
			this->velocity.y -= PLAYER_JUMP_FORCE_3;
			break;
		case(3):
			this->velocity.y -= PLAYER_JUMP_FORCE_4;
			break;
		case(4):
			this->velocity.y -= PLAYER_JUMP_FORCE_5;
			break;
		case(5):
			jumpFrame = -1;
			return;
			break;
		case(-1):
			return;
			break;
		default:
			break;
	}
	jumpFrame++;
};