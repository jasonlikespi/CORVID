#ifndef CORVID_SPRITES_H
#define CORVID_SPRITES_H
#include "CORVID_GEOM.h"
#include <SDL_Image.h>
#include <vector>
namespace CORVID_SPRITE {
	class CORVID_SPRITEDATATYPE {
	public:
		int id;
		CORVID_SPRITEDATATYPE() : id(0) {};
		CORVID_SPRITEDATATYPE(int id) : id(id) {};
	};
	class CORVID_SCREENOBJECT {
	public:
		CORVID_BOUNDBOX box;
		CORVID_SPRITEDATATYPE id;
		SDL_Surface* texture;
		CORVID_SCREENOBJECT() : box(CORVID_BOUNDBOX()), id(CORVID_SPRITEDATATYPE()), texture(NULL) {};
		CORVID_SCREENOBJECT(int xval, int yval) : box(CORVID_BOUNDBOX(xval, yval)) {
			std::string fileName = "brick.png";
			texture = IMG_Load(fileName.c_str());
		}; // default brick
		CORVID_SCREENOBJECT(std::vector<int>* data) : box(data->at(1), data->at(2), data->at(3), data->at(4), 0, 0), id(data->at(5)) {
			std::string fileName = "brick.png";
			texture = IMG_Load(fileName.c_str());
		};
		int* dataDump(); // This is definitely a memory leak, but considering how broken everything is already, I will fix it later
		// Also it's not a super bad memory leak considering it only runs whenever the game saves
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