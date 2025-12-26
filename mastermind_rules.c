#include <stdio.h>
#include "mastermind_rules.h"

void afficher_regles() {
    printf("\n=======================================================\n");
    printf("             MANUEL DU MASTERMIND EN C                 \n");
    printf("=======================================================\n\n");  

    printf("1. BUT DU JEU\n");
    printf("   L'objectif est de trouver le Code Secret de 4 couleurs.\n");
    printf("   Apres chaque tentative, l'ordinateur vous donne des indices :\n");
    printf("   - Bien place (Noir)  : Couleur correcte et bien placee.\n");
    printf("   - Mal place (Blanc)  : Couleur correcte mais mal placee.\n\n");

    printf("2. COMMENT JOUER\n");
    printf("   Entrez votre proposition en utilisant la premiere lettre des couleurs.\n");
    printf("   Exemple : pour \033[31mRouge\033[0m-\033[33mJaune\033[0m-\033[34mBleu\033[0m-\033[32mVert\033[0m, tapez '\033[31mR\033[33mJ\033[34mB\033[32mV\033[0m'.\n");
    printf("   (Le jeu accepte les minuscules et les majuscules).\n\n");

    printf("3. SAUVEGARDE ET CHARGEMENT\n");
    printf("   - Pour Sauvegarder : Tapez simplement 'S' (ou 's') a la place d'une\n");
    printf("     couleur pendant la partie. Le jeu vous demandera un nom de fichier.\n");
    printf("   - Pour Charger : Choisissez l'option 2 dans le menu principal.\n\n");

    printf("4. MODES DE JEU (Via le Menu Avance)\n");
    printf("   Par defaut, le jeu est en mode Classique (4 couleurs, 10 essais).\n");
    printf("   Allez dans le 'Mode Avance' pour changer la difficulte :\n");
    printf("   - \033[32mFacile\033[0m        : 3 couleurs, 20 essais.\n");
    printf("   - \033[33mIntermediaire\033[0m : 4 couleurs, 15 essais.\n");
    printf("   - \033[31mDifficile\033[0m     : 5 couleurs, 10 essais.\n");
    printf("   - \033[35mExpert\033[0m        : 6 couleurs, 5 essais.\n\n");

    printf("5. CHRONOMETRE\n");
    printf("   Une option 'Temps Imparti' est disponible dans le menu avance.\n");
    printf("   Si le temps est ecoule avant la validation, l'essai est perdu !\n");
    printf("\n=======================================================\n");
}