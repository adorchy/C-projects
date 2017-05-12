
#include "Pong.h"






int main(int argc, char *argv[])
{


    PongGame myGame;
    int isRunning;
    unsigned int frameLimit = SDL_GetTicks() + 16;

    //Init myGame
    initPongGame (&myGame);

    //Init SDL
    if(initSDL("Pong",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,SCREEN_WIDTH,SCREEN_HEIGHT,SDL_WINDOW_SHOWN,&myGame.displayGame)){
            isRunning=1;
    }else{
            fprintf(stdout,"Unable to initialize SDL (%s)\n",SDL_GetError());
            return EXIT_FAILURE;
    }

    while(isRunning){

            //Pour intercepter événements click
            handleEvents(&isRunning,&myGame.racket1,&myGame.racket2);
            renderPongGame (myGame);
            MoveBall(&myGame.ball);


           // Gestion des 60 fps (1000ms/60 = 16.6 -> 16)
            delay(frameLimit);

            frameLimit = SDL_GetTicks() + 16;

    }

        destroy(&myGame.displayGame); // free pointer

        SDL_Quit(); //free memory


    return EXIT_SUCCESS;
}

