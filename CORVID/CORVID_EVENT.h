#pragma once
#ifndef CORVID_EVENT_H
#define CORVID_EVENT_H
#include <SDL.h>
#include <string>
#include "CORVID_WORLD.h"
// Don't really remember what keyPressData means, maybe I'll remember later
class CORVID_EVENTHANDLER{
	inline static bool Bleft = false;
	inline static bool Bright = false;
	inline static bool Bdown = false;
	inline static bool Bup = false;
	inline static bool B1 = false;
	inline static bool B2 = false;
	inline static bool BW = false;
	inline static bool BA = false;
	inline static bool BS = false;
	inline static bool BD = false;
	inline static bool BC = false;
	int keyPressData;
	SDL_Event* E;
	int cursor_x;
	int cursor_y;
public:
	CORVID_EVENTHANDLER();
	int poll(CORVID_WORLD* world);
	void updateWorld(CORVID_WORLD* world);
};
#endif