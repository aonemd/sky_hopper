#include "character.h"

Character *Character__create() {
	Character *character = malloc(sizeof(*character));

	character->x          = 0;
	character->y          = 0;
	character->z          = 0;
	character->y_velocity = 0;
	character->is_jumping = false;

	return character;
}

void Character__render(Character *self) {
	(void) self;

	glPushMatrix();
	glColor3f(1, 0, 0);
	glTranslated(self->x, self->y, self->z);
	glutSolidCube(1.0);
	glPopMatrix();
}

void Character__update(Character *self) {
	self->y += self->y_velocity;

	Character__move_down(self);
}

void Character__jump_up(Character *self) {
	if (!self->is_jumping) {
		self->y_velocity = 0.04f;
		self->is_jumping = true;
	}
}

void Character__move_down(Character *self) {
	if (self->y <= 0) {
		self->y_velocity = 0;
		self->is_jumping = false;
		return;
	}

	if (self->y >= 5) {
		self->y_velocity -= 0.04f;
		self->is_jumping  = false;
	}
}
