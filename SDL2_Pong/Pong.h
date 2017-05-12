#ifndef PONG_H_INCLUDED
#define PONG_H_INCLUDED



#endif // PONG_H_INCLUDED



#include "Define.h"

typedef struct PongRacket{
    float x,y;
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

enum Collision {
    Top, Bottom, Right, Left, None
};

enum BOOL{
    True,False
};


//prototypes
void initPongGame (PongGame *myGame);
int initSDL(char *title, int xpos,int ypos,int width, int height,int flags,DisplayPongGame *myDisplay);

void handleEvents(int *isRunning, PongGame *myGame);
void HandleAI ();

void renderRackets(PongGame *myGame);
void renderLineSquares(PongGame *myGame, int width, int height, int positionX, int positionY, int colorR, int colorG, int colorB);
void renderCircle(PongGame *myGame, int R, int G, int B);
void renderPongGame (PongGame myGame);

enum Collision CheckCollisionBallWalls (PongGame myGame);
void HandleScore ();
void ResetBall (PongGame *myGame);
enum BOOL CheckCollisionBallRackets (PongGame myGame);
void BallMovement(PongGame *myGame);
void delay(unsigned int frameLimit);
void destroy(DisplayPongGame *myGame);
