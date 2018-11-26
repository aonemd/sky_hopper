#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

#include "GL/freeglut.h"
#include "GL/gl.h"

#include "texture_loader.h"
#include "road_block.h"
#include "character.h"

int oldTimeSinceStart = 0;

GLuint sky_texture_id, asphalt_texture_id;
RoadBlock *road[9];
Character *character;

void render_sky() {
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    GLUquadricObj* sphere = gluNewQuadric();
    gluQuadricOrientation(sphere, GLU_INSIDE);
    gluQuadricTexture(sphere, true);
    gluQuadricNormals(sphere, GLU_SMOOTH);
    glBindTexture(GL_TEXTURE_2D, sky_texture_id);
    glEnable(GL_CULL_FACE);
    gluSphere(sphere, 400, 100, 100);
    gluDeleteQuadric(sphere);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
}

void render() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	render_sky();

	for (int i = 0; i < 9; i++) {
		RoadBlock__render(road[i]);
	}

	Character__render(character);

	glFlush();
}

void update() {
	for (int i = 0; i < 9; i++) {
		RoadBlock__update(road[i]);
	}

	Character__update(character);

	glutPostRedisplay();
}

void handle_timer(int val) {
	(void) val;

	glutTimerFunc(5000, handle_timer, 0);
}

void handle_keyboard(unsigned char key, int mouse_x, int mouse_y) {
	(void) mouse_x;
	(void) mouse_y;

	switch(key) {
		case 27:
		case 'q':
			exit(0);
		case ' ':
			Character__jump_up(character);
			break;
		case 'd':
			Character__move_right(character);
			break;
		case 'a':
			Character__move_left(character);
			break;
	}
}

int main(int argc, char *argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);

	glutInitWindowSize(1000, 1000);
	glutInitWindowPosition(150, 150);
	glutCreateWindow("Sky Hopper");

	glutFullScreen();
	glutDisplayFunc(render);
	glutIdleFunc(update);
	glutTimerFunc(0, handle_timer, 0);
	glutKeyboardFunc(handle_keyboard);

	glEnable(GL_DEPTH_TEST);

	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
    gluPerspective(45.0f, 1000.0f/1000.0f, 0.1f, 800.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.0, 4.0, 15.0, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);

	// load textures
	sky_texture_id     = TextureLoader__load_bmp("assets/sky_day_1.bmp", false);
	asphalt_texture_id = TextureLoader__load_bmp("assets/asphalt.bmp", true);

	// initialize the road
	for (int i = 0; i < 9; i += 3) {
		road[i + 0] = RoadBlock__create(0 - 2, ((i + 0) * -15) - (2 * i), asphalt_texture_id);
		road[i + 1] = RoadBlock__create(0 - 2, ((i + 1) * -15) - (2 * i), asphalt_texture_id);
		road[i + 2] = RoadBlock__create(0 - 2, ((i + 2) * -15) - (2 * i), asphalt_texture_id);
	}

	// initialize the main character
	character = Character__create();

	glutMainLoop();

	return 0;
}
