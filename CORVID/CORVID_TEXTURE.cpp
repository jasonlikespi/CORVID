#include "CORVID_TEXTURE.h"
// Default Constructor; Should never run
// TODO consider renaming fields in this class
CORVID_TEXTURE::CORVID_TEXTURE(){
	textureType = CORVID_TEXTURETYPE::BLANK;
};

CORVID_TEXTURE::CORVID_TEXTURE(int texture){
	switch (texture) {
	case(0):
		textureType = CORVID_TEXTURETYPE::BLANK;
		break;
	case(1):
		textureType = CORVID_TEXTURETYPE::TITLE_SCREEN;
		break;
	case(2):
		textureType = CORVID_TEXTURETYPE::SKY;
		break;
	case(3):
		textureType = CORVID_TEXTURETYPE::PLAYER;
		break;
	case(4):
		textureType = CORVID_TEXTURETYPE::BRICK;
		break;
	case(5):
		textureType = CORVID_TEXTURETYPE::BLOCK;
		break;
	case(6):
		textureType = CORVID_TEXTURETYPE::UNSELECTED_BLOCK;
		break;
	default:
		break;
	}
};

void CORVID_TEXTURE::initializeTextures(std::vector<std::filesystem::path>* imgfiles, SDL_Renderer* renderer) {
	if (textureList != nullptr) { return; }
	// TODO this may lead to complicated problems down the line if there are multiple texture files
	// but if that's the case then I will need to rewrite this section anyways
	// Also, the first line of the method may be able to prevent memory leaks if there are multiple worlds
	textureList = new std::vector<SDL_Texture*>(); 
	for (std::filesystem::path i : *imgfiles) { 
		SDL_Surface* loader = IMG_Load(i.string().c_str());
		textureList->push_back(SDL_CreateTextureFromSurface(renderer, loader));
		// For some reason, I need to convert loader to a string, and then a C string
		SDL_FreeSurface(loader);
	} 

};
// Will need to make more complicated as I create more complicated textures
// objectState is 0 when object is unselected, 1 when it is selected
// TODO Make this compliant with toRect method
void CORVID_TEXTURE::render(SDL_Renderer* surface, SDL_Rect* offset, int objectState) {
	switch (this->textureType) {
	case(CORVID_TEXTURETYPE::TITLE_SCREEN):
		SDL_RenderCopy(surface, textureList->at(1), &spriteSizes[1], offset);
		break;
	case(CORVID_TEXTURETYPE::SKY):
		SDL_RenderCopy(surface, textureList->at(2), &spriteSizes[2], offset);
		break;
	case(CORVID_TEXTURETYPE::PLAYER):
		SDL_RenderCopy(surface, textureList->at(4), &spriteSizes[4], offset);
		break;
	case(CORVID_TEXTURETYPE::BRICK):
		if (objectState == 1) { 
			SDL_RenderCopy(surface, textureList->at(3), &spriteSizes[3], offset);
		} else{
			SDL_RenderCopy(surface, textureList->at(0), &spriteSizes[0], offset);
		}
		break;
	case(CORVID_TEXTURETYPE::BLOCK):
		if (objectState == 1) {
			renderCustom(surface, offset, 6);
		}
		else {
			renderCustom(surface, offset, 5);
		}
		break;
	case(CORVID_TEXTURETYPE::UNSELECTED_BLOCK):
		renderCustom(surface, offset, 7);
		break;
	default:
		break;
	}

};
// Warning, the methods below are really complicated and tedious
// And used to render custom sized rectangles
// TODO There's gotta be a better way to solve all of the type conversions from int to double
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
	SDL_Rect topEdge = { (int)offset->x, (int)offset->y, (int)KUNIT, (int)KUNIT };
	SDL_Rect bottomEdge = { (int)offset->x, (int)(offset->y + offset->h - KUNIT), (int)KUNIT, (int)KUNIT };
	SDL_RenderCopy(surface, textureList->at(spriteSheet), &spriteList[14], offset);
	SDL_RenderCopy(surface, textureList->at(spriteSheet), &spriteList[12], &bottomEdge);
	for (int i = (int)(topEdge.y + KUNIT); i < bottomEdge.y; i+= KUNIT) {
		SDL_Rect offset1 = { offset->x, i, KUNIT, KUNIT };
		SDL_RenderCopy(surface, textureList->at(spriteSheet), &spriteList[9], &offset1);
	}
};

