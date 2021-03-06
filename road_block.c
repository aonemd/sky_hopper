#include "road_block.h"

RoadBlock *RoadBlock__create(float y, float z) {
	RoadBlock *road_block = malloc(sizeof(*road_block));

	road_block->x          = 0;
	road_block->y          = y;
	road_block->z          = z ;
	road_block->original_z = z;

	return road_block;
}

void RoadBlock__render(RoadBlock *self, GLuint texture_id) {
	glPushMatrix();
	glTranslated(self->x, self->y, self->z);

	glPushMatrix();
	glScaled(8.0f, 0.1f, BLOCK_LENGTH);

	glColor3f(0, 0, 1);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture_id);

	glBegin(GL_QUADS);
	// top
	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2f(1.0, 0.0);
	glVertex3f( -0.5f, 0.5f, 0.5f);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(0.5f, 0.5f, 0.5f);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(0.5f, 0.5f, -0.5f);
	glTexCoord2f(0.0, 0.0);
	glVertex3f( -0.5, 0.5f, -0.5f);

	// bottom
	glNormal3f(0.0f, -1.0f, 0.0f);
	glVertex3f( -0.5f, -0.5f, 0.5f);
	glVertex3f(0.5f, -0.5f, 0.5f);
	glVertex3f(0.5f, -0.5f, -0.5f);
	glVertex3f( -0.5, -0.5f, -0.5f);

	// right
	glNormal3f(1.0f, 0.0f, 0.0f);
	glVertex3f(0.5f, -0.5f, 0.5f);
	glVertex3f(0.5f, -0.5f, -0.5f);
	glVertex3f(0.5f, 0.5f, -0.5f);
	glVertex3f(0.5, 0.5f, 0.5f);

	// left
	glNormal3f(-1.0f, 0.0f, 0.0f);
	glVertex3f(-0.5f, -0.5f, 0.5f);
	glVertex3f(-0.5f, -0.5f, -0.5f);
	glVertex3f(-0.5f, 0.5f, -0.5f);
	glVertex3f(-0.5, 0.5f, 0.5f);

	// back
	glNormal3f(0.0f, 0.0f, -1.0f);
	glVertex3f(-0.5f, -0.5f, -0.5f);
	glVertex3f(0.5f, -0.5f, -0.5f);
	glVertex3f(0.5f, 0.5f, -0.5f);
	glVertex3f(-0.5, 0.5f, -0.5f);

	// front
	glNormal3f(0.0f, 0.0f, 1.0f);
	glVertex3f(-0.5f, -0.5f, 0.5f);
	glVertex3f(0.5f, -0.5f, 0.5f);
	glVertex3f(0.5f, 0.5f, 0.5f);
	glVertex3f(-0.5, 0.5f, 0.5f);
	glEnd();

	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	glPopMatrix();
}

void RoadBlock__update(RoadBlock *self) {
	self->z += 0.09;
}
