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
#include "sky.h"
#include "road.h"
#include "blockade.h"
#include "character.h"
#include "coinage.h"

int score = 0;
int elapsed_minutes = 0;
int elapsed_seconds = 0;

bool pause_scene = false;

clock_t start_time;

GLuint sky_texture_id, asphalt_texture_id, brick_texture_id;
Camera *camera;
Road *road;
Blockade *blockade;
Character *character;
Coinage *coinage;

void Timer__render() {
	char full_time[] = "Time: ";
	char time_string[512];
	sprintf(time_string, "%d:%d", elapsed_minutes, elapsed_seconds);
	strcat(full_time, time_string);

	glPushMatrix();
	glColor3f(1.0, 1.0, 0.0);
	glTranslatef(-6.5, 5.7, -2);
	glScaled(0.003, 0.003, 0.003);
	for(size_t i = 0; i < strlen(full_time); i++) {
		glutStrokeCharacter(GLUT_STROKE_ROMAN, full_time[i]);
	}
	glPopMatrix();
}

void Score__render(int score) {
	char full_score[] = "Score: ";
	char scoreString[512];
	sprintf(scoreString, "%d", score);
	strcat(full_score, scoreString);

	glPushMatrix();
	glColor3f(1.0, 1.0, 0.0);
	glTranslatef(-4, 5.7, -2);
	glScaled(0.003, 0.003, 0.003);
	for(size_t i = 0; i < strlen(full_score); i++) {
		glutStrokeCharacter(GLUT_STROKE_ROMAN, full_score[i]);
	}
	glPopMatrix();
}

void render() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	Camera__render(camera);
	Sky__render(sky_texture_id);
	Road__render(road);
	Blockade__render(blockade);
	Character__render(character);
	Coinage__render(coinage);
	Score__render(score);
	Timer__render();

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

	if(Coinage__hide_intersecting_coins(coinage, character)) {
		score++;
	}

	clock_t stop = clock();
	double elapsed = (double)(stop - start_time) * 1000.0 / CLOCKS_PER_SEC;
	elapsed_minutes = ((int)elapsed/1000 / 60) % 60;
	elapsed_seconds = (int)elapsed/1000 % 60;

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

	start_time = clock();

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
