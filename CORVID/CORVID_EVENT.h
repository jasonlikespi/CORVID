#ifndef CORVID_EVENT_H
#define CORVID_EVENT_H
#include <SDL.h>
#include <string>
#include "CORVID_WORLD.h"

struct CORVID_EVENTHANDLER{
	int keyPressData;
	SDL_Event* E;
	//struct CORVID_R2* cursorPosition;
	CORVID_EVENTHANDLER() {
		keyPressData = 0;
		E = new SDL_Event;
		//cursorPosition = &(new (struct CORVID_R2*));
	}
};
inline int poll(CORVID_EVENTHANDLER* E, CORVID_WORLD* world) {
	SDL_PollEvent(E->E);
	if ((*E->E).type == SDL_QUIT) { return 0; };
	if ((*E->E).type == SDL_KEYDOWN) {
		switch ((*E->E).key.keysym.sym) {
		case SDLK_p:
			world->saveWorld();
			break;
		case SDLK_DOWN:
			world->setLevel(1);
			break;
		case SDLK_q:
			return 0;
			break;
		case SDLK_s:
			world->block_y += 32;
			std::cout << "[" << world->block_x << ", " << world->block_y << "]\n";
			break;
		case SDLK_a:
			world->block_x -= 32;
			std::cout << "[" << world->block_x << ", " << world->block_y << "]\n";
			break;
		case SDLK_w:
			world->block_y -= 32;
			std::cout << "[" << world->block_x << ", " << world->block_y << "]\n";
			break;
		case SDLK_d:
			world->block_x += 32;
			std::cout << "[" << world->block_x << ", " << world->block_y << "]\n";
			break;
		case SDLK_r:
			world->levels->at(1)->staticList->push_back(new CORVID_SCREENOBJECT(world->block_x, world->block_y));
			std::cout << "[" << world->block_x << ", " << world->block_y << "]\n";
			break;
		};
	}
	return 1;
}
#endif