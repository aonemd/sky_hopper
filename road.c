#include "road.h"

Road *Road__create() {
	Road *road = malloc(sizeof(*road));

	road->farthest_road_index = 0;

	for (int i = 0; i < NUMBER_OF_ROADS; i++) {
		road->blocks[i + 0] = RoadBlock__create(0 - 2, ((i + 0) * -1 * BLOCK_LENGTH) - (ROAD_GAP_LENGTH * i));
	}

	return road;
}

void Road__render(Road *road, GLuint texture_id) {
	for (int i = 0; i < NUMBER_OF_ROADS; i++) {
		RoadBlock__render(road->blocks[i], texture_id);
	}
}

void Road__update(Road *road) {
	for (int i = 0; i < NUMBER_OF_ROADS; i++) {
		RoadBlock__update(road->blocks[i]);
	}

	int farthest_road_index = road->farthest_road_index;
	if(road->blocks[farthest_road_index]->z >= (NUMBER_OF_ROADS / 2.0) * BLOCK_LENGTH) {
		int previous_road_index = (farthest_road_index + NUMBER_OF_ROADS - 1) % NUMBER_OF_ROADS;

		road->blocks[farthest_road_index]->z = road->blocks[previous_road_index]->z - BLOCK_LENGTH - ROAD_GAP_LENGTH;
		road->farthest_road_index            = (farthest_road_index + 1) % NUMBER_OF_ROADS;
	}
}

bool Road__character_intersects_gap(Road *road, Character *character) {
	int minimum_z_index = 0;
	for (int i = 0; i < NUMBER_OF_ROADS; i++) {
		if (road->blocks[i]->z >= 0) {
			if (road->blocks[i]->z < road->blocks[minimum_z_index]->z) {
				minimum_z_index = i;
			}
		}
	}

	if ((road->blocks[minimum_z_index]->z > 15.7f && road->blocks[minimum_z_index]->z <= 18) && character->y <= 0) {
		return true;
	}

	return false;
}
