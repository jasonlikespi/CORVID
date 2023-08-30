#include "CORVID_SPRITES.h"
using namespace std;
void CORVID_SPRITE::render(CORVID_SCREENOBJECT* object, SDL_Surface* surface) {
	if (object->texture != NULL) {
		SDL_Rect offset = { (int)object->box.rectangle.location.x, (int)object->box.rectangle.location.y, 0, 0 };
		SDL_BlitSurface(object->texture, NULL, surface, &offset);
	} else {
		printf("Error: could not find texture for object with following data:\n");
		dataDump(object);
	}
};
void CORVID_SPRITE::dataDump(CORVID_SCREENOBJECT* object) {
	printf("Location (x, y) at (%f, %f)\n", object->box.rectangle.location.x, object->box.rectangle.location.y);
	printf("Size (width, height) at (%f, %f)\n", object->box.rectangle.size.x, object->box.rectangle.size.y);
	printf("Velocity (x, y) at (%f, %f)\n", object->box.velocity.x, object->box.velocity.y);
	printf("Object id is %d\n", object->id.id);
};
int* CORVID_SPRITE::CORVID_SCREENOBJECT::dataDump() {
	int* dataDump = new int[8];
	dataDump[0] = 0;
	dataDump[1] = (int)this->box.rectangle.location.x;
	dataDump[2] = (int)this->box.rectangle.location.y;
	dataDump[3] = (int)this->box.rectangle.size.x;
	dataDump[4] = (int)this->box.rectangle.size.y;
	dataDump[5] = (int)this->id.id;
	dataDump[6] = 0;
	dataDump[7] = 0;
	return dataDump;
};
void CORVID_SPRITE::CORVID_SCREENOBJECT::loadSpriteTexture() {
	std::filesystem::path texturePath = textureSource->imgfiles->at(textureNumber);
	texture = IMG_Load((const char*)(texturePath.c_str()));
};
