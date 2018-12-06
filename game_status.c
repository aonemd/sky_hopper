#include "game_status.h"

GameStatus *GameStatus__create() {
	GameStatus *game_status = malloc(sizeof(*game_status));

	game_status->level           = 0;
	game_status->score           = 0;
	game_status->start_time      = clock();
	game_status->elapsed_minutes = 0;
	game_status->elapsed_seconds = 0;
	game_status->paused          = false;
	game_status->is_over         = false;
	game_status->highest_score   = _read_highest_score();

	return game_status;
}

void GameStatus__render(GameStatus *self) {
	_render_timer(self->elapsed_minutes, self->elapsed_seconds);
	_render_score(self->score);

	if (self->is_over) {
		_render_game_over(self->score, self->highest_score);
		if (self->score > self->highest_score) {
			_update_highest_score(self->score);
		}
	}
}

void GameStatus__update(GameStatus *self) {
	if(self->is_over) {
		return;
	}

	clock_t stop = clock();
	double elapsed = (double)(stop - self->start_time) * 1000.0 / CLOCKS_PER_SEC;
	self->elapsed_minutes = ((int)elapsed/1000 / 60) % 60;
	self->elapsed_seconds = (int)elapsed/1000 % 60;

	if (self->level == 0 && self->score >= 25) {
		self->level = 1;
	}
}

void GameStatus__reset(GameStatus *self) {
	self->level           = 0;
	self->score           = 0;
	self->start_time      = clock();
	self->elapsed_minutes = 0;
	self->elapsed_seconds = 0;
	self->paused          = false;
	self->is_over         = false;
	self->highest_score   = _read_highest_score();
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

void _render_game_over(int score, int highest_score) {
	glPushMatrix();
	glColor3f(1.0, 1.0, 0.0);
	glTranslatef(-3.0f, 4.0f, 0);
	glScaled(0.008f, 0.008f, 0.008f);

	char *loss_message = "You're Dead!";
	for(size_t i = 0; i < strlen(loss_message); i++)
		glutStrokeCharacter(GLUT_STROKE_ROMAN, loss_message[i]);

	glPopMatrix();

	glPushMatrix();
	glColor3f(0.0f, 0.69f, 0.40);
	glTranslated(-2.0f, 3.0f, 0);
	glScaled(0.003f, 0.003f, 0.003f);

	char *result_message;
	if (score > highest_score) {
		result_message = "New High Score!";
	} else {
		result_message = "Try Better Next Time";
	}
	for(size_t i = 0; i < strlen(result_message); i++)
		glutStrokeCharacter(GLUT_STROKE_ROMAN, result_message[i]);

	glPopMatrix();

	glPushMatrix();
	glColor3f(0.85f, 0.11f, 0.09f);
	glTranslatef(-1.5f, 2.0f, 0);
	glScaled(0.002f, 0.002f, 0.002f);

	char *replay_message = "Press R to replay";
	for(size_t i = 0; i < strlen(replay_message); i++)
		glutStrokeCharacter(GLUT_STROKE_ROMAN, replay_message[i]);

	glPopMatrix();
}

int _read_highest_score() {
	int highest_score = 0;
	FILE *file;

	file = fopen("score.txt", "r");
	if (file == NULL) {
		file = fopen("score.txt", "w");
		fprintf(file, "%d", highest_score);
	}

	fscanf(file, "%d", &highest_score);

	fclose(file);

	return highest_score;
}

void _update_highest_score(int highest_score) {
	FILE *file;

	file = fopen("score.txt", "w+");

	fprintf(file, "%d", highest_score);

	fclose(file);
}
