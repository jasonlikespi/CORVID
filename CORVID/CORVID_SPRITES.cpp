#include "CORVID_SPRITES.h"
using namespace std;
bool CORVID_SPRITE::CORVID_SPRITEDATATYPE::isAffectedByGravity() {
	switch (id) {
	case(2):
		return true;
		break;
	default:
		return false;
		break;
	}
};
// TODO Write Method
bool CORVID_SPRITE::CORVID_SPRITEDATATYPE::hasFriction() {
	return true;
};
// TODO Write Method
bool CORVID_SPRITE::CORVID_SPRITEDATATYPE::canDamage() {
	return true;
};
// TODO Write Method
bool CORVID_SPRITE::CORVID_SPRITEDATATYPE::isCheckPoint() {
	return true;
};
// TODO Write Method
bool CORVID_SPRITE::CORVID_SPRITEDATATYPE::isLevelSwap() {
	return true;
};

// This is only remaining because a default constructor is required; it should not be used
CORVID_SPRITE::CORVID_SCREENOBJECT::CORVID_SCREENOBJECT() : 
	CORVID_BOUNDBOX(CORVID_BOUNDBOX()), CORVID_TEXTURE(), CORVID_SPRITEDATATYPE(), selected(false), freeFall(false) {

}; 

void CORVID_SPRITE::CORVID_SCREENOBJECT::render(SDL_Renderer* surface, CORVID_R2* cameraLocation) {
	SDL_Rect offset = { (int)((((this->location.x + cameraLocation->x)) * MINI_SCREEN_FACTOR) + MINI_SCREEN_CORNER_WIDTH), (int)((this->location.y * MINI_SCREEN_FACTOR) + MINI_SCREEN_CORNER_HEIGHT), (int)(this->size.x * MINI_SCREEN_FACTOR), (int)(this->size.y * MINI_SCREEN_FACTOR) };
	
	if (this->selected) {
		CORVID_TEXTURE::render(surface, &offset, 1);
	} else {
		CORVID_TEXTURE::render(surface, &offset, 0);
	}
};

int* CORVID_SPRITE::CORVID_SCREENOBJECT::dataDump() {
	int* dataDump = new int[8];
	dataDump[0] = 0;
	dataDump[1] = (int)this->location.x;
	dataDump[2] = (int)this->location.y;
	dataDump[3] = (int)this->size.x;
	dataDump[4] = (int)this->size.y;
	dataDump[5] = 0;
	dataDump[6] = (int)this->id;
	dataDump[7] = 0;
	return dataDump;
};

void CORVID_SPRITE::CORVID_SCREENOBJECT::updateFrame() {
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

void CORVID_SPRITE::CORVID_PLAYER::moveLeft() {
	if (velocity.x > -SPEED_CAP) {
		velocity.x -= ACCELERATION;
	}
};

void CORVID_SPRITE::CORVID_PLAYER::moveRight() {
	if (velocity.x < SPEED_CAP) {
		velocity.x += ACCELERATION;
	}
};

void CORVID_SPRITE::CORVID_PLAYER::jump() {
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