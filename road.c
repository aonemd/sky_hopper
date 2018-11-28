#include "road.h"

Road *Road__create(GLuint texture_id) {
	Road *road = malloc(sizeof(*road));

	road->texture_id = texture_id;

	for (int i = 0; i < NUMBER_OF_ROADS; i += 3) {
		road->blocks[i + 0] = RoadBlock__create(0 - 2, ((i + 0) * -15) - (2 * i), road->texture_id);
		road->blocks[i + 1] = RoadBlock__create(0 - 2, ((i + 1) * -15) - (2 * i), road->texture_id);
		road->blocks[i + 2] = RoadBlock__create(0 - 2, ((i + 2) * -15) - (2 * i), road->texture_id);
	}

	return road;
}

void Road__render(Road *road) {
	for (int i = 0; i < NUMBER_OF_ROADS; i++) {
		RoadBlock__render(road->blocks[i]);
	}
}

void Road__update(Road *road) {
	for (int i = 0; i < NUMBER_OF_ROADS; i++) {
		RoadBlock__update(road->blocks[i]);
	}
}
