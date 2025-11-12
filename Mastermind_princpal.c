#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "mastermind.h"

// Fonction qui affiche les règles du jeu
void afficher_regles() {
    printf("\n=== RÈGLES DU MASTERMIND ===\n");
    printf("Le codeur choisit un code secret de 4 couleurs parmi : R, V, J, B, N, M\n");
    printf("Le joueur doit deviner ce code en 10 essais maximum.\n");
    printf("Feedback :\n");
    printf(" - Bien placé : bonne couleur à la bonne position\n");
    printf(" - Mal placé : bonne couleur mais mauvaise position\n");
    printf("Pas de répétition de couleur dans le code.\n\n");
}

// Fonction qui lance une partie de Mastermind
void jouer_partie() {
    char code[TAILLE_CODE]; // Code secret
    char essais[NB_ESSAIS_MAX][TAILLE_CODE]; // Tableau des propositions
    int feedback[NB_ESSAIS_MAX][2]; // Tableau des feedbacks
    int nb_essais = 0; // Compteur d'essais

    generer_code(code); // Génère le code secret
    printf("\nUne nouvelle partie commence !\n");

    // Boucle principale du jeu
    while (nb_essais < NB_ESSAIS_MAX) {
        char proposition[TAILLE_CODE + 1]; 
        lire_proposition(proposition); // Lecture de la proposition

        int bien_places = 0, mal_places = 0;
        comparer_codes(code, proposition, &bien_places, &mal_places); // Compare avec le code

        // Sauvegarde de l'essai et du feedback
        strncpy(essais[nb_essais], proposition, TAILLE_CODE);
        feedback[nb_essais][0] = bien_places;
        feedback[nb_essais][1] = mal_places;
        nb_essais++;

        afficher_historique(essais, feedback, nb_essais); // Affiche les essais précédents

        // Condition de victoire
        if (bien_places == TAILLE_CODE) {
            printf("Bravo ! Vous avez trouvé le code secret !\n");
            return;
        }
    }

    // Si le joueur n'a pas trouvé le code
    printf("Partie terminée ! Le code était : ");
    for (int i = 0; i < TAILLE_CODE; i++) {
        printf("%c ", code[i]);
    }
    printf("\n");
}

// Fonction principale avec menu interactif
int main() {
    srand(time(NULL)); // Initialise le générateur aléatoire

    int choix;
    do {
        // Affichage du menu principal
        printf("\n=== MENU PRINCIPAL ===\n");
        printf("1. Jouer une partie classique\n");
        printf("2. Afficher les règles\n");
        printf("3. Quitter\n");
        printf("Votre choix : ");
        scanf("%d", &choix);

        // Traitement du choix
        switch (choix) {
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
                printf("Choix invalide. Veuillez entrer 1, 2 ou 3.\n");
        }
    } while (choix != 3); // Boucle jusqu'à ce que l'utilisateur quitte

    return 0;
}
