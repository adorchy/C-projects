/*
 * BattleShipGameFunctions.c
 *
 *      Author: Arnaud
 */

#include "HeaderBattleShipGame.h"



void Intro (){

	printf ("\n\n");
	printf ("	 _           _   _   _           _     _\n");
	printf ("	| |         | | | | | |         | |   (_)\n");
	printf ("	| |__   __ _| |_| |_| | ___  ___| |__  _ _ __\n");
	printf ("	| '_ \\ / _` | __| __| |/ _ \\/ __| '_ \\| | '_ \\ \n");
	printf ("	| |_) | (_| | |_| |_| |  __/\\__ \\ | | | | |_) |\n");
	printf ("	|_.__/ \\__,_|\\__|\\__|_|\\___||___/_| |_|_| .__/\n");
	printf ("	                                        | |\n");
	printf ("	                                        |_|\n");

	printf ("   	  __ _  __ _ _ __ ___   ___ \n");
	printf ("   	 / _` |/ _` | '_ ` _ \\ / _ \\\n");
	printf ("   	| (_| | (_| | | | | | |  __/\n");
	printf ("   	 \\__, |\\__,_|_| |_| |_|\\___|\n");
	printf ("   	  __/ |\n");
	printf ("   	 |___/\n\n");


	printf("Player Fleet formation\n");


}

// Procédure dont la fonction est de créer une grille qui permet de vérifier si les coordonnées de 2 bateaux sont identiques et
// d'afficher les coordonnées de frappe
void InitGrid (char Grid[LIGNEMAX+1][COLMAX+1]){
	int i,j=0;
	for (i=0;i<11;i++){ //boucle des lignes
		for (j=0;j<11;j++){ //boucle des colonnes
			Grid[i][j]='-';
		}
	}
}

// Procédure dont la fonction est d'afficher un résumé des actions du joueur
void DisplayGrid (char Grid[LIGNEMAX+1][COLMAX+1]){
	int i,j=0;
	for (i=1;i<LIGNEMAX+1;i++){ //boucle des lignes
		for (j=1;j<COLMAX+1;j++){ //boucle des colonnes
			printf("%3c",Grid[i][j]);
		}
		printf ("\n"); //saut de ligne dès qu'une ligne complète
	}
}


// Fonction d'initialisation d'une cellule
Cellule InitCell () {
	Cellule newcellinit;
	newcellinit.col=0;
	newcellinit.ligne=0;
	return newcellinit;
}

// Fonction de saisie d'un entier
int GetValidInt (int Max, int Min) {
	int isValid=0;
	int para=-1;
	while (isValid==0){
		scanf("%i",&para);
		if (para<Min || para>Max){
			fflush (stdin);
			printf ("incorrect parameters, please try again\n");
		} else {
			isValid=1;
		}
	}

	return para;
}

// Fonction remplissage d'une cellule
// Utilise fonction d'initialisation d'une cellule et la fonction de saisie d'un entier
Cellule GetCoordinates (){
	Cellule cellule=InitCell();
	printf ("\nEnter coordinates\n");
	printf ("Line: Enter an integer from 1 to 10\n");
	cellule.ligne=GetValidInt(LIGNEMAX, LIGNEMIN);
	printf ("Row: Enter an integer from  de 1 to 10\n");
	cellule.col=GetValidInt(COLMAX, COLMIN);

	return cellule;
}

// Fonction remplissage aléatoire d'une cellule, simule une AI
// Utilise fonction d'initialisation d'une cellule et la fonction de saisie d'un entier
Cellule AIGetCoordinates (){
	Cellule cellule=InitCell();
	cellule.ligne= rand() % LIGNEMAX + LIGNEMIN;
	cellule.col= rand() % COLMAX + COLMIN;
	return cellule;
}

