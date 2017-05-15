#include "Pong.h"

void initPongGame (PongGame *myGame){

//ball
 myGame->ball.px=SCREEN_WIDTH/3;
 myGame->ball.py=SCREEN_HEIGHT/2;
 myGame->ball.sx=1.0;
 myGame->ball.sy=-0.5;
 myGame->ball.radius=BALL_RADIUS;

 //padle 1
 myGame->paddle1.x=0;
 myGame->paddle1.y=0;
 myGame->paddle1.dy=0;

 //padle 2
 myGame->paddle2.x=SCREEN_WIDTH-PADDLE_WIDTH;
 myGame->paddle2.y=0;
 myGame->paddle2.dy=0;

 //score
 myGame->score.AI=0;
 myGame->score.player=0;

}

void initFont (font *myFont){
    if(TTF_Init() == -1)
        {
            fprintf(stderr, "Erreur d'initialisation de TTF_Init : %s\n", TTF_GetError());
            exit(EXIT_FAILURE);
            }

    myFont->g_font=TTF_OpenFont("./assets/fonts/gameplay/Gameplay.ttf",65);

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
                    case SDLK_UP: myGame->paddle1.dy-=PADDLE_MOVE_INCREMENT; break;
                    case SDLK_DOWN: myGame->paddle1.dy+=PADDLE_MOVE_INCREMENT;break;
                    default:break;
                }
                break;

            case SDL_KEYUP:
                switch (event.key.keysym.sym)
                {
                   case SDLK_UP: myGame->paddle1.dy=myGame->paddle1.y;break;
                   case SDLK_DOWN: myGame->paddle1.dy=myGame->paddle1.y;break;
                   default:break;
                }

                break;

            default:break;
        }
    }

}

void handleAI(PongGame *myGame){

    if (myGame->ball.py==(myGame->paddle2.y+PADDLE_HEIGHT/2)){
            myGame->paddle2.dy=myGame->paddle2.y;
            }

/*
    if (myGame->ball.py>(myGame->paddle2.y+PADDLE_HEIGHT/3)&&
        myGame->ball.py<(myGame->paddle2.y+PADDLE_HEIGHT*2/3)){
            myGame->paddle2.dy=myGame->paddle2.y;
            }
*/
    if (myGame->ball.py>myGame->paddle2.y &&
        myGame->ball.py<(myGame->paddle2.y+PADDLE_HEIGHT)){
            if (myGame->ball.py<(myGame->paddle2.y+PADDLE_HEIGHT/2)){
                    myGame->paddle2.dy=myGame->paddle2.y;
                    myGame->paddle2.dy-=8;
            }

            if (myGame->ball.py>(myGame->paddle2.y+PADDLE_HEIGHT/2)){
                    myGame->paddle2.dy=myGame->paddle2.y;
                    myGame->paddle2.dy+=8;
            }
    }



    if (myGame->ball.py<(myGame->paddle2.y)){
            myGame->paddle2.dy=myGame->paddle2.y;
            myGame->paddle2.dy-=PADDLE_MOVE_INCREMENT;
            }


    if (myGame->ball.py>(myGame->paddle2.y+PADDLE_HEIGHT)){
            myGame->paddle2.dy=myGame->paddle2.y;
            myGame->paddle2.dy+=PADDLE_MOVE_INCREMENT;
            }

/*
    if (myGame->ball.py<(myGame->paddle2.y+PADDLE_HEIGHT/2)){
            myGame->paddle2.dy=myGame->paddle2.y;
            myGame->paddle2.dy-=PADDLE_SPEED/100;
            }

    if (myGame->ball.py>(myGame->paddle2.y+PADDLE_HEIGHT/2)){
            myGame->paddle2.dy=myGame->paddle2.y;
            myGame->paddle2.dy+=PADDLE_SPEED/100;
            }
*/
}

void playerPaddlesMove (PongGame *myGame){

    if (myGame->paddle1.y>myGame->paddle1.dy){
        if (myGame->paddle1.y>0){ // if paddle not at top screen
                myGame->paddle1.y-=4;
                }
    }

    if (myGame->paddle1.y<myGame->paddle1.dy){
        if (myGame->paddle1.y<SCREEN_HEIGHT-100){ // if paddle not at bottom screen
            myGame->paddle1.y+=4;
            }
    }
}

