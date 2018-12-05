#include "game_status.h"

GameStatus *GameStatus__create() {
	GameStatus *game_status = malloc(sizeof(*game_status));

	game_status->score           = 0;
	game_status->start_time      = clock();
	game_status->elapsed_minutes = 0;
	game_status->elapsed_seconds = 0;
	game_status->paused			 = false;

	return game_status;
}

void GameStatus__render(GameStatus *self) {
	_render_timer(self->elapsed_minutes, self->elapsed_seconds);
	_render_score(self->score);
}

void GameStatus__update(GameStatus *self) {
	clock_t stop = clock();
	double elapsed = (double)(stop - self->start_time) * 1000.0 / CLOCKS_PER_SEC;
	self->elapsed_minutes = ((int)elapsed/1000 / 60) % 60;
	self->elapsed_seconds = (int)elapsed/1000 % 60;
}

void _render_timer(int minutes, int seconds) {
	char full_time[] = "Time: ";
	char time_string[512];
	sprintf(time_string, "%d:%d", minutes, seconds);
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

void _render_score(int score) {
	char full_score[] = "Score: ";
	char score_string[512];
	sprintf(score_string, "%d", score);
	strcat(full_score, score_string);

	glPushMatrix();
	glColor3f(1.0, 1.0, 0.0);
	glTranslatef(-4, 5.7, -2);
	glScaled(0.003, 0.003, 0.003);
	for(size_t i = 0; i < strlen(full_score); i++) {
		glutStrokeCharacter(GLUT_STROKE_ROMAN, full_score[i]);
	}
	glPopMatrix();
}
