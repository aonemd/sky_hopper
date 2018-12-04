#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

#include "GL/freeglut.h"
#include "GL/gl.h"

#include "texture_loader.h"
#include "camera.h"
#include "sky.h"
#include "road.h"
#include "blockade.h"
#include "character.h"
#include "coinage.h"

bool pause_scene = false;

GLuint sky_texture_id, asphalt_texture_id, brick_texture_id;
Camera *camera;
Road *road;
Blockade *blockade;
Character *character;
Coinage *coinage;

void render() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	Camera__render(camera);
	Sky__render(sky_texture_id);
	Road__render(road);
	Blockade__render(blockade);
	Character__render(character);
	Coinage__render(coinage);

	glFlush();
}

void update() {
	if (pause_scene) {
		return;
	}

	Road__update(road);
	Blockade__update(blockade);
	Character__update(character);
	Coinage__update(coinage);

	if (Road__character_intersects_gap(road, character)) {
		character->is_falling = true;
	}

	if (Blockade__character_intersects_brick(blockade, character)) {
		printf("DEAD!\n");
		/* TODO: Game me over */
	}

	Coinage__hide_intersecting_coins(coinage, character);

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
		case 'p':
			pause_scene = !pause_scene;
			break;
		case 'v':
			Camera__toggle_top_view(camera);
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

	// load textures
	sky_texture_id     = TextureLoader__load_bmp("assets/sky_day_1.bmp", false);
	asphalt_texture_id = TextureLoader__load_bmp("assets/asphalt.bmp", true);
	brick_texture_id   = TextureLoader__load_bmp("assets/brick.bmp", true);

	camera    = Camera__create();
	road      = Road__create(asphalt_texture_id);
	blockade  = Blockade__create(brick_texture_id);
	character = Character__create();
	coinage   = Coinage__create();

	glutMainLoop();

	return 0;
}
