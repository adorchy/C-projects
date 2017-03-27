/*
 * HeaderBattleShipGame.h
 *
 *  Created on: 27 mars 2017
 *      Author: Arnaud
 */

#ifndef HEADERBATTLESHIPGAME_H_
#define HEADERBATTLESHIPGAME_H_

#endif /* HEADERBATTLESHIPGAME_H_ */


#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define LIGNEMAX 10
#define LIGNEMIN 1
#define COLMAX 10
#define COLMIN 1
#define NBOAT 2
#define NFLEET 1



typedef struct Cellule {
	int ligne;
	int col;
}Cellule;

typedef struct Bateau {
	Cellule cell[NBOAT];
}Bateau;

typedef struct Flotte {
	Bateau bat[NFLEET];
}Flotte;

enum BOOL{
    True,False
};

enum Result{
    Stricken,Missed
};

void Intro ();
void InitGrid (char Grid[LIGNEMAX+1][COLMAX+1]);
void DisplayGrid (char Grid[LIGNEMAX+1][COLMAX+1]);
Cellule InitCell ();
int GetValidInt (int Max, int Min);
Cellule GetCoordinates ();
Cellule AIGetCoordinates ();
Cellule CoordinatesCheck (int player);
Bateau BoatInit (int player);
Flotte FleetInit (int player);
void InitBoatCounter (int *nbBoat);
enum BOOL CompareCell(Cellule mCell, Cellule pCell);
enum BOOL CompareCellBoat (Cellule Cell, Bateau Bat);
enum BOOL CompareCellFleet (Cellule Cell, Flotte Flot);
enum Result Attack(Flotte fleet, char Grid[LIGNEMAX+1][COLMAX+1], int player);
void Win (int playerNumb, int nbBoat);

