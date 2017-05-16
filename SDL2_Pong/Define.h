#ifndef DEFINE_H_INCLUDED
#define DEFINE_H_INCLUDED


// Include
#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <time.h>
#include <math.h>

// Miscellaneous
#define PI 3.14159265358979323846
#define SCORE_TO_WIN 12

// Screen size
#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 780

// Ball
#define BALL_RADIUS 12.0
#define BOUNCE_WALL_ANGLE 45.0
#define BOUNCE_RACKET_ANGLE 45.0
#define BOUNCE_SPEED 1.2

// Boundary line
#define LINE_WIDTH 5
#define LINE_HEIGHT 10

// Paddle
#define PADDLE_MOVE_INCREMENT 220
#define PADDLE_MAX_SPEED 7
#define PADDLE_WIDTH 13
#define PADDLE_HEIGHT 100

// Location of output text
#define SCORE_Y 50
#define SCORE_W 60
#define SCORE_H 60

#endif // DEFINE_H_INCLUDED
