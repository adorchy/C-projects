#include "Pong.h"

void initPongGame (PongGame *myGame){

//ball
 myGame->ball.px=SCREEN_WIDTH/3;
 myGame->ball.py=SCREEN_HEIGHT/2;
 myGame->ball.sx=5.0;
 myGame->ball.sy=2.0;
 myGame->ball.radius=BALL_RADIUS;

 //padle 1
 myGame->paddle1.h=PADDLE_HEIGH;
 myGame->paddle1.w=PADDLE_WIDTH;
 myGame->paddle1.x=0;
 myGame->paddle1.y=0;

 //padle 2
 myGame->paddle2.h=PADDLE_HEIGH;
 myGame->paddle2.w=PADDLE_WIDTH;
 myGame->paddle2.x=SCREEN_WIDTH-PADDLE_WIDTH;
 myGame->paddle2.y=0;


 //score
 myGame->score.AI=0;
 myGame->score.player=0;


}

void initFont (font *mFont){
    if(TTF_Init() == -1)
        {
            fprintf(stderr, "Erreur d'initialisation de TTF_Init : %s\n", TTF_GetError());
            exit(EXIT_FAILURE);
            }

    mFont->g_font=TTF_OpenFont("./assets/fonts/gameplay/Gameplay.ttf",65);

}

int initSDL(char *title, int xpos,int ypos,int width, int height,int flags,DisplayPongGame *displayGame){


    displayGame->g_pWindow=NULL;
    displayGame->g_pRenderer=NULL;
    displayGame->g_pTexture=NULL;
    displayGame->g_pSurface=NULL;

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
                                case SDLK_UP: if (myGame->paddle1.y>0){myGame->paddle1.y-=PADDLE_SPEED;myGame->paddle2.y-=PADDLE_SPEED;} break;
                                case SDLK_DOWN:  if (myGame->paddle1.y<SCREEN_HEIGHT-100) {myGame->paddle1.y+=PADDLE_SPEED;myGame->paddle2.y+=PADDLE_SPEED;} break;
                            }
                            break;

        case SDL_KEYUP:;break;

        default:break;

        }
    }


}

