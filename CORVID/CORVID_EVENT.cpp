#include "CORVID_EVENT.h"
CORVID_EVENTHANDLER::CORVID_EVENTHANDLER() {
	cursor_x = 0;
	cursor_y = 0;
	keyPressData = 0;
	E = new SDL_Event;
}
int CORVID_EVENTHANDLER::poll(CORVID_WORLD* world) {
	SDL_PollEvent(E);
	if ((*E).type == SDL_QUIT) { return 0; };
	if ((*E).type == SDL_KEYDOWN) {
		switch ((*E).key.keysym.sym) {
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
			CORVID_TEXTURE* texture = new CORVID_TEXTURE(0);
			world->levels->at(1)->staticList->push_back(new CORVID_SCREENOBJECT(world->block_x, world->block_y, texture));
			std::cout << "[" << world->block_x << ", " << world->block_y << "]\n";
			break;
		};
	}
	if ((*E).type == SDL_MOUSEBUTTONDOWN) {
		SDL_GetMouseState(&cursor_x, &cursor_y);

	}
	return 1;
}