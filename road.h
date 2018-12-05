#ifndef _road_h_
#define _road_h_

#include <stdbool.h>

#include "GL/freeglut.h"
#include "road_block.h"
#include "character.h"

#define NUMBER_OF_ROADS 9
#define ROAD_GAP_LENGTH 4

typedef struct Road {
	RoadBlock *blocks[NUMBER_OF_ROADS];
	int       farthest_road_index;
	GLuint    texture_id;
} Road;

Road *Road__create(GLuint texture_id);
void Road__render(Road *road);
void Road__update(Road *road);
bool Road__character_intersects_gap(Road *road, Character *character);

#endif
