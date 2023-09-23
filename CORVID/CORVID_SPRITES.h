#pragma once
#ifndef CORVID_SPRITES_H
#define CORVID_SPRITES_H
#include "CORVID_GEOM.h"
#include <SDL_Image.h>
#include <vector>
#include "CORVID_TEXTURE.h"
// TODO: Reconfigure so this class does not involve any paths, the Corvid File class should only be used by the CORVID_SCREEN class
// In replacement, I will have it so each screenobject is passed with a parameter to the CORVID_SCREEN's texture vector
// Since any rendering will be done through the world, a CORVID_SCREENOBJECT created without this constructor will never call the render method
namespace CORVID_SPRITE {
	class CORVID_SPRITEDATATYPE {
	public:
		int id;
		CORVID_SPRITEDATATYPE();
		CORVID_SPRITEDATATYPE(int id);
	};
	class CORVID_SCREENOBJECT : public CORVID_BOUNDBOX<int>, public CORVID_TEXTURE{
	public:
		CORVID_SPRITEDATATYPE id;
		int textureNumber;
		bool selected;
		CORVID_SCREENOBJECT();
		template <class NUMBER>
		CORVID_SCREENOBJECT(NUMBER x, NUMBER y, CORVID_TEXTURE* texture) : CORVID_BOUNDBOX<NUMBER>(x, y), CORVID_TEXTURE(*texture) {};
		CORVID_SCREENOBJECT(std::vector<int>* objectData) : CORVID_BOUNDBOX(objectData->at(1), objectData->at(2), objectData->at(3), objectData->at(4), 0, 0), id(objectData->at(5)), CORVID_TEXTURE(objectData->at(6)), textureNumber(objectData->at(6)), selected(false) { // Still need to fix constructor
		};
		int* dataDump(); // This is definitely a memory leak, but considering how broken everything is already, I will fix it later
		// Also it's not a super bad memory leak considering it only runs whenever the game saves
		// void loadSpriteTexture();
		void render(SDL_Surface* surface);
	};
	class CORVID_PLAYER : public CORVID_SCREENOBJECT{
	public:
		CORVID_SCREENOBJECT* objectStandingOn;
		CORVID_SCREENOBJECT* leftObject;
		CORVID_SCREENOBJECT* rightObject;
		CORVID_PLAYER();
	};
	class CORVID_BACKGROUND {
	public:
		CORVID_SCREENOBJECT imageData;
		int stationaryBackground;
		CORVID_BACKGROUND();
	};
	void dataDump(CORVID_SCREENOBJECT* object);
}
#endif