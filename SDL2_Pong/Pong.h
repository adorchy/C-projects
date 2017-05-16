#ifndef PONG_H_INCLUDED
#define PONG_H_INCLUDED



#endif // PONG_H_INCLUDED

#include "Define.h"

typedef struct PongPaddle{
    float x,y,dy;

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
void initFont (font *myFont);

int initSDL(char *title, int xpos,int ypos,int width, int height,int flags,PongGame *myGame);

void handleIntroEvents(int *introIsRunning, int *gameIsRunning, PongGame *myGame);
void introWindow(PongGame *myGame, font myFont);
void handleGameEvents(int *gameIsRunning, PongGame *myGame);
void handleAI(PongGame *myGame);
void playerPaddlesMove (PongGame *myGame);
void AIPaddlesMove (PongGame *myGame);

void renderPaddles(PongGame *myGame);
void renderBoundaryLine(PongGame *myGame, int colorR, int colorG, int colorB);
void renderCircle(PongGame *myGame, int R, int G, int B);
void renderAIScore (PongGame *myGame, font myFont);
void renderPlayerScore (PongGame *myGame, font myFont);
void renderPongGame (PongGame myGame, font myFont);

enum Collision CheckCollisionBallWalls (PongGame myGame);
void HandleScore (PongGame *myGame);
void checkVictoryConditions (int *gameIsRunning, PongGame *myGame);
void ResetBall (PongGame *myGame);
enum BOOL CheckCollisionBallPaddles (PongGame myGame);
void ballMovementAndScore(PongGame *myGame);
void delay(unsigned int frameLimit);
void loserWindow (PongGame *myGame, font myFont);
void winnerWindow (PongGame *myGame, font myFont);
void destroy(DisplayPongGame *myGame);
void releaseFont (font *myFont);
