#include "Pong.h"

void initPongGame (PongGame *myGame){

 myGame->ball.px=SCREEN_WIDTH/3;
 myGame->ball.py=SCREEN_HEIGHT/2;
 myGame->ball.sx=3.0;
 myGame->ball.sy=4.0;
 myGame->ball.radius=BALL_RADIUS;

 //racket 1
 myGame->racket1.x=0;
 myGame->racket1.y=0;
 myGame->racket1.h=100;
 myGame->racket1.w=20;

 //racket 2
 myGame->racket2.x=SCREEN_WIDTH-20;
 myGame->racket2.y=0;
 myGame->racket2.h=100;
 myGame->racket2.w=20;

 //score
 myGame->score.AI=0;
 myGame->score.player=0;


}

int initSDL(char *title, int xpos,int ypos,int width, int height,int flags,DisplayPongGame *displayGame){


    displayGame->g_pWindow=NULL;
    displayGame->g_pRenderer=NULL;
    displayGame->g_psurface=NULL;

    //initialize SDL

    if(SDL_Init(SDL_INIT_VIDEO)>=0) // Loading video (return 0 on success)
    {
            //if succeeded create our window
            displayGame->g_pWindow=SDL_CreateWindow(title,xpos,ypos,width,height,flags);
            //if succeeded create window, create our render
            if(displayGame->g_pWindow!=NULL){
                displayGame->g_pRenderer=SDL_CreateRenderer(displayGame->g_pWindow,-1,SDL_RENDERER_PRESENTVSYNC);

            }


    }else{

        return 0;

    }

    return 1;

}

void handleEvents(int *isRunning, PongGame *myGame){


    SDL_Event event;

    if(SDL_PollEvent(&event)){
        switch(event.type){
        case SDL_QUIT:
              *isRunning=0; break;
        case SDL_KEYDOWN:
                        switch (event.key.keysym.sym)
                            {
                                case SDLK_UP: if (myGame->racket1.y>0){myGame->racket1.y-=10;myGame->racket2.y-=10;} break;
                                case SDLK_DOWN:  if (myGame->racket1.y<SCREEN_HEIGHT-100) {myGame->racket1.y+=10;myGame->racket2.y+=10;} break;
                            }
                            break;

        case SDL_KEYUP:;break;

        default:break;

        }
    }


}

void renderRackets(PongGame *myGame) {


       //Définition du rectangle 1 a dessiner
        SDL_Rect rectangle;
        rectangle.x=myGame->racket1.x;//debut x
        rectangle.y=myGame->racket1.y;//debut y
        rectangle.w=myGame->racket1.w; //Largeur
        rectangle.h=myGame->racket1.h; //Hauteur


        //Définition du rectangle 2 a dessiner
        SDL_Rect rectangle2;
        rectangle2.x=myGame->racket2.x;//debut x
        rectangle2.y=myGame->racket2.y;//debut y
        rectangle2.w=myGame->racket2.w; //Largeur
        rectangle2.h=myGame->racket2.h; //Hauteur

        //Draw in texture
        SDL_SetRenderDrawColor(myGame->displayGame.g_pRenderer,255,0,0,255); // set the color used for drawing operations


        SDL_RenderFillRect(myGame->displayGame.g_pRenderer, &rectangle); // fill a rectangle on the current rendering target with the drawing color
        SDL_RenderFillRect(myGame->displayGame.g_pRenderer, &rectangle2);

}

void renderLineSquares(PongGame *myGame,
                                        int width,
                                        int height,
                                        int positionX,
                                        int positionY,
                                        int colorR,
                                        int colorG,
                                        int colorB){

        int y;
        SDL_SetRenderDrawColor(myGame->displayGame.g_pRenderer,colorR,colorG,colorB,255);

        for (y=20; y<SCREEN_HEIGHT-20; y=y+30){

        SDL_Rect Rectangle;
        Rectangle.x=SCREEN_WIDTH/2-width/2;
        Rectangle.y=y;
        Rectangle.w=width;
        Rectangle.h=height;

        SDL_RenderFillRect(myGame->displayGame.g_pRenderer, &Rectangle);
        }

}

void renderCircle(PongGame *myGame, int R, int G, int B){
    SDL_SetRenderDrawColor(myGame->displayGame.g_pRenderer, R, G, B, SDL_ALPHA_OPAQUE);
    int radiusMin;

    int x, y = 0;

    for (radiusMin = myGame->ball.radius ; radiusMin>=1; radiusMin--){
        for (float angle = 0.0; angle<360; angle++){
            x = myGame->ball.px-radiusMin * cos(angle);
            y = myGame->ball.py-radiusMin * sin(angle);
            SDL_RenderDrawPoint(myGame->displayGame.g_pRenderer, x, y);
            }
    }
}

