#include "character.h"

Character *Character__create() {
	Character *character = malloc(sizeof(*character));

	character->x          = 0;
	character->y          = 0;
	character->z          = 0;
	character->x_velocity = 0;
	character->y_velocity = 0;
	character->is_jumping = false;
	character->is_falling = false;

	return character;
}

void Character__render(Character *self) {
	glPushMatrix();
	glTranslated(self->x, self->y, self->z);
	glColor3f(0, 0.13725490196078433, 0.42745098039215684);

	glPushMatrix();
	glScaled(1, 1.3, 1);
	glutSolidCube(1.0);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0, 1.1, 0);
	glutSolidSphere(0.5, 100, 100);
	glPopMatrix();

	glPopMatrix();
}

void Character__update(Character *self) {
	self->y += self->y_velocity;
	self->x += self->x_velocity;
	self->z -= self->y_velocity;

	_move_down(self);
	_stop_horizontal_movement(self);
}

void Character__jump_up(Character *self) {
	if (!self->is_jumping) {
		self->y_velocity = 0.04f;
		self->z_velocity = 0.04f;
		self->is_jumping = true;
	}
}

void _move_down(Character *self) {
	if (!self->is_falling && !self->is_jumping) {
		self->y_velocity = 0;
		self->y			 = 0;
	} else if (self->is_jumping) {
		if (self->y >= 5) {
			self->y_velocity -= 0.04f;
			self->is_jumping  = false;

			if (self->y <= 0) {
				self->y_velocity = 0;
			}
		}
	} else {
		self->y_velocity -= 0.004;
	}
}

void Character__move_right(Character *self) {
	self->x_velocity = 0.1 * cos(10 * M_PI / 180.0);
}

void Character__move_left(Character *self) {
	self->x_velocity = -1 * 0.1 * cos(10 * M_PI / 180.0);
}

void _stop_horizontal_movement(Character *self) {
	if (self->x > 2 || self->x < -2) {
		self->x_velocity = 0;
	}
}
