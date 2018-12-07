#include "brick.h"

Brick *Brick__create(float x, float y, float z, GLuint texture_id) {
	Brick *brick = malloc(sizeof(*brick));

	brick->x          = x;
	brick->y          = y;
	brick->z          = z ;
	brick->original_z = z;
	brick->texture_id = texture_id;

	return brick;
}

void Brick__render(Brick *self) {
	glPushMatrix();
	glTranslatef(self->x, self->y, self->z);

	glScaled(1, 2, 1);

	glColor3f(1, 0, 0);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, self->texture_id);

	glBegin(GL_QUADS);
	// top
	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2f(1.0, 0.0);
	glVertex3f( -0.5f, 0.5f,0.5f);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(0.5f, 0.5f,0.5f);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(0.5f, 0.5f, -0.5f);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(-0.5, 0.5f, -0.5f);

	// right
	glNormal3f(1.0f, 0.0f, 0.0f);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(0.5f, -0.5f,0.5f);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(0.5f, -0.5f,-0.5f);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(0.5f, 0.5f, -0.5f);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(0.5, 0.5f, 0.5f);

	// left
	glNormal3f(-1.0f, 0.0f, 0.0f);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(-0.5f, -0.5f,0.5f);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(-0.5f, -0.5f,-0.5f);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(-0.5f, 0.5f, -0.5f);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(-0.5, 0.5f, 0.5f);

	// back
	glNormal3f(0.0f, 0.0f, -1.0f);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(-0.5f, -0.5f, -0.5f);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(0.5f, -0.5f,-0.5f);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(0.5f, 0.5f, -0.5f);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(-0.5, 0.5f, -0.5f);

	// front
	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(-0.5f, -0.5f, 0.5f);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(0.5f, -0.5f,0.5f);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(0.5f, 0.5f, 0.5f);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(-0.5, 0.5f, 0.5f);
	glEnd();

	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}

void Brick__update(Brick *self) {
	self->z += 0.09;

	if(self->z > 40) {
		self->z = self->original_z;
	}
}
