#include "CORVID_SPRITES.h"
using namespace std;
void CORVID_SPRITE::render(CORVID_SCREENOBJECT* object, SDL_Surface* surface) { // TODO Make this not effectively static
	if (object->texture != NULL) {
		SDL_Rect offset = { (int)object->location.x, (int)object->location.y, 0, 0 };
		SDL_BlitSurface(object->texture, NULL, surface, &offset);
	} else {
		printf("Error: could not find texture for object with following data:\n");
		dataDump(object);
	}
};
void CORVID_SPRITE::dataDump(CORVID_SCREENOBJECT* object) {
	//printf("Location (x, y) at (%f, %f)\n", object->location.x, object->location.y);
	//printf("Size (width, height) at (%f, %f)\n", object->size.x, object->size.y);
	//printf("Velocity (x, y) at (%f, %f)\n", object->velocity.x, object->velocity.y);
	//printf("Object id is %d\n", object->id.id);
};
int* CORVID_SPRITE::CORVID_SCREENOBJECT::dataDump() {
	int* dataDump = new int[8];
	dataDump[0] = 0;
	dataDump[1] = (int)this->location.x;
	dataDump[2] = (int)this->location.y;
	dataDump[3] = (int)this->size.x;
	dataDump[4] = (int)this->size.y;
	dataDump[5] = (int)this->id.id;
	dataDump[6] = 0;
	dataDump[7] = 0;
	return dataDump;
};
void CORVID_SPRITE::CORVID_SCREENOBJECT::loadSpriteTexture() {
	std::filesystem::path texturePath = textureSource->imgfiles->at(textureNumber);
	std::string textureString = texturePath.string();
	const char* textureCString = textureString.c_str();
	this->texture = IMG_Load(textureCString);

};