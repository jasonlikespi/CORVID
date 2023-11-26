#include "CORVID_EVENT.h"
CORVID_EVENTHANDLER::CORVID_EVENTHANDLER() {
	cursor = new CORVID_R2();
	keyPressData = 0;
	E = new SDL_Event;
}
int CORVID_EVENTHANDLER::poll(CORVID_LEVEL* world) {
	SDL_PollEvent(E);
	int tempx, tempy;
	SDL_GetMouseState( &tempx, &tempy);
	cursor->x = tempx;
	cursor->y = tempy;
	// TODO objectUnderCursor has a memory leak
	CORVID_SCREENOBJECT* objectUnderCursor = world->findByPosition(new CORVID_R2(cursor->x - (int)((world->getcameraLocation())->x) - (int)MINI_SCREEN_CORNER_WIDTH, cursor->y - (int)world->getcameraLocation()->y - (int)MINI_SCREEN_CORNER_HEIGHT));
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
		default:
			break;
		};
	}
	// What happens when a key is pressed down
	if ((*E).type == SDL_KEYDOWN) {
		switch ((*E).key.keysym.sym) {
		case SDLK_p:
			world->save(defaultFolder);
			break;
		case SDLK_DOWN:
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
			world->deleteObject(world->selectedObject);
			break;
		default:
			break;
		};
		// if (world->unselectedObject->size.x < 32) { world->unselectedObject->size.x = 32; }
		// if (world->unselectedObject->size.y < 32) { world->unselectedObject->size.y = 32; }
	}
	// The clicking portion of the program
	if ((*E).type == SDL_MOUSEBUTTONDOWN) {
		if (objectUnderCursor != nullptr) {
			world->selectObject(objectUnderCursor);
		} else {
			// CORVID_SCREENOBJECT* newObject = new CORVID_SCREENOBJECT(0, 32 * ((cursor->x - (int)world->getcameraLocation()->x) / 32) - MINI_SCREEN_CORNER_WIDTH, 32 * ((cursor->y - (int)world->getcameraLocation()->y) / 32) - MINI_SCREEN_CORNER_HEIGHT, (int)world->unselectedObject->size.x, (int)world->unselectedObject->size.y, 0, 4, 0);
			// world->addObject(newObject);
			// world->selectObject(newObject);
		}
	}
	// This runs whenever the mouse moves (It also runs when the mouse doesn't move but in that case it does nothing)
	// TODO I probably broke this when I changed the methods
	if (objectUnderCursor != nullptr) { // The nullptr was originally the background
		world->unselectedObject->location.x = (cursor->x - (int)world->getcameraLocation()->x - ((int)cursor->x - (int)world->getcameraLocation()->x) % (int)KUNIT) - MINI_SCREEN_CORNER_WIDTH;
		world->unselectedObject->location.y = (cursor->y - (int)world->getcameraLocation()->y - ((int)cursor->y - (int)world->getcameraLocation()->y) % (int)KUNIT) - MINI_SCREEN_CORNER_HEIGHT;
	} else {
		// The -2048 is completely arbitrary, it just makes it out of frame
		// world->unselectedObject->location.x = -2048;
	}
	return 1;
}
void CORVID_EVENTHANDLER::updateWorld(CORVID_LEVEL* world) { 
	if (BEnter) {
		world->activeContig = world->contigs->at(1);
	};
	if (world->player != nullptr) {
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