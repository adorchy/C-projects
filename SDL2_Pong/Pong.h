#ifndef PONG_H_INCLUDED
#define PONG_H_INCLUDED



#endif // PONG_H_INCLUDED



#include "Define.h"


typedef struct VideoGame{

     SDL_Window *g_pWindow;
     SDL_Renderer *g_pRenderer;
     SDL_Surface *g_psurface;

}VideoGame;

typedef struct gameState{

    int isRunning;


}gameState;

typedef struct Racket{
    double x;
    double y;

}Racket;

typedef struct Score{
    int player, enemy;

}score;

typedef struct PongBall{
    int px,py,sx,sy,radius;

}PongBall;

enum BOOL{
    True,False
};


//prototypes
int init(char *title, int xpos,int ypos,int width, int height,int flags,VideoGame *myGame, PongBall *ball);
void destroy(VideoGame *myGame);
void handleEvents(gameState *state, Racket *racket1, Racket *racket2);
void delay(unsigned int frameLimit);

void renderRackets(VideoGame *myGame,Racket *dep,Racket *dep2 );
void RenderLineSquares(VideoGame *myGame, int width, int height, int positionX, int positionY, int colorR, int colorG, int colorB);
void RenderCircle(VideoGame *myGame, PongBall ball, int R, int G, int B);
void MoveBall(PongBall Ball);
void HandleAI ();
void HandlePlayerScore ();
void HandleAIScore ();

enum BOOL CheckCollisionWalls ();
enum BOOL CheckCollisionRackets ();




