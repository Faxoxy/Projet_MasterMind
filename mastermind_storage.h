#ifndef MASTERMIND_STORAGE_H
#define MASTERMIND_STORAGE_H

#include "mastermind_utilities.h"

//sauvegarde l'état actuel dans un fichier
void sauvegarder_partie(const char code[], char essais[][TAILLE_CODE], int reponse[][2], int nb_essais);

//charge une partie (renvoie 1 si succès, 0 si échec)
int charger_partie(char code[], char essais[][TAILLE_CODE], int reponse[][2], int *nb_essais);

#endif