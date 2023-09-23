#include "CORVID_TEXTURE.h"
// Default Constructor; Should never run
CORVID_TEXTURE::CORVID_TEXTURE() : textureType(EMPTY), activePNG(0) {
	textureList = new std::vector<int>(); 
};
// All of the texture options are PNG's; this one is just a PNG and nothing else.
CORVID_TEXTURE::CORVID_TEXTURE(int texture) : textureType(PNG), activePNG(0) { 
	textureList = new std::vector<int>();
	textureList->push_back(texture);
};
// Constructor for objects that can be selected, with a different appearance to indicate that they are being selected
CORVID_TEXTURE::CORVID_TEXTURE(int unselected, int selected) : textureType(BRICK), activePNG(0) { 
	textureList = new std::vector<int>();
	textureList->push_back(unselected);
	textureList->push_back(selected);
};
void CORVID_TEXTURE::initializeTextures(std::vector<path>* imgfiles) {
	if (global_textureList != nullptr) { return; }
	// TODO this may lead to complicated problems down the line if there are multiple texture files
	// but if that's the case then I will need to rewrite this section anyways
	// Also, the first line of the method may be able to prevent memory leaks if there are multiple worlds
	global_textureList = new std::vector<SDL_Surface*>(); 
	for (path i : *imgfiles) { global_textureList->push_back(IMG_Load(i.string().c_str())); } 
	// For some reason, I need to convert it to a string, and then a C string
};
void CORVID_TEXTURE::rendertext(SDL_Surface* surface, SDL_Rect* offset) { 
	SDL_BlitSurface(global_textureList->at(textureList->at(0)), NULL, surface, offset);
}; // Will need to make more complicated as I create more complicated textures
// TODO: rename this method render