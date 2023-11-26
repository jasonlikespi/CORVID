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
#include <stdlib.h>
#include <time.h>

using namespace std::filesystem;

bool init();
void close();
int currentLevel = 0;
SDL_Window* window = NULL;
SDL_Renderer* CORVID_CAMERA::surface = NULL;
SDL_Texture* gameSurface = NULL;
SDL_Rect windowHalver = SDL_Rect{ WINDOW_WIDTH - MINI_SCREEN_WIDTH, WINDOW_HEIGHT - MINI_SCREEN_HEIGHT, 0, 0 };
SDL_Rect menuWindow = SDL_Rect{ 0, -164, WINDOW_WIDTH - MINI_SCREEN_WIDTH, WINDOW_HEIGHT - MINI_SCREEN_HEIGHT };
std::vector<SDL_Texture*>* CORVID_TEXTURE::textureList = NULL;

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
			WINDOW_WIDTH,
			WINDOW_HEIGHT,
			SDL_WINDOW_OPENGL
		);
		if (window == NULL) {
			printf("Could not create window: %s\n", SDL_GetError());
		}
		else {
			CORVID_CAMERA::surface = SDL_CreateRenderer(window, -1, 0);
		}
	}
	return success;
}

void close() {
	SDL_DestroyWindow(window);
	window = NULL;
	SDL_Quit();
}

int main() {
	if (!init()) {
		printf("Failed to initialize!\n");
		close();
		return 0;
	}
	int fps = 0;
	int frameOfLastSecond = 0;
	int frame = 0;
	time_t startTime;
	time_t currentTime;
	time_t now;
	time(&startTime);
	time(&currentTime);

	// This is the part that is going to have the temporary(ish) text interface for level selection
	// TODO Make it where it works for levels other than default
	bool textMode = false;
	std::string textIn = "";
	std::string folder = "default";
	while (textMode) {
		std::cout << "Type a level to play, or press p to play default level.\n";
		std::cin >> textIn;
		if (textIn == "p") {
			folder = "default";
			textMode = false;
		}
	}
	path mainPath = current_path();
	path objPath = path(mainPath) / folder / objFile;
	path texturePath = path(mainPath) / folder / textureFile;
	// TODO I think the below method should simplify the constructor to remove CORVID_CAMERA::surface
	CORVID_LEVEL* world = new CORVID_LEVEL(objPath, texturePath, CORVID_CAMERA::surface);
	CORVID_EVENTHANDLER* E = new CORVID_EVENTHANDLER();
	CORVID_TEXTURE::initializeTextures(world->imgfiles, CORVID_CAMERA::surface);
	while (E->poll(world)) {
		SDL_RenderClear(CORVID_CAMERA::surface);
		E->updateWorld(world);
		world->render();
		SDL_RenderPresent(CORVID_CAMERA::surface);
		SDL_Delay(10);
		frame++;
		time(&now);
		if (now != currentTime) {
			currentTime++;
			fps = frame - frameOfLastSecond;
			frameOfLastSecond = frame;
			std::cout << fps;
			std::cout << "\n";
		}
	}
	world->save(current_path() / defaultFolder);
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