void CORVID_TEXTURE::renderCustomHorz(SDL_Renderer* surface, SDL_Rect* offset, int spriteSheet) {
	// TODO leftEdge is functionally identical to offset, but for some inexplicable reason, it keeps deleting the memory
	SDL_Rect leftEdge = { (int)offset->x, (int)offset->y, (int)KUNIT, (int)KUNIT };
	SDL_Rect rightEdge = { (int)offset->x + (int)(offset->w - KUNIT), (int)offset->y, (int)KUNIT, (int)KUNIT };
	SDL_RenderCopy(surface, textureList->at(spriteSheet), &spriteList[15], offset);
	SDL_RenderCopy(surface, textureList->at(spriteSheet), &spriteList[13], &rightEdge);
	for (int i = (int)(leftEdge.x + KUNIT); i < rightEdge.x; i+= KUNIT) {
		SDL_Rect offset1 = { i, (int)offset->y, (int)KUNIT, (int)KUNIT };
		SDL_RenderCopy(surface, textureList->at(spriteSheet), &spriteList[8], &offset1);
	}
};

void CORVID_TEXTURE::renderCustomSingle(SDL_Renderer* surface, SDL_Rect* offset, int spriteSheet) {
	SDL_RenderCopy(surface, textureList->at(spriteSheet), &spriteList[11], offset);
};

void CORVID_TEXTURE::renderCustomBlock(SDL_Renderer* surface, SDL_Rect* offset, int spriteSheet) {
	SDL_Rect topleftCorner = { (int)offset->x, (int)offset->y, (int)KUNIT, (int)KUNIT };
	SDL_Rect toprightCorner = { (int)offset->x + (int)(offset->w - KUNIT), (int)offset->y, (int)KUNIT, (int)KUNIT };
	SDL_Rect bottomleftCorner = { (int)offset->x, (int)(offset->y + offset->h - KUNIT), (int)KUNIT, (int)KUNIT };
	SDL_Rect bottomrightCorner = { (int)(offset->x + offset->w - KUNIT), (int)(offset->y + offset->h - KUNIT), (int)KUNIT, (int)KUNIT };
	SDL_RenderCopy(surface, textureList->at(spriteSheet), &spriteList[4], &topleftCorner);
	SDL_RenderCopy(surface, textureList->at(spriteSheet), &spriteList[7], &toprightCorner);
	SDL_RenderCopy(surface, textureList->at(spriteSheet), &spriteList[5], &bottomleftCorner);
	SDL_RenderCopy(surface, textureList->at(spriteSheet), &spriteList[6], &bottomrightCorner);
	int blockheight = (int)(offset->h / KUNIT);
	int blockwidth = (int)(offset->w / KUNIT);
	for (int i = 1; i < blockwidth - 1; i++) {
		for (int j = 1; j < blockheight - 1; j++) {
			SDL_Rect offset0 = { (int)(offset->x + KUNIT * i), (int)(offset->y + KUNIT * j), (int)KUNIT, (int)KUNIT };
			SDL_RenderCopy(surface, textureList->at(spriteSheet), &spriteList[10], &offset0);
		}
	}
	for (int i = 1; i < blockwidth - 1; i++) { //Top Side
		SDL_Rect offset1 = { (int)(offset->x + KUNIT * i), (int)offset->y, (int)KUNIT, (int)KUNIT };
		SDL_RenderCopy(surface, textureList->at(spriteSheet), &spriteList[0], &offset1);
	}
	for (int i = 1; i < blockwidth - 1; i++) { // Bottom Side
		SDL_Rect offset2 = { (int)(offset->x + KUNIT * i), (int)(offset->y + offset->h - KUNIT), (int)KUNIT, (int)KUNIT };
		SDL_RenderCopy(surface, textureList->at(spriteSheet), &spriteList[2], &offset2);
	}
	for (int i = 1; i < blockheight - 1; i++) { // Left Side
		SDL_Rect offset3 = { (int)(offset->x), (int)(offset->y + KUNIT * i), (int)KUNIT, (int)KUNIT };
		SDL_RenderCopy(surface, textureList->at(spriteSheet), &spriteList[1], &offset3);
	}
	for (int i = 1; i < blockheight - 1; i++) { // Right Side
		SDL_Rect offset4 = { (int)(offset->x + offset->w - KUNIT), (int)(offset->y + KUNIT * i), (int)KUNIT, (int)KUNIT };
		SDL_RenderCopy(surface, textureList->at(spriteSheet), &spriteList[3], &offset4);
	}
};