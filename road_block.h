#ifndef _road_block_h_
#define _road_block_h_

#include <stdbool.h>

#include "GL/freeglut.h"

typedef struct {
	float x;
	float y;
	float z;
	float original_z;
	GLuint texture_id;
} RoadBlock;

RoadBlock *RoadBlock__create(float y, float z, GLuint texture_id);
void RoadBlock__render(RoadBlock *self);
void RoadBlock__update(RoadBlock *self);

#endif
