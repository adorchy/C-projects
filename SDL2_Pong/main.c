
#include "Pong.h"






int main(int argc, char *argv[])
{


    DisplayPongGame myGame;
    int isRunning;
    unsigned int frameLimit = SDL_GetTicks() + 16;
    Racket racket1;
    Racket racket2;
    PongBall ball;


    if(init("Pong",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,SCREEN_WIDTH,SCREEN_HEIGHT,SDL_WINDOW_SHOWN,&myGame,&ball)){
            isRunning=1;
    }else{
            fprintf(stdout,"Unable to initialize SDL (%s)\n",SDL_GetError());
            return EXIT_FAILURE;//si impossible d'init sdl
    }

    while(isRunning){

            //Pour intercepter événements click
            handleEvents(&isRunning,&racket1,&racket2);
            renderRackets(&myGame,&racket1,&racket2);
            RenderLineSquares (&myGame, 5, 20, 300, 300, 255, 255, 255);
            RenderCircle (&myGame,ball,255,255,255);


           // Gestion des 60 fps (1000ms/60 = 16.6 -> 16)
            delay(frameLimit);

            frameLimit = SDL_GetTicks() + 16;

    }

        destroy(&myGame); // free pointer

        SDL_Quit(); //free memory


    return EXIT_SUCCESS;
}

