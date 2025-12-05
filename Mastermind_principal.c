#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "mastermind_utilities.h"

//affiche les règles du jeu
void afficher_regles() {
    printf("\n=-= RÈGLES DU MASTERMIND =-=\n");
    printf("Le codeur choisit un code secret de 4 couleurs parmi : %sR%s, %sV%s, %sJ%s, %sB%s, %sN%s, %sM%s\n", ROUGE, RESET, VERT, RESET, JAUNE, RESET, BLEU, RESET, NOIR, RESET, MAGENTA, RESET);
    printf("Le joueur doit deviner ce code en 10 essais maximum.\n");
    printf("reponse :\n");
    printf(" - Bien placé : bonne couleur à la bonne position\n");
    printf(" - Mal placé : bonne couleur mais mauvaise position\n\n");
}

//lance une partie de Mastermind
void jouer_partie() {   
    char code[TAILLE_CODE]; //code secret
    char essais[NB_ESSAIS_MAX][TAILLE_CODE]; //tableau pour sauvegarder les propositions à chaque essai
    int reponse[NB_ESSAIS_MAX][2]; //tableau pour sauvegarder les reponses obtenues à chaque essai
    int nb_essais = 0; //compteur d'essais

    generer_code(code); //générateur de code secret
    printf("\nUne nouvelle partie commence !\n");

    //partie de test ou il donne le code avant ; a enlever pour le jeu de base
    printf("\tcode secret a ne pas donner (uniquement pour les tests) : ");
    for (int i = 0; i < TAILLE_CODE; i++) {
        printf("%s%c%s ", col(code[i]), code[i], RESET);
    }
    printf("\n");

    //boucle principale du jeu
    while (nb_essais < NB_ESSAIS_MAX) {
        char proposition[TAILLE_CODE]; //tableau de caractère pour enregistrer la proposition du joueur
        lire_proposition(proposition); //lecture de la proposition

        int bien_places = 0;
        int mal_places = 0;
        verifier_proposition(code, proposition, &bien_places, &mal_places); //compare avec le code

        //sauvegarde de l'essai et de la reponse
        strncpy(essais[nb_essais], proposition, TAILLE_CODE); //permet de sauvegarder proposition dans le tableau essais avec une taille max
        reponse[nb_essais][0] = bien_places; //sauveagrde le nb de bien placés pour cette proposition
        reponse[nb_essais][1] = mal_places; //sauvegarde le nb de mal placés pour cette proposition
        nb_essais++;

        afficher_historique(essais, reponse, nb_essais); //affiche les essais précédents

        //condition de victoire
        if (bien_places == TAILLE_CODE) {
            printf("Bravo ! Vous avez trouvé le code secret !\n");
            return;
        }
    }

    //si le joueur n'a pas trouvé le code
    printf("Partie terminée ! Le code était : ");
    for (int i = 0; i < TAILLE_CODE; i++) {
        printf("%s%c%s ", col(code[i]), code[i], RESET);
    }
    printf("\n");
    return;
}

//main et menu interactif
int main() {
    srand(time(NULL)); //initialise le générateur aléatoire pour ne pas avoir deux fois la même valeur aléatoire

    int choix;
    do {
        //affichage du menu principal
        printf("\n--- MENU PRINCIPAL ---\n\n");
        printf("1. Jouer une partie classique\n");
        printf("2. Afficher les règles\n");
        printf("3. Quitter\n");
        printf("Votre choix : ");
        scanf("%d", &choix);
        
        //verification du choix, ne marche pas après une partie ni après les règles
        if (choix != 1 && choix !=2 && choix !=3){
            printf("Entrez un chox valide \n");
            return 1;
        }
        
        //choix
        switch(choix) {
            case 1:
                jouer_partie();
                break;
            case 2:
                afficher_regles();
                break;
            case 3:
                printf("A bientôt !\n");
                break;
            default:
                printf("Choix invalide. Entrez 1, 2 ou 3.\n");
        }
    } while (choix != 3); //boucle jusqu'à ce que l'utilisateur quitte, il ne peut pas sortir du menu si il est pas dans le jeu ou sorti

    return 0;
}