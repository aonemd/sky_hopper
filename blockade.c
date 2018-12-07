#include "blockade.h"

Blockade *Blockade__create(GLuint texture_id) {
	Blockade *blockade = malloc(sizeof(*blockade));

	blockade->texture_id = texture_id;

	float possible_x_positions[3] = { -2, 0, 2 };
	float z_position              = -1 * (9 / 2.0) * 20;
	for (int i = 0; i < NUMBER_OF_BRICKS; i++) {
		blockade->bricks[i] = Brick__create(possible_x_positions[i % 3], -1, z_position, texture_id);
		z_position += 30;
	}

	return blockade;
}

void Blockade__render(Blockade *self) {
	for (int i = 0; i < NUMBER_OF_BRICKS; i++) {
		Brick__render(self->bricks[i]);
	}
}

void Blockade__update(Blockade *self) {
	for (int i = 0; i < NUMBER_OF_BRICKS; i++) {
		Brick__update(self->bricks[i]);
	}
}

bool Blockade__character_intersects_brick(Blockade *self, Character *character) {
	for (int i = 0; i < NUMBER_OF_BRICKS; i++) {
		if ((fabs(self->bricks[i]->z - character->z) <= 0.07) &&
				(fabs(self->bricks[i]->x - character->x) <= 0.3) &&
				character->y == 0) {
			return true;
		}
	}

	return false;
}
