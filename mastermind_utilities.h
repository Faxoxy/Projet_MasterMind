#ifndef MASTERMIND_UTILITIES_H
#define MASTERMIND_UTILITIES_H

#include <stdio.h> 

//constantes du jeu (LIMITES TECHNIQUES)
#define MAX_ESSAIS_MEMOIRE 30  //taille maximale du tableau en memoire
#define TAILLE_CODE 4          //longueur du code secret (fixe)
#define MAX_COULEURS 6         //nombre maximum de couleurs disponibles

//variables "globales" de configuration (accessibles partout)
extern int nb_essais_partie;   //nombre d'essais pour la partie en cours
extern int nb_couleurs_partie; //nombre de couleurs pour la partie en cours
extern int mode_chrono;        //0 = desactive / 1 = active
extern int temps_imparti;      //temps en secondes par tour

#define ROUGE "\033[31m"
#define VERT "\033[32m"
#define JAUNE "\033[33m"
#define BLEU "\033[34m"
#define NOIR "\033[90m"
#define MAGENTA "\033[35m"
#define RESET "\033[0m"


//générateur de code secret aléatoire sans répétition
void generer_code(char code[]);

//affichage de l'historique des essais et des reponses associées
void afficher_historique(char essais[][TAILLE_CODE], int reponse[][2], int nb_essais);

//lit la proposition du joueur depuis l'entrée clavier
//retourne 1 si valide, 0 si le temps est ecoule
int lire_proposition(char proposition[]);

//compare la proposition du joueur avec le code secret et calcule les bien/mal placés avec des pointeurs
void verifier_proposition(const char code[], const char proposition[], int *bien_places, int *mal_places);

//déclaration de la fonction de traduction de couleurs
const char* col(char c);

#endif