void renderPaddles(PongGame *myGame) {


       //D�finition du rectangle 1 a dessiner
        SDL_Rect rectangle;
        rectangle.x=myGame->paddle1.x;//debut x
        rectangle.y=myGame->paddle1.y;//debut y
        rectangle.w=myGame->paddle1.w; //Largeur
        rectangle.h=myGame->paddle1.h; //Hauteur


        //D�finition du rectangle 2 a dessiner
        SDL_Rect rectangle2;
        rectangle2.x=myGame->paddle2.x;//debut x
        rectangle2.y=myGame->paddle2.y;//debut y
        rectangle2.w=myGame->paddle2.w; //Largeur
        rectangle2.h=myGame->paddle2.h; //Hauteur

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

        for (y=10; y<SCREEN_HEIGHT-10; y=y+20){

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

void renderScore (PongGame *myGame, font mFont){

        char playerScore [1];
        sprintf (playerScore, "%i", myGame->score.player);
        //fprintf(stdout,"valeur buffer:%c%c\n", playerScore[0],playerScore[1]);
        SDL_Color fontColor={255,255,255};
        myGame->displayGame.g_pSurface=TTF_RenderText_Blended(mFont.g_font, playerScore, fontColor);//Charge la police


        if(myGame->displayGame.g_pSurface){


                //D�finition du rectangle pour blitter la chaine
                SDL_Rect rectangle;
                rectangle.x=SCREEN_WIDTH/2-100;//debut x
                rectangle.y=50;//debut y
                rectangle.w=60; //Largeur
                rectangle.h=60; //Hauteur


                 myGame->displayGame.g_pTexture = SDL_CreateTextureFromSurface(myGame->displayGame.g_pRenderer,myGame->displayGame.g_pSurface); // Pr�paration de la texture pour la chaine
                 SDL_FreeSurface(myGame->displayGame.g_pSurface); // Lib�ration de la ressource occup�e par le sprite


                 if(myGame->displayGame.g_pTexture){

                        SDL_RenderCopy(myGame->displayGame.g_pRenderer,myGame->displayGame.g_pTexture,NULL,&rectangle); // Copie du sprite gr�ce au SDL_Renderer
                 }
                 else{
                        fprintf(stdout,"�chec de cr�ation de la texture (%s)\n",SDL_GetError());
                }

                }
        else{
            fprintf(stdout,"�chec de creation surface pour chaine (%s)\n",SDL_GetError());
        }

}

void renderPongGame (PongGame myGame){
    renderPaddles(&myGame);
    renderLineSquares (&myGame, 5, 10, 300, 300, 255, 255, 255);
    renderCircle (&myGame,255,255,255);
    SDL_RenderPresent(myGame.displayGame.g_pRenderer); // update the screen with any rendering performed since the previous cal

    SDL_SetRenderDrawColor(myGame.displayGame.g_pRenderer,0,0,0,255); // black background
    SDL_RenderClear(myGame.displayGame.g_pRenderer);

}

//  Check if the ball hits a wall
enum Collision CheckCollisionBallWalls (PongGame myGame){
    //check if ball hit right side
    if (myGame.ball.px >=SCREEN_WIDTH-BALL_RADIUS){
        fprintf(stdout,"score right side\n");
        return Right;
    }
    //check if ball hit left side
    if (myGame.ball.px <=BALL_RADIUS){
        fprintf(stdout,"score left side\n");
        return Left;
    }
    //check if ball hit top
    if (myGame.ball.py <= BALL_RADIUS){
        fprintf(stdout,"collision on top\n");
        return Top;
    }
    //check if ball hit bottom
    if (myGame.ball.py >= SCREEN_HEIGHT-BALL_RADIUS){
        fprintf(stdout,"collision on bottom\n");
        return Bottom;
    }

    // if no collision
    return None;
};

void HandleScore (PongGame *myGame){
    if (CheckCollisionBallWalls (*myGame)== Right){
            myGame->score.player+=1;
            fprintf(stdout,"score Player:%i\n",myGame->score.player);
    }

    if (CheckCollisionBallWalls (*myGame)== Left){
            myGame->score.AI+=1;
            fprintf(stdout,"score AI:%i\n",myGame->score.AI);
            }

}

void ResetBall (PongGame *myGame){
    myGame->ball.px= SCREEN_WIDTH/3 + (rand () % 200);
    myGame->ball.py= SCREEN_HEIGHT/3 + (rand () % 200);
    myGame->ball.sx= (rand () % 2 + 4) + cos (rand () % 90);
    myGame->ball.sy= (rand () % 1 + 2) + cos (rand () % 90);

    if ((rand () % 2)==1) {
        myGame->ball.sx*=-1;
    }

    if ((rand () % 2)==1) {
        myGame->ball.sy*=-1;
    }
}


//  Check if the ball hits a racket
enum BOOL CheckCollisionBallPaddles (PongGame myGame){
    //Racket1
   if ((myGame.ball.px-myGame.ball.radius)<=myGame.paddle1.w &&
                        myGame.ball.py>=myGame.paddle1.y &&
                        myGame.ball.py<=(myGame.paddle1.y+myGame.paddle1.h)){
                            fprintf(stdout,"collision on left Racket\n");
                            return True;
                        }



    //Racket2

   if ((myGame.ball.px+myGame.ball.radius)>=(SCREEN_WIDTH-myGame.paddle1.w) &&
                    myGame.ball.py>=myGame.paddle2.y &&
                    myGame.ball.py<=(myGame.paddle2.y+myGame.paddle2.h)){
                        fprintf(stdout,"collision on right Racket\n");
                        return True;
                    }

    return False;
};


void ballMovement(PongGame *myGame){
    if (CheckCollisionBallWalls (*myGame)== Right ||
    CheckCollisionBallWalls (*myGame)== Left
    ){
        ResetBall (myGame);
    }
    // if ball hit Top or Bottom
    if (CheckCollisionBallWalls (*myGame)== Top ||
        CheckCollisionBallWalls (*myGame)== Bottom
        ){
            myGame->ball.sy=-myGame->ball.sy*BOUNCE_SPEED;
            //myGame->ball.sx*=cos (BOUNCE_WALL_ANGLE)*BOUNCE_SPEED;

            //speed cap
            if (myGame->ball.sx>BALL_RADIUS-2){
                    myGame->ball.sx=BALL_RADIUS-2;
                    }

            if (myGame->ball.sy<-BALL_RADIUS-2){
                  myGame->ball.sy=-BALL_RADIUS-2;
                  }
            }
    // if ball hit a racket
    if (CheckCollisionBallPaddles (*myGame)== True){
            myGame->ball.sx=-myGame->ball.sx*BOUNCE_SPEED;
            myGame->ball.sy*=1.3;

            //speed cap
            if (myGame->ball.sx<-BALL_RADIUS-2){
                    myGame->ball.sx=-BALL_RADIUS-2;
                    }
            //speed cap
            if (myGame->ball.sy>BALL_RADIUS-2){
                  myGame->ball.sy=BALL_RADIUS-2.0;
                  }
    }

    myGame->ball.px+=myGame->ball.sx;
    myGame->ball.py+=myGame->ball.sy;

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
     if(displayGame->g_pSurface!=NULL)
         SDL_FreeSurface(displayGame->g_pSurface);

    //Destroy texture
     if(displayGame->g_pTexture!=NULL)
         SDL_DestroyTexture(displayGame->g_pTexture);

    //Destroy window
    if(displayGame->g_pWindow!=NULL)
        SDL_DestroyWindow(displayGame->g_pWindow);

}
