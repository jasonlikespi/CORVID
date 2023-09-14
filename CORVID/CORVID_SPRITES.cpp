#include "CORVID_SPRITES.h"
using namespace std;
void CORVID_SPRITE::CORVID_SCREENOBJECT::render(SDL_Surface* surface) { // The outer ifelse section is only used for error checking

	switch (this->textureType) {
	case(PNG):
		if (this->textureList->size() > 0 && this->textureList->at(0) != NULL) {
			SDL_Rect offset = { (int)this->location.x, (int)this->location.y, 0, 0 };
			SDL_BlitSurface(this->textureList->at(0), NULL, surface, &offset);
		}
		else {
			printf("Error: could not find texture for object with following data:\n");
			dataDump();
		}
		break;
	case(BRICK):
		if (this->textureList->size() > 1 && this->textureList->at(0) != NULL && this->textureList->at(1) != NULL) {
			SDL_Rect offset = { (int)this->location.x, (int)this->location.y, 0, 0 };
			if (this->selected == true) {
				SDL_BlitSurface(this->textureList->at(1), NULL, surface, &offset);
			} else {
				SDL_BlitSurface(this->textureList->at(0), NULL, surface, &offset);
			}
		}
		else {
			printf("Error: could not find texture for object with following data:\n");
			dataDump();
		}
		break;
	case(EMPTY):
	default:
		printf("Error: object does not have texture:\n");
		dataDump();
		break;
	}
};
void CORVID_SPRITE::dataDump(CORVID_SCREENOBJECT* object) {
	//printf("Location (x, y) at (%f, %f)\n", object->location.x, object->location.y);
	//printf("Size (width, height) at (%f, %f)\n", object->size.x, object->size.y);
	//printf("Velocity (x, y) at (%f, %f)\n", object->velocity.x, object->velocity.y);
	//printf("Object id is %d\n", object->id.id);
};
int* CORVID_SPRITE::CORVID_SCREENOBJECT::dataDump() {
	int* dataDump = new int[8];
	dataDump[0] = 0;
	dataDump[1] = (int)this->location.x;
	dataDump[2] = (int)this->location.y;
	dataDump[3] = (int)this->size.x;
	dataDump[4] = (int)this->size.y;
	dataDump[5] = (int)this->id.id;
	dataDump[6] = 0;
	dataDump[7] = 0;
	return dataDump;
};
/*
void CORVID_SPRITE::CORVID_SCREENOBJECT::loadSpriteTexture() {
	switch (textureNumber) {
		case(0):
			path unselectedPath = textureSource->imgfiles->at(textureNumber);
			std::string unselectedString = unselectedPath.string();
			const char* unselectedCString = unselectedString.c_str();
			this->texture = IMG_Load(textureCString);
	}
	path texturePath = textureSource->imgfiles->at(textureNumber);
	std::string textureString = texturePath.string();
	const char* textureCString = textureString.c_str();
	this->texture = IMG_Load(textureCString);
};
*/