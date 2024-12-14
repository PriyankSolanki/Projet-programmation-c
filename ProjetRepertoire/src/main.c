#include "../include/repertoire.h"
#include <stdio.h>

int main() {
    int fonctionnalite;
    node_t *repertoire = NULL;

    printf("Bienvenue a toi !");
    while (true) {
        printf("\nQue voulez-vous faire ?");
        printf("\n\t1. Ajouter une personne");
        printf("\n\t2. Afficher le repertoire");
        printf("\n\t3. Rechercher une personne");
        printf("\n\t4. Supprimer une personne");
        printf("\n\t5. Quitter\n");
        printf("\nEntrez votre choix : ");

        if (scanf("%d", &fonctionnalite) != 1 || fonctionnalite < 1 || fonctionnalite > 5) {
            printf("Choisissez un chiffre entre 1 et 5.\n");
            while (getchar() != '\n');
            continue;
        }

        if (fonctionnalite == 5) break;

        switch (fonctionnalite) {
            case 1:
                repertoire = ajouter_personne(repertoire);
            break;
            case 2:
                afficher_repertoire(repertoire);
            break;
            case 3:
                rechercher_personne(repertoire);
            break;
            case 4:
                repertoire = supprimer_personne(repertoire);
            break;
        }
    }

    printf("\nMerci de votre visite !\n");
    return 0;
}
