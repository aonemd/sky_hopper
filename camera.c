#include "camera.h"

Camera *Camera__create() {
	Camera *camera = malloc(sizeof(*camera));

	camera->x		 = 0;
	camera->x		 = 0;
	camera->z		 = 0;
	camera->angle	 = 0;
	camera->rotate_x = true;
	camera->rotate_y = false;
	camera->rotate_z = false;
	camera->view_mode	 = 0;

	return camera;
}

void Camera__render(Camera *self) {
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslated(-1 * self->x, -1 * self->y, self->z);
	gluLookAt(0.0, 4.0, 15.0, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
	glRotatef(self->angle, self->rotate_x , self->rotate_y, self->rotate_z);
}

void Camera__update(Camera *self, int x, int y) {
	if (self->view_mode != 2) {
		return;
	}

	self->x = x;
	self->y = y;
}

void Camera__toggle_view_mode(Camera *self) {
	self->view_mode = (self->view_mode + 1) % 4;

	switch(self->view_mode) {
		case 0:
			self->x		= 0;
			self->y		= 0;
			self->z		= 0;
			self->angle = 0;
			self->rotate_x = true;
			self->rotate_y = false;
			self->rotate_z = false;
			break;
		case 1:
			self->angle = 70;
			self->rotate_x = true;
			self->rotate_y = false;
			self->rotate_z = false;
			break;
		case 2:
			self->angle = 0;
			self->z     = 15;
			self->rotate_x = true;
			self->rotate_y = false;
			self->rotate_z = false;
			break;
		case 3:
			self->z        = 0;
			self->angle    = 180;
			self->rotate_x = false;
			self->rotate_y = true;
			self->rotate_z = false;
			break;
	}
}
