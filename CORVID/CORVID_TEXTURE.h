#pragma once
#ifndef CORVID_TEXTURE_H
#define CORVID_TEXTURE_H
// Needed for SDL_RenderCopy and most of the texture related methods
#include "SDL.h"
// Needed for IMG_Load method and I think specifically the png file format
// And I think that SDL.h only does bmp files
#include "SDL_Image.h"
// Needed for spriteList and probably others stuff
#include "CORVID_CONSTS.h"
// The vector used for global_textureList
// TODO see if it can be replaced with an array
#include <vector>
// Mostly for the initializeTextures method
// TODO see if it can be removed
#include <filesystem>
// Explained in the Class Itself
#include "CORVID_CLASS.h"
// Note since I reassigned the values, all current files are
// Junk Data
enum class CORVID_TEXTURETYPE {
	BLANK,
	TITLE_SCREEN,
	SKY,
	PLAYER,
	BRICK,
	BLOCK,
	UNSELECTED_BLOCK
};

// Class with an integer corresponding to its texture data
// Also has a static vector of SDL_Textures
// TODO See if I should have a static SDL_Renderer to replace that parameter being in every method
// And considering I already have SDL.h and SDL_Image.h it wouldn't require additional includes
class CORVID_TEXTURE{
public:
	// CORVID_TEXTURETYPE corresponding to the objects texture ID
	CORVID_TEXTURETYPE textureType;
	// The texture list instantiated with initializeTextures method
	// Making this static so everything just references it
	static std::vector<SDL_Texture*>* textureList;
	// Empty Constructor
	// @return CORVID_TEXTURE with ID 3 
	CORVID_TEXTURE();
	// First Complete Constructor
	// @return CORVID_TEXTURE with id texture
	CORVID_TEXTURE(int texture);
	// Static Method to initialize textures
	// @param imgfiles the vector of filepaths containing the image textures
	// @param renderer passed down reference to the single SDL_Renderer from main
	// @return void but more importantly global_textureList is initialized
	static void initializeTextures(std::vector<std::filesystem::path>* imgfiles, SDL_Renderer* renderer);
	// Renders the texture at the location given by offset
	// TODO make private
	// @param surface renderer passed down from the single SDL_Renderer from main
	// @param offset location and size of the place the texture is rendered to
	// @param objectState 0 when unselected, 1 when selected, may become a more complicated object
	// if I add more complicated objects
	// @return void
	void render(SDL_Renderer* surface, SDL_Rect* offset, int objectState);
	// Special Submethod of render for objects of custom size (of multiple of UNIT)
	// TODO make private
	// @param surface renderer passed down from the single SDL_Renderer from main
	// @param offset location and size of the place the texture is rendered to
	// @param objectState 0 when unselected, 1 when selected, may become a more complicated object
	// if I add more complicated objects
	// @return void
	void renderCustom(SDL_Renderer* surface, SDL_Rect* offset, int spriteSheet);
	// Special Submethod of renderCustom for objects one UNIT wide
	// TODO make private
	// @param surface renderer passed down from the single SDL_Renderer from main
	// @param offset location and size of the place the texture is rendered to
	// @param objectState 0 when unselected, 1 when selected, may become a more complicated object
	// if I add more complicated objects
	// @return void
	void renderCustomVert(SDL_Renderer* surface, SDL_Rect* offset, int spriteSheet);
	// Special Submethod of renderCustom for objects of one UNIT tall
	// TODO make private
	// @param surface renderer passed down from the single SDL_Renderer from main
	// @param offset location and size of the place the texture is rendered to
	// @param objectState 0 when unselected, 1 when selected, may become a more complicated object
	// if I add more complicated objects
	// @return void
	void renderCustomHorz(SDL_Renderer* surface, SDL_Rect* offset, int spriteSheet);
	// Special Submethod of renderCustom for objects 1x1 UNIT
	// @param surface renderer passed down from the single SDL_Renderer from main
	// @param offset location and size of the place the texture is rendered to
	// @param objectState 0 when unselected, 1 when selected, may become a more complicated object
	// if I add more complicated objects
	// @return void
	void renderCustomSingle(SDL_Renderer* surface, SDL_Rect* offset, int spriteSheet);
	// Special Submethod of renderCustom for objects of multiple UNITs wide and tall
	// TODO make private
	// @param surface renderer passed down from the single SDL_Renderer from main
	// @param offset location and size of the place the texture is rendered to
	// @param objectState 0 when unselected, 1 when selected, may become a more complicated object
	// if I add more complicated objects
	// @return void
	void renderCustomBlock(SDL_Renderer* surface, SDL_Rect* offset, int spriteSheet);
};
#endif
// TODO Remove all of the comments below this and put them in a better place

// As a default, if there are 2 textures in the texturelist, the first
// represents the unselected variant, and the second is the selected variant.
// 
// Every object shouldn't contain actual texture data, but integers referring
// to indexes. The static global_textureList contains all of the data
