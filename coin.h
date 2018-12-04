#ifndef _coin_h_
#define _coin_h_

#include "stdbool.h"

#include "GL/freeglut.h"

typedef struct Coin {
	float x;
	float y;
	float z;
	float original_z;
	float angle;
	bool  visible;
} Coin;

Coin *Coin__create(float x, float y, float z);
void Coin__render(Coin *coin);
void Coin__update(Coin *coin);

#endif
