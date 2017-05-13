#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>


#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 780

//Option de build dans les linker setting mettre les libSDL2main.a libSDL2.dll.a
//Dans search directory
//Option de build compiler mettre les include
//Option de build linker mettre les lib

//mettre dans build linker -lmingw32

typedef struct game{


     SDL_Window *g_pWindow;
     SDL_Renderer *g_pRenderer;
     SDL_Texture *g_ptexture;

}game;

typedef struct gameState{

    int g_bRunning;


}gameState;


//Prototypes
int init(char *title, int xpos,int ypos,int width,int height,int flags,game *myGame);
void handleEvents(gameState *state);
void delay(unsigned int frameLimit);
void destroy(game *myGame);



int main(int argc, char *argv[])
{

     game myGame;
     gameState state;

    //Pour les 60 fps
    unsigned int frameLimit = SDL_GetTicks() + 16;


    if(init("Chapter 1 setting up SDL",SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,SCREEN_WIDTH,SCREEN_HEIGHT,SDL_WINDOW_SHOWN,&myGame)){

                state.g_bRunning=1;


    }else{


            return EXIT_FAILURE;//si impossible d'init sdl

    }



    //Creation texture pour dessiner dans la texture (ou charger une image)
    myGame.g_ptexture=SDL_CreateTexture(myGame.g_pRenderer, SDL_PIXELFORMAT_RGBA8888,
                                         SDL_TEXTUREACCESS_TARGET,SCREEN_WIDTH,SCREEN_HEIGHT);

    while(state.g_bRunning){

            handleEvents(&state); //Pour intercepter événements click

           // Gestion des 60 fps (1000ms/60 = 16.6 -> 16)
            delay(frameLimit);
            frameLimit = SDL_GetTicks() + 16;

    }


        destroy(&myGame);

        SDL_Quit();




  return EXIT_SUCCESS;
}

/********************************************************************
BUT : INIT de SDL
ENTREES : titre, position fenetre, hauteur, largeur,flags gameObject
SORTIE : SDL init
*********************************************************************/

int init(char *title, int xpos,int ypos,int width,int height,int flags,game *myGame){


    //init SDL
    if(SDL_Init(SDL_INIT_EVERYTHING)>=0)
    {
            //creation fenetre
            myGame->g_pWindow=SDL_CreateWindow(title,xpos,ypos,width,height,flags);

            //si fenetre
            if(myGame->g_pWindow!=NULL){
                myGame->g_pRenderer=SDL_CreateRenderer(myGame->g_pWindow,-1,SDL_RENDERER_ACCELERATED);//creation rendu


            }


    }else{


        return 0;
    }

    return 1;


}

/********************************************************************
BUT : GESTION des events (input=>clavier)
ENTREES : gameStateObject
SORTIE : state
*********************************************************************/


void handleEvents(gameState *state){


    SDL_Event event; //gestion evenements

    if(SDL_PollEvent(&event)){
        switch(event.type){
        case SDL_QUIT: //ex clique croix
              state->g_bRunning=0;break;
        case SDL_KEYDOWN://pression sur touche clavier
                        switch (event.key.keysym.sym)
                            {
                                case SDLK_LEFT:  ; break; //fleche gauche
                                case SDLK_RIGHT: ; break; //fleche droite
                                case SDLK_UP:    ; break; //fleche haut
                                case SDLK_DOWN:  ; break; //fleche bas
                            }
                            break;

        case SDL_KEYUP:;break;

        default:break;

        }
    }


}
/********************************************************************
BUT : GESTION FrameRate 60fps(1 images/16ms => (1/60fps)*1000 =16.67ms)
ENTREES : FrameLimit
SORTIE : Delay=>frameLimit
*********************************************************************/

void delay(unsigned int frameLimit){

    // Gestion des 60 fps (images/seconde)
    unsigned int ticks = SDL_GetTicks();

    if (frameLimit < ticks)
    {
        return;
    }

    if (frameLimit > ticks + 16)
    {
        SDL_Delay(16);
    }

    else
    {
        SDL_Delay(frameLimit - ticks);
    }
}


/********************************************************************
BUT : Destruction de la SDL
ENTREES : GameObject
SORTIE : SDL Destroy
*********************************************************************/

void destroy(game *myGame){


    //Destruction texture
    if(myGame->g_ptexture!=NULL)
            SDL_DestroyTexture(myGame->g_ptexture);


    //Destuction du rendu
    if(myGame->g_pRenderer!=NULL)
           SDL_DestroyRenderer(myGame->g_pRenderer);


    //Destruction fenetre
    if(myGame->g_pWindow!=NULL)
        SDL_DestroyWindow(myGame->g_pWindow);

}
