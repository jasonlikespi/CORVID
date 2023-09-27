#include "CORVID_EVENT.h"
CORVID_EVENTHANDLER::CORVID_EVENTHANDLER() {
	cursor_x = 0;
	cursor_y = 0;
	keyPressData = 0;
	E = new SDL_Event;
}
int CORVID_EVENTHANDLER::poll(CORVID_WORLD* world) {
	SDL_PollEvent(E);
	SDL_GetMouseState(&cursor_x, &cursor_y);
	CORVID_SCREENOBJECT* objectUnderCursor = world->findByPosition(cursor_x, cursor_y);
	// Shuts down the program if the window is exited out of
	if ((*E).type == SDL_QUIT) { return 0; };
	// What happens when a key is released- mostly just their respective variables resetting
	if ((*E).type == SDL_KEYUP) {
		switch ((*E).key.keysym.sym){
		case SDLK_DOWN:
			Bdown = false;
			break;
		case SDLK_UP:
			Bup = false;
			break;
		case SDLK_LEFT:
			Bleft = false;
			break;
		case SDLK_RIGHT:
			Bright = false;
		};
	}
	// What happens when a key is pressed down
	if ((*E).type == SDL_KEYDOWN) {
		switch ((*E).key.keysym.sym) {
		case SDLK_p:
			world->saveWorld();
			break;
		case SDLK_DOWN:
			world->setLevel(1);
			Bdown = true;
			break;
		case SDLK_UP:
			Bup = true;
			break;
		case SDLK_LEFT:
			Bleft = true;
			break;
		case SDLK_RIGHT:
			Bright = true;
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
			world->levels->at(1)->staticList->push_back(new CORVID_SCREENOBJECT(world->block_x, world->block_y, new CORVID_TEXTURE(3)));
			std::cout << "[" << world->block_x << ", " << world->block_y << "]\n";
			break;
		case SDLK_DELETE:
			world->deleteObject();
			break;
		default:
			break;
		};
	}
	// The clicking portion of the program
	if ((*E).type == SDL_MOUSEBUTTONDOWN) {
		if (objectUnderCursor != world->getbackground()) {
			world->selectObject(objectUnderCursor);
		} else {
			CORVID_SCREENOBJECT* newObject = new CORVID_SCREENOBJECT(32 * (cursor_x / 32), 32 * (cursor_y / 32), new CORVID_TEXTURE(4));
			world->levels->at(1)->staticList->push_back(newObject);
			world->selectObject(newObject);
		}
	}
	// This runs whenever the mouse moves (It also runs when the mouse doesn't move but in that case it does nothing)
	if (objectUnderCursor == world->getbackground()) {
		world->unselectedObject->location.x = 32 * (cursor_x / 32);
		world->unselectedObject->location.y = 32 * (cursor_y / 32);
	} else {
		// The -2048 is completely arbitrary
		world->unselectedObject->location.x = -2048;
	}
	return 1;
}
void CORVID_EVENTHANDLER::updateWorld(CORVID_WORLD* world) { 
	if (Bleft) { world->playerMoveLeft(); }
	if (Bright) { world->playerMoveRight(); }
	if (Bup) { world->playerJump(); }
	if (Bdown) { 
		world->setLevel(1);
	};
};