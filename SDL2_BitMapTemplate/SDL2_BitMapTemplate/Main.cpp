#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "SDL.h"

#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 780

//Option de build dans les linker setting mettre les libSDL2main.a libSDL2.dll.a
//Dans search directory
//Option de build compiler mettre les include
//Option de build linker mettre les lib

//mettre dans build linker -lmingw32

typedef struct game {


	SDL_Window *g_pWindow;
	SDL_Renderer *g_pRenderer;
	SDL_Texture *g_texture;
	SDL_Surface *g_surface;


}game;

typedef struct gameState {

	int g_bRunning;


}gameState;


typedef struct coordonnees {

	double x;
	double y;



}coordonnees;


int init(char *title, int xpos, int ypos, int height, int width, int flags, game *myGame);
void handleEvents(gameState *state);
void delay(unsigned int frameLimit);
void destroy(game *myGame);


void renderTexture(game *myGame);



int main(int argc, char *argv[]) {

	game myGame;
	gameState state;

	//Pour les 60 fps
	unsigned int frameLimit = SDL_GetTicks() + 16;


	if (init("Chapter 1 setting up SDL", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN, &myGame)) {

		state.g_bRunning = 1;


	}
	else {

		return 1;//something's wrong

	}


	//Create texture for drawing in texture or load picture
	myGame.g_texture = SDL_CreateTexture(myGame.g_pRenderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, SCREEN_WIDTH, SCREEN_HEIGHT);

	while (state.g_bRunning) {

		handleEvents(&state);
		renderTexture(&myGame);


		// Gestion des 60 fps (1000ms/60 = 16.6 -> 16
		delay(frameLimit);
		frameLimit = SDL_GetTicks() + 16;




	}


	destroy(&myGame);

	SDL_Quit();




	return 0;
}


int init(char *title, int xpos, int ypos, int height, int width, int flags, game *myGame) {


	//initialize SDL

	if (SDL_Init(SDL_INIT_EVERYTHING) >= 0) {
		//if succeeded create our window
		myGame->g_pWindow = SDL_CreateWindow(title, xpos, ypos, height, width, flags);
		//if succeeded create window, create our render
		if (myGame->g_pWindow != NULL) {
			myGame->g_pRenderer = SDL_CreateRenderer(myGame->g_pWindow, -1, SDL_RENDERER_ACCELERATED);


		}


	}
	else {


		return 0;
	}




	return 1;


}

void handleEvents(gameState *state) {


	SDL_Event event;

	if (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_QUIT:
			state->g_bRunning = 0; break;
		case SDL_KEYDOWN:
			switch (event.key.keysym.sym) {
			case SDLK_LEFT:; break;
			case SDLK_RIGHT:; break;
			case SDLK_UP:; break;
			case SDLK_DOWN:; break;
			}
			break;

		case SDL_KEYUP:; break;

		default:break;

		}
	}


}

void renderTexture(game *myGame) {

	SDL_Rect rectangleDest;
	SDL_Rect rectangleSource;

	myGame->g_surface = SDL_LoadBMP("./assets/rider.bmp");//Chargement de l'image bitmap

	if (myGame->g_surface) {

		myGame->g_texture = SDL_CreateTextureFromSurface(myGame->g_pRenderer, myGame->g_surface); // Préparation du sprite
		SDL_FreeSurface(myGame->g_surface); // Libération de la ressource occupée par le sprite

		if (myGame->g_texture) {

			SDL_QueryTexture(myGame->g_texture, NULL, NULL, &rectangleSource.w, &rectangleSource.h);

			//Définition du rectangle dest pour dessiner Bitmap
			rectangleDest.x = 0;//debut x
			rectangleDest.y = 0;//debut y
			rectangleDest.w = rectangleSource.w; //Largeur
			rectangleDest.h = rectangleSource.h; //Hauteur



			SDL_RenderCopy(myGame->g_pRenderer, myGame->g_texture, NULL, &rectangleDest); // Copie du sprite grâce au SDL_Renderer



			SDL_RenderPresent(myGame->g_pRenderer); // Affichage

		}

		else {
			fprintf(stdout, "Échec de création de la texture (%s)\n", SDL_GetError());
		}



	}
	else {
		fprintf(stdout, "Échec de chargement du sprite (%s)\n", SDL_GetError());
	}



}

void delay(unsigned int frameLimit) {
	// Gestion des 60 fps (images/seconde)
	unsigned int ticks = SDL_GetTicks();

	if (frameLimit < ticks) {
		return;
	}

	if (frameLimit > ticks + 16) {
		SDL_Delay(16);
	}

	else {
		SDL_Delay(frameLimit - ticks);
	}
}




void destroy(game *myGame) {


	//Destroy texture
	if (myGame->g_texture != NULL)
		SDL_DestroyTexture(myGame->g_texture);


	//Destroy render
	if (myGame->g_pRenderer != NULL)
		SDL_DestroyRenderer(myGame->g_pRenderer);


	//Destroy window
	if (myGame->g_pWindow != NULL)
		SDL_DestroyWindow(myGame->g_pWindow);

}
