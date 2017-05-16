#include "Pong.h"

int main(int argc, char *argv[])
{


    PongGame myGame;
    int isRunning;
    font mFont;
    unsigned int frameLimit = SDL_GetTicks() + 16;

    //Init myGame
    initPongGame (&myGame);
    initFont (&mFont);

    //Init SDL
    if(initSDL("Pong",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,SCREEN_WIDTH,SCREEN_HEIGHT,SDL_WINDOW_SHOWN,&myGame.displayGame)){
            isRunning=1;
            srand (time(NULL)); // initialize random seed
    }else{
            fprintf(stdout,"Unable to initialize SDL (%s)\n",SDL_GetError());
            return EXIT_FAILURE;
    }
    //introScreen(&myGame, mFont);

    while(isRunning){

            //Pour intercepter événements click
            handleEvents(&isRunning,&myGame);
            handleAI(&myGame);
            renderPongGame (myGame, mFont);
            checkVictoryConditions (&isRunning, &myGame);
            ballMovementAndScore(&myGame);

            playerPaddlesMove (&myGame);
            AIPaddlesMove (&myGame);

           // Gestion des 60 fps (1000ms/60 = 16.6 -> 16)
            delay(frameLimit);

            frameLimit = SDL_GetTicks() + 16;

    }

        destroy(&myGame.displayGame); // free pointer

        TTF_Quit();
        SDL_Quit(); //free memory


    return EXIT_SUCCESS;
}
