#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#include "mastermind_utilities.h"
#include "mastermind_storage.h"
#include "mastermind_advanced.h"


//affiche les règles du jeu
void afficher_regles() {
    printf("\n=-= REGLES DU MASTERMIND =-=\n");
    printf("Le codeur choisit un code secret de 4 couleurs.\n");
    printf("Parametres actuels : %d couleurs, %d tentatives max.\n", nb_couleurs_partie, nb_essais_partie);
    printf("reponse :\n");
    printf(" - Bien placé : bonne couleur à la bonne position\n");
    printf(" - Mal placé : bonne couleur mais mauvaise position\n\n");
}

//lance une partie de Mastermind
void jouer_partie(int charger) {   
    char code[TAILLE_CODE]; //code secret
    //on utilise MAX_ESSAIS_MEMOIRE pour la declaration du tableau (fixe)
    char essais[MAX_ESSAIS_MEMOIRE][TAILLE_CODE]; //tableau pour sauvegarder les propositions à chaque essai
    int reponse[MAX_ESSAIS_MEMOIRE][2]; //tableau pour sauvegarder les reponses obtenues à chaque essai
    int nb_essais = 0; //compteur d'essais

    
    if (charger == 1) {
        //charger = 1, le joueur veut CHARGER
        //si la fonction renvoie 0 (échec), on arrête tout et on retourne au menu
        if (charger_partie(code, essais, reponse, &nb_essais) == 0) {
            printf("Retour au menu principal.\n");
            return;
        }
        
        //si on est la c'est que le chargement a réussi
        printf("\n--- Partie reprise avec succes --- \n");
        afficher_historique(essais, reponse, nb_essais);
    } 
    else {
        //sinon Le joueur veut une nouvelle partie
        generer_code(code);
        nb_essais = 0; //on commence à 0
        printf("\nUne nouvelle partie commence !\n");
    }

//###################################
    //partie de test ou il donne le code avant ; a enlever pour le jeu de base
    printf("\tcode secret a ne pas donner (uniquement pour les tests) : ");
    for (int i = 0; i < TAILLE_CODE; i++) {
        printf("%s%c%s ", col(code[i]), code[i], RESET);
    }
    printf("\n");
//###################################


    //boucle principale du jeu : on utilise la variable de configuration nb_essais_partie
    while (nb_essais < nb_essais_partie) {
        char proposition[TAILLE_CODE]; //tableau de caractère pour enregistrer la proposition du joueur
        
        //lire_proposition renvoie maintenant le resultat du chrono
        int lecture_ok = lire_proposition(proposition); //lecture de la proposition

        // Si la première lettre est S, on sauvegarde et on quitte
        if (proposition[0] == 'S') {
            sauvegarder_partie(code, essais, reponse, nb_essais);
            return; // On retourne au menu
        }

        int bien_places = 0;
        int mal_places = 0;
        
        if (lecture_ok == 0) {
            //temps ecoule, on compte 0 points
            bien_places = 0;
            mal_places = 0;
        } else {
            verifier_proposition(code, proposition, &bien_places, &mal_places); //compare avec le code
        }

        //sauvegarde de l'essai et de la reponse
        strncpy(essais[nb_essais], proposition, TAILLE_CODE); //permet de sauvegarder proposition dans le tableau essais avec une taille max
        reponse[nb_essais][0] = bien_places; //sauveagrde le nb de bien placés pour cette proposition
        reponse[nb_essais][1] = mal_places; //sauvegarde le nb de mal placés pour cette proposition
        nb_essais++;

        afficher_historique(essais, reponse, nb_essais); //affiche les essais précédents

        //condition de victoire
        if (bien_places == TAILLE_CODE) {
            printf("Bravo ! Vous avez trouve le code secret !\n");
            return;
        }
    }

    //si le joueur n'a pas trouvé le code
    printf("Partie terminee ! Le code etait : ");
    for (int i = 0; i < TAILLE_CODE; i++) {
        printf("%s%c%s ", col(code[i]), code[i], RESET);
    }
    printf("\n");
    return;
}

//main et menu interactif
int main() {
    srand(time(NULL)); //initialise le générateur aléatoire pour ne pas avoir deux fois la même valeur aléatoire (réinitialise la seed)

    int choix;
    do {
        //affichage du menu principal
        printf("\n--- MENU PRINCIPAL ---\n\n");
        printf("1. Jouer une partie\n");
        printf("2. Charger une partie\n");
        printf("3. Afficher les regles\n");
        printf("4. Mode Avance -Configuration-\n");
        printf("5. Quitter\n");
        printf("Votre choix : ");
        
        choix = 0;

        //lecture sécurisée
        if (scanf("%d", &choix) != 1) {
            //si l'utilisateur a tapé une lettre (ex: 'S'), scanf renvoie 0.
            //il faut alors vider le buffer pour "manger" cette lettre.
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
        }

        //choix
        switch(choix) {
            case 1:
                jouer_partie(0); // 0 = Nouvelle partie
                break;
            case 2:
                jouer_partie(1); // 1 = Charger partie
                break;
            case 3:
                afficher_regles();
                break;
            case 4:
                menu_avance();
                break;
            case 5:
                printf("A bientot !\n");
                break;
            default:
                printf("Choix invalide.\n");
        }
    } while (choix != 5); //boucle jusqu'à ce que l'utilisateur quitte

    return 0;
}