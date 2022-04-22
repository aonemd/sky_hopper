#ifndef _brick_h_
#define _brick_h_

#ifdef OS_WIN
#include <glut.h>
#else
#include "GL/freeglut.h"
#include "GL/gl.h"
#endif

typedef struct Brick {
	float x;
	float y;
	float z;
	float original_z;
	GLuint texture_id;
} Brick;

Brick *Brick__create(float x, float y, float z, GLuint texture_id);
void Brick__render(Brick *self);
void Brick__update(Brick *self);

#endif
