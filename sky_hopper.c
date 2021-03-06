#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>

#include "GL/freeglut.h"
#include "GL/gl.h"

#include "texture_loader.h"
#include "camera.h"
#include "game_status.h"
#include "sky.h"
#include "road.h"
#include "blockade.h"
#include "character.h"
#include "coinage.h"

GLuint sky_day_texture_id, sky_night_texture_id, asphalt_texture_id, steel_texture_id, brick_texture_id;
Camera *camera;
GameStatus *game_status;
Road *road;
Blockade *blockade;
Character *character;
Coinage *coinage;

void render() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	Camera__render(camera);
	GameStatus__render(game_status);
	if (game_status->level == 0) {
		Sky__render(sky_day_texture_id);
		Road__render(road, asphalt_texture_id);
	} else {
		Sky__render(sky_night_texture_id);
		Road__render(road, steel_texture_id);
	}
	Blockade__render(blockade);
	Character__render(character);
	Coinage__render(coinage);

	glFlush();
}

void update() {
	if (game_status->paused) {
		return;
	}

	Camera__update(camera, character->x, character->y);
	GameStatus__update(game_status);
	Road__update(road);
	Blockade__update(blockade);
	Character__update(character);
	Coinage__update(coinage);

	if (Road__character_intersects_gap(road, character)) {
		character->is_falling = true;
		game_status->is_over  = true;
	}

	if (Blockade__character_intersects_brick(blockade, character)) {
		game_status->is_over = true;
	}

	if(!game_status->is_over && Coinage__hide_intersecting_coins(coinage, character)) {
		game_status->score++;
	}

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
		case 'r':
			GameStatus__reset(game_status);
			Character__reset(character);
			break;
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
			game_status->paused = !game_status->paused;
			break;
		case 'v':
			Camera__toggle_view_mode(camera);
			break;
	}
}

void handle_mouse_click(int button, int state, int x, int y) {
	(void) state;
	(void) x;
	(void) y;

    if (button == GLUT_LEFT_BUTTON) {
		Character__jump_up(character);
    }
}

void handle_mouse_motion(int x, int y) {
	(void) y;

	if (x < 300) {
		Character__move_left(character);
	} else if (x > 700) {
		Character__move_right(character);
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
	glutMouseFunc(handle_mouse_click);
    glutPassiveMotionFunc(handle_mouse_motion);

	glEnable(GL_DEPTH_TEST);

	// lights on
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_NORMALIZE);
	glEnable(GL_SMOOTH);
	glShadeModel(GL_SMOOTH);

	GLfloat ambient_pos[] = { 0.2, 0.2, 0.2, 1.0 };
	GLfloat diffuse_pos[] = { 0.8, 0.8, 0.8, 1.0 };
	GLfloat specular_pos[] = {1.0, 1.0, 1.0, 1.0 };
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient_pos);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse_pos);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular_pos);

	GLfloat light_pos[] = { 0.5, 0.5, 0.0, 1.0 };
	glLightfv(GL_LIGHT0, GL_POSITION, light_pos);

	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
    gluPerspective(45.0f, 1000.0f/1000.0f, 0.1f, 800.0f);

	// load textures
	sky_day_texture_id   = TextureLoader__load_bmp("assets/sky_day_1.bmp", false);
	sky_night_texture_id = TextureLoader__load_bmp("assets/sky_night_1.bmp", false);
	asphalt_texture_id   = TextureLoader__load_bmp("assets/asphalt.bmp", true);
	steel_texture_id     = TextureLoader__load_bmp("assets/steel.bmp", true);
	brick_texture_id     = TextureLoader__load_bmp("assets/brick.bmp", true);

	camera      = Camera__create();
	game_status = GameStatus__create();
	road        = Road__create();
	blockade    = Blockade__create(brick_texture_id);
	character   = Character__create();
	coinage     = Coinage__create();

	glutMainLoop();

	return 0;
}
