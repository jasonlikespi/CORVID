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
	CORVID_EVENTHANDLER();
	int poll(CORVID_WORLD* world);
};
#endif