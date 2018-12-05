#ifndef _camera_h_
#define _camera_h_

#include <stdbool.h>

#include "GL/freeglut.h"

typedef struct Camera {
	float x;
	float y;
	float z;
	float angle;
	bool  rotate_x;
	bool  rotate_y;
	bool  rotate_z;
	int	  view_mode;
} Camera;

Camera *Camera__create();
void Camera__render(Camera *self);
void Camera__update(Camera *self, int x, int y);
void Camera__toggle_view_mode(Camera *self);

#endif
