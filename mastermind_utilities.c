#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#include "mastermind_utilities.h"


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
            printf("%s%c%s ", col(essais[i][j]), essais[i][j], RESET); //affiche la proposition de l'essai i
        }
        //affiche le nombre de bien placés et mal placés
        printf(" | Bien placés : %d | Mal placés : %d\n", reponse[i][0], reponse[i][1]);
    }
}


//fonction qui lit une proposition du joueur
void lire_proposition(char proposition[]) {
    //on limite la lecture à 4 caractères (%4s) pour éviter le stack smashing
    printf("Entrez votre proposition (%d lettres parmi %sR%s, %sV%s, %sJ%s, %sB%s, %sN%s, %sM%s), en majuscule et sans espaces : ",TAILLE_CODE, ROUGE, RESET, VERT, RESET, JAUNE, RESET, BLEU, RESET, NOIR, RESET, MAGENTA, RESET);
    scanf("%s", proposition); //lecture de la chaîne de caractères du joueur

    
    for (int i = 0; proposition[i] != '\0'; i++) { //on parcourt ce qui vient d'être écrit et on met tout en majuscule on s'arrête au caractère invisible de fin de la chaine
        proposition[i] = toupper(proposition[i]);   //on remplace
    }
    
    //on vide le tampon clavier au cas où l'utilisateur a écrit "ROUGE" (5 lettres)
    int c;  //variable temporaire pour stocker chaque caractère lu un par un
    while ((c = getchar()) != '\n' && c != EOF);    //vide le "buffer" (mémoire tampon) en mangeant tous les caractères restants jusqu'à la touche Entrée
}

void verifier_proposition(const char code[], const char proposition[], int *bien_places, int *mal_places) {
    *bien_places = 0;
    *mal_places = 0;
    
    //tableaux pour marquer les pions déjà comptés
    int code_utilise[TAILLE_CODE] = {0};
    int prop_utilise[TAILLE_CODE] = {0};

    //Test1 -> Bien placés (Noirs)
    for (int i = 0; i < TAILLE_CODE; i++) {
        if (proposition[i] == code[i]) {
            (*bien_places)++;
            code_utilise[i] = 1; //ce pion du code est "grillé"
            prop_utilise[i] = 1; //ce pion de la proposition est traité
        }
    }

    //Test2 -> Mal placés (Blancs)
    for (int i = 0; i < TAILLE_CODE; i++) {
        if (prop_utilise[i] == 1) 
            continue;   //si ce pion est déjà bien placé, on l'ignore

        for (int j = 0; j < TAILLE_CODE; j++) {
            //si le pion du code n'est pas utilisé ET que les couleurs correspondent
            if (code_utilise[j] == 0 && proposition[i] == code[j]) {
                (*mal_places)++;
                code_utilise[j] = 1; //on marque ce pion du code comme utilisé
                break; //on arrête de chercher pour ce pion de proposition j
            }
        }
    }
}