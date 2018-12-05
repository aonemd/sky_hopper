#ifndef _game_status_h_
#define _game_status_h_

#include <stdio.h>
#include <string.h>
#include <time.h>
#include "stdbool.h"

#include "GL/freeglut.h"

typedef struct GameStatus {
	int     score;
	clock_t start_time;
	int     elapsed_minutes;
	int     elapsed_seconds;
	bool    paused;
} GameStatus;

GameStatus *GameStatus__create();
void GameStatus__render(GameStatus *self);
void GameStatus__update(GameStatus *self);
void _render_timer(int minutes, int seconds);
void _render_score(int score);

#endif
