#include "coinage.h"

Coinage *Coinage__create() {
	Coinage *coinage = malloc(sizeof(*coinage));

	float possible_x_positions[2] = { -2, 2 };
	for (int i = 0; i < NUMBER_OF_COINS; i++) {
		coinage->coins[i] = Coin__create(possible_x_positions[i % 2], 0, i);
	}

	return coinage;
}

void Coinage__render(Coinage *self) {
	for (int i = 0; i < NUMBER_OF_COINS; i++) {
		Coin__render(self->coins[i]);
	}
}

void Coinage__update(Coinage *self) {
	for (int i = 0; i < NUMBER_OF_COINS; i++) {
		Coin__update(self->coins[i]);
	}
}

bool Coinage__hide_intersecting_coins(Coinage *self, Character *character) {
	for (int i = 0; i < NUMBER_OF_COINS; i++) {
		if (fabs(self->coins[i]->z - character->z) <= 0.07 &&
				(fabs(self->coins[i]->x - character->x) <= 0.068097) &&
				character->y <= 1) {
			self->coins[i]->visible = false;
			return true;
		}
	}

	return false;
}