// Fonction remplissage et de validation d'une cellule
Cellule CoordinatesCheck (int player){
	Cellule cellule;
	if (player==1){
		cellule=GetCoordinates();
	} else {
		cellule=AIGetCoordinates();
	}

	static char grid [LIGNEMAX+1][COLMAX+1];
	static int initgrid=0;
	if (initgrid==0){ // initialisation de la grille la première fois que la fonction est lancée
		InitGrid (grid);
	}

	if (initgrid==NBOAT){ // Reinitialisation de la grille pour l'AI
		InitGrid (grid);
	}

	initgrid++;
	int check=0;
	while (check==0){ // empêcher de choisir 2 fois la même position
		if (grid[cellule.ligne][cellule.col]=='-'){
			grid[cellule.ligne][cellule.col]=1;
			check=1;
			return cellule;
		} else {
			printf ("Error, coordinates already used\n");
			if (player==1){
				cellule=GetCoordinates();
			}

			if (player==0){
				cellule=AIGetCoordinates();
			}
		}
	}

	return cellule;
}

// Fonction d'initialisation de 2 bateaux
Bateau BoatInit (int player){
	Bateau newbat;
	int i=0;
	for (i=0;i<NBOAT;i++){
		newbat.cell[i]=CoordinatesCheck(player);
	}
	return newbat;
}

// Fonction d'initialisation d'une flottes composé de 2 bateaux
Flotte FleetInit (int player){
	Flotte newflotte;
	int i=0;
	for (i=0;i<NFLEET;i++){
		newflotte.bat[i]=BoatInit(player);
	}
	return newflotte;
}

// Procédure initialisant nbBoat
void InitBoatCounter (int *nbBoat){
	*nbBoat=NBOAT;
}

// Fonction comparant 2 cellules, cette fonction renvoie vrai ou faux
enum BOOL CompareCell(Cellule mCell, Cellule pCell){

    if(mCell.col==pCell.col && mCell.ligne==pCell.ligne){
            return True;
        }
    return  False;
}

// Fonction qui vérifie si une cellule appartient à un bateau, cette fonction renvoie vrai ou faux
enum BOOL CompareCellBoat (Cellule Cell, Bateau Bat){
	int i;
	for (i=0;i<NBOAT;i++){
		if(CompareCell(Cell,Bat.cell[i])==True){
			return True;
		}
	}
	return False;
}

// Fonction qui vérifie si une cellule appartient à une flotte, cette fonction renvoie vrai ou faux
enum BOOL CompareCellFleet (Cellule Cell, Flotte Flot){
	int i;
	for (i=0;i<NFLEET;i++){
		if(CompareCellBoat(Cell,Flot.bat[i])==True){
			return True;
		}
	}
	return False;
}

// Fonction permettant player d'attaquer
enum Result Attack(Flotte fleet, char Grid[LIGNEMAX+1][COLMAX+1], int player, int *BoatNumber){
	printf ("Choose a cell to attack\n");
	Cellule Torpedo;
	if (player==1){ // 1 correspond au player
		Torpedo=GetCoordinates();
	} else {
		Torpedo=AIGetCoordinates();
	}

	if (CompareCellFleet(Torpedo,fleet)==True){
		if (Grid[Torpedo.ligne][Torpedo.col]=='-'){ // empêcher de valider plusieur fois une touche à la même position
			printf("Stricken\n");
			printf("\n");
			Grid[Torpedo.ligne][Torpedo.col]='s';
			*BoatNumber=*BoatNumber-1;
			return Stricken;
		}
	}
	printf("Missed\n");
	printf("\n");
	if (Grid[Torpedo.ligne][Torpedo.col]=='-'){
		Grid[Torpedo.ligne][Torpedo.col]='m';
	}
	return Missed;

}

// Procédure pour déterminer si un joueur à gagné.
void Win (int playerNumb, int nbBoat){
	if (nbBoat==0){
		printf ("Player %i won\n",playerNumb);
		exit  (0); // dans le cas ou le joueur 1 gagne, cela permet de terminer la boucle while et donc d'éviter au joueur 2 de continuer.
	}

}
