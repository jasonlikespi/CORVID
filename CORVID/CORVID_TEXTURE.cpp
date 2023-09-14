#include "CORVID_TEXTURE.h"
CORVID_TEXTURE::CORVID_TEXTURE() {
	textureList = new std::vector<SDL_Surface*>();
	textureType = EMPTY;
};
CORVID_TEXTURE::CORVID_TEXTURE(SDL_Surface* texture) {
	textureList = new std::vector<SDL_Surface*>();
	textureType = PNG;
	textureList->push_back(texture);
};
CORVID_TEXTURE::CORVID_TEXTURE(SDL_Surface* unselected, SDL_Surface* selected) {
	textureList = new std::vector<SDL_Surface*>();
	textureType = BRICK;
	textureList->push_back(unselected);
	textureList->push_back(selected);
};
CORVID_TEXTURE::CORVID_TEXTURE(int textureNumber, std::vector<SDL_Surface*>* globalTextureData) {
	textureList = new std::vector<SDL_Surface*>();
	if (globalTextureData->size() <= textureNumber) {
		textureType = EMPTY;
		return;
	}
	textureType = PNG;
	textureList->push_back(globalTextureData->at(textureNumber));
}
CORVID_TEXTURE::CORVID_TEXTURE(std::vector<int>* objectData, std::vector<SDL_Surface*>* globalTextureData) {
	textureList = new std::vector<SDL_Surface*>();
	if (globalTextureData->size() < 4) { // This is error checking and should never run
		textureType = EMPTY;
		return;
	}
	switch (objectData->at(6)) {
	case 0:
		textureType = BRICK;
		textureList->push_back(globalTextureData->at(0));
		textureList->push_back(globalTextureData->at(3));
		break;
	case 1:
		textureType = PNG;
		textureList->push_back(globalTextureData->at(1));
		break;
	case 2:
		textureType = PNG;
		textureList->push_back(globalTextureData->at(2));
		break;
	default:
		textureType = EMPTY;
		break;
	}
}