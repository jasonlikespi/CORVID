#pragma once
#ifndef CORVID_TEXTURE_MODE_H
#define CORVID_TEXTURE_MODE_H
#include "SDL.h"
#include "SDL_Image.h"
#include <vector>

enum CORVID_TEXTURE_TYPE{EMPTY, PNG, BRICK};

class CORVID_TEXTURE_MODE {
public:
	CORVID_TEXTURE_TYPE textureType;
	std::vector<SDL_Surface*>* textureList;
	CORVID_TEXTURE_MODE() {
		textureList = new std::vector<SDL_Surface*>();
		textureType = EMPTY;
	};
	CORVID_TEXTURE_MODE(SDL_Surface* texture) {
		textureList = new std::vector<SDL_Surface*>();
		textureType = PNG;
		textureList->push_back(texture);
	};
	CORVID_TEXTURE_MODE(SDL_Surface* unselected, SDL_Surface* selected) {
		textureList = new std::vector<SDL_Surface*>();
		textureType = BRICK;
		textureList->push_back(unselected);
		textureList->push_back(selected);
	};
};
#endif