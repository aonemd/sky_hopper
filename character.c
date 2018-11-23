#include "character.h"

Character *Character__create() {
	Character *character = malloc(sizeof(*character));

	character->x = 0;
	character->y = -2;
	character->z = 0;

	return character;
}

void Character__render(Character *self) {
	(void) self;

	glPushMatrix();
	glColor3f(1, 0, 0);
	glutSolidCube(1.0);
	glPopMatrix();
}

void Character__update(Character *self) {
	(void) self;
}
