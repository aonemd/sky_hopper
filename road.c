#include "road.h"

Road *Road__create() {
	Road *road = malloc(sizeof(*road));

	road->farthest_road_index = 0;

	for (int i = 0; i < NUMBER_OF_ROADS; i++) {
		road->blocks[i + 0] = RoadBlock__create(0 - 2, ((i + 0) * -1 * BLOCK_LENGTH) - (ROAD_GAP_LENGTH * i));
	}

	return road;
}

void Road__render(Road *self, GLuint texture_id) {
	for (int i = 0; i < NUMBER_OF_ROADS; i++) {
		RoadBlock__render(self->blocks[i], texture_id);
	}
}

void Road__update(Road *self) {
	for (int i = 0; i < NUMBER_OF_ROADS; i++) {
		RoadBlock__update(self->blocks[i]);
	}

	int farthest_road_index = self->farthest_road_index;
	if(self->blocks[farthest_road_index]->z >= (NUMBER_OF_ROADS / 2.0) * BLOCK_LENGTH) {
		int previous_self_index = (farthest_road_index + NUMBER_OF_ROADS - 1) % NUMBER_OF_ROADS;

		self->blocks[farthest_road_index]->z = self->blocks[previous_self_index]->z - BLOCK_LENGTH - ROAD_GAP_LENGTH;
		self->farthest_road_index            = (farthest_road_index + 1) % NUMBER_OF_ROADS;
	}
}

bool Road__character_intersects_gap(Road *self, Character *character) {
	int minimum_z_index = 0;
	for (int i = 0; i < NUMBER_OF_ROADS; i++) {
		if (self->blocks[i]->z >= 0) {
			if (self->blocks[i]->z < self->blocks[minimum_z_index]->z) {
				minimum_z_index = i;
			}
		}
	}

	if ((self->blocks[minimum_z_index]->z > 15.7f && self->blocks[minimum_z_index]->z <= 18) && character->y <= 0) {
		return true;
	}

	return false;
}
