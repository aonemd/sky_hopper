#ifndef _coin_h_
#define _coin_h_

#include "stdbool.h"

#ifdef OS_WIN
#include <glut.h>
#else
#include "GL/freeglut.h"
#include "GL/gl.h"
#endif

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
