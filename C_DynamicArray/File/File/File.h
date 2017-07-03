#ifndef FILE_H_INCLUDED
#define FILE_H_INCLUDED

#include<stdio.h>
#include<stdlib.h>
#include<string.h>


typedef struct ElementListe{
  char *donnee;
  struct ElementListe *suivant;
} Element;

typedef struct ListeRepere{
  Element *debut;
  Element *fin;
  int taille;
} File;

/* initialisation */
extern void initialisation (File * suite);

/* ENFILER*/
extern int enFiler (File * suite, Element * courant, char *donnee);

/* DE_FILER*/
extern int deFiler (File * suite);

/* FirstInFirstOut */
#define file_donnee(suite) suite->debut->donnee

/* Affiche la file */
extern void affiche(File *suite);


#endif // FILE_H_INCLUDED
