#pragma once
#ifndef CORVID_SPRITES_H
#define CORVID_SPRITES_H
#include "CORVID_GEOM.h"
#include <SDL_Image.h>
#include <vector>
//#include "CORVID_FILE.h"
#include "CORVID_TEXTURE.h"

// using namespace std::filesystem;
// TODO: Reconfigure so this class does not involve any paths, the Corvid File class should only be used by the CORVID_SCREEN class
// In replacement, I will have it so each screenobject is passed with a parameter to the CORVID_SCREEN's texture vector
// Since any rendering will be done through the world, a CORVID_SCREENOBJECT created without this constructor will never call the render method
namespace CORVID_SPRITE {
	//static path defaultPath = (current_path() / "testo\\textures.txt.txt");
	class CORVID_SPRITEDATATYPE {
	public:
		int id;
		CORVID_SPRITEDATATYPE() : id(0) {};
		CORVID_SPRITEDATATYPE(int id) : id(id) {};
	};
	class CORVID_SCREENOBJECT : public CORVID_BOUNDBOX<int>, public CORVID_TEXTURE{
	public:
		CORVID_SPRITEDATATYPE id;
		// CORVID_FILE::CORVID_TEXTLIST* textureSource;
		int textureNumber;
		// CORVID_TEXTURE* texture;
		// SDL_Surface* texture;
		bool selected;
		CORVID_SCREENOBJECT() : CORVID_BOUNDBOX(CORVID_BOUNDBOX()), CORVID_TEXTURE(), id(CORVID_SPRITEDATATYPE()), selected(false) { // This is only remaining because a default constructor is required; it should not be used
			textureNumber = 0;
			//textureSource = new CORVID_FILE::CORVID_TEXTLIST(defaultPath);
		};
		//CORVID_SCREENOBJECT(int xval, int yval) : CORVID_BOUNDBOX(CORVID_BOUNDBOX(xval, yval)), CORVID_TEXTURE(), selected(false) {
			// texture = NULL;
			//textureSource = new CORVID_FILE::CORVID_TEXTLIST(defaultPath);
			//textureNumber = 0;
			//loadSpriteTexture();
		//};
		//CORVID_SCREENOBJECT(std::vector<int>* data) : CORVID_BOUNDBOX(data->at(1), data->at(2), data->at(3), data->at(4), 0, 0), id(data->at(5)), CORVID_TEXTURE(), selected(false) {
			// texture = NULL;
			//textureSource = new CORVID_FILE::CORVID_TEXTLIST(defaultPath);
			//textureNumber = 0;
			//loadSpriteTexture();
		//};
		template <class NUMBER>
		CORVID_SCREENOBJECT(NUMBER x, NUMBER y, CORVID_TEXTURE* texture) : CORVID_BOUNDBOX<NUMBER>(x, y), CORVID_TEXTURE(*texture) {};
		CORVID_SCREENOBJECT(std::vector<int>* objectData, std::vector<SDL_Surface*>* textureData) : CORVID_BOUNDBOX(objectData->at(1), objectData->at(2), objectData->at(3), objectData->at(4), 0, 0), id(objectData->at(5)), CORVID_TEXTURE(objectData, textureData), textureNumber(objectData->at(6)), selected(false) {
			// texture = NULL;
			// textureSource = textureData;
			//loadSpriteTexture();
		};
		int* dataDump(); // This is definitely a memory leak, but considering how broken everything is already, I will fix it later
		// Also it's not a super bad memory leak considering it only runs whenever the game saves
		// void loadSpriteTexture();
		void render(SDL_Surface* surface);
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
	void dataDump(CORVID_SCREENOBJECT* object);
}
#endif