#include "Pong.h"

void initPongGame (PongGame *myGame){

 myGame->ball.px=SCREEN_WIDTH/3;
 myGame->ball.py=SCREEN_HEIGHT/2;
 myGame->ball.sx=1.0;
 myGame->ball.sy=0.25;
 myGame->ball.radius=12;

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

        SDL_RenderPresent(myGame->displayGame.g_pRenderer); // update the screen with any rendering performed since the previous cal

        SDL_SetRenderDrawColor(myGame->displayGame.g_pRenderer,0,0,0,255); // black background
        SDL_RenderClear(myGame->displayGame.g_pRenderer);

}

void renderLineSquares(DisplayPongGame *displayGame, int width, int height, int positionX, int positionY, int colorR, int colorG, int colorB){

        int y;
        SDL_SetRenderDrawColor(displayGame->g_pRenderer,colorR,colorG,colorB,255);

        for (y=20; y<SCREEN_HEIGHT-20; y=y+30){

        SDL_Rect Rectangle;
        Rectangle.x=SCREEN_WIDTH/2-width/2;
        Rectangle.y=y;
        Rectangle.w=width;
        Rectangle.h=height;

        SDL_RenderFillRect(displayGame->g_pRenderer, &Rectangle);
        }

}

void renderCircle(DisplayPongGame *displayGame, PongBall ball, int R, int G, int B){
    SDL_SetRenderDrawColor(displayGame->g_pRenderer, R, G, B, SDL_ALPHA_OPAQUE);
    int radiusMin;

    int x, y = 0;
    int* xptr = &x;
    int* yptr = &y;

    for (radiusMin = ball.radius ; radiusMin>=1; radiusMin--){
        for (float angle = 0.0; angle<360; angle++){
            *xptr = ball.px-radiusMin * cos(angle);
            *yptr = ball.py-radiusMin * sin(angle);
            SDL_RenderDrawPoint(displayGame->g_pRenderer, x, y);
            }
    free (yptr);
    free (xptr);
    }
}

void renderPongGame (PongGame myGame){
    renderRackets(&myGame);
    renderLineSquares (&myGame.displayGame, 5, 20, 300, 300, 255, 255, 255);
    renderCircle (&myGame.displayGame,myGame.ball,255,255,255);

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

void handleEvents(int *isRunning, PongRacket *racket1, PongRacket *racket2){


    SDL_Event event;

    if(SDL_PollEvent(&event)){
        switch(event.type){
        case SDL_QUIT:
              *isRunning=0; break;
        case SDL_KEYDOWN:
                        switch (event.key.keysym.sym)
                            {
                                case SDLK_UP: if (racket1->y>0){racket1->y-=30;racket2->y-=30;} break;
                                case SDLK_DOWN:  if (racket1->y<SCREEN_HEIGHT-100) {racket1->y+=30;racket2->y+=30;} break;
                            }
                            break;

        case SDL_KEYUP:;break;

        default:break;

        }
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

void MoveBall(PongBall Ball){


}

//  Check if the ball hits a wall
enum BOOL CheckCollisionWalls (){
    return False;
};

//  Check if the ball hits a racket
enum BOOL CheckCollisionRackets (){
    return False;
};



