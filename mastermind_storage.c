#include <stdio.h>
#include <stdlib.h>
#include "mastermind_storage.h"

void sauvegarder_partie(const char code[], char essais[][TAILLE_CODE], int reponse[][2], int nb_essais) {
    char nom_fichier[100];
    printf("Nom du fichier de sauvegarde (ex: save.txt) : ");
    scanf("%s", nom_fichier);
    
    FILE *fichier = fopen(nom_fichier, "w");
    if (fichier == NULL) {
        printf("Erreur : Impossible de créer le fichier.\n");
        return;
    }

    //0_on écrit les 4 variables qui définissent les règles de la partie (le plus important) [nouveauté avec le mode avancé]
    fprintf(fichier, "%d %d %d %d\n", nb_couleurs_partie, nb_essais_partie, mode_chrono, temps_imparti);
    
    //1_sauvegarde du Code Secret
    for(int i = 0; i < TAILLE_CODE; i++) {
        fprintf(fichier, "%c", code[i]); //modif saut de ligne******
    }
    fprintf(fichier, "\n");

    //2_sauvegarde du nombre d'essais pour reprendre au milieu de partie
    fprintf(fichier, "%d\n", nb_essais);
    
    //3_sauvegarde de l'historique
    for(int i = 0; i < nb_essais; i++) {
        for(int j=0; j<TAILLE_CODE; j++) fprintf(fichier, "%c", essais[i][j]);
        fprintf(fichier, " %d %d\n", reponse[i][0], reponse[i][1]);
    }
    
    fclose(fichier);
    printf("Partie sauvegardée avec succès dans %s\n", nom_fichier);
}

//dans mastermind_storage.c

int charger_partie(char code[], char essais[][TAILLE_CODE], int reponse[][2], int *nb_essais) {
    char nom_fichier[100];
    printf("Nom du fichier à charger : ");
    scanf("%s", nom_fichier);
    
    FILE *fichier = fopen(nom_fichier, "r");
    if (fichier == NULL) {
        printf("Erreur : Fichier introuvable.\n");
        return 0;
    }
    
    //on récupère les règles du jeu sauvegardées
    fscanf(fichier, "%d %d %d %d", &nb_couleurs_partie, &nb_essais_partie, &mode_chrono, &temps_imparti);

    //1_lecture directe dans le tableau 'code'
    for (int i = 0; i < TAILLE_CODE; i++) {
        fscanf(fichier, " %c", &code[i]); //l'espace avant %c est important
    }

    //2_lecture du nombre d'essais
    fscanf(fichier, "%d", nb_essais);
    
    //3_lecture de l'historique directement dans les tableaux
    for(int i=0; i < *nb_essais; i++) {
        //on lit l'essai
        for(int j=0; j<TAILLE_CODE; j++) {
            fscanf(fichier, " %c", &essais[i][j]);
        }
        //on lit les scores
        fscanf(fichier, "%d %d", &reponse[i][0], &reponse[i][1]);
    }
    
    fclose(fichier);
    printf("Partie chargée ! Reprise au tour %d.\n", *nb_essais + 1);
    return 1;
}