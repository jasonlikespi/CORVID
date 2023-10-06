#pragma once
#ifndef CORVID_CONSTS_H
#define CORVID_CONSTS_H
#include "SDL.h"
#include <filesystem>
namespace CORVID_CONSTS {
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
	const int WINDOW_WIDTH = 1920;
	const int WINDOW_HEIGHT = 1080;
	const int SCREEN_WIDTH = 7680;
	const int SCREEN_HEIGHT = 1080;
	const int MINI_SCREEN_WIDTH = 1680; 
	const int MINI_SCREEN_HEIGHT = 945;
	const double STRENGTH_OF_GRAVITY = 5;
	const double FRICTION_CONSTANT_VERTICAL = .8;
	const double FRICTION_CONSTANT_HORIZONTAL = .9;
	const double PLAYER_JUMP_FORCE_1 = 20;
	const double PLAYER_JUMP_FORCE_2 = 20;
	const double PLAYER_JUMP_FORCE_3 = 20;
	const double PLAYER_JUMP_FORCE_4 = 20;
	const double PLAYER_JUMP_FORCE_5 = 20;
	const double ACCELERATION = 1;
	const double SPEED_CAP = 20;
	const double LEFT_QUARTER_SCREEN = 320;
	const double RIGHT_QUARTER_SCREEN = 960;
	const double HALF_SCREEN_HORZ = 640;
	const double MIN_X = 0; // TODO Add failsafe preventing camera from scrolling past these points.
	const double MIN_Y = 0; // TODO Add failsave preventing player from moving past these points.
	const double MAX_X = 7680;
	const double MAX_Y = 1080;
	// TODO Fix framedip
	// TODO Player cannot move from block to another at same height
	// TODO Add duck button
	// TODO Add sprint
	// TODO BUG Screen scrolls at half of the screen instead of three quarters
	// TODO Add metaanalysis to determine which functions are running most often (probaly needed to fix lag, useful to optimize)
	// TODO Get rid of memory leaks
	// TODO Add actual documentation
	// TODO Add ground to default world creation
	// TODO add text renderer
	// TODO Add better file system
}
#endif