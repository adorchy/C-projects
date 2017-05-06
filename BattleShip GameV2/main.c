#include "BattleShip.h"


int main()
{

    Flotte flotteJoueur1;
    Flotte flotteJoueur2;
    Case mCase;//Pour test tir player
    int numBateau=0;
    int numJoueur=0;
    int valminLigne, valmaxLigne, valminCol, valmaxCol;


     /* initialize random seed: */
      srand (time(NULL));

      initFlotteJoueur(&flotteJoueur1,&flotteJoueur2,mCase);


    do{
        system("cls");

        printf("\nAffiche debug Bateau player 2\n");

         afficheDebug(flotteJoueur2);
         minMax(flotteJoueur2, &valminLigne, &valmaxLigne,&valminCol,&valmaxCol);
         printf("Flotte j2 Val min ligne : %d, val max ligne : %d\n",valminLigne,valmaxLigne);
         printf("Flotte j2 Val min col : %d, val max col : %d\n",valminCol,valmaxCol);

        if(etatFlot(flotteJoueur1)!=aSombrer){
                 numJoueur=1;
                 printf("Player %d a vous\n",numJoueur);
                 saisirAttaque(&mCase);



            if(controlFlotte(flotteJoueur2,mCase)==True){
                printf("Tir ok\n");
                attaqueBateau(&flotteJoueur2,mCase,&numBateau);

            }else{

                printf("Votre tir echoue\n");

            }
        }


        effaceEcran();

        printf("\nAffiche debug Bateau player 1\n");

        afficheDebug(flotteJoueur1);
        minMax(flotteJoueur1, &valminLigne, &valmaxLigne,&valminCol,&valmaxCol);
        printf("Flotte j1 Val min ligne : %d, val max ligne : %d\n",valminLigne,valmaxLigne);
        printf("Flotte j1 Val min col : %d, val max col : %d\n",valminCol,valmaxCol);

        if(etatFlot(flotteJoueur2)!=aSombrer){
                numJoueur=2;
                printf("Player %d a vous\n",numJoueur);
                saisirAttaque(&mCase);

            if(controlFlotte(flotteJoueur1,mCase)==True){
                printf("Tir ok\n");
                attaqueBateau(&flotteJoueur1,mCase,&numBateau);

            }else{

                printf("Votre tir echoue\n");

            }
        }

         puts("Appuyer sur enter pour continuer\n");
         getchar();
         fflush(stdin);


    }while(etatFlot(flotteJoueur1)!=aSombrer && etatFlot(flotteJoueur2)!=aSombrer);

     system("cls");



    etatJ(flotteJoueur1)==gagne? printf("joueur 1 gagne!!!\n"):printf("joueur 2 gagne");


    getchar();


    return 0;
}
