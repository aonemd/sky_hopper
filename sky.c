#include "sky.h"

void Sky__render(GLuint texture_id) {
	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	GLUquadricObj* sphere = gluNewQuadric();
	gluQuadricOrientation(sphere, GLU_INSIDE);
	gluQuadricTexture(sphere, true);
	gluQuadricNormals(sphere, GLU_SMOOTH);
	glBindTexture(GL_TEXTURE_2D, texture_id);
	glEnable(GL_CULL_FACE);
	gluSphere(sphere, 400, 100, 100);
	gluDeleteQuadric(sphere);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}
