#include "../include/repertoire.h"
#include <stdio.h>

#define FICHIER_REPERTOIRE "repertoire.txt"

int main() {
    int fonctionnalite;
    node_t *repertoire = charger_repertoire(FICHIER_REPERTOIRE);

    printf("Bienvenue a toi !");
    while (true) {
        printf("\nGestion du repertoire :");
        printf("\n\t1. Ajouter une personne");
        printf("\n\t2. Afficher le repertoire");
        printf("\n\t3. Rechercher une personne");
        printf("\n\t4. Supprimer une personne");
        printf("\n\t5. Quitter\n");
        scanf("%d", &fonctionnalite);

        if (fonctionnalite == 5) break;

        switch (fonctionnalite) {
            case 1:
                repertoire = ajouter_personne(repertoire);
                sauvegarder_repertoire(repertoire, FICHIER_REPERTOIRE);
            break;
            case 2:
                charger_repertoire(FICHIER_REPERTOIRE);
                afficher_repertoire(repertoire);
            break;
            case 3:
                rechercher_personne(repertoire);
            break;
            case 4:
                repertoire = supprimer_personne(repertoire);
                sauvegarder_repertoire(repertoire, FICHIER_REPERTOIRE);
            break;
            default:
                printf("Option invalide.\n");
        }
    }

    printf("\nMerci de votre visite !\n");
    return 0;
}