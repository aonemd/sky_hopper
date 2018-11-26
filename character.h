#ifndef _character_h_
#define _character_h_

#include <math.h>
#include <stdbool.h>

#include "GL/freeglut.h"

typedef struct {
	float x;
	float y;
	float z;
	float x_velocity;
	float y_velocity;
	bool is_jumping;
} Character;

Character *Character__create();
void Character__render(Character *self);
void Character__update(Character *self);
void Character__jump_up(Character *self);
void _move_down(Character *self);
void Character__move_right(Character *self);
void Character__move_left(Character *self);
void _stop_horizontal_movement(Character *self);

#endif
