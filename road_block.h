#ifndef _road_block_h_
#define _road_block_h_

#include <stdbool.h>

#include "texture_loader.h"

typedef struct {
	float x;
	float y;
	float z;
	float original_z;
	char *texture_path;
} RoadBlock;

RoadBlock *RoadBlock__create(float y, float z, char *texture_path);
void RoadBlock__render(RoadBlock *self);
void RoadBlock__update(RoadBlock *self);

#endif
