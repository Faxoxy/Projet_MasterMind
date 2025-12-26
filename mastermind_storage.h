#ifndef MASTERMIND_STORAGE_H
#define MASTERMIND_STORAGE_H

#include "mastermind_utilities.h"

//sauvegarde l'etat actuel dans un fichier
void sauvegarder_partie(const char code[], char essais[][TAILLE_CODE], int reponse[][2], int nb_essais);

//charge une partie (renvoie 1 si succes, 0 si echec)
int charger_partie(char code[], char essais[][TAILLE_CODE], int reponse[][2], int *nb_essais);

#endif