void AIPaddlesMove (PongGame *myGame){

    if (myGame->paddle2.y>myGame->paddle2.dy){
        if (myGame->paddle2.y>0){ // if paddle not at top screen
                myGame->paddle2.y-=4;
                }
    }

    if (myGame->paddle2.y<myGame->paddle2.dy){
        if (myGame->paddle2.y<SCREEN_HEIGHT-100){ // if paddle not at bottom screen
            myGame->paddle2.y+=4;
            }
    }
}

void renderPaddles(PongGame *myGame) {

       //Définition du rectangle 1 a dessiner
        SDL_Rect rectangle;
        rectangle.x=myGame->paddle1.x;//debut x
        rectangle.y=myGame->paddle1.y;//debut y
        rectangle.w=PADDLE_WIDTH; //Largeur
        rectangle.h=PADDLE_HEIGHT; //Hauteur

        //Définition du rectangle 2 a dessiner
        SDL_Rect rectangle2;
        rectangle2.x=myGame->paddle2.x;//debut x
        rectangle2.y=myGame->paddle2.y;//debut y
        rectangle2.w=PADDLE_WIDTH; //Largeur
        rectangle2.h=PADDLE_HEIGHT; //Hauteur

        //Draw in texture
        SDL_SetRenderDrawColor(myGame->displayGame.g_pRenderer,255,0,0,255); // set the color used for drawing operations

        SDL_RenderFillRect(myGame->displayGame.g_pRenderer, &rectangle); // fill a rectangle on the current rendering target with the drawing color
        SDL_RenderFillRect(myGame->displayGame.g_pRenderer, &rectangle2);

}

void renderBoundaryLine(PongGame *myGame, int colorR, int colorG, int colorB){

        int y;
        SDL_SetRenderDrawColor(myGame->displayGame.g_pRenderer,colorR,colorG,colorB,255);

        for (y=10; y<SCREEN_HEIGHT-10; y=y+15){

        SDL_Rect Rectangle;
        Rectangle.x=SCREEN_WIDTH/2-LINE_WIDTH/2;
        Rectangle.y=y;
        Rectangle.w=LINE_WIDTH;
        Rectangle.h=LINE_HEIGHT;

        SDL_RenderFillRect(myGame->displayGame.g_pRenderer, &Rectangle);
        }
}

void renderCircle(PongGame *myGame, int R, int G, int B){
    SDL_SetRenderDrawColor(myGame->displayGame.g_pRenderer, R, G, B, SDL_ALPHA_OPAQUE);
    int radiusMin;

    int x, y = 0;

    for (radiusMin = myGame->ball.radius ; radiusMin>=0; radiusMin--){
        for (float angle = 0.0; angle<360; angle++){
            x = myGame->ball.px-radiusMin * cos(angle);
            y = myGame->ball.py-radiusMin * sin(angle);
            SDL_RenderDrawPoint(myGame->displayGame.g_pRenderer, x, y);
            }
    }
}

void renderAIScore (PongGame *myGame, font myFont){
        char AIScoreArr [1];
        sprintf (AIScoreArr, "%i", myGame->score.AI);
        //fprintf(stdout,"score AI:%c%c\n", AIScoreArr[0],AIScoreArr[1]);
        SDL_Color fontColor={255,255,255};
        myGame->displayGame.g_pSurface=TTF_RenderText_Blended(myFont.g_font, AIScoreArr, fontColor);//Charge la police


        if(myGame->displayGame.g_pSurface){


                //Définition du rectangle pour blitter la chaine
                SDL_Rect playerScoreRect;
                playerScoreRect.x=SCREEN_WIDTH/2-SCORE_W+100;//start point (x)
                playerScoreRect.y=SCORE_Y;// start point (y)
                playerScoreRect.w=SCORE_W; //Width
                playerScoreRect.h=SCORE_H; //Height


                 myGame->displayGame.g_pTexture = SDL_CreateTextureFromSurface(myGame->displayGame.g_pRenderer,myGame->displayGame.g_pSurface);
                 SDL_FreeSurface(myGame->displayGame.g_pSurface);


                 if(myGame->displayGame.g_pTexture){
                        //  copy a portion of the texture to the current rendering target
                        SDL_RenderCopy(myGame->displayGame.g_pRenderer,myGame->displayGame.g_pTexture,NULL,&playerScoreRect); // Copie du sprite grâce au SDL_Renderer
                 }
                 else{
                        fprintf(stdout,"Failed to create texture (%s)\n",SDL_GetError());
                }

                }
        else{
            fprintf(stdout,"Failed to create surface (%s)\n",SDL_GetError());
        }

}

