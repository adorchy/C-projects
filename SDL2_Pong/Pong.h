#ifndef PONG_H_INCLUDED
#define PONG_H_INCLUDED



#endif // PONG_H_INCLUDED



#include "Define.h"

typedef struct PongRacket{
    double x,y;
    int w,h;

}PongRacket;

typedef struct PongScore{
    int player, AI;

}PongScore;

typedef struct PongBall{
    float px, py, sx, sy;
    int radius;

}PongBall;

typedef struct DisplayPongGame{

     SDL_Window *g_pWindow;
     SDL_Renderer *g_pRenderer;
     SDL_Surface *g_psurface;

}DisplayPongGame;

typedef struct PongGame{
    DisplayPongGame displayGame;
    PongBall ball;
    PongRacket racket1;
    PongRacket racket2;
    PongScore score;

}PongGame;


enum BOOL{
    True,False
};


//prototypes
void initPongGame (PongGame *myGame);
int initSDL(char *title, int xpos,int ypos,int width, int height,int flags,DisplayPongGame *myDisplay);

void handleEvents(int *isRunning, PongRacket *racket1, PongRacket *racket2);
void delay(unsigned int frameLimit);

void renderRackets(PongGame *myGame);
void renderLineSquares(DisplayPongGame *myGame, int width, int height, int positionX, int positionY, int colorR, int colorG, int colorB);
void renderCircle(DisplayPongGame *myGame, PongBall ball, int R, int G, int B);
void renderPongGame (PongGame myGame);
void MoveBall(PongBall *ball);
void HandleAI ();
void HandleScore ();

enum BOOL CheckCollisionWalls ();
enum BOOL CheckCollisionRackets ();

void destroy(DisplayPongGame *myGame);
