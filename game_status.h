#ifndef _game_status_h_
#define _game_status_h_

#include <stdio.h>
#include <string.h>
#include <time.h>
#include "stdbool.h"

#include "GL/freeglut.h"

typedef struct GameStatus {
	int		level;
	int     score;
	clock_t start_time;
	int     elapsed_minutes;
	int     elapsed_seconds;
	bool    paused;
	bool	is_over;
} GameStatus;

GameStatus *GameStatus__create();
void GameStatus__render(GameStatus *self);
void GameStatus__update(GameStatus *self);
void GameStatus__reset();
void _render_timer(int minutes, int seconds);
void _render_score(int score);
void _render_game_over();

#endif
