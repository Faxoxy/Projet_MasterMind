#ifndef MASTERMIND_H
#define MASTERMIND_H

//constantes du jeu
#define NB_ESSAIS_MAX 10    //nb maximum d'essais autorisés
#define TAILLE_CODE 4   //longueur du code secret
#define NB_COULEURS 6   //nb de couleurs disponibles


#define ROUGE     "\033[31m"
#define VERT   "\033[32m"
#define JAUNE  "\033[33m"
#define BLEU    "\033[34m"
#define NOIR  "\033[90m"
#define MAGENTA "\033[35m"
#define RESET   "\033[0m"


//générateur de code secret aléatoire sans répétition
void generer_code(char code[]);

//affichage de l'historique des essais et des reponses associées
void afficher_historique(char essais[][TAILLE_CODE], int reponse[][2], int nb_essais);

//lit la proposition du joueur depuis l'entrée clavier
void lire_proposition(char proposition[]);

//compare la proposition du joueur avec le code secret et calcule les bien/mal placés avec des pointeurs
void verifier_proposition(const char code[], const char proposition[], int *bien_places, int *mal_places);


const char* col(char c);

#endif