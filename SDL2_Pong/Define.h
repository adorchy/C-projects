#ifndef DEFINE_H_INCLUDED
#define DEFINE_H_INCLUDED


// Include
#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <time.h>
#include <math.h>

// Constant Mathematics
#define PI 3.14159265358979323846

// Screen size
#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 780

// Ball
#define BALL_RADIUS 12.0
#define BOUNCE_WALL_ANGLE 45.0
#define BOUNCE_RACKET_ANGLE 45.0
#define BOUNCE_SPEED 1.2

// Paddle
#define PADDLE_SPEED 20.0
#define PADDLE_WIDTH 13
#define PADDLE_HEIGH 100

// Location of output text
#define COMPUTER_SCORE_X 10
#define COMPUTER_SCORE_Y 10
#define PLAYER_SCORE_X   150
#define PLAYER_SCORE_Y   10

#endif // DEFINE_H_INCLUDED
