#ifndef _bloackage_h_
#define _bloackage_h_

#include "GL/freeglut.h"
#include "brick.h"

#define NUMBER_OF_BRICKS 30

typedef struct Blockade {
	Brick  *bricks[NUMBER_OF_BRICKS];
	GLuint texture_id;
} Blockade;

Blockade *Blockade__create(GLuint texture_id);
void Blockade__render(Blockade *blockade);
void Blockade__update(Blockade *blockade);

#endif