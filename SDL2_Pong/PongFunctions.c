#include "Pong.h"


int init(char *title, int xpos,int ypos,int width, int height,int flags,VideoGame *myGame, PongBall *ball){


    myGame->g_pWindow=NULL;
    myGame->g_pRenderer=NULL;
    myGame->g_psurface=NULL;
    ball->px=SCREEN_WIDTH/4;
    ball->py=SCREEN_HEIGHT/2;

    //initialize SDL

    if(SDL_Init(SDL_INIT_VIDEO)>=0) // Loading video (return 0 on success)
    {
            //if succeeded create our window
            myGame->g_pWindow=SDL_CreateWindow(title,xpos,ypos,width,height,flags);
            //if succeeded create window, create our render
            if(myGame->g_pWindow!=NULL){
                myGame->g_pRenderer=SDL_CreateRenderer(myGame->g_pWindow,-1,SDL_RENDERER_PRESENTVSYNC);

            }


    }else{

        return 0;

    }

    return 1;

}



void renderRackets(VideoGame *myGame,Racket *racket1,Racket *racket2 ) {

       //Définition du rectangle 1 a dessiner
        SDL_Rect rectangle;
        rectangle.x=0;//debut x
        rectangle.y=racket1->y;//debut y
        rectangle.w=20; //Largeur
        rectangle.h=100; //Hauteur


        //Définition du rectangle 2 a dessiner
        SDL_Rect rectangle2;
        rectangle2.x=SCREEN_WIDTH-20;//debut x
        rectangle2.y=racket2->y;//debut y
        rectangle2.w=20; //Largeur
        rectangle2.h=100; //Hauteur

        //Draw in texture
        SDL_SetRenderDrawColor(myGame->g_pRenderer,255,0,0,255); // set the color used for drawing operations


        SDL_RenderFillRect(myGame->g_pRenderer, &rectangle); // fill a rectangle on the current rendering target with the drawing color
        SDL_RenderFillRect(myGame->g_pRenderer, &rectangle2);

        SDL_RenderPresent(myGame->g_pRenderer); // update the screen with any rendering performed since the previous cal

        SDL_SetRenderDrawColor(myGame->g_pRenderer,0,0,0,255); // black background
        SDL_RenderClear(myGame->g_pRenderer);

}

void RenderLineSquares(VideoGame *myGame, int width, int height, int positionX, int positionY, int colorR, int colorG, int colorB){

        int y;
        SDL_SetRenderDrawColor(myGame->g_pRenderer,colorR,colorG,colorB,255);

        for (y=20; y<SCREEN_HEIGHT-20; y=y+30){

        SDL_Rect Rectangle;
        Rectangle.x=SCREEN_WIDTH/2-width/2;
        Rectangle.y=y;
        Rectangle.w=width;
        Rectangle.h=height;

        SDL_RenderFillRect(myGame->g_pRenderer, &Rectangle);
        }

}



void RenderCircle(VideoGame *myGame, PongBall ball, int R, int G, int B){
    SDL_SetRenderDrawColor(myGame->g_pRenderer, R, G, B, SDL_ALPHA_OPAQUE);
    int radiusMin;

    ball.radius = 12;
    int x, y = 0;
    int* xptr = &x;
    int* yptr = &y;

    for (radiusMin = ball.radius ; radiusMin>=1; radiusMin--){
        for (float angle = 0.0; angle<360; angle++){
            *xptr = ball.px-radiusMin * cos(angle);
            *yptr = ball.py-radiusMin * sin(angle);
            SDL_RenderDrawPoint(myGame->g_pRenderer, x, y);
            }
    free (yptr);
    free (xptr);
    }
}

void destroy(VideoGame *myGame){

      //Destroy render
     if(myGame->g_pRenderer!=NULL)
        SDL_DestroyRenderer(myGame->g_pRenderer);

    //Destroy surface
     if(myGame->g_psurface!=NULL)
         SDL_FreeSurface(myGame->g_psurface);

    //Destroy window
    if(myGame->g_pWindow!=NULL)
        SDL_DestroyWindow(myGame->g_pWindow);

}


void handleEvents(gameState *state, Racket *racket1, Racket *racket2){


    SDL_Event event;

    if(SDL_PollEvent(&event)){
        switch(event.type){
        case SDL_QUIT:
              state->isRunning=0; break;
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



