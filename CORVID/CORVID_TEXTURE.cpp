#include "CORVID_TEXTURE.h"
CORVID_TEXTURE::CORVID_TEXTURE() {
	textureList = new std::vector<int>();
	textureType = EMPTY;
	activePNG = 0;
};
CORVID_TEXTURE::CORVID_TEXTURE(int texture) {
	textureList = new std::vector<int>();
	textureType = PNG;
	textureList->push_back(texture);
	activePNG = 0;
};
CORVID_TEXTURE::CORVID_TEXTURE(int unselected, int selected) {
	textureList = new std::vector<int>();
	textureType = BRICK;
	textureList->push_back(unselected);
	textureList->push_back(selected);
	activePNG = 0;
};
void CORVID_TEXTURE::initializeTextures(std::vector<path>* imgfiles) {
	if (global_textureList != nullptr) { return; } // TODO this may lead to complicated problems down the line if there are multiple texture files but if that's the case then I will need to rewrite this section anyways
	global_textureList = new std::vector<SDL_Surface*>();
	for (path i : *imgfiles) {
		std::string pathstring = i.string();
		const char* pathchar = pathstring.c_str();
		global_textureList->push_back(IMG_Load(pathchar));
	}

};
void CORVID_TEXTURE::rendertext(SDL_Surface* surface, SDL_Rect* offset) {
	
	SDL_BlitSurface(global_textureList->at(textureList->at(0)), NULL, surface, offset);
};