#ifndef _road_h_
#define _road_h_

#include <stdbool.h>

#ifdef OS_WIN
#include <glut.h>
#else
#include "GL/freeglut.h"
#include "GL/gl.h"
#endif

#include "road_block.h"
#include "character.h"

#define NUMBER_OF_ROADS 9
#define ROAD_GAP_LENGTH 4

typedef struct Road {
	RoadBlock *blocks[NUMBER_OF_ROADS];
	int       farthest_road_index;
} Road;

Road *Road__create();
void Road__render(Road *self, GLuint texture_id);
void Road__update(Road *self);
bool Road__character_intersects_gap(Road *self, Character *character);

#endif
