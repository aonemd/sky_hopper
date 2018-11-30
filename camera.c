#include "camera.h"

Camera *Camera__create() {
	Camera *camera = malloc(sizeof(*camera));

	camera->angle	 = 0;
	camera->rotate_x = true;
	camera->rotate_y = false;
	camera->rotate_z = false;

	return camera;
}

void Camera__render(Camera *self) {
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.0, 4.0, 15.0, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
	glRotatef(self->angle, self->rotate_x , self->rotate_y, self->rotate_z);
}

void Camera__toggle_top_view(Camera *self) {
	self->angle = (70 + 0) - self->angle;
}
