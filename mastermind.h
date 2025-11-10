#ifndef MASTERMIND_H
#define MASTERMIND_H

// Constantes du jeu
#define NB_ESSAIS_MAX 10      // Nombre maximum d'essais autorisés
#define TAILLE_CODE 4         // Longueur du code secret
#define NB_COULEURS 6         // Nombre de couleurs disponibles

// Prototypes des fonctions utilisées dans mastermind.c

// Génère un code secret aléatoire sans répétition
void generer_code(char code[]);

// Affiche l'historique des essais et les feedbacks associés
void afficher_historique(char essais[][TAILLE_CODE], int feedback[][2], int nb_essais);

// Lit une proposition du joueur depuis l'entrée clavier
void lire_proposition(char proposition[]);

// Compare la proposition du joueur avec le code secret et calcule les bien/mal placés
void comparer_codes(const char code[], const char proposition[], int *bien_places, int *mal_places);

#endif

