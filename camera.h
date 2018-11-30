#ifndef _camera_h
#define _camera_h

#include <stdbool.h>

#include "GL/freeglut.h"

typedef struct Camera {
	float angle;
	bool  rotate_x;
	bool  rotate_y;
	bool  rotate_z;
} Camera;

Camera *Camera__create();
void Camera__render(Camera *self);
void Camera__toggle_top_view(Camera *self);

#endif
