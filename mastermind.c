#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "mastermind.h"

// Définition des couleurs disponibles
const char COULEURS[NB_COULEURS] = {'R', 'V', 'J', 'B', 'N', 'M'}; // Rouge, Vert, Jaune, Bleu, Noir, Magenta

// Fonction qui génère un code secret aléatoire sans répétition
void generer_code(char code[]) {
    int utilisees[NB_COULEURS] = {0}; // Tableau pour suivre les couleurs déjà utilisées
    int i = 0;
    while (i < TAILLE_CODE) {
        int index = rand() % NB_COULEURS; // Choix aléatoire d'une couleur
        if (!utilisees[index]) {          // Si la couleur n'a pas encore été utilisée
            code[i++] = COULEURS[index];  // On l'ajoute au code
            utilisees[index] = 1;         // On la marque comme utilisée
        }
    }
}

// Fonction qui affiche l'historique des essais et les feedbacks
void afficher_historique(char essais[][TAILLE_CODE], int feedback[][2], int nb_essais) {
    printf("\nHistorique des essais :\n");
    for (int i = 0; i < nb_essais; i++) {
        printf("Essai %d : ", i + 1);
        for (int j = 0; j < TAILLE_CODE; j++) {
            printf("%c ", essais[i][j]); // Affiche les couleurs proposées
        }
        // Affiche le nombre de bien placés et mal placés
        printf(" | Bien placés : %d | Mal placés : %d\n", feedback[i][0], feedback[i][1]);
    }
}

// Fonction qui lit une proposition du joueur
void lire_proposition(char proposition[]) {
    printf("Entrez votre proposition (%d lettres parmi R, V, J, B, N, M) : ", TAILLE_CODE);
    scanf("%s", proposition); // Lecture de la chaîne de caractères
}

// Fonction qui compare la proposition au code secret
void comparer_codes(const char code[], const char proposition[], int *bien_places, int *mal_places) {
    int marque_code[TAILLE_CODE] = {0}, marque_prop[TAILLE_CODE] = {0}; // Marqueurs pour éviter les doubles comptages
    *bien_places = 0;
    *mal_places = 0;

    // Étape 1 : Vérifie les bien placés (bonne couleur, bonne position)
    for (int i = 0; i < TAILLE_CODE; i++) {
        if (proposition[i] == code[i]) {
            (*bien_places)++;
            marque_code[i] = marque_prop[i] = 1; // Marque comme utilisé
        }
    }

    // Étape 2 : Vérifie les mal placés (bonne couleur, mauvaise position)
    for (int i = 0; i < TAILLE_CODE; i++) {
        if (!marque_prop[i]) { // Si le pion n'était pas bien placé
            for (int j = 0; j < TAILLE_CODE; j++) {
                if (!marque_code[j] && proposition[i] == code[j]) {
                    (*mal_places)++;
                    marque_code[j] = 1; // Marque le pion du code comme utilisé
                    break;
                }
            }
        }
    }
}
