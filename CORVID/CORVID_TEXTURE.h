#pragma once
#ifndef CORVID_TEXTURE_H
#define CORVID_TEXTURE_H
#include "SDL.h"
#include "SDL_Image.h"
#include <vector>
#include <filesystem>
using namespace std::filesystem;
enum CORVID_TEXTURE_TYPE{EMPTY, PNG, BRICK};
class CORVID_TEXTURE {
public:
	CORVID_TEXTURE_TYPE textureType;
	static std::vector<SDL_Surface*>* global_textureList;
	std::vector<int>* textureList;
	int activePNG;
	CORVID_TEXTURE();
	CORVID_TEXTURE(int texture);
	CORVID_TEXTURE(int unselected, int selected);
	static void initializeTextures(std::vector<path>* imgfiles);
	void rendertext(SDL_Surface* surface, SDL_Rect* offset);
};
#endif
// As a default, if there are 2 textures in the texturelist, the first represents the unselected variant, and the second is the selected variant
// 
// 
// Every object shouldn't contain actual texture data, but integers referring to indexes. The static global_textureList contains all of the data
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
 * 3 - PlayerSprite.png
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
 * PlayerSprite.png
 */