#include <stdio.h>
#include "Jeu_classique.h"

int main(void) {
    printf("Bienvenue dans le jeu Mastermind !\n");
    
    char choix_utilisateur;

    char* opt0 = "0 : Quitter.";
    char* opt1 = "1 : Lancer une partie classique."; //on pourra rajouter d'autre option comme les règles du jeu, un autre mode (essais infini, variantes)...


    while(1){
        printf("Bonjour chère utilisatrice, cher utilisateur.\n \
        Plusieurs options s'offrent à vous. Faites votre choix.\n\n");

        printf("%s\n%s\n", opt0, opt1);

        scanf("%hhd", &choix_utilisateur);

        switch(choix_utilisateur){
            case 0 : 
                printf("Au revoir.\n");
                return 0;
            case 1 : 
                lancer_jeu_classique();
                printf("Merci d'avoir joué ! Au revoir.\n");
                return 0;   // dans ce cas la ou il n'y a qu'une seule partir on peut mettre un return 0 mais des qu'il faudra enchainer les partie mettre des sauvegarde et tout le jeu ne devra jamais s'aaréter on mettra un break...
            default :
                printf("Je n'ai pas compris votre choix.\n");
                break;
        }
    }

    return 0;
}