#ifndef PONG_H_INCLUDED
#define PONG_H_INCLUDED



#endif // PONG_H_INCLUDED



#include "Define.h"

typedef struct PongPaddle{
    float x,y;

}PongPaddle;

typedef struct PongScore{
    int player, AI;

}PongScore;

typedef struct PongBall{
    float px, py, sx, sy;
    float radius;

}PongBall;

typedef struct DisplayPongGame{

     SDL_Window *g_pWindow;
     SDL_Renderer *g_pRenderer;
     SDL_Texture *g_pTexture;
     SDL_Surface *g_pSurface;

}DisplayPongGame;

typedef struct PongGame{
    DisplayPongGame displayGame;
    PongBall ball;
    PongPaddle paddle1;
    PongPaddle paddle2;
    PongScore score;

}PongGame;

typedef struct font{

    TTF_Font *g_font;

}font;

enum Collision {
    Top, Bottom, Right, Left, None
};

enum BOOL{
    True,False
};


//prototypes
void initPongGame (PongGame *myGame);
void initFont (font *mFont);
int initSDL(char *title, int xpos,int ypos,int width, int height,int flags,DisplayPongGame *myDisplay);

void handleEvents(int *isRunning, PongGame *myGame);
void HandleAI ();

void renderPaddles(PongGame *myGame);
void renderBoundaryLine(PongGame *myGame, int colorR, int colorG, int colorB);
void renderCircle(PongGame *myGame, int R, int G, int B);
void renderAIScore (PongGame *myGame, font mFont);
void renderPlayerScore (PongGame *myGame, font mFont);
void renderPongGame (PongGame myGame, font mFont);

enum Collision CheckCollisionBallWalls (PongGame myGame);
void HandleScore (PongGame *myGame);
void ResetBall (PongGame *myGame);
enum BOOL CheckCollisionBallPaddles (PongGame myGame);
void ballMovement(PongGame *myGame);
void delay(unsigned int frameLimit);
void destroy(DisplayPongGame *myGame);
