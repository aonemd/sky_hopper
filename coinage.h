#ifndef _coinage_h_
#define _coinage_h_

#include "stdbool.h"

#include "coin.h"
#include "character.h"

#define NUMBER_OF_COINS 5

typedef struct Coinage {
	Coin *coins[NUMBER_OF_COINS];
} Coinage;

Coinage *Coinage__create();
void Coinage__render(Coinage *self);
void Coinage__update(Coinage *self);
bool Coinage__hide_intersecting_coins(Coinage *self, Character *character);

#endif
