#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#include "mastermind_utilities.h"

//initialisation des variables de configuration par defaut
int nb_essais_partie = 10;
int nb_couleurs_partie = 6; //par defaut toutes les couleurs on peut changer dans le mode avance (ex simple : 3 couleurs)
int mode_chrono = 0; //par defaut pas de chrono
int temps_imparti = 60; //par defaut si jamais il y a un chrono alors il est de 60 secondes

//definition des couleurs disponibles
const char COULEURS[MAX_COULEURS] = {'R', 'V', 'J', 'B', 'N', 'M'}; //Rouge, Vert, Jaune, Bleu, Noir, Magenta

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

//fonction pour generer un code secret aleatoire sans repetition avec srand(time(NULL))
void generer_code(char code[]) {
    int i = 0;
    while (i < TAILLE_CODE) {
        //on utilise nb_couleurs_partie au lieu de la constante fixe
        int index = rand() % nb_couleurs_partie; //choix aleatoire d'une couleur
        code[i] = COULEURS[index];  //on l'ajoute au code
        i = i+1;
    }
}

//fonction qui affiche l'historique des essais et les reponses
void afficher_historique(char essais[][TAILLE_CODE], int reponse[][2], int nb_essais) {
    printf("\nHistorique des essais :\n");
    for (int i = 0; i < nb_essais; i++) {
        printf("Essai %d : ", i + 1); //affiche le numero de l'essai
        for (int j = 0; j < TAILLE_CODE; j++) {
            printf("%s%c%s ", col(essais[i][j]), essais[i][j], RESET); //affiche la proposition de l'essai i
        }
        //affiche le nombre de bien places et mal places
        printf(" | Bien places : %d | Mal places : %d\n", reponse[i][0], reponse[i][1]);
    }
}


//fonction qui lit une proposition du joueur
int lire_proposition(char proposition[]) {
    time_t debut = time(NULL); //prise du temps de depart pour le calcul de temps

    //on limite la lecture à 4 caracteres pour eviter le stack smashing
    printf("Entrez votre proposition (%d lettres parmi ", TAILLE_CODE);
    //affichage dynamique des couleurs selon la difficulte
    for(int i=0; i<nb_couleurs_partie; i++) { //pas plus de couleurs que ce qui est attendu
        printf("%s%c%s ", col(COULEURS[i]), COULEURS[i], RESET);
    }
    
    if (mode_chrono) { //si il contient quelque chose : "1"
        printf("| %d sec max", temps_imparti); //on ecrit le chrono (le temps qu'il contient)
    }
    printf("), sans espaces : ");

    char buffer[100]; //variable tampon
    scanf("%s", buffer); //lecture de la chaîne de caracteres du joueur
    //on vide le tampon clavier au cas où l'utilisateur a ecrit "ROUGE" (5 lettres)
    int c;  //variable temporaire pour stocker chaque caractere lu un par un
    while ((c = getchar()) != '\n' && c != EOF);    //vide le "buffer" (memoire tampon)
    
    double secondes_ecoulees = difftime(time(NULL), debut); //calcul du temps que le joueur a mis a repondre

    //verification du temps ecoule si le chrono est actif
    if (mode_chrono) {
        if (difftime(time(NULL), debut) > temps_imparti) {
            printf("\nTEMPS ECOULE ! La tentative est comptee mais invalide.\n");
            //remplissage avec des X pour marquer l'echec
            for(int i=0; i<TAILLE_CODE; i++) proposition[i] = 'X';
            return 0; //retourne 0 pour indiquer l'echec temps
        }
        else {
            printf(">> Reponse donnee en %.0f secondes.\n", secondes_ecoulees); //affichage du temps de reponse en secondes
        }                                                                       //%.0f = double arrondi sans chiffre apres la virgule
    }

    //copie et mise en majuscule
    for (int i = 0; i < TAILLE_CODE; i++) { 
        proposition[i] = toupper(buffer[i]);   //on remplace ; toupper = convertion minuscule vers majuscule
    }

    //gestion de la sauvegarde
    if (proposition[0] == 'S') return 1;

    //verification si la couleur est autorisee dans ce niveau
    for (int i = 0; i < TAILLE_CODE; i++) {
        int trouve = 0;
        for (int j = 0; j < nb_couleurs_partie; j++) {
            if (proposition[i] == COULEURS[j]) trouve = 1;
        }
        if (proposition[i] == 'X') trouve = 1; //exception pour le timeout avec les X

        if (!trouve) { //si ça a echoue
            printf("Erreur : La couleur %c n'est pas disponible dans ce niveau.\n", proposition[i]);
            return lire_proposition(proposition); //appel recursif en cas d'erreur on retourne au debut
        }
    }
    
    return 1; //retourne 1 si tout est ok
}

void verifier_proposition(const char code[], const char proposition[], int *bien_places, int *mal_places) {
    *bien_places = 0;
    *mal_places = 0;
    
    //si la proposition est invalide (temps ecoule), on ne calcule rien
    if (proposition[0] == 'X') return;

    //tableaux pour marquer les pions dejà comptes et eviter de les recompter une deuxieme fois et avoir des doublons
    int code_utilise[TAILLE_CODE] = {0}; //les tableaux sont valable et pour le code secret et pour le code du joueur il peut y avoir des doublons dans les deux sens
    int prop_utilise[TAILLE_CODE] = {0};

    //test1 -> bien places (Noirs)
    for (int i = 0; i < TAILLE_CODE; i++) {
        if (proposition[i] == code[i]) {
            (*bien_places)++;
            code_utilise[i] = 1; //ce pion du code est "grille"
            prop_utilise[i] = 1; //ce pion de la proposition est traite
        }
    }

    //Test2 -> Mal places (Blancs)
    for (int i = 0; i < TAILLE_CODE; i++) {
        if (prop_utilise[i] == 1) 
            continue;   //si ce pion est dejà bien place on l'ignore on sort de la fonction

        for (int j = 0; j < TAILLE_CODE; j++) {
            //si le pion du code n'est pas utilise ET que les couleurs correspondent
            if (code_utilise[j] == 0 && proposition[i] == code[j]) {
                (*mal_places)++;
                code_utilise[j] = 1; //on marque ce pion du code comme utilise
                break; //on arrête de chercher pour ce pion de proposition j
            }
        }
    }
}