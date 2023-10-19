#include "CORVID_TEXTURE.h"
using namespace CORVID_CONSTS;
// Default Constructor; Should never run
CORVID_TEXTURE::CORVID_TEXTURE(){
	textureID = 3;
};

// Can't think of anything to include in the constructor
CORVID_TEXTURE::CORVID_TEXTURE(int texture) : textureID(texture){};

void CORVID_TEXTURE::initializeTextures(std::vector<path>* imgfiles, SDL_Renderer* renderer) {
	if (global_textureList != nullptr) { return; }
	// TODO this may lead to complicated problems down the line if there are multiple texture files
	// but if that's the case then I will need to rewrite this section anyways
	// Also, the first line of the method may be able to prevent memory leaks if there are multiple worlds
	global_textureList = new std::vector<SDL_Texture*>(); 
	for (path i : *imgfiles) { 
		SDL_Surface* loader = IMG_Load(i.string().c_str());
		global_textureList->push_back(SDL_CreateTextureFromSurface(renderer, loader));
		// For some reason, I need to convert loader to a string, and then a C string
		SDL_FreeSurface(loader);
	} 

};
// Will need to make more complicated as I create more complicated textures
// objectState is 0 when object is unselected, 1 when it is selected
void CORVID_TEXTURE::render(SDL_Renderer* surface, SDL_Rect* offset, int objectState) {
	switch (this->textureID) {
	case(0):
		SDL_RenderCopy(surface, global_textureList->at(1), &spriteSizes[1], offset);
		break;
	case(1):
		SDL_RenderCopy(surface, global_textureList->at(2), &spriteSizes[2], offset);
		break;
	case(2):
		SDL_RenderCopy(surface, global_textureList->at(4), &spriteSizes[4], offset);
		break;
	case(3):
		if (objectState == 1) { 
			SDL_RenderCopy(surface, global_textureList->at(3), &spriteSizes[3], offset);
		} else{
			SDL_RenderCopy(surface, global_textureList->at(0), &spriteSizes[0], offset);
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
void CORVID_TEXTURE::renderCustom(SDL_Renderer* surface, SDL_Rect* offset, int spriteSheet) {
	if (offset->w <= KUNIT) {
		if (offset->h <= KUNIT) {
			renderCustomSingle(surface, offset, spriteSheet);
		} else {
			renderCustomVert(surface, offset, spriteSheet);
		}
	} else {
		if (offset->h <= KUNIT) {
			renderCustomHorz(surface, offset, spriteSheet);
		} else {
			renderCustomBlock(surface, offset, spriteSheet);
		}
	}
};

void CORVID_TEXTURE::renderCustomVert(SDL_Renderer* surface, SDL_Rect* offset, int spriteSheet) {
	// TODO topEdge is functionally identical to offset, but for some inexplicable reason, it keeps deleting the memory
	SDL_Rect topEdge = { offset->x, offset->y, KUNIT, KUNIT };
	SDL_Rect bottomEdge = { offset->x, offset->y + offset->h - KUNIT, KUNIT, KUNIT };
	SDL_RenderCopy(surface, global_textureList->at(spriteSheet), &spriteList[14], offset);
	SDL_RenderCopy(surface, global_textureList->at(spriteSheet), &spriteList[12], &bottomEdge);
	for (int i = topEdge.y + KUNIT; i < bottomEdge.y; i+= KUNIT) {
		SDL_Rect offset1 = { offset->x, i, KUNIT, KUNIT };
		SDL_RenderCopy(surface, global_textureList->at(spriteSheet), &spriteList[9], &offset1);
	}
};

void CORVID_TEXTURE::renderCustomHorz(SDL_Renderer* surface, SDL_Rect* offset, int spriteSheet) {
	// TODO leftEdge is functionally identical to offset, but for some inexplicable reason, it keeps deleting the memory
	SDL_Rect leftEdge = { offset->x, offset->y, KUNIT, KUNIT };
	SDL_Rect rightEdge = { offset->x + offset->w - KUNIT, offset->y, KUNIT, KUNIT };
	SDL_RenderCopy(surface, global_textureList->at(spriteSheet), &spriteList[15], offset);
	SDL_RenderCopy(surface, global_textureList->at(spriteSheet), &spriteList[13], &rightEdge);
	for (int i = leftEdge.x + KUNIT; i < rightEdge.x; i+= KUNIT) {
		SDL_Rect offset1 = { i, offset->y, KUNIT, KUNIT };
		SDL_RenderCopy(surface, global_textureList->at(spriteSheet), &spriteList[8], &offset1);
	}
};

void CORVID_TEXTURE::renderCustomSingle(SDL_Renderer* surface, SDL_Rect* offset, int spriteSheet) {
	SDL_RenderCopy(surface, global_textureList->at(spriteSheet), &spriteList[11], offset);
};

void CORVID_TEXTURE::renderCustomBlock(SDL_Renderer* surface, SDL_Rect* offset, int spriteSheet) {
	SDL_Rect topleftCorner = { offset->x, offset->y, KUNIT, KUNIT };
	SDL_Rect toprightCorner = { offset->x + offset->w - KUNIT, offset->y, KUNIT, KUNIT };
	SDL_Rect bottomleftCorner = { offset->x, offset->y + offset->h - KUNIT, KUNIT, KUNIT };
	SDL_Rect bottomrightCorner = { offset->x + offset->w - KUNIT, offset->y + offset->h - KUNIT, KUNIT, KUNIT };
	SDL_RenderCopy(surface, global_textureList->at(spriteSheet), &spriteList[4], &topleftCorner);
	SDL_RenderCopy(surface, global_textureList->at(spriteSheet), &spriteList[7], &toprightCorner);
	SDL_RenderCopy(surface, global_textureList->at(spriteSheet), &spriteList[5], &bottomleftCorner);
	SDL_RenderCopy(surface, global_textureList->at(spriteSheet), &spriteList[6], &bottomrightCorner);
	int blockheight = offset->h / KUNIT;
	int blockwidth = offset->w / KUNIT;
	for (int i = 1; i < blockwidth - 1; i++) {
		for (int j = 1; j < blockheight - 1; j++) {
			SDL_Rect offset0 = { offset->x + KUNIT * i, offset->y + KUNIT * j, KUNIT, KUNIT };
			SDL_RenderCopy(surface, global_textureList->at(spriteSheet), &spriteList[10], &offset0);
		}
	}
	for (int i = 1; i < blockwidth - 1; i++) { //Top Side
		SDL_Rect offset1 = { offset->x + KUNIT * i, offset->y, KUNIT, KUNIT };
		SDL_RenderCopy(surface, global_textureList->at(spriteSheet), &spriteList[0], &offset1);
	}
	for (int i = 1; i < blockwidth - 1; i++) { // Bottom Side
		SDL_Rect offset2 = { offset->x + (int)KUNIT * i, offset->y + offset->h - KUNIT, KUNIT, KUNIT };
		SDL_RenderCopy(surface, global_textureList->at(spriteSheet), &spriteList[2], &offset2);
	}
	for (int i = 1; i < blockheight - 1; i++) { // Left Side
		SDL_Rect offset3 = { offset->x, offset->y + KUNIT * i, KUNIT, KUNIT };
		SDL_RenderCopy(surface, global_textureList->at(spriteSheet), &spriteList[1], &offset3);
	}
	for (int i = 1; i < blockheight - 1; i++) { // Right Side
		SDL_Rect offset4 = { offset->x + offset->w - KUNIT, offset->y + (int)KUNIT * i, KUNIT, KUNIT };
		SDL_RenderCopy(surface, global_textureList->at(spriteSheet), &spriteList[3], &offset4);
	}
};