/*
 ============================================================================
 Name        : Battleship Game
 1 player Vs AI
 */



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

void Intro (int playerNumb);
void InitGrid (char Grid[LIGNEMAX+1][COLMAX+1]);
void DisplayGrid (char Grid[LIGNEMAX+1][COLMAX+1]);
Cellule InitCell ();
int ParaAcq (int Max, int Min);
Cellule CellPara ();
Cellule AICellPara ();
Cellule CellParaCheck (int player);
Bateau BoatInit (int player);
Flotte FleetInit (int player);
void InitBoatCounter (int *nbBoat);
enum BOOL CompareCell(Cellule mCell, Cellule pCell);
enum BOOL CompareCellBat (Cellule Cell, Bateau Bat);
enum BOOL CompareCellFlot (Cellule Cell, Flotte Flot);
enum Result Attack(Flotte fleet, char Grid[LIGNEMAX+1][COLMAX+1], int player);
void Win (int playerNumb, int nbBoat);

/* Programme qui simule le jeu de la bataille navale.

 */
int main() {

	// Joueur
	int nbBoat1;  // Nombre de bateaux
	char PlayerGrid [LIGNEMAX+1][COLMAX+1];
	InitGrid (PlayerGrid);
	Intro (1);
	Flotte fleet1=FleetInit(1);
	InitBoatCounter (&nbBoat1);

	// AI
	srand (time(NULL));
	int nbBoat2;  // Nombre de bateaux
	char AIGrid [LIGNEMAX+1][COLMAX+1];
	InitGrid (AIGrid);
	Intro (2);
	Flotte fleet2=FleetInit(0);
	InitBoatCounter (&nbBoat2);


	while (nbBoat1>0 && nbBoat2>0){ // tant que les 2 joueurs ont encore 1 bateau
		printf ("Player 1 turn, %d boat left\n", nbBoat1);
		DisplayGrid (PlayerGrid);
		if (Attack (fleet2, PlayerGrid, 1)==Stricken){
			nbBoat2--;
			Win (1,nbBoat2);
		}
		printf ("AI turn, %d boat left\n", nbBoat2);
		if (Attack (fleet1, AIGrid, 0)==Stricken){
			nbBoat1--;
			Win (2,nbBoat1);
		}
	}

	return 0;
}

// Procédure dont la fonction est d'afficher un texte générique d'introduction
void Intro (int playerNumb){
	printf("Player %i\n", playerNumb);
	printf("Fleet formation\n");
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
int ParaAcq (int Max, int Min) {
	int isDigit=0;
	int para=-1;
	while (isDigit==0){
		scanf("%i",&para);
		if (para<Min || para>Max){
			fflush (stdin);
			printf ("incorrect parameters, please try again\n");
		} else {
			isDigit=1;
		}
	}

	return para;
}

// Fonction remplissage d'une cellule
// Utilise fonction d'initialisation d'une cellule et la fonction de saisie d'un entier
Cellule CellPara (){
	Cellule cellule=InitCell();
	printf ("Enter coordinates\n");
	printf ("Line: Enter an integer from 1 to 10\n");
	cellule.ligne=ParaAcq(LIGNEMAX, LIGNEMIN);
	printf ("Row: Enter an integer from  de 1 to 10\n");
	cellule.col=ParaAcq(COLMAX, COLMIN);

	return cellule;
}

// Fonction remplissage aléatoire d'une cellule, simule une AI
// Utilise fonction d'initialisation d'une cellule et la fonction de saisie d'un entier
Cellule AICellPara (){
	Cellule cellule=InitCell();
	cellule.ligne= rand() % LIGNEMAX + LIGNEMIN;
	cellule.col= rand() % COLMAX + COLMIN;
	return cellule;
}

// Fonction remplissage et de validation d'une cellule
Cellule CellParaCheck (int player){
	Cellule cellule;
	if (player==1){
		cellule=CellPara();
	} else {
		cellule=AICellPara();
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
	while (check==0){ // empêcher le joueur de choisir 2 fois la même position
		if (grid[cellule.ligne][cellule.col]=='-'){
			grid[cellule.ligne][cellule.col]=1;
			check=1;
			return cellule;
		} else {
			printf ("Error, coordinates already used\n");
			if (player==1){
				cellule=CellPara();
			}

			if (player==0){
				cellule=AICellPara();
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
		newbat.cell[i]=CellParaCheck(player);
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
enum BOOL CompareCellBat (Cellule Cell, Bateau Bat){
	int i;
	for (i=0;i<NBOAT;i++){
		if(CompareCell(Cell,Bat.cell[i])==True){
			return True;
		}
	}
	return False;
}

// Fonction qui vérifie si une cellule appartient à une flotte, cette fonction renvoie vrai ou faux
enum BOOL CompareCellFlot (Cellule Cell, Flotte Flot){
	int i;
	for (i=0;i<NFLEET;i++){
		if(CompareCellBat(Cell,Flot.bat[i])==True){
			return True;
		}
	}
	return False;
}

// Fonction permettant player d'attaquer
enum Result Attack(Flotte fleet, char Grid[LIGNEMAX+1][COLMAX+1], int player){
	printf ("Choose a cell to attack\n");
	Cellule Torpedo;
	if (player==1){ // 1 correspond au player
		Torpedo=CellPara();
	} else {
		Torpedo=AICellPara();
	}

	if (CompareCellFlot(Torpedo,fleet)==True){
		if (Grid[Torpedo.ligne][Torpedo.col]=='-'){ // empêcher de valider plusieur fois une touche à la même position
			printf("Stricken\n");
			printf("\n");
			Grid[Torpedo.ligne][Torpedo.col]='s';
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
