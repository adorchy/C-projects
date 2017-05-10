#ifndef PONG_H_INCLUDED
#define PONG_H_INCLUDED



#endif // PONG_H_INCLUDED


#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <time.h>
#include <math.h>
#include "Define.h"


typedef struct VideoGame{

     SDL_Window *g_pWindow;
     SDL_Renderer *g_pRenderer;
     SDL_Texture *g_ptexture;
     SDL_Surface *g_psurface;

}VideoGame;

typedef struct gameState{

    int g_bRunning;


}gameState;

typedef struct Racket{

    double x;
    double y;

}Racket;

typedef struct score{
    int player, enemy;

}score;

typedef struct PongBall{
    int x,y,radius;


}PongBall;


//prototypes
int init(char *title, int xpos,int ypos,int width, int height,int flags,VideoGame *myGame, PongBall *ball);
void destroy(VideoGame *myGame);
void handleEvents(gameState *state,Racket *dep,Racket *dep2);
void delay(unsigned int frameLimit);

void render(VideoGame *myGame);
void drawInRenderer(VideoGame *myGame);
void drawInSurface(VideoGame *myGame);
void renderRackets(VideoGame *myGame,Racket *dep,Racket *dep2 );
void RenderLineSquares(VideoGame *myGame, int width, int height, int positionX, int positionY, int colorR, int colorG, int colorB);
void RenderCircle(VideoGame *myGame, PongBall ball, int R, int G, int B);




