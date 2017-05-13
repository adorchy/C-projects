#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <time.h>


#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 780

// carré noire 300x300 sur fond blanc centré sur écran
// désssiner un triangle rouge sur fond noire 300x300 centré sur écran
// déssiner un carré de 300x300 divisé en 4 couleurs sur foind noire centré sur écran
// dessiner un carré de 4 bandes alternés (rouge, jaune,vert,bleu) 300x300 sur fond noire centré sur écran
// dessiner un échiquier



//Option de build dans les linker setting mettre les libSDL2main.a libSDL2.dll.a
//Dans search directory
//Option de build compiler mettre les include
//Option de build linker mettre les lib

//mettre dans build linker -lmingw32



typedef struct game{


     SDL_Window *g_pWindow;
     SDL_Renderer *g_pRenderer;
     SDL_Texture *g_ptexture;
     SDL_Surface *g_psurface;


}game;

typedef struct gameState{

    int g_bRunning;


}gameState;

typedef struct coordonnees{

    double x;
    double y;

}coordonnees;

//prototypes
int init(char *title, int xpos,int ypos,int width, int height,int flags,game *myGame);
void destroy(game *myGame);
void handleEvents(gameState *state,coordonnees *dep,coordonnees *dep2);
void delay(unsigned int frameLimit);

void render(game *myGame);
void drawInRenderer(game *myGame);
void drawInSurface(game *myGame);
void renderTexture(game *myGame,coordonnees *dep,coordonnees *dep2 );




int main(int argc, char *argv[])
{


     game myGame;
     gameState state;

     unsigned int frameLimit = SDL_GetTicks() + 16;
     coordonnees dep;
     coordonnees dep2;

     int choix=0;


     state.g_bRunning=1;

        //Create texture for drawing in texture or load picture
        myGame.g_ptexture=SDL_CreateTexture(myGame.g_pRenderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET,SCREEN_WIDTH,SCREEN_HEIGHT);

        while(state.g_bRunning){



            if(choix==0){

                printf("1:procedure render\n");
                printf("2:procedure DrawInsurface\n");
                printf("3:procedure DrawInRenderer\n");
                printf("4:procedure DrawInTexture\n");

                scanf("%i",&choix);

            }
            switch (choix){
                    case 1:
                            init("Chapter 1 setting up SDL",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,SCREEN_WIDTH,SCREEN_HEIGHT,SDL_WINDOW_SHOWN,&myGame);
                            render(&myGame);choix=0;
                            break;

                    case 2:
                            init("Chapter 1 setting up SDL",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,SCREEN_WIDTH,SCREEN_HEIGHT,SDL_WINDOW_SHOWN,&myGame);
                            drawInSurface(&myGame);choix=0;
                            break;
                    case 3:
                             init("Chapter 1 setting up SDL",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,SCREEN_WIDTH,SCREEN_HEIGHT,SDL_WINDOW_SHOWN,&myGame);
                             drawInRenderer(&myGame);choix=0;
                             break;

                    case 4:init("Chapter 1 setting up SDL",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,SCREEN_WIDTH,SCREEN_HEIGHT,SDL_WINDOW_SHOWN,&myGame);
                            while(state.g_bRunning){

                                handleEvents(&state,&dep,&dep2);
                                renderTexture(&myGame,&dep,&dep2);

                            }

                             break;
                    default:break;


            }

             system ("cls");


             // Gestion des 60 fps (1000ms/60 = 16.6 -> 16
            delay(frameLimit);
            frameLimit = SDL_GetTicks() + 16;

        }

        destroy(&myGame);

        SDL_Quit();


    return 0;
}


