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
	CORVID_SCREENOBJECT* objectUnderCursor = world->findByPosition(cursor_x - (int)world->getcameraLocation()->x, cursor_y - (int)world->getcameraLocation()->y);
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
			break;
		case SDLK_RETURN:
			BEnter = false;
			break;
		};
	}
	// What happens when a key is pressed down
	if ((*E).type == SDL_KEYDOWN) {
		switch ((*E).key.keysym.sym) {
		case SDLK_p:
			world->saveWorld();
			break;
		case SDLK_DOWN:
			//world->setLevel(1);
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
			world->unselectedObject->size.y += 32;
			break;
		case SDLK_a:
			world->unselectedObject->size.x -= 32;
			break;
		case SDLK_w:
			world->unselectedObject->size.y -= 32;
			break;
		case SDLK_d:
			world->unselectedObject->size.x += 32;
			break;
		case SDLK_RETURN:
			BEnter = true;
			break;
		case SDLK_r:
			std::cout << "Huh?\n";
			break;
		case SDLK_DELETE:
			world->deleteObject();
			break;
		default:
			break;
		};
		if (world->unselectedObject->size.x < 32) { world->unselectedObject->size.x = 32; }
		if (world->unselectedObject->size.y < 32) { world->unselectedObject->size.y = 32; }
	}
	// The clicking portion of the program
	if ((*E).type == SDL_MOUSEBUTTONDOWN) {
		if (objectUnderCursor != world->getbackground()) {
			world->selectObject(objectUnderCursor);
		} else {
			CORVID_SCREENOBJECT* newObject = new CORVID_SCREENOBJECT(0, 32 * ((cursor_x - (int)world->getcameraLocation()->x) / 32), 32 * ((cursor_y - (int)world->getcameraLocation()->y) / 32), (int)world->unselectedObject->size.x, (int)world->unselectedObject->size.y, 0, 4, 0);
			world->levels->at(1)->staticList->push_back(newObject);
			world->selectObject(newObject);
		}
	}
	// This runs whenever the mouse moves (It also runs when the mouse doesn't move but in that case it does nothing)
	if (objectUnderCursor == world->getbackground()) {
		world->unselectedObject->location.x = 32 * ((cursor_x - (int)world->getcameraLocation()->x) / 32) ;
		world->unselectedObject->location.y = 32 * ((cursor_y - (int)world->getcameraLocation()->y) / 32) ;
	} else {
		// The -2048 is completely arbitrary
		world->unselectedObject->location.x = -2048;
	}
	return 1;
}
void CORVID_EVENTHANDLER::updateWorld(CORVID_WORLD* world) { 
	if (BEnter) {
		world->setLevel(1);
	};
	if (world->activeLevel()->player != nullptr) {
		if (Bleft) { world->playerMoveLeft(); }
		if (Bright) { world->playerMoveRight(); }
		if (Bup) { world->playerJump(); }
		if (!Bup) { world->stopJump(); }
		world->updateStatics();
		world->updateDynamics();
		world->updatePlayer();
		world->collisionDetect();
		world->updateCamera();
	}
};