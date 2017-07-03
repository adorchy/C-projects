#ifndef LISTE_H_INCLUDED
#define LISTE_H_INCLUDED


#include <stdio.h>
#include <stdlib.h>
#include <string.h>



/* ---------- liste.h ----------- */
typedef struct ElementListe
{
  char *donnee;
  struct ElementListe *suivant;
} Element;

typedef struct ListeRepere
{
  Element *debut;
  Element *fin;
  int taille;
} Liste;

/* initialisation de la liste */
extern void initialisation (Liste * liste);


/* INSERTION */

/* insertion dans une liste vide */
extern int insListeVide (Liste * liste, char *donnee);

/* insertion au début de la liste */
extern int insDebutListe (Liste * liste, char *donnee);

/* insertion Ã a fin de la liste */
extern int insFinListe (Liste * liste, Element * courant, char *donnee);

/* insertition ailleurs */
extern int insListe (Liste * liste, char *donnee, int pos);


/* SUPPRESSION */

extern int suppDebut (Liste * liste);
extern int suppDansListe (Liste * liste, int pos);


extern int menu (Liste *liste,int *k);
extern void affiche (Liste * liste);
extern void detruire (Liste * liste);
/* -------- FIN liste.h --------- */

#endif // LISTE_H_INCLUDED