int init(char *title, int xpos,int ypos,int width, int height,int flags,game *myGame){


    myGame->g_pWindow=NULL;
    myGame->g_pRenderer=NULL;
    myGame->g_psurface=NULL;
    myGame->g_ptexture=NULL;


    //initialize SDL

    if(SDL_Init(SDL_INIT_EVERYTHING)>=0)
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

void render(game *myGame){


    //set to orange
    SDL_SetRenderDrawColor(myGame->g_pRenderer,254,123,2,255);

    //clear the window to orange
    SDL_RenderClear(myGame->g_pRenderer);

    //Show in the window
    SDL_RenderPresent(myGame->g_pRenderer);

    SDL_Delay(4000);

    destroy(myGame);

}

void drawInSurface(game *myGame){


            /* Creating the surface. */
            myGame->g_psurface = SDL_CreateRGBSurface(100, 100, 400, 32, 0, 0, 0, 0);

            /* Filling the surface with red color. */
            SDL_FillRect(myGame->g_psurface, NULL, SDL_MapRGB(myGame->g_psurface->format,
                                                              255, 0, 0));

            SDL_Texture *texture_tampon = SDL_CreateTextureFromSurface(myGame->g_pRenderer,
                                                                       myGame->g_psurface);
            SDL_SetRenderTarget(myGame->g_pRenderer, texture_tampon);

            SDL_Rect position;//position de debut du dessin dans screen
            position.x = 0;
            position.y = 0;
            SDL_QueryTexture(texture_tampon, NULL, NULL, &position.w, &position.h);
            SDL_RenderCopy(myGame->g_pRenderer,texture_tampon,NULL,&position);


            SDL_RenderPresent(myGame->g_pRenderer);

            SDL_Delay(4000);

            destroy(myGame);


}

//dessiner dans le renderer

void drawInRenderer(game *myGame){


       //Définition du rectangle a dessiner
        SDL_Rect rectangle;


        SDL_SetRenderDrawColor(myGame->g_pRenderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(myGame->g_pRenderer);

        SDL_SetRenderDrawColor(myGame->g_pRenderer, 255, 255, 255, SDL_ALPHA_OPAQUE);

        //Triangle
        SDL_RenderDrawLine(myGame->g_pRenderer, 320, 200, 300, 240);
        SDL_RenderDrawLine(myGame->g_pRenderer, 300, 240, 340, 240);
        SDL_RenderDrawLine(myGame->g_pRenderer, 340, 240, 320, 200);

        rectangle.x=100;//debut x
        rectangle.y=100;//debut y
        rectangle.w=10; //Largeur
        rectangle.h=100; //Hauteur

        //rectangle vide
        SDL_RenderDrawRect(myGame->g_pRenderer,&rectangle);

        rectangle.x=0;//debut x
        rectangle.y=0;//debut y
        rectangle.w=100; //Largeur
        rectangle.h=100; //Hauteur


        //rectangle plein
        SDL_RenderFillRect(myGame->g_pRenderer,&rectangle);

        //Affichage dans fenêtre
        SDL_RenderPresent(myGame->g_pRenderer);

        SDL_Delay(4000);

        destroy(myGame);


}



void renderTexture(game *myGame,coordonnees *dep,coordonnees *dep2 ) {

       //Définition du rectangle 1 a dessiner
        SDL_Rect rectangle;
        rectangle.x=0;//debut x
        rectangle.y=dep->y;//debut y
        rectangle.w=10; //Largeur
        rectangle.h=100; //Hauteur


        //Définition du rectangle 2 a dessiner
        SDL_Rect rectangle2;
        rectangle2.x=SCREEN_WIDTH-10;//debut x
        rectangle2.y=dep2->y;//debut y
        rectangle2.w=10; //Largeur
        rectangle2.h=100; //Hauteur


        //Draw in texture
        SDL_SetRenderDrawColor(myGame->g_pRenderer,255,0,0,255);
        SDL_SetRenderTarget(myGame->g_pRenderer, myGame->g_ptexture); //on modifie la texture

        SDL_RenderFillRect(myGame->g_pRenderer, &rectangle);
        SDL_RenderFillRect(myGame->g_pRenderer, &rectangle2);

        SDL_SetRenderTarget(myGame->g_pRenderer, NULL);// Dorénavent, on modifie à nouveau le renderer

        SDL_Rect position;//position de la texture dans screen
        position.x = 0;
        position.y = 0;
        SDL_QueryTexture(myGame->g_ptexture, NULL, NULL, &position.w, &position.h);
        SDL_RenderCopy(myGame->g_pRenderer,myGame->g_ptexture,NULL,&position);


         SDL_RenderPresent(myGame->g_pRenderer);

         SDL_SetRenderDrawColor(myGame->g_pRenderer,0,0,0,255);
         SDL_DestroyTexture(myGame->g_ptexture);
         SDL_RenderClear(myGame->g_pRenderer);




}

void destroy(game *myGame){

      //Destroy render
     if(myGame->g_pRenderer!=NULL)
        SDL_DestroyRenderer(myGame->g_pRenderer);

      //Destroy texture
     if(myGame->g_ptexture!=NULL)
        SDL_DestroyTexture(myGame->g_ptexture);

    //Destroy surface
     if(myGame->g_psurface!=NULL)
         SDL_FreeSurface(myGame->g_psurface);

    //Destroy window
    if(myGame->g_pWindow!=NULL)
        SDL_DestroyWindow(myGame->g_pWindow);

}


void handleEvents(gameState *state,coordonnees *dep,coordonnees *dep2){


    SDL_Event event;

    if(SDL_PollEvent(&event)){
        switch(event.type){
        case SDL_QUIT:
              state->g_bRunning=0;break;
        case SDL_KEYDOWN:
                        switch (event.key.keysym.sym)
                            {
                                case SDLK_LEFT:  dep->x--;dep2->x--; break;
                                case SDLK_RIGHT: dep->x++;dep2->x++; break;
                                case SDLK_UP:    dep->y--;dep2->y--; break;
                                case SDLK_DOWN:  dep->y++;dep2->y++; break;
                            }
                            break;

        case SDL_KEYUP:;break;

        default:break;

        }
    }


}

void delay(unsigned int frameLimit)
{
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


