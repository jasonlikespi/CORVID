#pragma once
#ifndef CORVID_SPRITES_H
#define CORVID_SPRITES_H
#include "CORVID_GEOM.h"
#include <SDL_Image.h>
#include <vector>
#include "CORVID_FILE.h"
#include "CORVID_TEXTURE_MODE.h"

using namespace std::filesystem;

namespace CORVID_SPRITE {
	static path defaultPath = (current_path() / "testo\\textures.txt.txt");
	class CORVID_SPRITEDATATYPE {
	public:
		int id;
		CORVID_SPRITEDATATYPE() : id(0) {};
		CORVID_SPRITEDATATYPE(int id) : id(id) {};
	};
	class CORVID_SCREENOBJECT : public CORVID_BOUNDBOX<int>{
	public:
		CORVID_SPRITEDATATYPE id;
		CORVID_FILE::CORVID_TEXTLIST* textureSource;
		int textureNumber;
		SDL_Surface* texture;
		bool selected;
		CORVID_SCREENOBJECT() : CORVID_BOUNDBOX(CORVID_BOUNDBOX()), id(CORVID_SPRITEDATATYPE()), texture(NULL), selected(false) {
			textureNumber = 0;
			textureSource = new CORVID_FILE::CORVID_TEXTLIST(defaultPath);
		};
		CORVID_SCREENOBJECT(int xval, int yval) : CORVID_BOUNDBOX(CORVID_BOUNDBOX(xval, yval)), selected(false) {
			texture = NULL;
			textureSource = new CORVID_FILE::CORVID_TEXTLIST(defaultPath);
			textureNumber = 0;
			loadSpriteTexture();
		};
		CORVID_SCREENOBJECT(std::vector<int>* data) : CORVID_BOUNDBOX(data->at(1), data->at(2), data->at(3), data->at(4), 0, 0), id(data->at(5)), selected(false) {
			texture = NULL;
			textureSource = new CORVID_FILE::CORVID_TEXTLIST(defaultPath);
			textureNumber = 0;
			loadSpriteTexture();
		};
		CORVID_SCREENOBJECT(std::vector<int>* data, CORVID_FILE::CORVID_TEXTLIST* textureData) : CORVID_BOUNDBOX(data->at(1), data->at(2), data->at(3), data->at(4), 0, 0), id(data->at(5)), textureNumber(data->at(6)), selected(false) {
			texture = NULL;
			textureSource = textureData;
			loadSpriteTexture();
		};
		int* dataDump(); // This is definitely a memory leak, but considering how broken everything is already, I will fix it later
		// Also it's not a super bad memory leak considering it only runs whenever the game saves
		void loadSpriteTexture();
	};
	class CORVID_PLAYER {
	public:
		CORVID_SCREENOBJECT playerData;
		CORVID_SCREENOBJECT* objectStandingOn;
		CORVID_SCREENOBJECT* leftObject;
		CORVID_SCREENOBJECT* rightObject;
		CORVID_PLAYER() : playerData(CORVID_SCREENOBJECT()), objectStandingOn(NULL), leftObject(NULL), rightObject(NULL) {};
	};
	class CORVID_BACKGROUND {
	public:
		CORVID_SCREENOBJECT imageData;
		int stationaryBackground;
		CORVID_BACKGROUND() : imageData(CORVID_SCREENOBJECT()), stationaryBackground(0) {};
	};
	void render(CORVID_SCREENOBJECT* object, SDL_Surface* surface);
	void dataDump(CORVID_SCREENOBJECT* object);
}

#endif