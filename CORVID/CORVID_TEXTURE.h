#pragma once
#ifndef CORVID_TEXTURE_H
#define CORVID_TEXTURE_H
#include "SDL.h"
#include "SDL_Image.h"
#include <vector>
#include <filesystem>
// TODO Maybe make another consts file?
const SDL_Rect spriteList[16] = { 
	 {  0,  0,  32,  32 },
	 { 32,  0,  32,  32 },
	 { 64,  0,  32,  32 },
	 { 96,  0,  32,  32 },
	 {128,  0,  32,  32 },
	 {160,  0,  32,  32 },
	 {192,  0,  32,  32 },
	 {224,  0,  32,  32 },
	 {  0, 32,  32,  32 },
	 { 32, 32,  32,  32 },
	 { 64, 32,  32,  32 },
	 { 96, 32,  32,  32 },
	 {128, 32,  32,  32 },
	 {160, 32,  32,  32 },
	 {192, 32,  32,  32 },
	 {224, 32,  32,  32 }
};
using namespace std::filesystem;

class CORVID_TEXTURE{
public:
	int textureID;
	static std::vector<SDL_Surface*>* global_textureList;
	CORVID_TEXTURE();
	CORVID_TEXTURE(int texture);
	// CORVID_TEXTURE(int unselected, int selected);
	static void initializeTextures(std::vector<path>* imgfiles);
	// TODO make these private
	void render(SDL_Surface* surface, SDL_Rect* offset, int objectState);
	void renderCustom(SDL_Surface* surface, SDL_Rect* offset, int spriteSheet);
	void renderCustomVert(SDL_Surface* surface, SDL_Rect* offset, int spriteSheet);
	void renderCustomHorz(SDL_Surface* surface, SDL_Rect* offset, int spriteSheet);
	void renderCustomSingle(SDL_Surface* surface, SDL_Rect* offset, int spriteSheet);
	void renderCustomBlock(SDL_Surface* surface, SDL_Rect* offset, int spriteSheet);
};
#endif

// As a default, if there are 2 textures in the texturelist, the first
// represents the unselected variant, and the second is the selected variant.
// 
// Every object shouldn't contain actual texture data, but integers referring
// to indexes. The static global_textureList contains all of the data
// 
// 
// Notes on Structure of File
// Object Data File follows the format ( One int for each)
// 0- Header Int
// 1- Location X Value
// 2- Location Y Value
// 3- Size X Value
// 4- Size Y Value
// 5- Object Type Value (0 is static, 1 is dynamic, 2 is background,
//		 3 is checkpoint)
// 6- Texture Value
// 7- Movement Behavior Value

//Texture List
/*
 * 0 - Title Screen
 * 1 - Sky
 * 2 - Player
 * 3 - Brick- Selectable
 * 4 - Block- Selectable
 *
 *
 */

// Literally the PNG List
/*
 * 0  brick.png
 * 1  titleScreen.png
 * 2  sky.png
 * 3  brick-selected.png
 * 4  PlayerSprite.png
 * 5  SpriteSheetBlock.png
 * 6  SpriteSheetBlockSelected.png
 */