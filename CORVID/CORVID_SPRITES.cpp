#include "CORVID_SPRITES.h"
using namespace std;
// This is only remaining because a default constructor is required; it should not be used
CORVID_SPRITE::CORVID_SCREENOBJECT::CORVID_SCREENOBJECT() : CORVID_BOUNDBOX(CORVID_BOUNDBOX()), CORVID_TEXTURE(), id(CORVID_SPRITEDATATYPE()), selected(false) {}; 
// The outer ifelse section is only used for error checking
// TODO Removed error checking for out of index because it incorrectly gave
// error on texture data 0 but too tedious to add back in
void CORVID_SPRITE::CORVID_SCREENOBJECT::render(SDL_Surface* surface) { 
	SDL_Rect offset;
	switch (this->textureType) { 
		case(PNG):
			offset = { (int)this->location.x, (int)this->location.y, 0, 0 };
			this->rendertext(surface, &offset);
		break;
	case(BRICK):
		offset = { (int)this->location.x, (int)this->location.y, 0, 0 };
		this->rendertext(surface, &offset); // TODO Make sure that the selected option is added to the rendertext method
			// TODO also rename rendertext method to like render or something, it's not supposed to have anything to do with text, the complier was just confusing it with another method
		break;
	case(EMPTY):
	default:
		printf("Error: Empty Object\n");
		break;
	}
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