#ifndef BATTLESHIP_H_INCLUDED
#define BATTLESHIP_H_INCLUDED

#include "Definition.h"


typedef struct Case{


        int ligne;
        int col;


}Case;

typedef struct Bateau{


    Case nCase[MAXCASE];



}Bateau;

typedef struct Flotte{

    Bateau nBateau[NBBATEAU];


}Flotte;

enum Bool{

    True,False

}Bool;

enum positionBateau{

    enLigne,enColonne,enDiag

}positionBateau;

enum etatBateau{


    toucher,couler


}etatBateau;


enum etatFlotte{


    aFlot,aSombrer

}etatFlotte;

enum etatJoueur{

    gagne, perd

}etatJoueur;






//Prototypes
extern void createCase(int l, int c,Case *mCase);
extern enum Bool cmpCase(Case mCase, Case tCase);
extern Bateau createBateau(Case nCase, int taille);
extern enum Bool controlCase(Bateau mBat, Case mCase);
extern enum Bool controlFlotte(Flotte f,Case mCase);
extern void fPlayer(Case mCase,Flotte *f);
extern void afficheDebug(Flotte f);
extern int tailleBateau(Flotte f,int numBateau);
extern void attaqueBateau(Flotte *f, Case mCase,int *numBateau);
extern enum etatBateau etatBat(Flotte f, int numBateau);
extern enum etatFlotte etatFlot(Flotte f);
extern void saisirAttaque(Case *mCase);
extern enum etatJoueur etatJ(Flotte f);
extern int validSaisiJoueur(char val[]);
extern void effaceEcran();
extern void saisieJoueur(char valLigne[], char valCol[]);
extern void initFlotteJoueur(Flotte *flotteJoueur1, Flotte *flotteJoueur2, Case mCase);
extern void minMax(Flotte f, int *minLigne, int *maxLigne, int *minCol, int *maxCol);

#endif // BATTLESHIP_H_INCLUDED
