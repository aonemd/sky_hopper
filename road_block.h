#ifndef _road_block_h_
#define _road_block_h_

#include <stdbool.h>

#include "GL/freeglut.h"

#define BLOCK_LENGTH 30

typedef struct {
	float x;
	float y;
	float z;
	float original_z;
	GLuint texture_id;
} RoadBlock;

RoadBlock *RoadBlock__create(float y, float z);
void RoadBlock__render(RoadBlock *self, GLuint texture_id);
void RoadBlock__update(RoadBlock *self);

#endif
