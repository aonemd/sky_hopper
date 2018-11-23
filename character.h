#ifndef _character_h_
#define _character_h_

#include "GL/freeglut.h"

typedef struct {
	float x;
	float y;
	float z;
} Character;

Character *Character__create();
void Character__render(Character *self);
void Character__update(Character *self);

#endif
