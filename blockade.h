#ifndef _bloackage_h_
#define _bloackage_h_

#include <stdbool.h>

#ifdef OS_WIN
#include <glut.h>
#else
#include "GL/freeglut.h"
#include "GL/gl.h"
#endif

#include "brick.h"
#include "character.h"

#define NUMBER_OF_BRICKS 30

typedef struct Blockade {
	Brick  *bricks[NUMBER_OF_BRICKS];
	GLuint texture_id;
} Blockade;

Blockade *Blockade__create(GLuint texture_id);
void Blockade__render(Blockade *self);
void Blockade__update(Blockade *self);
bool Blockade__character_intersects_brick(Blockade *self, Character *character);

#endif
