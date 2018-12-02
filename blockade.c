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

void Blockade__render(Blockade *blockade) {
	for (int i = 0; i < NUMBER_OF_BRICKS; i++) {
		Brick__render(blockade->bricks[i]);
	}
}

void Blockade__update(Blockade *blockade) {
	for (int i = 0; i < NUMBER_OF_BRICKS; i++) {
		Brick__update(blockade->bricks[i]);
	}
}
