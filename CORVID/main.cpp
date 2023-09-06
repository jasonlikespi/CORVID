#define SDL_MAIN_HANDLED
#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <vector>
#include <iostream>
#include "CORVID_FILE.h"
#include "CORVID_WORLD.h"
#include "CORVID_EVENT.h"
#include <fstream>
#include "SDL_filesystem.h"
#include <windows.h>

bool init();
void close();
int currentLevel = 0;
SDL_Window* window = NULL;
SDL_Surface* EditSurface = NULL;
const int SCREEN_WIDTH = 1920;
const int  SCREEN_HEIGHT = 1080;
const int MINI_SCREEN_WIDTH = 1920; // To change to miniscreen mode: change this to the screen size
const int MINI_SCREEN_HEIGHT = 1080;
SDL_Rect windowHalver = SDL_Rect{ SCREEN_WIDTH - MINI_SCREEN_WIDTH, SCREEN_HEIGHT - MINI_SCREEN_HEIGHT, 0, 0 };
SDL_Rect menuWindow = SDL_Rect{ 0, -164, SCREEN_WIDTH - MINI_SCREEN_WIDTH, SCREEN_HEIGHT - MINI_SCREEN_HEIGHT };
const char* staticFiles = "asdf";
SDL_Surface* Stage = SDL_CreateRGBSurface(0, SCREEN_WIDTH, SCREEN_HEIGHT, 32, 0, 0, 0, 0);
SDL_Surface* Layer = SDL_CreateRGBSurface(0, SCREEN_WIDTH, SCREEN_HEIGHT, 32, 0, 0, 0, 0);
SDL_Surface* Blank = SDL_CreateRGBSurface(0, SCREEN_WIDTH, SCREEN_HEIGHT, 32, 0, 0, 0, 0);
SDL_Surface* GameSurface = SDL_CreateRGBSurface(0, SCREEN_WIDTH, SCREEN_HEIGHT, 32, 0, 0, 0, 0);
SDL_Surface* ObjectMenu = SDL_CreateRGBSurface(0, SCREEN_WIDTH, SCREEN_HEIGHT, 32, 0, 0, 0, 0);

using namespace std::filesystem;

bool init() {
	bool success = true;
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("SDL could not initilaize! SDL_Error: %s\n", SDL_GetError());
		success = false;
	}
	else {
		window = SDL_CreateWindow
		(
			"An SDL2 window",
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			SCREEN_WIDTH,
			SCREEN_HEIGHT,
			SDL_WINDOW_OPENGL
		);
		if (window == NULL) {
			printf("Could not create window: %s\n", SDL_GetError());
		}
		else {
			EditSurface = SDL_GetWindowSurface(window);
		}
	}
	return success;
}

void close() {
	SDL_DestroyWindow(window);
	window = NULL;
	SDL_Quit();
}
/*
void loadObjectMenu() {
	const std::string text = "LargeBrick.png";
	SDL_BlitSurface(IMG_Load(text.c_str()), NULL, ObjectMenu, NULL);
}
*/
int main() {
	path worldFile = current_path() / "testo\\testo.bin";
	path textureFile = current_path() / "testo\\textures.txt.txt";
	//path firstPath = current_path() / "brick.png";
	//std::string stringyNow = firstPath.string();
	//const char* textTexto = stringyNow.c_str();
	//SDL_Surface* textTexture = IMG_Load(textTexto);
	CORVID_WORLD* world = new CORVID_WORLD(worldFile, textureFile);
	if (!init()) {
		printf("Failed to initialize!\n");
		close();
		return 0;
	}

	CORVID_EVENTHANDLER* E = new CORVID_EVENTHANDLER();
	while (E->poll(world)) {

		world->render(Stage);
		//loadObjectMenu();
		SDL_BlitSurface(Stage, NULL, GameSurface, NULL);
		SDL_BlitSurface(GameSurface, NULL, EditSurface, &windowHalver);
		SDL_BlitSurface(ObjectMenu, &menuWindow, EditSurface, NULL);
		SDL_UpdateWindowSurface(window);

	}

	world->saveWorld();
	return 0;
}




//One day a day may come where there is an error in the code, and the only solution is to insert this method back into the program
//Until that day, it will remain here
/*
SDL_Surface* loadSurface(std::string path) {
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL) {
		printf("Unable to load image %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
	}
	return loadedSurface;
}
*/