void renderPongGame (PongGame myGame){
    renderRackets(&myGame);
    renderLineSquares (&myGame, 5, 20, 300, 300, 255, 255, 255);
    renderCircle (&myGame,255,255,255);
    SDL_RenderPresent(myGame.displayGame.g_pRenderer); // update the screen with any rendering performed since the previous cal

    SDL_SetRenderDrawColor(myGame.displayGame.g_pRenderer,0,0,0,255); // black background
    SDL_RenderClear(myGame.displayGame.g_pRenderer);

}

//  Check if the ball hits a wall
enum Collision CheckCollisionBallWalls (PongGame myGame){
    //check if ball hit right side
    if (myGame.ball.px >=SCREEN_WIDTH-BALL_RADIUS){
        fprintf(stdout,"score right side (%s)\n",SDL_GetError());
        fprintf(stdout,"ball position x(%s):%f\n",SDL_GetError(),myGame.ball.px);
        return Right;
    }
    //check if ball hit left side
    if (myGame.ball.px <=BALL_RADIUS){
        fprintf(stdout,"score left side (%s)\n",SDL_GetError());
        return Left;
    }
    //check if ball hit top
    if (myGame.ball.py <= BALL_RADIUS){
        fprintf(stdout,"collision on top (%s)\n",SDL_GetError());
        return Top;
    }
    //check if ball hit bottom
    if (myGame.ball.py >= SCREEN_HEIGHT-BALL_RADIUS){
        fprintf(stdout,"collision on bottom (%s)\n",SDL_GetError());
        return Bottom;
    }

    // if no collision
    return None;
};

void ResetBall (PongGame *myGame){
    myGame->ball.px= rand() % SCREEN_WIDTH/2 + SCREEN_WIDTH/3;     // in the range SCREEN_WIDTH/2 to SCREEN_WIDTH/3
    myGame->ball.py= rand() % SCREEN_HEIGHT/2 + SCREEN_HEIGHT/3;
    myGame->ball.sx= (rand () % 2 + 4) + cos (rand () % 90);
    myGame->ball.sy= (rand () % 2) + cos (rand () % 90);

    if ((rand () % 2)==1) {
        myGame->ball.sx*=-1;
    }


    if ((rand () % 2)==1) {
        myGame->ball.sy*=-1;
    }


}


//  Check if the ball hits a racket
enum BOOL CheckCollisionBallRackets (PongGame myGame){
    return False;
};

void BallMovement(PongGame *myGame){
    if (CheckCollisionBallWalls (*myGame)== Right ||
    CheckCollisionBallWalls (*myGame)== Left
    ){
    ResetBall (myGame);
    }
    // if ball hit Top or Bottom
    else if (CheckCollisionBallWalls (*myGame)== Top ||
        CheckCollisionBallWalls (*myGame)== Bottom
        ){

        float angle = 30.0;
    /*
        myGame->ball.px+=myGame->ball.sx;
        myGame->ball.py+=myGame->ball.sy; */

    }
    // if ball hit a racket
    else if (CheckCollisionBallRackets (*myGame)== True){

    }
    // else the ball keeps its trajectory
    else {
    myGame->ball.px+=myGame->ball.sx;
    myGame->ball.py+=myGame->ball.sy;
    }

}

void delay(unsigned int frameLimit)
{
    // Gestion des 60 fps (images/seconde) soit environ 1 frame toutes les 16 ms
    unsigned int ticks = SDL_GetTicks();

    if (frameLimit < ticks)
    {
        return;
    }

    if (frameLimit > ticks + 16)
    {
        SDL_Delay(16);

    } else {
        SDL_Delay(frameLimit - ticks);
    }
}

void destroy(DisplayPongGame *displayGame){

      //Destroy render
     if(displayGame->g_pRenderer!=NULL)
        SDL_DestroyRenderer(displayGame->g_pRenderer);

    //Destroy surface
     if(displayGame->g_psurface!=NULL)
         SDL_FreeSurface(displayGame->g_psurface);

    //Destroy window
    if(displayGame->g_pWindow!=NULL)
        SDL_DestroyWindow(displayGame->g_pWindow);

}
