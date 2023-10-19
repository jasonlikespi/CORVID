#pragma once
#ifndef CORVID_SPRITES_H
#define CORVID_SPRITES_H
#include "CORVID_GEOM.h"
#include <SDL_Image.h>
#include <vector>
#include "CORVID_TEXTURE.h"
using namespace CORVID_CONSTS;
namespace CORVID_SPRITE {
	class CORVID_SPRITEDATATYPE {
	public:
		int id;
		CORVID_SPRITEDATATYPE() : id(0) {};
		CORVID_SPRITEDATATYPE(int id) : id(id) {};
		bool isEffectedByGravity();
		bool hasFriction();
		bool canDamage();
		bool isCheckPoint();
		bool isLevelSwap();
	};
	class CORVID_SCREENOBJECT : public CORVID_BOUNDBOX, public CORVID_TEXTURE, public CORVID_SPRITEDATATYPE{
	public:
		bool selected;
		bool freeFall;
		CORVID_SCREENOBJECT();
		// TODO I think I should deprecate this constructor
		CORVID_SCREENOBJECT(double x, double y, CORVID_TEXTURE* texture) : 
			CORVID_BOUNDBOX(x, y), CORVID_TEXTURE(*texture), selected(false), freeFall(true) {};
		// TODO Still need to fix constructor
		CORVID_SCREENOBJECT(std::vector<int>* data) : 
			CORVID_BOUNDBOX(data->at(1), data->at(2), data->at(3), data->at(4), 0, 0),
			CORVID_SPRITEDATATYPE(data->at(6)), CORVID_TEXTURE(data->at(6)), selected(false), freeFall(true){ };
		CORVID_SCREENOBJECT(double i0, double i1, double i2, double i3, double i4, double i5, double i6, double i7) : 
			CORVID_BOUNDBOX((int)i1, (int)i2, (int)i3, (int)i4, 0, 0), CORVID_SPRITEDATATYPE((int)i6), CORVID_TEXTURE((int)i6), selected(false), freeFall(true) {};
		void render(SDL_Renderer* surface, CORVID_R2* cameraLocation);
		// This is definitely a memory leak, but considering how broken everything is already, I will fix it later
		// Also it's not a super bad memory leak considering it only runs whenever the game saves
		int* dataDump(); 
		void updateFrame();
	};
	class CORVID_PLAYER : public CORVID_SCREENOBJECT{
	public:
		CORVID_SCREENOBJECT* objectStandingOn;
		CORVID_SCREENOBJECT* leftObject;
		CORVID_SCREENOBJECT* rightObject;
		int jumpFrame;
		// This one I actually do want to use as a default constructor
		CORVID_PLAYER() : CORVID_SCREENOBJECT(), objectStandingOn(NULL), leftObject(NULL), rightObject(NULL), jumpFrame(-1) {};
		// TODO I think I should deprecate this constructor
		CORVID_PLAYER(double xloc, double yloc, CORVID_TEXTURE* texture) : 
			CORVID_SCREENOBJECT(0, xloc, yloc, 32, 64, 0, 2, 0), objectStandingOn(NULL), leftObject(NULL), rightObject(NULL), jumpFrame(-1) {};
		CORVID_PLAYER(double i0, double i1, double i2, double i3, double i4, double i5, double i6, double i7) :
			CORVID_SCREENOBJECT(i0, i1, i2, i3, i4, i5, i6, i7), objectStandingOn(NULL), leftObject(NULL), rightObject(NULL), jumpFrame(-1) {};
		void moveLeft();
		void moveRight();
		void jump();
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