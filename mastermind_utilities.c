#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "mastermind_utilities.h"

<<<<<<< HEAD

=======
>>>>>>> readme-branch
const char* col(char c) {
    switch(c) {
        case 'R': return ROUGE;
        case 'V': return VERT;
        case 'J': return JAUNE;
        case 'B': return BLEU;
        case 'N': return NOIR;
        case 'M': return MAGENTA;
        default: return RESET;
    }
}

//définition des couleurs disponibles
const char COULEURS[NB_COULEURS] = {'R', 'V', 'J', 'B', 'N', 'M'}; //Rouge, Vert, Jaune, Bleu, Noir, Magenta

//fonction pour génerer un code secret aléatoire sans répétition avec srand(time(NULL))
void generer_code(char code[]) {
    int i = 0;
    while (i < TAILLE_CODE) {
        int index = rand() % NB_COULEURS; //choix aléatoire d'une couleur
        code[i] = COULEURS[index];  //on l'ajoute au code
        i = i+1;
    }
}

//fonction qui affiche l'historique des essais et les reponses
void afficher_historique(char essais[][TAILLE_CODE], int reponse[][2], int nb_essais) {
    printf("\nHistorique des essais :\n");
    for (int i = 0; i < nb_essais; i++) {
        printf("Essai %d : ", i + 1); //affiche le numéro de l'essai
        for (int j = 0; j < TAILLE_CODE; j++) {
<<<<<<< HEAD
            printf("%s%c%s ", col(essais[i][j]), essais[i][j], RESET); //affiche la proposition de l'essai i
=======
            printf("%s%c%s ", col(essais[i][j]), essais[i][j], RESET);
>>>>>>> readme-branch
        }
        //affiche le nombre de bien placés et mal placés
        printf(" | Bien placés : %d | Mal placés : %d\n", reponse[i][0], reponse[i][1]);
    }
}

//fonction qui lit une proposition du joueur
void lire_proposition(char proposition[]) {
<<<<<<< HEAD
    printf("Entrez votre proposition (%d lettres parmi %sR%s, %sV%s, %sJ%s, %sB%s, %sN%s, %sM%s), en majuscule et sans espaces : ",TAILLE_CODE, ROUGE, RESET, VERT, RESET, JAUNE, RESET, BLEU, RESET, NOIR, RESET, MAGENTA, RESET);
=======
    printf("Entrez votre proposition (%d lettres parmi %sR%s, %sV%s, %sJ%s, %sB%s, %sN%s, %sM%s) : ", TAILLE_CODE, ROUGE, RESET, VERT, RESET, JAUNE, RESET, BLEU, RESET, NOIR, RESET, MAGENTA, RESET);
>>>>>>> readme-branch
    scanf("%s", proposition); //lecture de la chaîne de caractères du joueur
}

void verifier_proposition(const char code[], const char proposition[], int *bien_places, int *mal_places) {
    int pion_deja_utilise[TAILLE_CODE] ={0};
    for (int i = 0; i < TAILLE_CODE; i++) {
        if (proposition[i] == code[i]) {
            (*bien_places) = (*bien_places) + 1;
            pion_deja_utilise[i] = 1;
        }
        else {
            for (int j = 0; j < TAILLE_CODE; j++) {
                if (proposition[i] == code [j] && pion_deja_utilise[j] == 0) {
                    (*mal_places) = (*mal_places) + 1;
                    pion_deja_utilise[j] = 1;
                }
            }
        }
    }    
}