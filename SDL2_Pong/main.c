#include "Pong.h"

int main(int argc, char *argv[])
{


    PongGame myGame;
    int gameIsRunning;
    int introIsRunning;
    font myFont;
    unsigned int frameLimit = SDL_GetTicks() + 16;

    //Init myGame
    initPongGame (&myGame);
    initFont (&myFont);

    //Init SDL
    if(initSDL("Pong",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,SCREEN_WIDTH,SCREEN_HEIGHT,SDL_WINDOW_SHOWN,&myGame.displayGame)){
            gameIsRunning=1;
            introIsRunning=1;
            srand (time(NULL)); // initialize random seed
    }else{
            fprintf(stdout,"Unable to initialize SDL (%s)\n",SDL_GetError());
            return EXIT_FAILURE;
    }

    while (introIsRunning){
        handleIntroEvents(&introIsRunning,&gameIsRunning,&myGame);
        introScreen(&myGame, myFont);
    }

    while(gameIsRunning){

            //Pour intercepter événements click
            handleGameEvents(&gameIsRunning,&myGame);
            handleAI(&myGame);
            renderPongGame (myGame, myFont);
            checkVictoryConditions (&gameIsRunning, &myGame);
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
