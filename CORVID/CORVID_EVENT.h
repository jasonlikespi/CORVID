#pragma once
#ifndef CORVID_EVENT_H
#define CORVID_EVENT_H
// Needed because SDL_Event is a key part of this class
#include <SDL.h>
// I need the world class in order to interact with it
#include "CORVID_WORLD.h"

// Class for handling all keyboard interactions with the world
// TODO Should I make the CORVID_WORLD a superclass or field?
class CORVID_EVENTHANDLER{
	// Is the left key pressed?
	inline static bool Bleft = false;
	// Is the left key pressed?
	inline static bool Bright = false;
	// Is the left key pressed?
	inline static bool Bdown = false;
	// Is the left key pressed?
	inline static bool Bup = false;
	// Is the left key pressed?
	inline static bool B1 = false;
	// Is the left key pressed?
	inline static bool B2 = false;
	// Is the left key pressed?
	inline static bool BW = false;
	// Is the left key pressed?
	inline static bool BA = false;
	// Is the left key pressed?
	inline static bool BS = false;
	// Is the left key pressed?
	inline static bool BD = false;
	// Is the left key pressed?
	inline static bool BC = false;
	// Is the left key pressed?
	inline static bool BEnter = false;
	// Don't really remember what keyPressData means, maybe I'll remember later
	// TODO Figure out if I can just remove this
	int keyPressData;
	// The actual SDL interactions with the keyboard
	// TODO should this be just an extension or something?
	// Or can you not extend unions? IDK.
	SDL_Event* E;
	// Cursors x coordinate
	// TODO Rename to specify how it interacts with the miniscreen and possibly change to CORVID_R2 to use coordinate types
	int cursor_x;
	// Cursors y coordinate
	// TODO Rename to specify how it interacts with the miniscreen and possibly change to CORVID_R2 to use coordinate types
	int cursor_y;
public:
	// @return CORVID_EVENTHANDLER with cursor at (0, 0), keyPressData 0 and a new SDL_Event
	CORVID_EVENTHANDLER();
	// Runs every frame to update variables in response to player input
	// TODO Look over each method that runs in main and see if it needs to be consolidated, and which class it should run from
	// @param world the CORVID_WORLD that is running
	// @return 0 if the window should close immediately, 1 otherwise
	int poll(CORVID_LEVEL* world);
	// Runs Every frame to update the world
	// TODO Should probaly merge with poll method
	// @param the CORVID_WORLD that is running
	// @return void
	void updateWorld(CORVID_LEVEL* world);
};
#endif