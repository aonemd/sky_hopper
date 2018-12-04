#ifndef _coinage_h
#define _coinage_h

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
void Coinage__hide_intersecting_coins(Coinage *self, Character *character);

#endif
