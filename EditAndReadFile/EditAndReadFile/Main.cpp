#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAILLE_MAX 1000


void lireFichier(FILE *Fichier, char[]);
void ecrireFichier(FILE *Fichier, char[]);
void viderBuffer();
int lire(char *chaine, int longueur);


//Les Fichiers en C

/*C string containing a file access mode. It can be:
"r"	read: Open file for input operations. The file must exist.
"w"	write: Create an empty file for output operations. If a file with the same name already exists, its contents are discarded and the file is treated as a new empty file.
"a"	append: Open file for output at the end of a file. Output operations always write data at the end of the file, expanding it.
Repositioning operations (fseek, fsetpos, rewind) are ignored. The file is created if it does not exist.
"r+"	read/update: Open a file for update (both for input and output). The file must exist.
"w+"	write/update: Create an empty file and open it for update (both for input and output).
If a file with the same name already exists its contents are discarded and the file is treated as a new empty file.
"a+"	append/update: Open a file for update (both for input and output) with all output operations writing data at the end of the file.
Repositioning operations (fseek, fsetpos, rewind) affects the next input operations, but output operations move the position back to the end of file. The file is created if it does not exist.
*/


int main() {


	FILE fichier;
	int choix = 0;
	char *chemin = "Fichier1.txt";


	do {

		printf("\n1: Ecrire fichier\n");
		printf("2: Lire fichier\n");
		printf("0: quitter\n");
		scanf("%d", &choix);

		switch (choix) {
		case 1:ecrireFichier(&fichier, chemin); break;// appel fct EcrireFichier
		case 2:lireFichier(&fichier, chemin); break; //appel fct lireFichier
		case 0:printf("Bye..."); break;
		default:printf("Mauvaise saisie\n"); break;

		}

		fflush(stdin);
		printf("Appuyer sur ENTER pour continuer...\n");
		getchar();
		system("cls");

	} while (choix != 0);


	return 0;
}



/*
Fonction lire fichier
Lecture fichier passer en parametre, utilisation primitive fgets
Affichage format� �cran*/
void lireFichier(FILE *Fichier, char *chemin) {

	char tabChaine[TAILLE_MAX];
	int errnum = 0;

	if ((Fichier = fopen(chemin, "r")) == NULL) {

		fprintf(stderr, "Erreur ouverture fichier :%s", strerror(errnum));
		//Ou perror

	}
	else {


		while (fgets(tabChaine, TAILLE_MAX, Fichier) != NULL) // On lit le fichier tant qu'on ne re�oit pas d'erreur (NULL)
		{
			printf("%s", tabChaine); // On affiche la cha�ne qu'on vient de lire
		}

	}
	fclose(Fichier);

}

/*fonction ViderBuffer
R�cup�ration du flux tantque diff \n et End of file*/
void viderBuffer() {
	int c = 0;
	while (c != '\n' && c != EOF) {
		c = getchar();
	}
}


/*fonction lire
lecture de la chaine pass�e en param�tre
Utilisation primitive fgets lecture du flux d'entr�e type input(clavier)
Prend les caract�res du flux tant que diff entr�*/

int lire(char *chaine, int longueur) {

	char *positionEntree = NULL;
	getchar();

	if (fgets(chaine, longueur, stdin) != NULL) {
		positionEntree = strchr(chaine, '\n');//Recherche un caract�re d'une cha�ne,
		if (positionEntree != NULL) {
			*positionEntree = '\0';
		}
		else {
			viderBuffer();
		}
		return 1;
	}
	else {
		viderBuffer();
		return 0;
	}
}

/* Fonction ecrire fichier
Ecriture dans fichier pass� en parametre
Primitive fputs, �criture de la chaine+ caractere espace analys� depuis fonction lire()
*/
void ecrireFichier(FILE *Fichier, char *chemin) {


	char tabChaine[TAILLE_MAX];
	int errnum = 0;
	printf("Saisir chaine\n");
	lire(tabChaine, TAILLE_MAX);

	if ((Fichier = fopen(chemin, "a")) == NULL) {

		fprintf(stderr, "Erreur ouverture fichier :%s", strerror(errnum));
	}
	else {

		fputs(tabChaine, Fichier);
		fputc('\n', Fichier);

	}

	fclose(Fichier);



}
