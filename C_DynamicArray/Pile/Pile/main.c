
#include <stdio.h>
#include <stdlib.h>

typedef struct Element Element;
struct Element
{
    int entier;
    Element *suivant;
};

typedef struct Pile
{
    Element *sommet;
    int taille;
}Pile;

enum Bool{

    True,False


};


Pile *initialiser();
void empiler(Pile *pile, int val);
void afficherPile(Pile *pile);
int depiler(Pile *pile);
enum Bool pileVide(Pile *pile);


int main()
{

    int i;
    Pile *maPile=initialiser();
    for(i=0;i<=10;i++)
        empiler(maPile,i);

    printf("Taille de la pile :%d\n",maPile->taille);

    afficherPile(maPile);

      while(maPile->sommet!=NULL){

             depiler(maPile);
             afficherPile(maPile);

      }
      printf("Taille de la pile :%d\n",maPile->taille);


      if(pileVide(maPile)==True)
            printf("Pile vide");



    return 0;
}


Pile *initialiser()
{
    Pile *pile = malloc(sizeof(*pile));
    pile->sommet = NULL;
    pile->taille=0;
    return pile;
}

void empiler(Pile *pile, int val)
{
    Element *nouveau = malloc(sizeof(*nouveau));
    if (pile == NULL || nouveau == NULL)
    {
        exit(EXIT_FAILURE);
    }

    nouveau->entier = val;
    nouveau->suivant = pile->sommet;
    pile->sommet = nouveau;
    pile->taille++;
}



void afficherPile(Pile *pile)
{
    if (pile == NULL)
    {
        exit(EXIT_FAILURE);
    }
    Element *actuel = pile->sommet;

    while (actuel != NULL)
    {
        printf("%d\n", actuel->entier);
        actuel = actuel->suivant;
    }

    printf("\n");
}

int depiler(Pile *pile)
{
    if (pile == NULL)
    {
        exit(EXIT_FAILURE);
    }

    int nombreDepile = 0;
    Element *elementDepile = pile->sommet;

    if (pile != NULL && pile->sommet != NULL)
    {
        nombreDepile = elementDepile->entier;
        pile->sommet = elementDepile->suivant;
        free(elementDepile);
        pile->taille--;
    }

    return nombreDepile;
}

enum Bool pileVide(Pile *pile){


    enum Bool vide=False;


    if(pile->sommet==NULL){

        vide=True;

    }

    return vide;
}
