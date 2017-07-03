#include "File.h"

int main ()
{
  File *suite;
  char *nom;

  if ((suite = (File *) malloc (sizeof (File))) == NULL)
        return -1;
  if ((nom = (char *) malloc (50 * sizeof (char))) == NULL)
        return -1;

  initialisation (suite);

  printf ("Entrez un mot : ");
  scanf ("%s", nom);
  enFiler (suite, suite->fin, nom);
  printf ("La file (%d elements)\n",suite->taille);
  printf("\nDebut de la FILE [ ");
  affiche (suite);      /*le premier entré sera affiché */
  printf(" ] Fin de la FILE\n\n");

  printf ("Entrez un mot : ");
  scanf ("%s", nom);
  enFiler (suite, suite->fin, nom);
  printf ("La file (%d elements)\n",suite->taille);


  printf("\nDebut de la FILE [ ");
  affiche (suite);      /*le premier entré sera affiché */
  printf(" ] Fin de la FILE\n\n");

  printf ("Entrez un mot : ");
  scanf ("%s", nom);
  enFiler (suite, suite->fin, nom);
  printf ("La file (%d elements)\n",suite->taille);
  printf("\nDebut de la FILE [ ");
  affiche (suite);      /*le premier entré sera affiché */
  printf(" ] Fin de la FILE\n\n");


  printf ("\nLe premier entre (FirstInFirstOut) [ %s ] sera supprime",
                    file_donnee(suite));
  printf ("\nLe premier entre est supprime\n");
  deFiler (suite);              /* suppression de premier element entre */
  printf ("La file (%d elements): \n",suite->taille);
  printf("\nDebut de la FILE [ ");
  affiche (suite);
  printf(" ] Fin de la FILE\n\n");

  free(nom);
  free(suite);

  return 0;
}