void renderPlayerScore (PongGame *myGame, font myFont){

        char playerScoreArr [1];
        sprintf (playerScoreArr, "%i", myGame->score.player);
        //fprintf(stdout,"score player:%c%c\n", playerScoreArr[0],playerScoreArr[1]);
        SDL_Color fontColor={255,255,255};
        myGame->displayGame.g_pSurface=TTF_RenderText_Blended(myFont.g_font, playerScoreArr, fontColor);//Charge la police


        if(myGame->displayGame.g_pSurface){


                //Définition du rectangle pour blitter la chaine
                SDL_Rect playerScoreRect;
                playerScoreRect.x=SCREEN_WIDTH/2-100;//start point (x)
                playerScoreRect.y=SCORE_Y;// start point (y)
                playerScoreRect.w=SCORE_W; //Width
                playerScoreRect.h=SCORE_H; //Height


                 myGame->displayGame.g_pTexture = SDL_CreateTextureFromSurface(myGame->displayGame.g_pRenderer,myGame->displayGame.g_pSurface);
                 SDL_FreeSurface(myGame->displayGame.g_pSurface);


                 if(myGame->displayGame.g_pTexture){
                        //  copy a portion of the texture to the current rendering target
                        SDL_RenderCopy(myGame->displayGame.g_pRenderer,myGame->displayGame.g_pTexture,NULL,&playerScoreRect); // Copie du sprite grâce au SDL_Renderer
                 }
                 else{
                        fprintf(stdout,"Failed to create texture (%s)\n",SDL_GetError());
                }

                }
        else{
            fprintf(stdout,"Failed to create surface (%s)\n",SDL_GetError());
        }

}

void renderPongGame (PongGame myGame, font myFont){
    renderPaddles(&myGame);
    renderBoundaryLine (&myGame, 255, 255, 255);
    renderCircle (&myGame,255,255,255);
    renderAIScore (&myGame, myFont);
    renderPlayerScore (&myGame, myFont);

    SDL_RenderPresent(myGame.displayGame.g_pRenderer); // update the screen with any rendering performed since the previous cal

    SDL_SetRenderDrawColor(myGame.displayGame.g_pRenderer,0,0,0,255); // black background
    SDL_RenderClear(myGame.displayGame.g_pRenderer);

}

//  Check if the ball hits a wall
enum Collision CheckCollisionBallWalls (PongGame myGame){
    //check if ball hit right side
    if (myGame.ball.px >=SCREEN_WIDTH-BALL_RADIUS){
        //fprintf(stdout,"score right side\n");
        return Right;
    }
    //check if ball hit left side
    if (myGame.ball.px <=BALL_RADIUS){
        //fprintf(stdout,"score left side\n");
        return Left;
    }
    //check if ball hit top
    if (myGame.ball.py <= BALL_RADIUS){
        //fprintf(stdout,"collision on top\n");
        return Top;
    }
    //check if ball hit bottom
    if (myGame.ball.py >= SCREEN_HEIGHT-BALL_RADIUS){
        //fprintf(stdout,"collision on bottom\n");
        return Bottom;
    }

    // if no collision
    return None;
};

void checkVictoryConditions (int *isRunning, PongGame *myGame){
    if (myGame->score.AI >=SCORE_TO_WIN){
        *isRunning=0;
    }

    if (myGame->score.player >=SCORE_TO_WIN){
        *isRunning=0;
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
   if ((myGame.ball.px-myGame.ball.radius)<=PADDLE_WIDTH &&
                        myGame.ball.py>=myGame.paddle1.y &&
                        myGame.ball.py<=(myGame.paddle1.y+PADDLE_HEIGHT)){
                            fprintf(stdout,"collision on left Racket\n");
                            return True;
                        }



    //Racket2

   if ((myGame.ball.px+myGame.ball.radius)>=(SCREEN_WIDTH-PADDLE_WIDTH) &&
                    myGame.ball.py>=myGame.paddle2.y &&
                    myGame.ball.py<=(myGame.paddle2.y+PADDLE_HEIGHT)){
                        fprintf(stdout,"collision on right Racket\n");
                        return True;
                    }

    return False;
};

void ballMovementAndScore(PongGame *myGame){
    // if ball hit right wall
    if (CheckCollisionBallWalls (*myGame)== Right){
        myGame->score.player+=1;
        ResetBall (myGame);
    }

    // if ball hit left wall
    if (CheckCollisionBallWalls (*myGame)== Left){
        myGame->score.AI+=1;
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

void delay(unsigned int frameLimit){
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
