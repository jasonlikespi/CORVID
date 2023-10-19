#pragma once
#ifndef CORVID_CONSTS_H
#define CORVID_CONSTS_H
// Used for SDL_Rect Structs
#include "SDL.h"
// Seperate Namespace so it is differentiated from local variables
namespace CORVID_CONSTS {
	// Used perhaps exclusively by the CORVID_TEXTURE::renderCustomBlock method to interface with the spriteSheet
	const SDL_Rect spriteList[16] = {
		 {  0,  0,  32,  32 },
		 { 32,  0,  32,  32 },
		 { 64,  0,  32,  32 },
		 { 96,  0,  32,  32 },
		 {128,  0,  32,  32 },
		 {160,  0,  32,  32 },
		 {192,  0,  32,  32 },
		 {224,  0,  32,  32 },
		 {  0, 32,  32,  32 },
		 { 32, 32,  32,  32 },
		 { 64, 32,  32,  32 },
		 { 96, 32,  32,  32 },
		 {128, 32,  32,  32 },
		 {160, 32,  32,  32 },
		 {192, 32,  32,  32 },
		 {224, 32,  32,  32 }
	};
	// Array of the dimensions of the texture array
	const SDL_Rect spriteSizes[8] = {
		{0, 0, 32, 32},
		{0, 0, 1920, 1080},
		{0, 0, 7680, 1320},
		{0, 0, 32, 32},
		{0, 0, 32, 64},
		{0, 0, 256, 256},
		{0, 0, 256, 256},
		{0, 0, 256, 256}
	};
	// Width of overall display window
	const int WINDOW_WIDTH = 1920;
	// Height of overall display window
	const int WINDOW_HEIGHT = 1080;
	// Width of the level in pixels, should make this nonglobal variable, also width of the image sky.png
	const int SCREEN_WIDTH = 7680;
	// Height of the level in pixels, should make this nonglobal variable, also height of the image sky.png
	const int SCREEN_HEIGHT = 1080;
	// Base size of block for creation of normal objects. I don't think I will ever have to change it at the moment
	const double UNIT = 32.0;
	// Constant tied to speed of downward acceleration
	const double STRENGTH_OF_GRAVITY = 5;
	// Constant tied to amount of vertical friction: 1 is no friction, 0 means dynamic objects can't move up or down
	const double FRICTION_CONSTANT_VERTICAL = .8;
	// Constant tied to amount of horizontal friction: 1 is no friction, 0 means dynamic objects can't move left/right
	const double FRICTION_CONSTANT_HORIZONTAL = .9;
	// The specific added force given to player after holding jump for 1 frame 
	const double PLAYER_JUMP_FORCE_1 = 20;
	// The specific added force given to player after holding jump for 2 frames
	const double PLAYER_JUMP_FORCE_2 = 20;
	// The specific added force given to player after holding jump for 3 frames
	const double PLAYER_JUMP_FORCE_3 = 20;
	// The specific added force given to player after holding jump for 4 frames
	const double PLAYER_JUMP_FORCE_4 = 20;
	// The specific added force given to player after holding jump for 5 frames
	// TODO find if the physics simulation running above 60 fps causes the PLAYER_JUMP_FORCE constants to not work as intended
	const double PLAYER_JUMP_FORCE_5 = 20;
	// Constant tied to the players default acceleration on pushing the arrow keys
	const double ACCELERATION = 1;
	// Constant tied to max player speed
	const double SPEED_CAP = 20;
	// Constant for relative size of the miniscreen to the entire screen: 1 is it takes up the entire screen, 0 means that it doesn't show anything
	// .875 is what I want to use for edit mode
	const double MINI_SCREEN_FACTOR = 1;
	// The width of the miniature game screen
	const int MINI_SCREEN_WIDTH = (int)(WINDOW_WIDTH * MINI_SCREEN_FACTOR); 
	// The height of the miniature game screen
	const int MINI_SCREEN_HEIGHT = (int)(WINDOW_HEIGHT * MINI_SCREEN_FACTOR);
	// The width of the non-game screen in miniature mode
	const double MINI_SCREEN_CORNER_WIDTH = WINDOW_WIDTH - MINI_SCREEN_WIDTH;
	// The height of the non-game screen in miniature mode
	const double MINI_SCREEN_CORNER_HEIGHT = WINDOW_HEIGHT - MINI_SCREEN_HEIGHT;
	// The size of the base block adjusted for the miniature screen
	const double KUNIT = (double)MINI_SCREEN_FACTOR * (double)UNIT;
	// One Quarter of the screens width in pixels
	// TODO I know it adjusts for different window sizes, but find if failure to adjust for miniature screen is causing error
	const double LEFT_QUARTER_SCREEN = WINDOW_WIDTH * .25;
	// Three Quarters of the screens width in pixels
	// TODO I know it adjusts for different window sizes, but find if failure to adjust for miniature screen is causing error
	const double RIGHT_QUARTER_SCREEN = WINDOW_WIDTH * .75;
	// Half of the screens width in pixels
	// TODO I know it adjusts for different window sizes, but find if failure to adjust for miniature screen is causing error
	const double HALF_SCREEN_HORZ = WINDOW_WIDTH * .5;
	// Minimum X location allowable by player
	// TODO Find out if they can be substituted with other constants
	const double MIN_X = 0; 
	// Minimum Y location allowable by player
	// TODO Find out if they can be substituted with other constants
	const double MIN_Y = 0; 
	// Maximum X location allowable by player
	// TODO Find out if they can be substituted with other constants
	const double MAX_X = 7680; 
	// Maximum Y location allowable by player
	// TODO Find out if they can be substituted with other constants
	const double MAX_Y = 1080;
}
#endif