#include "Jeu_classique.h"

void lancer_jeu_classique(void) {
    printf("=== Mode classique du Mastermind ===\n");
    
    int combinaison[4] = {1, 2, 3, 4}; //ajouter un random
    int essai[4] = {1, 3, 2, 4};    //c'est a l'utilisateur de remplir ici avec un scanf mais en attendant c'est le jeu qui joue tout seul

    int score = verifier_combinaison(essai, combinaison);
    printf("Résultat : %d bien placés.\n", score);
}

int verifier_combinaison(const int proposition[], const int combinaison_secrete[]) { //pour l'instant que position parce que pour vérifier la présence ça va être très compliqué (pointeurs surement)
    int bien_places = 0;
    for (int i = 0; i < 4; i++) {
        if (proposition[i] == combinaison_secrete[i])
            bien_places++;
    }
    return bien_places;
}