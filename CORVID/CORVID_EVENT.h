#pragma once
#ifndef CORVID_EVENT_H
#define CORVID_EVENT_H
#include <SDL.h>
#include <string>
#include "CORVID_WORLD.h"

class CORVID_EVENTHANDLER{
	int keyPressData;
	SDL_Event* E;
	int cursor_x;
	int cursor_y;
public:
	CORVID_EVENTHANDLER() {
		cursor_x = 0;
		cursor_y = 0;
		keyPressData = 0;
		E = new SDL_Event;
	}
	int poll(CORVID_WORLD* world);
};

#endif