#include "CORVID_TEXTURE.h"
using namespace CORVID_CONSTS;
// Default Constructor; Should never run
CORVID_TEXTURE::CORVID_TEXTURE(){
	textureID = 3;
};

// Can't think of anything to include in the constructor
CORVID_TEXTURE::CORVID_TEXTURE(int texture) : textureID(texture){};

void CORVID_TEXTURE::initializeTextures(std::vector<path>* imgfiles) {
	if (global_textureList != nullptr) { return; }
	// TODO this may lead to complicated problems down the line if there are multiple texture files
	// but if that's the case then I will need to rewrite this section anyways
	// Also, the first line of the method may be able to prevent memory leaks if there are multiple worlds
	global_textureList = new std::vector<SDL_Surface*>(); 
	for (path i : *imgfiles) { global_textureList->push_back(IMG_Load(i.string().c_str())); } 
	// For some reason, I need to convert it to a string, and then a C string
};
// Will need to make more complicated as I create more complicated textures
// objectState is 0 when object is unselected, 1 when it is selected
void CORVID_TEXTURE::render(SDL_Surface* surface, SDL_Rect* offset, int objectState) { 
	switch (this->textureID) {
	case(0):
		SDL_BlitSurface(global_textureList->at(1), NULL, surface, offset);
		break;
	case(1):
		SDL_BlitSurface(global_textureList->at(2), NULL, surface, offset);
		break;
	case(2):
		SDL_BlitSurface(global_textureList->at(4), NULL, surface, offset);
		break;
	case(3):
		if (objectState == 1) { 
			SDL_BlitSurface(global_textureList->at(3), NULL, surface, offset); 
		} else{
			SDL_BlitSurface(global_textureList->at(0), NULL, surface, offset);
		}
		break;
	case(4):
		if (objectState == 1) {
			renderCustom(surface, offset, 6);
		}
		else {
			renderCustom(surface, offset, 5);
		}
		break;
	case(5):
		renderCustom(surface, offset, 7);
		break;
	default:
		break;
	}

};
// Warning, the methods below are really complicated and tedious
// And used to render custom sized rectangles
void CORVID_TEXTURE::renderCustom(SDL_Surface* surface, SDL_Rect* offset, int spriteSheet) {
	if (offset->w <= 32) {
		if (offset->h <= 32) {
			renderCustomSingle(surface, offset, spriteSheet);
		} else {
			renderCustomVert(surface, offset, spriteSheet);
		}
	} else {
		if (offset->h <= 32) {
			renderCustomHorz(surface, offset, spriteSheet);
		} else {
			renderCustomBlock(surface, offset, spriteSheet);
		}
	}
};

void CORVID_TEXTURE::renderCustomVert(SDL_Surface* surface, SDL_Rect* offset, int spriteSheet) {
	// TODO topEdge is functionally identical to offset, but for some inexplicable reason, it keeps deleting the memory
	SDL_Rect topEdge = { offset->x, offset->y, 0, 0 };
	SDL_Rect bottomEdge = { offset->x, offset->y + offset->h - 32, 0, 0 };
	SDL_BlitSurface(global_textureList->at(spriteSheet), &spriteList[14], surface, offset);
	SDL_BlitSurface(global_textureList->at(spriteSheet), &spriteList[12], surface, &bottomEdge);
	for (int i = topEdge.y + 32; i < bottomEdge.y; i+= 32) {
		SDL_Rect offset1 = { offset->x, i, 0, 0 };
		SDL_BlitSurface(global_textureList->at(spriteSheet), &spriteList[9], surface, &offset1);
	}
};

void CORVID_TEXTURE::renderCustomHorz(SDL_Surface* surface, SDL_Rect* offset, int spriteSheet) {
	// TODO leftEdge is functionally identical to offset, but for some inexplicable reason, it keeps deleting the memory
	SDL_Rect leftEdge = { offset->x, offset->y, 0, 0 };
	SDL_Rect rightEdge = { offset->x + offset->w - 32, offset->y, 0, 0 };
	SDL_BlitSurface(global_textureList->at(spriteSheet), &spriteList[15], surface, offset);
	SDL_BlitSurface(global_textureList->at(spriteSheet), &spriteList[13], surface, &rightEdge);
	for (int i = leftEdge.x + 32; i < rightEdge.x; i+= 32) {
		SDL_Rect offset1 = { i, offset->y, 0, 0 };
		SDL_BlitSurface(global_textureList->at(spriteSheet), &spriteList[8], surface, &offset1);
	}
};

void CORVID_TEXTURE::renderCustomSingle(SDL_Surface* surface, SDL_Rect* offset, int spriteSheet) {
	SDL_BlitSurface(global_textureList->at(spriteSheet), &spriteList[11], surface, offset);
};

void CORVID_TEXTURE::renderCustomBlock(SDL_Surface* surface, SDL_Rect* offset, int spriteSheet) {
	SDL_Rect topleftCorner = { offset->x, offset->y, 0, 0 };
	SDL_Rect toprightCorner = { offset->x + offset->w - 32, offset->y, 0, 0 };
	SDL_Rect bottomleftCorner = { offset->x, offset->y + offset->h - 32, 0, 0 };
	SDL_Rect bottomrightCorner = { offset->x + offset->w - 32, offset->y + offset->h - 32, 0, 0 };
	SDL_BlitSurface(global_textureList->at(spriteSheet), &spriteList[4], surface, &topleftCorner);
	SDL_BlitSurface(global_textureList->at(spriteSheet), &spriteList[7], surface, &toprightCorner);
	SDL_BlitSurface(global_textureList->at(spriteSheet), &spriteList[5], surface, &bottomleftCorner);
	SDL_BlitSurface(global_textureList->at(spriteSheet), &spriteList[6], surface, &bottomrightCorner);
	int blockheight = offset->h / 32;
	int blockwidth = offset->w / 32;
	for (int i = 1; i < blockwidth - 1; i++) {
		for (int j = 1; j < blockheight - 1; j++) {
			SDL_Rect offset0 = { offset->x + 32 * i, offset->y + 32 * j, 0, 0 };
			SDL_BlitSurface(global_textureList->at(spriteSheet), &spriteList[10], surface, &offset0);
		}
	}
	for (int i = 1; i < blockwidth - 1; i++) { //Top Side
		SDL_Rect offset1 = { offset->x + 32 * i, offset->y, 0, 0 };
		SDL_BlitSurface(global_textureList->at(spriteSheet), &spriteList[0], surface, &offset1);
	}
	for (int i = 1; i < blockwidth - 1; i++) { // Bottom Side
		SDL_Rect offset2 = { offset->x + (int)32 * i, offset->y + offset->h - 32, 0, 0 };
		SDL_BlitSurface(global_textureList->at(spriteSheet), &spriteList[2], surface, &offset2);
	}
	for (int i = 1; i < blockheight - 1; i++) { // Left Side
		SDL_Rect offset3 = { offset->x, offset->y + 32 * i, 0, 0 };
		SDL_BlitSurface(global_textureList->at(spriteSheet), &spriteList[1], surface, &offset3);
	}
	for (int i = 1; i < blockheight - 1; i++) { // Right Side
		SDL_Rect offset4 = { offset->x + offset->w - 32, offset->y + (int)32 * i, 0, 0 };
		SDL_BlitSurface(global_textureList->at(spriteSheet), &spriteList[3], surface, &offset4);
	}
};