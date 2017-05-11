#ifndef PONG_H_INCLUDED
#define PONG_H_INCLUDED



#endif // PONG_H_INCLUDED



#include "Define.h"

typedef struct Racket{
    double x,y;

}Racket;

typedef struct Score{
    int player, enemy;

}score;

typedef struct PongBall{
    float px,py,sx,sy;
    int radius;

}PongBall;

typedef struct DisplayPongGame{

     SDL_Window *g_pWindow;
     SDL_Renderer *g_pRenderer;
     SDL_Surface *g_psurface;

}DisplayPongGame;


enum BOOL{
    True,False
};


//prototypes
int init(char *title, int xpos,int ypos,int width, int height,int flags,DisplayPongGame *myGame, PongBall *ball);
void destroy(DisplayPongGame *myGame);
void handleEvents(int *isRunning, Racket *racket1, Racket *racket2);
void delay(unsigned int frameLimit);

void renderRackets(DisplayPongGame *myGame,Racket *dep,Racket *dep2 );
void RenderLineSquares(DisplayPongGame *myGame, int width, int height, int positionX, int positionY, int colorR, int colorG, int colorB);
void RenderCircle(DisplayPongGame *myGame, PongBall ball, int R, int G, int B);
void MoveBall(PongBall Ball);
void HandleAI ();
void HandlePlayerScore ();
void HandleAIScore ();

enum BOOL CheckCollisionWalls ();
enum BOOL CheckCollisionRackets ();

