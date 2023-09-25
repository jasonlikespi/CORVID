#pragma once
#ifndef CORVID_SPRITES_H
#define CORVID_SPRITES_H
#include "CORVID_GEOM.h"
#include <SDL_Image.h>
#include <vector>
#include "CORVID_TEXTURE.h"
namespace CORVID_SPRITE {
	class CORVID_SPRITEDATATYPE {
	public:
		int id;
		CORVID_SPRITEDATATYPE() : id(0) {};
		CORVID_SPRITEDATATYPE(int id) : id(id) {};
	};
	class CORVID_SCREENOBJECT : public CORVID_BOUNDBOX, public CORVID_TEXTURE, public CORVID_SPRITEDATATYPE{
	public:
		bool selected;
		CORVID_SCREENOBJECT();
		CORVID_SCREENOBJECT(double x, double y, CORVID_TEXTURE* texture) : CORVID_BOUNDBOX(x, y), CORVID_TEXTURE(*texture), selected(false) {};
		// TODO Still need to fix constructor
		CORVID_SCREENOBJECT(std::vector<int>* data) : 
			CORVID_BOUNDBOX(data->at(1), data->at(2), data->at(3), data->at(4), 0, 0),
			CORVID_SPRITEDATATYPE(data->at(5)), CORVID_TEXTURE(data->at(6)), selected(false) { };
		void render(SDL_Surface* surface);
		// This is definitely a memory leak, but considering how broken everything is already, I will fix it later
		// Also it's not a super bad memory leak considering it only runs whenever the game saves
		int* dataDump(); 
	};
	class CORVID_PLAYER : public CORVID_SCREENOBJECT{
	public:
		CORVID_SCREENOBJECT* objectStandingOn;
		CORVID_SCREENOBJECT* leftObject;
		CORVID_SCREENOBJECT* rightObject;
		// This one I actually do want to use as a default constructor
		CORVID_PLAYER() : CORVID_SCREENOBJECT(), objectStandingOn(NULL), leftObject(NULL), rightObject(NULL) {}; 
		CORVID_PLAYER(double xloc, double yloc, CORVID_TEXTURE* texture) : 
			CORVID_SCREENOBJECT(xloc, yloc, texture), objectStandingOn(NULL), leftObject(NULL), rightObject(NULL) {};
	};
	// TODO literally anything with this class;
	class CORVID_BACKGROUND { 
	public:
		CORVID_SCREENOBJECT imageData;
		int stationaryBackground;
		CORVID_BACKGROUND() : imageData(CORVID_SCREENOBJECT()), stationaryBackground(0) {};
	};
}
#endif