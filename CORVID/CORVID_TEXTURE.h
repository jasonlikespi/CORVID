#pragma once
#ifndef CORVID_TEXTURE_H
#define CORVID_TEXTURE_H
#include "SDL.h"
#include "SDL_Image.h"
#include <vector>

enum CORVID_TEXTURE_TYPE{EMPTY, PNG, BRICK};

class CORVID_TEXTURE {
public:
	CORVID_TEXTURE_TYPE textureType;
	// As a default, if there are 2 textures in the texturelist, the first represents the unselected variant, and the second is the selected variant

	std::vector<SDL_Surface*>* textureList;
	CORVID_TEXTURE() {
		textureList = new std::vector<SDL_Surface*>();
		textureType = EMPTY;
	};
	CORVID_TEXTURE(SDL_Surface* texture) {
		textureList = new std::vector<SDL_Surface*>();
		textureType = PNG;
		textureList->push_back(texture);
	};
	CORVID_TEXTURE(SDL_Surface* unselected, SDL_Surface* selected) {
		textureList = new std::vector<SDL_Surface*>();
		textureType = BRICK;
		textureList->push_back(unselected);
		textureList->push_back(selected);
	};
	CORVID_TEXTURE(int textureNumber, std::vector<SDL_Surface*>* globalTextureData) {
		textureList = new std::vector<SDL_Surface*>();
		if (globalTextureData->size() <= textureNumber) {
			textureType = EMPTY;
			return;
		}
		textureType = PNG;
		textureList->push_back(globalTextureData->at(textureNumber));
	}
	CORVID_TEXTURE(std::vector<int>* objectData, std::vector<SDL_Surface*>* globalTextureData) {
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
};
#endif

// Notes on Structure of File
// Object Data File follows the format ( One int for each)
// 0- Header Int
// 1- Location X Value
// 2- Location Y Value
// 3- Size X Value
// 4- Size Y Value
// 5- Object Type Value (0 is static, 1 is dynamic, 2 is background, 3 is checkpoint)
// 6- Texture Value
// 7- Movement Behavior Value

//Texture List
/*
 * 0 - brick.png
 * 1 - titleScreen.png
 * 2 - sky.png
 *
 *
 *
 *
 */

// Literally the PNG List
/*
 * brick.png
 * titleScreen.png
 * sky.png
 * brick-selected.png
 */