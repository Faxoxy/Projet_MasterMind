#include <stdio.h>
#include <stdlib.h>
#include "mastermind_utilities.h"
#include "mastermind_advanced.h"

void menu_avance() {
    int choix;
    printf("\n--- MODE AVANCE : CONFIGURATION ---\n");
    printf("1. \033[32mFacile\033[0m        (3 couleurs, 20 tentatives)\n");
    printf("2. \033[33mIntermediaire\033[0m (4 couleurs, 15 tentatives)\n");
    printf("3. \033[31mDifficile\033[0m     (5 couleurs, 10 tentatives)\n");
    printf("4. \033[35mExpert\033[0m        (6 couleurs, 5 tentatives)\n");
    printf("5. RESTAURER LE MODE \033[34mCLASSIQUE\033[0m  (4 couleurs, 10 tentatives)\n");
    printf("Votre choix : ");
    
    if (scanf("%d", &choix) != 1) { // le =! 1 si le scanf à échoué a lire un nombre entier
        int c; 
        while ((c = getchar()) != '\n' && c != EOF); //chasse d'eau - EOF = End Of File
        choix = 0;
    }

    switch(choix) {
        case 1: 
            nb_couleurs_partie = 3; //changement des variable propre au gameplay
            nb_essais_partie = 20; 
            printf(">> Mode \033[32m FACILE \033[0m active.\n");
            break;
        case 2: 
            nb_couleurs_partie = 4; 
            nb_essais_partie = 15; 
            printf(">> Mode \033[33m INTERMEDIAIRE \033[0m active.\n");
            break;
        case 3: 
            nb_couleurs_partie = 5; 
            nb_essais_partie = 10; 
            printf(">> Mode \033[31m DIFFICILE \033[0m active.\n");
            break;
        case 4: 
            nb_couleurs_partie = 6; 
            nb_essais_partie = 5; 
            printf(">> Mode \033[35m EXPERT \033[0m active.\n");
            break;
        case 5: 
            nb_couleurs_partie = 6; 
            nb_essais_partie = 10; 
            mode_chrono = 0; //on desactive le chrono
            printf(">> Mode \033[34m CLASSIQUE \033[0m restaure.\n");
            printf("Parametres remis a zero.\n");
            return; //on quitte directement pour ne pas demander le chrono
        default:
            printf("Choix invalide. La configuration precedente est conservee.\n");
            return; 
    }

    //configuration du chronometre (sauf si on a choisi le reset case 5 ou default)
    printf("\nActiver le chronometre ? (1: Oui, 0: Non) : ");
    scanf("%d", &mode_chrono);

    if (mode_chrono == 1) {
        printf("Temps imparti par tentative (secondes) : ");
        scanf("%d", &temps_imparti);
    }
    
    printf("\nConfiguration mise a jour !\n");
    printf("Selectionnez '1. Jouer' dans le menu principal pour lancer la partie que vous venez de configurer\n");
}