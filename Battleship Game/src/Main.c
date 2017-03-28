/*
 ============================================================================
 Name        : Battleship Game
This is the console executable, that makes use of the Flotte structure.
This act as the view in a MVC pattern, and is responsible for all user interaction.
For game logic see the Header.

 1 player VS AI
 */


#include "HeaderBattleShipGame.h"



int main() {

	// Player
	int PlayerBoat;
	char PlayerGrid [LIGNEMAX+1][COLMAX+1];
	InitGrid (PlayerGrid);
	Intro (1);
	Flotte fleet1=FleetInit(1);
	InitBoatCounter (&PlayerBoat);

	// AI
	srand (time(NULL));
	int AIBoat;
	char AIGrid [LIGNEMAX+1][COLMAX+1];
	InitGrid (AIGrid);
	Flotte fleet2=FleetInit(0);
	InitBoatCounter (&AIBoat);


	while (PlayerBoat>0 && AIBoat>0){ // As long as the player and AI have at least one boat
		printf ("Player 1 turn, %d boat left\n", PlayerBoat);
		DisplayGrid (PlayerGrid);
		if (Attack (fleet2, PlayerGrid, 1, &AIBoat)==Stricken){
			Win (1,AIBoat);
		}
		printf ("AI turn, %d boat left\n", AIBoat);
		if (Attack (fleet1, AIGrid, 0, &PlayerBoat)==Stricken){
			Win (2,PlayerBoat);
		}
	}

	return 0;
}

